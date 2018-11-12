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

                    menu.push_back(Dish(idDish,dishName,stoi(dishPrice),dishType));                                 //?
                    idDish++;
                }
            }
        }

    }

void Restaurant::start() { open=true;}

int Restaurant::getNumOfTables() const {return tables.size();}

Table* Restaurant::getTable(int ind){
    return tables[ind];
}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const; // Return a reference to the history of actions

std::vector<Dish>& Restaurant::getMenu(){ return menu; }