#ifndef TABLE_H_
#define TABLE_H_

#include <vector>
#include <iostream>
#include "Customer.h"
#include "Dish.h"

typedef std::pair<int, Dish> OrderPair;

class Table{
public:
    Table();
    Table(int t_capacity);

    Table(const Table& otherTable);  //copy constructor
    Table(Table&& otherTable); //move constructor
    Table& operator=(const Table& otherTable);    //copy=
    Table& operator=(Table&& otherTable);  //move=
    virtual ~Table();  //destructor

    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    void moveOrders(Table* srcTable, int customerId);
    void setOrderList(std::vector<OrderPair> orderVec);
    std::vector<OrderPair>& getOrders();
    void order(const std::vector<Dish> &menu);
    void openTable();
    void closeTable();
    int getBill();
    bool isOpen();
private:
    int capacity;
    bool open;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order in a table - (customer_id, Dish)
};


#endif