//
// Created by inbarb123 on 11/15/18.
//

#include "Action.h"
#include "Table.h"

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
        if((restaurant.getNumOfTables()>tableId)&&(restaurant.getTable(tableId).open == true)) {
            std::string str = "Table does not exist or is already open";
            error(str);
        }
        else{
            int i=0;
            while (i < customers.size()) {
                restaurant.getTable(tableId).addCusomer(customersList[i]);
                i++;
            }
            restaurant.getTable(tableId).openTable();
            complete();
        }
    }

    std::string OpenTable::toString() const;


    Order::Order(int id):
        BaseAction(), tableId(id)
    {}

    void Order::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()>tableId)&&(restaurant.getTable(tableId).open == false)) {
            std::string str = "Table does not exist or is not open";
            error(str);
        }
        else {
            restaurant.getTable(tableId).order();
            complete();
            // to string??? - print order
        }
    }

    std::string Order::toString() const;


    MoveCustomer::MoveCustomer(int src, int dst, int customerId):
        BaseAction(), srcTable(src), dstTable(dst), id(customerId)
    {}

    void MoveCustomer::act(Restaurant &restaurant);

    std::string MoveCustomer::toString() const;


    Close::Close(int id):
        BaseAction(), tableId(id)
    {}

    void Close::act(Restaurant &restaurant){
        if((restaurant.getNumOfTables()>tableId)&&(restaurant.getTable(tableId).open == false)) {
            std::string str = "Table does not exist or is not open";
            error(str);
        }
        else{
            restaurant.getTable(tableId).getBill();                     //use bill amount???
            int i=0;
            while (i < restaurant.getTable(tableId).getCustomers().size()) {
                removeCustomer(restaurant.getTable(tableId).getCustomers()[i].getId());
                i++;
            }
            restaurant.getTable(tableId).closeTable();
            complete();
        }
    }

    std::string Close::toString() const;


    CloseAll::CloseAll():

    {}

    void CloseAll::act(Restaurant &restaurant){
        int i=0;
        while (i<restaurant.getNumOfTables())
        {
            if(restaurant.getTable(i).open == true)
            {
                Close(i).act(restaurant);                       //....?
            }
            //............close restaurant and exit

            complete();
        }
    }

    std::string CloseAll::toString() const;


    PrintMenu::PrintMenu():
        BaseAction()
    {}

    void PrintMenu::act(Restaurant &restaurant){
        std::vector<Dish>& menu= restaurant.getMenu();          //print menu

        complete();
    }

    std::string PrintMenu::toString() const;


    PrintTableStatus::PrintTableStatus(int id):
        BaseAction(), tableId(id)
    {}

    void PrintTableStatus::act(Restaurant &restaurant){
        if(restaurant.getTable(tableId).isOpen()==false)    //closed table
        {
                //print status
        }
        else                                                //opened table
        {
            std::vector<OrderPair>& orders= restaurant.getTable(tableId).getCustomers().getOrders();
                //print satatus, customers, orders
        }

        complete();
    }

    std::string PrintTableStatus::toString() const;


    PrintActionsLog::PrintActionsLog():
        BaseAction()
    {}

    void PrintActionsLog::act(Restaurant &restaurant){
        std::vector<BaseAction*>& log= restaurant.getActionsLog();
            //print log
    }
    std::string PrintActionsLog::toString() const;


    BackupRestaurant::BackupRestaurant():
        BaseAction()
    {}

    void BackupRestaurant::act(Restaurant &restaurant){
            //copy constructor
    }
    std::string BackupRestaurant::toString() const;


    RestoreResturant::RestoreResturant():
        BaseAction()
    {}

    void RestoreResturant::act(Restaurant &restaurant){
            // = constructor
    }
    std::string RestoreResturant::toString() const;


