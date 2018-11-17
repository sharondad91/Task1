//
// Created by inbarb123 on 11/15/18.
//

#include "Action.h"
#include "Table.h"
#include "Restaurant.h"

using namespace std;

    BaseAction::BaseAction():
    errorMsg(""), status(PENDING)
{}
    ActionStatus BaseAction::getStatus() const{
    return status;
}
    void BaseAction::complete(){
    status=COMPLETED;
}
    void BaseAction::error(std::string errorMsg){
    status=ERROR;
    this->errorMsg=errorMsg;
}
    std::string BaseAction::getErrorMsg() const{
        return errorMsg;
}


    OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):
    BaseAction(), tableId(id), customers(customersList)
    {}

    void OpenTable::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()>tableId)&&(restaurant.getTable(tableId)->isOpen() == true)) {
            std::string str = "Table does not exist or is already open";
            error(str);
        }
        else{
            restaurant.getTable(tableId)->openTable();                              //.............?
            int i=0;
            while (i < customers.size()) {
                restaurant.getTable(tableId)->addCustomer(customers[i]);
                i++;
            }
            restaurant.getTable(tableId)->openTable();
            complete();
        }
    }

    std::string OpenTable::toString() const{
        cout<<"open "<<tableId<<" ";
        for (int i=0;i<customers.size();i++)
        {
            cout<<customers[i]->getName()<<","<<customers[i]->toString()<<" ";
        }
        switch(getStatus()) {
            case COMPLETED: cout << "Completed"<<endl;
                break;
            case ERROR: cout << "Error: "<<getErrorMsg()<<endl;
                break;
        }

    }


    Order::Order(int id):
        BaseAction(), tableId(id)
    {}

    void Order::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()>tableId)&&(restaurant.getTable(tableId)->isOpen() == false)) {
            std::string str = "Table does not exist or is not open";
            error(str);
        }
        else {
            restaurant.getTable(tableId)->order(restaurant.getMenu());

            vector<OrderPair>& orders= restaurant.getTable(tableId)->getOrders();
            int i=0;
            while(i<orders.size())
            {
                int customer_id= orders[i].first;
                string customer_name= restaurant.getTable(tableId)->getCustomer(customer_id)->getName();
                cout<<customer_name<<" ordered "<<orders[i].second.getName()<<endl;
                i++;
            }

            complete();
        }
    }

    std::string Order::toString() const{
        cout<<"order "<<tableId<<" ";

        switch(getStatus()) {
            case COMPLETED: cout << "Completed"<<endl;
                break;
            case ERROR: cout << "Error: "<<getErrorMsg()<<endl;
                break;
        }
    }


    MoveCustomer::MoveCustomer(int src, int dst, int customerId):
        BaseAction(), srcTable(src), dstTable(dst), id(customerId)
    {}
            //move bill with customer
    void MoveCustomer::act(Restaurant &restaurant){
        if(restaurant.getTable(dstTable)->getCapacity()>restaurant.getTable(dstTable)->getCustomers().size())
        {
            Customer * customer2= restaurant.getTable(srcTable)->getCustomer(id)->clone();
            
            //take all his orders to new vector
            //push new vector to dest table

            restaurant.getTable(dstTable)->addCustomer(customer2);
            restaurant.getTable(srcTable)->removeCustomer(id);



            complete();
        }
        else {
            std::string str = "Cannot move customer";
            error(str);
        }


    }

    std::string MoveCustomer::toString() const{
        cout<<"move "<<srcTable<<" "<<dstTable<<" "<<id<<" ";
        switch(getStatus()) {
            case COMPLETED: cout << "Completed"<<endl;
                break;
            case ERROR: cout << "Error: "<<getErrorMsg()<<endl;
                break;
        }
    }



    Close::Close(int id):
        BaseAction(), tableId(id)
    {}

    void Close::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()>tableId) || (restaurant.getTable(tableId)->isOpen() == false) ) {
            std::string str = "Table does not exist or is not open";
            error(str);
        }
        else{
            int curr_bill= restaurant.getTable(tableId)->getBill();                     //use bill amount???
            restaurant.getTable(tableId)->closeTable();
            cout<<"Table "<<tableId<<" was closed. Bill "<<curr_bill<<"NIS"<<endl;
            complete();
        }
    }

    std::string Close::toString() const{
        cout<<"close "<<tableId<<" ";

        switch(getStatus()) {
            case COMPLETED: cout << "Completed"<<endl;
                break;
            case ERROR: cout << "Error: "<<getErrorMsg()<<endl;
                break;
        }
    }


    CloseAll::CloseAll():

    {}

    void CloseAll::act(Restaurant &restaurant){
        int i=0;
        while (i<restaurant.getNumOfTables())
        {
            if(restaurant.getTable(i)->isOpen() == true)
            {
                Close(i).act(restaurant);                       //....?
            }
            //............close restaurant and exit
        }
        complete();
    }

    std::string CloseAll::toString() const;


    PrintMenu::PrintMenu():
        BaseAction()
    {}

    void PrintMenu::act(Restaurant &restaurant){
        std::vector<Dish>& menu= restaurant.getMenu();          //print menu
        int i=0;
        while(i<menu.size())
        {
            cout<<menu[i].getName()<<" "<<menu[i].getType()<<" "<<menu[i].getPrice()<<"NIS"<<endl;
            i++;
        }
        complete();
    }

    std::string PrintMenu::toString() const{
        cout<<"menu Completed"<<endl;
    }


    PrintTableStatus::PrintTableStatus(int id):
        BaseAction(), tableId(id)
    {}

    void PrintTableStatus::act(Restaurant &restaurant){
        if(restaurant.getTable(tableId)->isOpen()==false)    //closed table
        {
            cout<<"Table "<<tableId<<" status: closed"<<endl;
        }
        else                                                //opened table
        {
            std::vector<OrderPair>& orders= restaurant.getTable(tableId)->getOrders();
                //print status, customers, orders
            cout<<"Table "<<tableId<<" status: open"<<endl;
            cout<<"Customers:"<<endl;
            for(int i=0;i<restaurant.getTable(tableId)->getCustomers().size();i++)
            {
                cout<<restaurant.getTable(tableId)->getCustomer(i)->getId()<<" "<<restaurant.getTable(tableId)->getCustomer(i)->getName()<<endl;
            }
            cout<<"Orders:"<<endl;
            for(int i=0;i<restaurant.getTable(tableId)->getOrders().size();i++)
            {
                cout<<restaurant.getTable(tableId)->getOrders()[i].second.getName()<<" "<<restaurant.getTable(tableId)->getOrders()[i].second.getPrice()<<"NIS "<<restaurant.getTable(tableId)->getOrders()[i].first<<endl;
            }
            cout<<"Current Bill: "<<restaurant.getTable(tableId)->getBill()<<"NIS"<<endl;
        }

        complete();
    }

    std::string PrintTableStatus::toString() const{
        cout<<"status "<<tableId<<" Completed"<<endl;

    }


    PrintActionsLog::PrintActionsLog():
        BaseAction()
    {}

    void PrintActionsLog::act(Restaurant &restaurant){
        for(int i=0;i<restaurant.getActionsLog().size();i++)
        {
            (restaurant.getActionsLog())[i]->toString();
        }
    }
    std::string PrintActionsLog::toString() const{
        cout<<"log Completed"<<endl;
    }


    BackupRestaurant::BackupRestaurant():
        BaseAction()
    {}

    void BackupRestaurant::act(Restaurant &restaurant){
            //copy constructor
    }
    std::string BackupRestaurant::toString() const{

        cout<<"backup Completed"<<endl;
    }


    RestoreResturant::RestoreResturant():
        BaseAction()
    {}

    void RestoreResturant::act(Restaurant &restaurant){
            // = constructor



    }
    std::string RestoreResturant::toString() const{
        cout<<"restore ";
        switch(getStatus()) {
            case COMPLETED: cout << "Completed"<<endl;
                break;
            case ERROR: cout << "Error: "<<getErrorMsg()<<endl;
                break;
        }
    }


