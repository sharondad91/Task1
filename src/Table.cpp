//
// Created by sharon on 11/12/18.
//

#include "Table.h"
using namespace std;

Table::Table():
        capacity(), open(false), customersList(), orderList()
{}
Table::Table(int t_capacity) :
    capacity(t_capacity), open(false), customersList(), orderList()
{
}

Table::Table(const Table& otherTable):  //copy constructor
capacity(otherTable.capacity), open(otherTable.open), customersList(), orderList()
{
    for(int i=0;i<(int)otherTable.customersList.size();i++)
    {
        customersList.push_back(otherTable.customersList[i]->clone());
    }

    for(int i=0;i<(int)otherTable.orderList.size();i++)
    {
        orderList.push_back(otherTable.orderList[i]);
    }
}
Table::Table(Table&& otherTable): //move constructor
        capacity(otherTable.capacity), open(otherTable.open), customersList(), orderList()
{
    for (int i = 0; i < (int)otherTable.customersList.size(); i++) {
        customersList.push_back(otherTable.customersList[i]);
        otherTable.customersList[i] = nullptr;
    }
    for (int i = 0; i < (int)otherTable.orderList.size(); i++) {
        orderList.push_back(otherTable.orderList[i]);
    }
}
Table& Table::operator=(const Table& otherTable){    //copy=

    if(this==&otherTable)
        return *this;
    this->capacity=otherTable.capacity;
    this->open=otherTable.open;

    for(int i=0;i<(int)otherTable.customersList.size();i++)
    {
        if(customersList[i]!= nullptr)
            delete customersList[i];
        customersList.push_back(otherTable.customersList[i]->clone());
    }
    for(int i=0;i<(int)otherTable.orderList.size();i++)
    {
        orderList.push_back(otherTable.orderList[i]);
    }

    return *this;
}

Table& Table::operator=(Table&& otherTable) {  //move=

    if (this != &otherTable) {
        this->capacity = otherTable.capacity;
        this->open = otherTable.open;

        for (int i = 0; i < (int)otherTable.customersList.size(); i++) {
            if (customersList[i] != nullptr)
                delete customersList[i];
            customersList.push_back(otherTable.customersList[i]);
            otherTable.customersList[i]= nullptr;
        }
        for (int i = 0; i < (int)otherTable.orderList.size(); i++) {
            orderList.push_back(otherTable.orderList[i]);
        }
    }
    return *this;
}
Table::~Table() {  //destructor
    for (int i = 0; i < (int)customersList.size(); i++) {
        if(customersList[i]!= nullptr)
        {
            delete customersList[i];
            customersList[i]= nullptr;
        }
    }
}


int Table::getCapacity() const{
    return capacity;
}

void Table::addCustomer(Customer* customer){
    customersList.push_back(customer);
}

void Table::removeCustomer(int id){
    int index=0;
    for(int i=0;i<(int)customersList.size();i++)
    {
        if(customersList[i]->getId()==id)
            index=i;
    }
    delete getCustomer(id);
    customersList.erase(customersList.begin()+index);

}

void Table::moveOrders(Table* srcTable, int customerId){
    vector<OrderPair> newOrderlist;
    for(int i=0;i<(int)srcTable->getOrders().size();i++){
        if((srcTable->getOrders())[i].first==customerId)
            orderList.push_back((srcTable->getOrders())[i]);
        else
            newOrderlist.push_back((srcTable->getOrders())[i]);
    }
    srcTable->setOrderList(newOrderlist);
}

void Table::setOrderList(vector<OrderPair> orderVec){
    orderList.clear();
    for(int i=0;i<(int)orderVec.size();i++){
        orderList.push_back(orderVec[i]);
    }
}

Customer* Table::getCustomer(int id){
    for(int i=0;i<(int)customersList.size();i++)
    {
        if(customersList[i]->getId()==id)
            return customersList[i];
    }
    return nullptr;
}

std::vector<Customer*>& Table::getCustomers(){
    return customersList;
}

std::vector<OrderPair>& Table::getOrders(){
    return orderList;
}

void Table::order(const std::vector<Dish> &menu){
    vector<int> orderlistid;
    for(int i=0;i<(int)customersList.size();i++)
    {
        orderlistid= customersList[i]->order(menu);                                  //right type of order?
        if(orderlistid[0]!=-1)                  //customer ordered
        {
            for(int j=0;j<(int)orderlistid.size();j++)
            {
                //Dish * dish2 = new Dish(menu[orderlistid[j]]);
                Dish dish2 = Dish(menu[orderlistid[j]]);
                //OrderPair* tmpOrder= new OrderPair(customersList[i]->getId(),dish2);
                OrderPair tmpOrder= OrderPair(customersList[i]->getId(),dish2);
                orderList.push_back(tmpOrder);

                cout<<getCustomer(tmpOrder.first)->getName()<<" ordered "<<tmpOrder.second.getName()<<endl;
            }
        }

    }

}

void Table::openTable(){
    open = true;
}

void Table::closeTable(){
    orderList.clear();
    for(int i=0;i<(int)customersList.size();i++)
    {
        removeCustomer(customersList[i]->getId());
    }
    open= false;
}

int Table::getBill(){
    int acc=0;
    for(int i=0;i<(int)orderList.size();i++)
    {
        acc=acc+orderList[i].second.getPrice();
    }
    return acc;
}

bool Table::isOpen(){
    return open;
}


