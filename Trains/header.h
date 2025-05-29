#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <vector> 
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

enum class Command {
    CREATE_TRAIN,
    TRAINS_FOR_TOWN,
    TOWNS_FOR_TRAIN,
    TRAINS,
    EXIT,
    UNKNOWN
};

struct Train {    // структура поезда
    string name;
    set<string> route;
    
    bool operator<(const Train& other) const {   // перегрузка оператора сравнения, чтобы спокойно добавить строку в set
            return name < other.name;
        }
};

struct Town {   // структура городов
    string name;
    set<string> passing_trains;
    
    bool operator<(const Town& other) const {
        return name < other.name;
    }
};



Command parseCommand(const string& cmd);

void CreateTrain(const string& train_name, const set<string>& towns,
                 set<Train>& all_trains,set<Town>& all_towns);

void TrainsForTown(const string& town_name, const set<Train>& trains);

void TownsForTrain(const string& train_name, const set<Town>& towns);


set<string> FromVecToSet(const vector<string>& vc);

void TrainsInfo(const set<Train>& trains);

void ArgumentCheck(const int& amount, const int& n);

void PrintInstruction();

template <typename T>
ostream& operator<<(ostream& os, set<T> s);


#endif
