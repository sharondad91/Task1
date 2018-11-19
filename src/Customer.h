#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Dish.h"

class Customer{
public:
    Customer();
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Dish> &menu)=0;
    virtual std::string toString() const = 0;
    virtual Customer* clone() =0;
    std::string getName() const;
    int getId() const;

//    Customer(const Customer& otherCustomer);  //copy constructor
//    Customer(Customer&& otherCustomer); //move constructor
//    //Customer& operator=(const Customer&& otherCustomer);    //copy=
//    //Customer& operator=(Customer&& otherCustomer);  //move=
//    ~Customer();  //destructor

private:
    const std::string name;
    const int id;
};


class VegetarianCustomer : public Customer {
public:
    VegetarianCustomer();
	VegetarianCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* clone();

//    VegetarianCustomer(const VegetarianCustomer& otherCustomer);  //copy constructor
//    VegetarianCustomer(VegetarianCustomer&& otherCustomer); //move constructor
//    ~VegetarianCustomer();  //destructor

private:

};


class CheapCustomer : public Customer {
public:
    CheapCustomer();
	CheapCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* clone();

//    CheapCustomer(const CheapCustomer& otherCustomer);  //copy constructor
//    CheapCustomer(CheapCustomer&& otherCustomer); //move constructor
//    ~CheapCustomer();  //destructor

private:
	bool first;
};


class SpicyCustomer : public Customer {
public:
    SpicyCustomer();
	SpicyCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* clone();

//    SpicyCustomer(const SpicyCustomer& otherCustomer);  //copy constructor
//    SpicyCustomer(SpicyCustomer&& otherCustomer); //move constructor
//    ~SpicyCustomer();  //destructor

private:
	bool first;
};


class AlchoholicCustomer : public Customer {
public:
    AlchoholicCustomer();
	AlchoholicCustomer(std::string name, int id);
    std::vector<int> order(const std::vector<Dish> &menu);
    std::string toString() const;
    Customer* clone();

//    AlchoholicCustomer(const AlchoholicCustomer& otherCustomer);  //copy constructor
//    AlchoholicCustomer(AlchoholicCustomer&& otherCustomer); //move constructor
//    ~AlchoholicCustomer();  //destructor

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