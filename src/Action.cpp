//
// Created by inbarb123 on 11/15/18.
//

#include "Action.h"
#include "Table.h"
#include "Restaurant.h"
extern Restaurant* backup;
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

BaseAction::~BaseAction(){  //destructor
}

OpenTable::~OpenTable() {  //destructor
    for (int i = 0; i < (int)customers.size(); i++) {
        if(customers[i]!= nullptr)
        {
            delete customers[i];
            customers[i]= nullptr;
        }
    }
}

BaseAction* OpenTable::clone(){
    return new OpenTable(*this);
    }

    OpenTable::OpenTable(int id, std::vector<Customer *> &customersList):
    BaseAction(), tableId(id), customers(customersList)
    {}

    void OpenTable::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()<=tableId)||(restaurant.getTable(tableId)->isOpen())) {
            std::string str = "Table does not exist or is already open";
            error(str);
        }
        else{
            restaurant.getTable(tableId)->openTable();
            int i=0;
            while (i < (int)customers.size()) {
                restaurant.getTable(tableId)->addCustomer(customers[i]->clone());
                i++;
            }
            restaurant.getTable(tableId)->openTable();
            complete();
        }
    }

    std::string OpenTable::toString() const{
        std::string str="open "+to_string(tableId)+" ";
        for (int i=0;i<(int)customers.size();i++)
        {
            str+=customers[i]->getName()+","+customers[i]->toString()+" ";
        }
        if(getStatus()==COMPLETED)
            str+="Completed";
        else if(getStatus()==ERROR)
            str+="Error: "+getErrorMsg();
        else if(getStatus()==PENDING)
            str+="Pending";

        return str;

    }
Order::~Order(){
    }

    BaseAction* Order::clone(){
        return new Order(*this);
    }

    Order::Order(int id):
        BaseAction(), tableId(id)
    {}

    void Order::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()<=tableId)||!(restaurant.getTable(tableId)->isOpen())) {
            std::string str = "Table does not exist or is not open";
            error(str);
        }
        else {
            restaurant.getTable(tableId)->order(restaurant.getMenu());

//            vector<OrderPair>& orders= restaurant.getTable(tableId)->getOrders();
//            int i=0;
//            while(i<(int)orders.size())
//            {
//                int customer_id= orders[i].first;
//                string customer_name= restaurant.getTable(tableId)->getCustomer(customer_id)->getName();
//                cout<<customer_name<<" ordered "<<orders[i].second.getName()<<endl;
//                i++;
//            }

            complete();
        }
    }

    std::string Order::toString() const{
        std::string str="order "+to_string(tableId)+" ";

        if(getStatus()==COMPLETED)
            str+="Completed";
        else if(getStatus()==ERROR)
            str+="Error: "+getErrorMsg();
        else if(getStatus()==PENDING)
            str+="Pending";

        return str;

    }

MoveCustomer::~MoveCustomer(){
}

    BaseAction* MoveCustomer::clone(){
        return new MoveCustomer(*this);
    }

    MoveCustomer::MoveCustomer(int src, int dst, int customerId):
        BaseAction(), srcTable(src), dstTable(dst), id(customerId)
    {}
            //move bill with customer
        void MoveCustomer::act(Restaurant &restaurant){
        bool exist= false;
        bool isLegal=true;

        if((restaurant.getNumOfTables()<=srcTable)||(restaurant.getNumOfTables()<=dstTable)||!(restaurant.getTable(srcTable)->isOpen())||!(restaurant.getTable(dstTable)->isOpen())) {
            isLegal=false;
        }
        if(isLegal && restaurant.getTable(dstTable)->getCapacity()==(int)restaurant.getTable(dstTable)->getCustomers().size())
        {
            isLegal=false;
        }
        for(int i=0;i<(int)restaurant.getTable(srcTable)->getCustomers().size() && isLegal ;i++) {
            if(restaurant.getTable(srcTable)->getCustomers()[i]->getId()==id)
                exist=true;
        }

        if(isLegal && exist)
        {
            Customer * customer2= restaurant.getTable(srcTable)->getCustomer(id)->clone();

            restaurant.getTable(dstTable)->moveOrders(restaurant.getTable(srcTable),id);
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
        std::string str="move "+to_string(srcTable)+" "+to_string(dstTable)+" "+to_string(id)+" ";

        if(getStatus()==COMPLETED)
            str+="Completed";
        else if(getStatus()==ERROR)
            str+="Error: "+getErrorMsg();
        else if(getStatus()==PENDING)
            str+="Pending";

        return str;
    }

Close::~Close(){
}

BaseAction* Close::clone(){
    return new Close(*this);
}

    Close::Close(int id):
        BaseAction(), tableId(id)
    {}

    void Close::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()<=tableId) || !(restaurant.getTable(tableId)->isOpen()) ) {
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
        std::string str="close "+to_string(tableId)+" ";

        if(getStatus()==COMPLETED)
            str+="Completed";
        else if(getStatus()==ERROR)
            str+="Error: "+getErrorMsg();
        else if(getStatus()==PENDING)
            str+="Pending";

        return str;
    }

CloseAll::~CloseAll(){
}

BaseAction* CloseAll::clone(){
    return new CloseAll(*this);
}

    CloseAll::CloseAll():
        BaseAction()
    {}

    void CloseAll::act(Restaurant &restaurant){
        int i=0;
        while (i<restaurant.getNumOfTables())
        {
            if(restaurant.getTable(i)->isOpen())
            {
                Close* action1= new Close(i);
                action1->act(restaurant);
                delete action1;
            }
            i++;
        }
        complete();
    }

    std::string CloseAll::toString() const{
        return "";
    }

PrintMenu::~PrintMenu(){
}

BaseAction* PrintMenu::clone(){
    return new PrintMenu(*this);
}

    PrintMenu::PrintMenu():
        BaseAction()
    {}

    void PrintMenu::act(Restaurant &restaurant){
        std::vector<Dish>& menu= restaurant.getMenu();          //print menu
        int i=0;
        while(i<(int)menu.size())
        {
            cout<<menu[i].getName()<<" "<<menu[i].getType()<<" "<<menu[i].getPrice()<<"NIS"<<endl;
            i++;
        }
        complete();
    }

    std::string PrintMenu::toString() const{
        return "menu Completed";
    }

PrintTableStatus::~PrintTableStatus(){
}

BaseAction* PrintTableStatus::clone(){
    return new PrintTableStatus(*this);
}

    PrintTableStatus::PrintTableStatus(int id):
        BaseAction(), tableId(id)
    {}

    void PrintTableStatus::act(Restaurant &restaurant){
        if(!restaurant.getTable(tableId)->isOpen())    //closed table
        {
            cout<<"Table "<<tableId<<" status: closed"<<endl;
        }
        else                                                //opened table
        {
            //std::vector<OrderPair>& orders= restaurant.getTable(tableId)->getOrders();
            cout<<"Table "<<tableId<<" status: open"<<endl;
            cout<<"Customers:"<<endl;
            for(int i=0;i<(int)restaurant.getTable(tableId)->getCustomers().size();i++)
            {
                cout<<restaurant.getTable(tableId)->getCustomers()[i]->getId()<<" "<<restaurant.getTable(tableId)->getCustomers()[i]->getName()<<endl;
            }
            cout<<"Orders:"<<endl;
            for(int i=0;i<(int)restaurant.getTable(tableId)->getOrders().size();i++)
            {
                cout<<restaurant.getTable(tableId)->getOrders()[i].second.getName()<<" "<<restaurant.getTable(tableId)->getOrders()[i].second.getPrice()<<"NIS "<<restaurant.getTable(tableId)->getOrders()[i].first<<endl;
            }
            cout<<"Current Bill: "<<restaurant.getTable(tableId)->getBill()<<"NIS"<<endl;
        }

        complete();
    }

    std::string PrintTableStatus::toString() const{
        return "status "+to_string(tableId)+" Completed";
    }

PrintActionsLog::~PrintActionsLog(){
}

BaseAction* PrintActionsLog::clone(){
    return new PrintActionsLog(*this);
}

    PrintActionsLog::PrintActionsLog():
        BaseAction()
    {}

    void PrintActionsLog::act(Restaurant &restaurant){
        for(int i=0;i<(int)restaurant.getActionsLog().size();i++)
        {
            cout<<(restaurant.getActionsLog())[i]->toString()<<endl;
        }
        complete();
    }
    std::string PrintActionsLog::toString() const{
        return "log Completed";
    }

BackupRestaurant::~BackupRestaurant(){
}

BaseAction* BackupRestaurant::clone(){
    return new BackupRestaurant(*this);
}

    BackupRestaurant::BackupRestaurant():
        BaseAction()
    {}

    void BackupRestaurant::act(Restaurant &restaurant){
        if(backup != nullptr)
            delete backup;
        backup = new Restaurant(restaurant);
        complete();
    }
    std::string BackupRestaurant::toString() const{

        return "backup Completed";
    }

RestoreResturant::~RestoreResturant(){
}

BaseAction* RestoreResturant::clone(){
    return new RestoreResturant(*this);
}

    RestoreResturant::RestoreResturant():
        BaseAction()
    {}

    void RestoreResturant::act(Restaurant &restaurant){
        if(backup== nullptr)
        {
            std::string str = "No backup available";
            error(str);
        }
        else{
            restaurant=*backup;
            complete();
        }
    }
    std::string RestoreResturant::toString() const{
        std::string str="restore ";
        if(getStatus()==COMPLETED)
            str+="Completed";
        else if(getStatus()==ERROR)
            str+="Error: "+getErrorMsg();
        else if(getStatus()==PENDING)
            str+="Pending";

        return str;
    }


