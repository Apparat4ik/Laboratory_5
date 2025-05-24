#include <iostream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

#define MAX_WAREHOUSE 640     // максимальная вместимость склада

enum class Command{
    ADD,
    REMOVE,
    INFO,
    EXIT,
    UNKNOWN
};

Command parseCommand(const string& cmd) {
    if (cmd == "ADD") return Command::ADD;
    if (cmd == "REMOVE") return Command::REMOVE;
    if (cmd == "INFO") return Command::INFO;
    if (cmd == "EXIT") return Command::EXIT;
    return Command::UNKNOWN;
}

// функция для добавления товара
void Add_product(map<string, map<string, int>>& wh, string& product, string& adress, int& amount){
    
    int current_amount = 0;   // текущее количество товара на полке
    
    for (pair<string, int> item : wh[adress]){
        current_amount += item.second;
    }
    
    if (amount + current_amount > 10){   // если общее количесвто товара > 10, то выдать ошибку
        stringstream serr;
        serr << "На одной полке может быть размещено лишь до 10 едениц товара. Добавьте меньшее количесто товара либо выберете другую ячейку";
        throw logic_error(serr.str());
        
    } else {
        wh[adress][product] += amount;   // добавляем товар на полку
    }
}

// функция для удаления товара
void Remove_product(map<string, map<string, int>>& wh, string& product, string& adress, int& amount){
    
    int current_amount = 0;
    
    for (pair<string, int> item : wh[adress]){
        current_amount += item.second;
    }
    
    if (current_amount - amount < 0 || wh[adress].count(product) == 0){   // если пользователь хочет удалить больше чем есть
        stringstream serr;
        serr << "На полке нет такого количества данного товара или его нет вообще";
        throw logic_error(serr.str());
        
    } else if (current_amount - amount == 0){   // удаление внутреннего map при количестве данного товара = 0
        wh[adress].erase(product);
    } else {
        wh[adress][product] -= amount;    // удаление определенного количества товара
    }
}


// расчет процентов
double GetFillPercentage(int total, int max) {
    return (static_cast<double>(total) / max) * 100;
}


// перегрузка вывода map
template <typename T, typename N>
ostream& operator<<(ostream& os, const map<T, N>& mp){
    for (pair<T, N> item : mp){
        os << item.first << ' ' << item.second << ' ';
    }
    return os;
}

// перегрузка вывода vector
template<typename T>
ostream& operator<<(ostream& os, const vector<T>& vc){
    for (T item : vc){
        cout << item << ' ';
    }
    return os;
}



// функция для вывода информации
void Information(const map<string, map<string, int>>& wh){
    
    int total = 0;    // счетчик общего количества товара на складе
    
    vector<string> emp_cells;  // список пустых ячеек
    
    map<string, map<string, int>> filled_cells;   // список непустых ячеек с их сожержанием
    
    for (char zone : {'A', 'B', 'C', 'D'}){     // перебираем по кажой зоне
        
        int zone_items = 0;  // количество товара на каждую отдельную зону
        
        for (pair <string, map<string, int>> shelf : wh){
            
            if (shelf.first[0] == zone && !empty(shelf.second)){    // если номер зоны ячейки соответствует перебираемой зоне
                for (pair<string, int> item : shelf.second){        // и ячейка не пуста
                    zone_items += item.second;                      // то добавляем количество товара на этой полке к zone_items
                    filled_cells[shelf.first] = shelf.second;       // сразу добавим эту ячейку в список
                }
                
            } else if (shelf.first[0] == zone && empty(shelf.second)){    // если ячейка пустая
                emp_cells.push_back(shelf.first);                         // то добавим ее в список пустых ячеек
            }
        }
        total += zone_items;       // прибавим количество товара в отдельной зоне к общему количеству
        
        cout << "Зона " << zone << " заполнена на " << GetFillPercentage(zone_items, MAX_WAREHOUSE / 4) << '%' << endl;
    }
    
    cout << "Общая заполненность склада: " << GetFillPercentage(total, MAX_WAREHOUSE) << '%' << endl;
    cout << "Занятые ячейки: " << filled_cells << endl;
    cout << "Пустые ячейки: " << emp_cells << endl;
}

// провекра правильности ввода адреса ячейки
bool CheckAdress(const string& adress){
    if (adress.size() != 4){return false;}  // проверка длины адреса
    
    int rack = adress[1] - '0';  // преобразование цифр адреса из строки в int
    int sect = adress[2] - '0';
    int shelf = adress[3] - '0';
    
    if (adress[0] != 'A' && adress[0] != 'B' &&
        adress[0] != 'C' && adress[0] != 'D'){return false;}
    
    else if (rack > 8 || rack < 1){return false;}
    else if (sect > 2 || sect < 1){return false;}
    else if (shelf != 1){return false;}
    return true;
}

int main() {
    
    const vector<int> shelfs = {1};    // полки на каждую секцию
    
    const vector<int> sections = {1, 2};  // секции на каждый стеллаж
    
    const vector<int> racks = {1, 2, 3, 4, 5, 6, 7, 8};   // стеллажи на каждую зону
            
    const vector<char> zones = {'A', 'B', 'C', 'D'};   // зоны хранение
    
    map<string, map<string, int>> warehouse;   // map, где ключ - адрес ячейки, а значение - map, в котором ключ - товар, значение - кол-во
    
    // заполнение warehouse
    for (char zone : zones){
        for (int rack : racks){
            for (int sec : sections){
                for (int shelf : shelfs){
                    string adress = zone + to_string(rack) + to_string(sec) + to_string(shelf);  // преобразование адреса в одну строку
                    warehouse[adress] = {};
                }
            }
        }
    }
    
    cout << "На складе есть: " << endl;
    cout << "Зоны хранения: A, B, C, D" << endl;
    cout << "Стеллажи: 1-8" << endl;
    cout << "Вертикальные секции: 1-2" << endl;
    cout << "Полки: 1" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "Программа имеет следуюште команды: " << endl;
    cout << "ADD <товар> <количество> <ячейка> - доюавление товара в ячейку" << endl;
    cout << "REMOVE <товар> <количество> <ячейка> - удаление товара с ячейки" << endl;
    cout << "INFO - информация о загруженности склада" << endl;
    cout << "EXIT - выход из программы" << endl;
    cout << "Адреса записывать в формате <A111>" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "Введите команду" << endl;
    
    while (true){
        cout << "> ";
        string command;
        getline(cin, command);
        stringstream s(command);
        
        vector<string> line;
        string word;
        
        while (s >> word) {
            line.push_back(word);
        }
        
        if (line.empty()) {
            continue;
        }
        
        Command cmd = parseCommand(line[0]);
        string product;
        string adress;
        int amount;
        
        stringstream serr;
        try {
            switch (cmd) {
                case Command::ADD:
                    if (line.size() != 4){
                        serr << "Некорректное число аргументов для данной команды";
                        throw out_of_range(serr.str());
                        break;
                    }
                    
                    product = line[1];
                    adress = line[3];
                    amount = stoi(line[2]);
                    
                    if (!CheckAdress(adress)){
                        serr << "Некотрректный адрес ячейки";
                        throw invalid_argument(serr.str());
                    }
                    
                    Add_product(warehouse, product, adress, amount);
                    break;
                    
                case Command::REMOVE:
                    if (line.size() != 4){
                        serr << "Некорректное число аргументов для данной команды";
                        throw out_of_range(serr.str());
                        break;
                    }
                    
                    product = line[1];
                    adress = line[3];
                    amount = stoi(line[2]);
                    
                    if (!CheckAdress(adress)){
                        serr << "Некотрректный адрес ячейки";
                        throw invalid_argument(serr.str());
                    }
                    
                    Remove_product(warehouse, product, adress, amount);
                    break;
                    
                case Command::INFO:
                    if (line.size() != 1){
                        serr << "Некорректное число аргументов для данной команды";
                        throw out_of_range(serr.str());
                        break;
                    }
                    Information(warehouse);
                    break;
                    
                case Command::UNKNOWN:
                    serr << "Неизвестная команда";
                    throw out_of_range(serr.str());
                    break;
                    
                case Command::EXIT:
                    return 0;
            }
        } catch (exception& s){
            cerr << s.what() << endl;
        }
    }
    return 0;
}
