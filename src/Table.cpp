//
// Created by sharon on 11/12/18.
//

#include "Table.h"


Table::Table(int t_capacity) :
    capacity(t_capacity)
{}

int Table::getCapacity() const{ return capacity;}

void Table::addCustomer(Customer* customer);

void Table::removeCustomer(int id);

Customer* Table::getCustomer(int id);

std::vector<Customer*>& Table::getCustomers();

std::vector<OrderPair>& Table::getOrders();

void Table::order(const std::vector<Dish> &menu);

void Table::openTable(){open = true;}

void Table::closeTable();

int Table::getBill();

bool Table::isOpen(){open;}



private:
int capacity;
bool open;
std::vector<Customer*> customersList;
std::vector<OrderPair> orderList; //A list of pairs for each order in a table - (customer_id, Dish)
};