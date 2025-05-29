#include "header.h"



ostream& operator<<(ostream& os, const Train& train) {
    os << train.name << ": ";
    for (const string& town : train.route) {
        os << town << " ";
    }
    return os;
}

ostream& operator<<(ostream& os, const Town& town) {
    os << town.name << " (Поезда: ";
    for (const string& train : town.passing_trains) {
        os << train << " ";
    }
    os << ")";
    return os;
}

Command parseCommand(const string& cmd) {
    if (cmd == "CREATE_TRAIN") return Command::CREATE_TRAIN;
    if (cmd == "TRAINS_FOR_TOWN") return Command::TRAINS_FOR_TOWN;
    if (cmd == "TOWNS_FOR_TRAIN") return Command::TOWNS_FOR_TRAIN;
    if (cmd == "TRAINS") return Command::TRAINS;
    if (cmd == "EXIT") return Command::EXIT;
    return Command::UNKNOWN;
}


void CreateTrain(const string& train_name, const set<string>& towns,   // создание поезда, добавление его в списки всех поездов и всех городов
                 set<Train>& all_trains, set<Town>& all_towns){
    Train train;
    train.name = train_name;
    train.route = towns;
    
    all_trains.insert(train);
    
    for (string town : towns){
        Town city;
        city.name = town;
        city.passing_trains.insert(train_name);
        all_towns.insert(city);
    }
}

// перегрузка оператора вывода для множества
template <typename T>
ostream& operator<<(ostream& os, set<T> s){
    for (T it : s){
        os << it << ' ';
    }
    return os;
}



void TrainsForTown(const string& town_name, const set<Train>& trains){    // все поезда, которые останавливаются в городе town_name
    for (Train tr : trains){
        if (count(tr.route.begin(), tr.route.end(), town_name) != 0){
            cout << tr.name << endl;
        }
    }
}


void TownsForTrain(const string& train_name, const set<Town>& towns){   // все города, которые проезжает поезд с именем train_name
    for (Town tn : towns){
        if (count(tn.passing_trains.begin(), tn.passing_trains.end(), train_name) != 0){
            cout << tn.name << " и другие поезда: ";
            tn.passing_trains.erase(train_name);
            cout << tn.passing_trains << endl;
        }
    }
}



set<string> FromVecToSet(const vector<string>& vc){   // перевод вектора во множество
    set<string> st;
    for (string it : vc){
        st.insert(it);
    }
    return st;
}

void TrainsInfo(const set<Train>& trains){   // информация о всех поездах
    for (Train tr : trains){
        cout << tr.name << ": " << tr.route << endl;
    }
}



void ArgumentCheck(const int& amount, const int& n){   // функция для проверки числа аргументов
    stringstream serr;
    if (amount < n){
        serr << "Недостаточное количесвто аргументов для этой команды";
        throw out_of_range(serr.str());
    }
}

void PrintInstruction(){
    cout << "Доступные команды:" << endl;
    cout << "CREATE_TRAIN <имя_поезда> <город 1, ... город N> - создание поезда с его остановками" << endl;
    cout << "TRAINS_FOR_TOWN <имя_города> - вывод всех поездов, которые проходят через город town" << endl;
    cout << "TOWNS_FOR_TRAIN <имя_поезда> - вывод всех городов, которые проезжает поезд с именем train." << endl;
    cout << "TRAINS - отобразить все поезда с указанием остановок" << endl;
    cout << "EXIT - выход из программы" << endl;
}
