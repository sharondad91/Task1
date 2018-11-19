//
// Created by inbarb123 on 11/13/18.
//

#include "Customer.h"


Customer::Customer() :
        name(), id() {}

Customer::Customer(std::string c_name, int c_id) :
        name(c_name), id(c_id) {}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

Customer::~Customer(){  //destructor
}

VegetarianCustomer::VegetarianCustomer() :
        Customer() {}

VegetarianCustomer::VegetarianCustomer(std::string name, int id) :
        Customer(name, id) {}

std::vector<int> VegetarianCustomer::order(const std::vector<Dish> &menu) {
    std::vector<int> vec;
    vec = vegOrder(menu);
    return vec;
}

std::string VegetarianCustomer::toString() const {
    return "veg";
}

Customer *VegetarianCustomer::clone() {
    return new VegetarianCustomer(*this);
}

VegetarianCustomer::~VegetarianCustomer(){
}

CheapCustomer::CheapCustomer() :
        Customer(), first(false) {}

CheapCustomer::CheapCustomer(std::string name, int id) :
        Customer(name, id), first(false) {}

std::vector<int> CheapCustomer::order(const std::vector<Dish> &menu) {
    std::vector<int> vec;
    if (first == false) {
        vec.push_back(FindCheapDish(menu));
        first = true;
    } else
        vec.push_back(-1);
    return vec;
}

std::string CheapCustomer::toString() const {
    return "chp";
}

Customer *CheapCustomer::clone() {
    return new CheapCustomer(*this);
}

CheapCustomer::~CheapCustomer(){
}

SpicyCustomer::SpicyCustomer() :
        Customer(), first(false) {}

SpicyCustomer::SpicyCustomer(std::string name, int id) :
        Customer(name, id), first(false) {}

std::vector<int> SpicyCustomer::order(const std::vector<Dish> &menu) {
    std::vector<int> vec;
    if (first == false) {
        vec.push_back(FindExpansiveSpicy(menu));
        first = true;
    } else {
        vec.push_back(FindCheapestBvg(menu));
    }
    return vec;
}

std::string SpicyCustomer::toString() const {
    return "spc";
}

Customer *SpicyCustomer::clone() {
    return new SpicyCustomer(*this);
}

SpicyCustomer::~SpicyCustomer(){
}

AlchoholicCustomer::AlchoholicCustomer() :
        Customer(), lastID(-1) {}

AlchoholicCustomer::AlchoholicCustomer(std::string name, int id) :
        Customer(name, id), lastID(-1) {}


std::vector<int> AlchoholicCustomer::order(const std::vector<Dish> &menu) {
    std::vector<int> vec;
    if (lastID == FindExpansiveAlc(menu))                  //if finished
        vec.push_back(-1);
    else {
        int tmp = FindCheapestAlc(menu, lastID);
        lastID = tmp;
        vec.push_back(lastID);
    }
    return vec;

}

AlchoholicCustomer::~AlchoholicCustomer(){
}

std::string AlchoholicCustomer::toString() const {
    return "alc";
}

Customer *AlchoholicCustomer::clone() {
    return new AlchoholicCustomer(*this);
}


int FindCheapDish(const std::vector<Dish> &menu) {
    int i = 1;
    int minimumInd = 0;
    while (i < (int)menu.size()) {
        if (menu[i].getPrice() < menu[minimumInd].getPrice())
            minimumInd = i;
        i++;
    }
    return minimumInd;
}

int FindExpansiveSpicy(const std::vector<Dish> &menu) {
    int i = 0;
    int maximumInd = -1;
    bool found = false;
    while (i < (int)menu.size()) {
        if (!found)
            if (menu[i].getType() == SPC) {
                maximumInd = i;
                found = true;
            } else if (menu[i].getType() == SPC && (menu[i].getPrice() > menu[maximumInd].getPrice()))
                maximumInd = i;
        i++;
    }
    return maximumInd;

}

int FindCheapestBvg(const std::vector<Dish> &menu) {
    int i = 0;
    int minimumInd = -1;
    bool found = false;
    while (i < (int)menu.size()) {
        if (!found)
            if (menu[i].getType() == BVG) {
                minimumInd = i;
                found = true;
            } else if (menu[i].getType() == BVG && (menu[i].getPrice() < menu[minimumInd].getPrice()))
                minimumInd = i;
        i++;
    }

    return minimumInd;

}

std::vector<int> vegOrder(const std::vector<Dish> &menu) {
    int i = 0;
    int vegDish = 0;
    std::vector<int> ret;
    while (i <(int) menu.size()) {
        if (menu[i].getType() == VEG)
            vegDish = i;
        i++;
    }
    if (menu[vegDish].getType() == VEG)
        ret.push_back(menu[vegDish].getId());
    else
        ret.push_back(-1);

    i = 0;
    int bevExp = -1;
    bool found = false;
    while (i < (int)menu.size()) {
        if (!found)
            if (menu[i].getType() == BVG) {
                bevExp = i;
                found = true;
            } else if (menu[i].getType() == BVG && (menu[i].getPrice() > menu[bevExp].getPrice()))
                bevExp = i;
        i++;
    }
    if (bevExp != -1)
        ret.push_back(menu[bevExp].getId());
    else {
        ret.pop_back();
        ret.push_back(-1);
    }

    return ret;
}

//TODO: double check
int FindCheapestAlc(const std::vector<Dish> &menu, int id) {
    int i = 0;
    bool found = false;
    int minimumInd = -1;
    int maxMinimum = INTMAX_MAX;
    int currentMinPrice = -1;
    if (id < 0)
        i = (int)menu.size();
    else {
        i = id + 1;
        currentMinPrice = menu[id].getPrice();
    }
    while (i < (int)menu.size()) {
        if (i > id && menu[i].getType() == ALC && (menu[i].getPrice() == currentMinPrice) && !found) {
            minimumInd = i;
            found = true;
        }
        i++;
    }
    i = 0;
    while (!found && i < (int)menu.size()) {
        if (menu[i].getType() == ALC && (menu[i].getPrice() > currentMinPrice) && (menu[i].getPrice() < maxMinimum)) {
            maxMinimum = menu[i].getPrice();
            minimumInd = i;
        }
        i++;
    }
    return minimumInd;

}

int FindExpansiveAlc(const std::vector<Dish> &menu) {                                //....?
    int i = (int)menu.size() - 1;
    int maximumInd = -1;
    bool found = false;
    while (i > -1) {
        if (!found)
            if (menu[i].getType() == ALC) {
                maximumInd = i;
                found = true;
            } else if (menu[i].getType() == ALC && (menu[i].getPrice() > menu[maximumInd].getPrice()))
                maximumInd = i;
        i--;
    }
    return maximumInd;
}