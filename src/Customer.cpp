//
// Created by inbarb123 on 11/13/18.
//

#include "Customer.h"


    Customer::Customer(std::string c_name, int c_id):
    name(c_name), id(c_id){}
    std::string Customer::getName() const
    {
        return name;
    }
    int Customer::getId() const
    {
        return id;
    }


    VegetarianCustomer::VegetarianCustomer(std::string name, int id):
            Customer(name,id)
    {}
    std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu);
    std::string VegetarianCustomer::toString() const;


    CheapCustomer::CheapCustomer(std::string name, int id):
            Customer(name,id)
    {}
    std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu);
    std::string CheapCustomer::toString() const;


    SpicyCustomer::SpicyCustomer(std::string name, int id):
            Customer(name,id)
    {}
    std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu);
    std::string SpicyCustomer::toString() const;


    AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):
            Customer(name,id)
    {}
    std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu);
    std::string AlchoholicCustomer::toString() const;


