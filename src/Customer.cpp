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
    std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu){
        std::vector<int> vec;
        vec=vegOrder(menu);
        return vec;
    }
    std::string VegetarianCustomer::toString() const;


    CheapCustomer::CheapCustomer(std::string name, int id):
            Customer(name,id), first(false)
    {}
    std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu){
        std::vector<int> vec;
        if (first==false)
        {
            vec.push_back(FindCheapDish(menu));
        }
        first=true;
        return vec;
    }
    std::string CheapCustomer::toString() const;


    SpicyCustomer::SpicyCustomer(std::string name, int id):
            Customer(name,id), first(false)
    {}
    std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu){
        std::vector<int> vec;
        if (first==false)
        {
            vec.push_back(FindExpansiveSpicy(menu));
        }
        else
        {
            vec.push_back(FindCheapestBvg(menu));
        }
        first=true;
        return vec;
    }
    std::string SpicyCustomer::toString() const;


    AlchoholicCustomer::AlchoholicCustomer(std::string name, int id):
            Customer(name,id), lastID(-1)
    {}
    std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu){
        std::vector<int> vec;
        if(lastID==FindExpansiveAlc(menu))
            vec.push_back(-1);
        else
        {
            vec.push_back(FindCheapestAlc(menu,lastID));
            lastID=vec[0];
        }
        return vec;

    }
    std::string AlchoholicCustomer::toString() const;



    int FindCheapDish(const std::vector<Dish> &menu){
        int i=0;
        int minimumInd=0;
        while(i< menu.size())
        {
            if (menu[i].getPrice()<menu[minimumInd].getPrice())
                minimumInd=i;
            i++;
        }
        return minimumInd;
    }

int FindExpansiveSpicy(const std::vector<Dish> &menu){
    int i=0;
    int maximumInd=0;
    while(i< menu.size())
    {
        if (menu[i].getType()==SPC && (menu[i].getPrice()>menu[maximumInd].getPrice()))
            maximumInd=i;
        i++;
    }
    if(menu[maximumInd].getType()==SPC)
        return maximumInd;
    return -1;
    }

int FindCheapestBvg(const std::vector<Dish> &menu){
    int i=0;
    int minimumInd=0;
    while(i< menu.size())
    {
        if (menu[i].getType()==BVG && (menu[i].getPrice()<menu[minimumInd].getPrice()))
            minimumInd=i;
        i++;
    }
    if(menu[minimumInd].getType()==BVG)
        return minimumInd;
    return -1;
    }

std::vector<int> vegOrder(const std::vector<Dish> &menu){
    int i=0;
    int vegDish=0;
    std::vector<int> ret;
    while(i< menu.size())
    {
        if (menu[i].getType()==VEG)
            vegDish=i;
        i++;
    }
    if(menu[vegDish].getType()==VEG)
        ret[0]=menu[vegDish].getId();
    else
        ret[0]=-1;

    i=0;
    int bevExp=0;
    while(i< menu.size())
    {
        if (menu[i].getType()==BVG && (menu[i].getPrice()>menu[bevExp].getPrice()))
            bevExp=i;
        i++;
    }
    if(menu[bevExp].getType()==BVG)
        ret[1]=menu[bevExp].getId();
    else
        ret[1]=-1;

    return ret;
}

//TODO: double check
int FindCheapestAlc(const std::vector<Dish> &menu, int id){
    int i=0;
    bool found=false;
    int minimumInd=-1;
    int maxMinimum= INTMAX_MAX;
    int currentMinPrice=-1;
    if (id<0)
        i= menu.size();
    else
        currentMinPrice= menu[id].getPrice();
    while(i< menu.size())
    {
        if (menu[i].getType()==ALC && (menu[i].getPrice()==currentMinPrice) && !found) {
            minimumInd = i;
            found = true;
        }
        i++;
    }
    i=0;
    while(!found && i< menu.size()) {
        if (menu[i].getType() == ALC && (menu[i].getPrice() > currentMinPrice) && (menu[i].getPrice() < maxMinimum) &&
            !found) {
            maxMinimum = menu[i].getPrice();
            minimumInd = i;
        }
        i++;
    }
    return minimumInd;

}

int FindExpansiveAlc(const std::vector<Dish> &menu){
    int i=0;
    int maximumInd=0;
    while(i< menu.size())
    {
        if (menu[i].getType()==ALC && (menu[i].getPrice()>menu[maximumInd].getPrice()))
            maximumInd=i;
        i++;
    }
    if(menu[maximumInd].getType()==ALC)
        return maximumInd;
    return -1;
}