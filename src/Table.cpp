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
    vector<OrderPair> newOrderlist;

    //     create new vector without my orders

    for(int i=0;i<orderList.size();i++){
        if(orderList[i].first==id)
            orderList.erase(orderList.begin()+i);
    }



    delete getCustomer(id);
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
                Dish * dish2 = new Dish(menu[orderlistid[j]]);
                OrderPair* tmpOrder= new OrderPair(customersList[i]->getId(),*dish2);
                orderList.push_back(*tmpOrder);
            }
        }

    }

}

void Table::openTable(){
    open = true;
}

void Table::closeTable(){
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


