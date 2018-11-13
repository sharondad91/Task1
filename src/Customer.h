#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;
};


class VegetarianCustomer : public Customer {
public:
	VegetarianCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
};


class CheapCustomer : public Customer {
public:
	CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
	bool first;
};


class SpicyCustomer : public Customer {
public:
	SpicyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
	bool first;
};


class AlchoholicCustomer : public Customer {
public:
	AlchoholicCustomer(std::string name, int id)
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
private:
	int lastID;
};

int FindCheapDish(const std::vector<Dish> &menu);
int FindExpansiveSpicy(const std::vector<Dish> &menu);
int FindCheapestBvg(const std::vector<Dish> &menu);
std::vector<int> vegOrder(const std::vector<Dish> &menu);
int FindCheapestAlc(const std::vector<Dish> &menu, int id);
int FindExpansiveAlc(const std::vector<Dish> &menu);

#endif