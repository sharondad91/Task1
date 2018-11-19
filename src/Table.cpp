//
// Created by sharon on 11/12/18.
//

#include "Table.h"
using namespace std;


Table::Table(int t_capacity) :
    capacity(t_capacity), open(false), customersList(), orderList()
{
}

int Table::getCapacity() const{
    return capacity;
}

void Table::addCustomer(Customer* customer){
    customersList.push_back(customer);
}

void Table::removeCustomer(int id){
    delete getCustomer(id);
}

void Table::moveOrders(Table* srcTable, int customerId){
    vector<OrderPair> newOrderlist;
    for(int i=0;i<srcTable->getOrders().size();i++){
        if((srcTable->getOrders())[i].first==customerId)
            orderList.push_back((srcTable->getOrders())[i]);
        else
            newOrderlist.push_back((srcTable->getOrders())[i]);
    }
    srcTable->setOrderList(newOrderlist);
}

void Table::setOrderList(vector<OrderPair> orderVec){
    orderList.clear();
    for(int i=0;i<orderVec.size();i++){
        orderList.push_back(orderVec[i]);
    }
}

Customer* Table::getCustomer(int id){
    for(int i=0;i<customersList.size();i++)
    {
        if(customersList[i]->getId()==id)
            return customersList[i];
    }
}

std::vector<Customer*>& Table::getCustomers(){
    return customersList;
}

std::vector<OrderPair>& Table::getOrders(){
    return orderList;
}

void Table::order(const std::vector<Dish> &menu){
    vector<int> orderlistid;
    for(int i=0;i<customersList.size();i++)
    {
        orderlistid= customersList[i]->order(menu);                                  //right type of order?
        if(orderlistid[0]!=-1)                  //customer ordered
        {
            for(int j=0;j<orderlistid.size();j++)
            {
                //Dish * dish2 = new Dish(menu[orderlistid[j]]);
                Dish dish2 = Dish(menu[orderlistid[j]]);
                //OrderPair* tmpOrder= new OrderPair(customersList[i]->getId(),dish2);
                OrderPair tmpOrder= OrderPair(customersList[i]->getId(),dish2);
                orderList.push_back(tmpOrder);
            }
        }

    }

}

void Table::openTable(){
    open = true;
}

void Table::closeTable(){
    orderList.clear();
    for(int i=0;i<customersList.size();i++)
    {
        removeCustomer(customersList[i]->getId());
    }
    open= false;
}

int Table::getBill(){
    int acc=0;
    for(int i=0;i<orderList.size();i++)
    {
        acc=acc+orderList[i].second.getPrice();
    }
    return acc;
}

bool Table::isOpen(){
    return open;
}


