//
// Created by sharon on 11/12/18.
//

#include "Restaurant.h"
#include <fstream>
using namespace std;

Restaurant::Restaurant():
    open (false),tables (),menu (),actionsLog ()
{}

Restaurant::Restaurant(const std::string &configFilePath):

    open (false),
    tables (),
    menu (),
    actionsLog ()

    {

        ifstream file(configFilePath);
        string line;
        bool first = false;
        int idDish=0;
        DishType dishType;
        int tablesNum;
        while(getline(file,line)) {
            if (isdigit(line[0]) || isalpha(line[0]))    //if number or letter
            {
                if (isdigit(line[0])) {
                    if (!first) {
                        first = true;
                        tablesNum = stoi(line);
                    }
                    else {
                        string token;
                        int start = 0;
                        int end = 0;
                        while (end != line.length()) {
                            while (line[end] != ',' & (end != line.length() - 1))
                                end++;
                            token = line.substr(start, end-start);
                            end++;
                            start = end;
                            tables.push_back(new Table(stoi(token)));
                        }
                    }

                }
                else                                    //menu
                {
                    int i=0;
                    while (line[i] != ',')
                        i++;
                    string dishName = line.substr(0, i);
                    string dishstr = line.substr(i+1, 3);
                    string dishPrice = line.substr(i+5,line.length()-(i+5));

                    if (dishstr=="VEG")
                        dishType = VEG;
                    if (dishstr=="SPC")
                        dishType = SPC;
                    if (dishstr=="BVG")
                        dishType = BVG,;
                    else
                        dishType = ALC;

                    menu.push_back(Dish(idDish,dishName,stoi(dishPrice),dishType));
                    idDish++;
                }
            }
        }

    }

void Restaurant::start() {

    open=true;
    cout << "Restaurant is now open!";

    int customer_index=0;

    string line;
    while(getline(cin,line)) {
        int i=0;
        while (line[i] != ' ')
            i++;
        string action = line.substr(0, i);                  //string of action

        //open table(with type-customers vector). customer gets id by entering order
        if (action=="open")
        {
            vector<Customer *> customers_input;
            int j=i+1;
            while (line[j] != ' ')
                j++;
            string table_id = line.substr(i+1, j);

            j++;
            i=j;

            while (j<line.size())
            {
                while(line[j] != ',')
                    j++;
                string customer_name = line.substr(i, j);
                if(line[j+1] == 's' || line[j+1] == 'S')
                    customers_input.push_back(new SpicyCustomer(customer_name, customer_index));
                if(line[j+1] == 'v' || line[j+1] == 'V')
                    customers_input.push_back(new VegetarianCustomer(customer_name, customer_index));
                if(line[j+1] == 'c' || line[j+1] == 'C')
                    customers_input.push_back(new CheapCustomer(customer_name, customer_index));
                else
                    customers_input.push_back(new AlchoholicCustomer(customer_name, customer_index));
                j=j+5;
                i=j;
            }
            OpenTable(stoi(table_id), customers_input).act(*this);
        }

        //order - make sure order printed
        if (action=="order")
        {
            int j=i+1;
            while (line[j] != ' ')
                j++;
            string table_id = line.substr(i+1, j);
            OpenTable(stoi(table_id), customers_input).act(*this);
        }
        if(action=="move")
        {

        }
        if(action=="close")
        {

        }
        //close all - quit loop   +
        //BaseAction.complete();
        if (action=="closeall")
        {

        }
        if (action=="menu")
        {

        }
        if (action=="status")
        {

        }
        if(action=="log")
        {

        }
        if(action=="backup")
        {

        }
        if(action=="restore")
        {

        }
        //BaseAction* action= new BaseAction();

    }
}

int Restaurant::getNumOfTables() const {return tables.size();}

Table* Restaurant::getTable(int ind){
    return tables[ind];
}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const; // Return a reference to the history of actions

std::vector<Dish>& Restaurant::getMenu(){ return menu; }