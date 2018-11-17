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
                                                    //actionslog init??

    }

void Restaurant::start() {

    open=true;
    cout << "Restaurant is now open!"<<endl;

    int customer_index=0;
    bool finito=false;
    string line;
    while(!finito && getline(cin,line)) {
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
            OpenTable* action1= new OpenTable(stoi(table_id), customers_input);
            action1->act(*this);
            actionsLog.push_back(action1);
        }

        //order - make sure order printed
        if (action=="order")
        {
            int j=i+1;
            while (j<line.size())
                j++;
            string table_id = line.substr(i+1, j);

            Order* action1= new Order(stoi(table_id));
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="move")
        {
            int j=i+1;
            i=j;
            while (line[j] != ' ')
                j++;
            string srctable = line.substr(i, j);
            j=j+1;
            i=j;
            while (line[j] != ' ')
                j++;
            string destable = line.substr(i, j);
            string idcustomer = line.substr(j+1, line.size());

            MoveCustomer* action1= new MoveCustomer(stoi(srctable),stoi(destable),stoi(idcustomer));
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="close")
        {
            int j=i+1;
            while (j<line.size())
                j++;
            string table_id = line.substr(i+1, j);

            Close* action1= new Close(stoi(table_id));
            action1->act(*this);
            actionsLog.push_back(action1);
        }

        if (action=="closeall")
        {
            CloseAll* action1= new CloseAll();
            action1->act(*this);
            actionsLog.push_back(action1);
            finito = true;
        }
        if (action=="menu")
        {
            PrintMenu* action1= new PrintMenu();
            action1->act(*this);
            actionsLog.push_back(action1);

        }
        if (action=="status")
        {
            int j=i+1;
            while (j<line.size())
                j++;
            string table_id = line.substr(i+1, j);

            PrintTableStatus* action1= new PrintTableStatus(stoi(table_id));
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="log")
        {

            PrintActionsLog* action1= new PrintActionsLog());
            action1->act(*this);
            actionsLog.push_back(action1);



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

int Restaurant::getNumOfTables() const {
    return tables.size();
}

Table* Restaurant::getTable(int ind){
    return tables[ind];
}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const; // Return a reference to the history of actions

std::vector<Dish>& Restaurant::getMenu(){
    return menu;
}