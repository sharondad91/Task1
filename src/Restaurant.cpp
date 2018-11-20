//
// Created by sharon on 11/12/18.
//

#include "Restaurant.h"
#include <fstream>
using namespace std;
extern Restaurant* backup;


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
        //ssint tablesNum;
        while(getline(file,line)) {
            if (isdigit(line[0]) || isalpha(line[0]))    //if number or letter
            {
                if (isdigit(line[0])) {
                    if (!first) {
                        first = true;
                        //tablesNum = stoi(line);
                    }
                    else {
                        string token;
                        int start = 0;
                        int end = 0;
                        while (end != (int)line.length()) {
                            while ((end != (int)line.length() - 1) && line[end] != ',')
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
                    else if (dishstr=="SPC")
                        dishType = SPC;
                    else if (dishstr=="BVG")
                        dishType = BVG;
                    else
                        dishType = ALC;

                    menu.push_back(Dish(idDish,dishName,stoi(dishPrice),dishType));
                    idDish++;
                }
            }
        }
                                                    //actionslog init??

    }


Restaurant::Restaurant(const Restaurant& otherRest):  //copy constructor
    open(otherRest.open), tables(), menu(), actionsLog()
{
    for(int i=0;i<(int)otherRest.tables.size();i++)
    {
        tables.push_back(new Table(*otherRest.tables[i]));
    }
    for(int i=0;i<(int)otherRest.menu.size();i++)
    {
        menu.push_back(otherRest.menu[i]);
    }
    for(int i=0;i<(int)otherRest.actionsLog.size();i++)
    {
        actionsLog.push_back(otherRest.actionsLog[i]->clone());
    }
}
Restaurant::Restaurant(Restaurant&& otherRest): //move constructor
        open(otherRest.open), tables(), menu(), actionsLog()
{
    for(int i=0;i<(int)otherRest.tables.size();i++)
    {
        tables.push_back(new Table(*otherRest.tables[i]));
        delete otherRest.tables[i];
        otherRest.tables[i]= nullptr;
    }
    for(int i=0;i<(int)otherRest.menu.size();i++)
    {
        menu.push_back(otherRest.menu[i]);
    }
    for(int i=0;i<(int)otherRest.actionsLog.size();i++)
    {
        actionsLog.push_back(otherRest.actionsLog[i]);
        delete otherRest.actionsLog[i];
        otherRest.actionsLog[i]= nullptr;
    }
}

Restaurant& Restaurant::operator=(const Restaurant& otherRest) {    //copy=

    if(this==&otherRest)
        return *this;
    this->open=otherRest.open;
//    int k = (int)tables.size();
    for(int i=0;i<(int)tables.size();i++){
        if(tables[i]!= nullptr) {
            delete tables[i];
            tables[i] = nullptr;
        }
    }
    tables.clear();
    for(int i=0;i<(int)otherRest.tables.size();i++)
        tables.push_back(new Table(*otherRest.tables[i]));


    menu.clear();
    for(int i=0;i<(int)otherRest.menu.size();i++)
        menu.push_back(otherRest.menu[i]);


    for(int i=0;i<(int)actionsLog.size();i++) {
        if (actionsLog[i] != nullptr){
            delete actionsLog[i];
            actionsLog[i]=nullptr;
        }
    }
    actionsLog.clear();
    for(int i=0;i<(int)otherRest.actionsLog.size();i++)
        {
        actionsLog.push_back(otherRest.actionsLog[i]->clone());
    }
    return *this;
}
Restaurant& Restaurant::operator=(Restaurant&& otherRest){  //move=
    if (this != &otherRest) {
        this->open=otherRest.open;

        for(int i=0;i<(int)otherRest.tables.size();i++)
        {
            tables.push_back(otherRest.tables[i]);
            otherRest.tables[i]= nullptr;
        }
        for(int i=0;i<(int)otherRest.menu.size();i++)
        {
            menu.push_back(otherRest.menu[i]);
        }
        for(int i=0;i<(int)otherRest.actionsLog.size();i++)
        {
            actionsLog.push_back(otherRest.actionsLog[i]);
            otherRest.actionsLog[i]= nullptr;
        }
    }
    return *this;
}
Restaurant::~Restaurant(){  //destructor
    for(int i=0;i<(int)tables.size();i++)
    {
        if(tables[i]!= nullptr) {
            delete tables[i];
            tables[i] = nullptr;
        }
    }
    for(int i=0;i<(int)actionsLog.size();i++)
    {
        if(actionsLog[i]!= nullptr){
            delete actionsLog[i];
            actionsLog[i] = nullptr;
            // actionsLog.erase(actionsLog.begin()+i);

        }
    }
}



void Restaurant::start() {

    open=true;
    cout << "Restaurant is now open!"<<endl;

    int customer_index=0;
    bool finito=false;
    string line;
    while(!finito) {
        int i=0;
        getline(cin,line);
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
            string table_id = line.substr(i+1, j-(i+1));

            j++;
            i=j;

            while (j<(int)line.size())
            {
                while(line[j] != ',')
                    j++;
                string customer_name = line.substr(i, j-i);
                if(line[j+1] == 's' || line[j+1] == 'S')
                    customers_input.push_back(new SpicyCustomer(customer_name, customer_index));
                else if(line[j+1] == 'v' || line[j+1] == 'V')
                    customers_input.push_back(new VegetarianCustomer(customer_name, customer_index));
                else if(line[j+1] == 'c' || line[j+1] == 'C')
                    customers_input.push_back(new CheapCustomer(customer_name, customer_index));
                else
                    customers_input.push_back(new AlchoholicCustomer(customer_name, customer_index));
                j=j+5;
                i=j;
                customer_index++;
            }


            OpenTable* action1= new OpenTable(stoi(table_id), customers_input);
            action1->act(*this);
            actionsLog.push_back(action1);
        }

        //order - make sure order printed
        if (action=="order")
        {
            int j=i+1;
            while (j<(int)line.size())
                j++;
            string table_id = line.substr(i+1, j-(i+1));

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
            string srctable = line.substr(i, j-i);
            j=j+1;
            i=j;
            while (line[j] != ' ')
                j++;
            string destable = line.substr(i, j-i);
            string idcustomer = line.substr(j+1, (int)line.size()-(j+1));

            MoveCustomer* action1= new MoveCustomer(stoi(srctable),stoi(destable),stoi(idcustomer));
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="close")
        {
            int j=i+1;
            while (j<(int)line.size())
                j++;
            string table_id = line.substr(i+1, j-(i+1));

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

//            for(int i=0;i<(int)tables.size();i++)
//            {
//                if(tables[i]!= nullptr) {
//                    delete tables[i];
//                    tables[i] = nullptr;
//                    //customersList.erase(customersList.begin()+index);
//                }
//                if(actionsLog[i]!= nullptr){
//                    delete actionsLog[i];
//                    //actionsLog[i] = nullptr;
//                    actionsLog.erase(actionsLog.begin()+i);
//                }
//            }

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
            while (j<(int)line.size())
                j++;
            string table_id = line.substr(i+1, j-(i+1));

            PrintTableStatus* action1= new PrintTableStatus(stoi(table_id));
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="log")
        {
            PrintActionsLog* action1= new PrintActionsLog();
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="backup")
        {
            BackupRestaurant* action1= new BackupRestaurant();
            action1->act(*this);
            actionsLog.push_back(action1);
        }
        if(action=="restore")
        {
            RestoreResturant* action1= new RestoreResturant();
            action1->act(*this);
            actionsLog.push_back(action1);
        }

    }
}

int Restaurant::getNumOfTables() const {
    return (int)tables.size();
}

Table* Restaurant::getTable(int ind){
    return tables[ind];
}

const std::vector<BaseAction*>& Restaurant::getActionsLog() const { // Return a reference to the history of actions
    return actionsLog;
}

std::vector<Dish>& Restaurant::getMenu(){
    return menu;
}