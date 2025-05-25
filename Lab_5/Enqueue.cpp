#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <iomanip>
#include <sstream>
#include <algorithm>


using namespace std;

enum class Command {
    ENQUEUE,
    DISTRIBUTE,
    EXIT,
    UNKNOWN
};

Command parseCommand(const string& cmd) {
    if (cmd == "ENQUEUE") return Command::ENQUEUE;
    if (cmd == "DISTRIBUTE") return Command::DISTRIBUTE;
    if (cmd == "EXIT") return Command::EXIT;
    return Command::UNKNOWN;
}


// добавление в очередь
void Enqueue(queue<pair<string, int>>& visitors, const int& visit_time){
    stringstream ticket_s;
    ticket_s << 'T' << setw(3) << setfill('0') << to_string(rand() % 1000);
    visitors.push({ticket_s.str(), visit_time});  // добавление талона в очередь
    cout << ">>> "<<ticket_s.str() << endl;
}

// перегрузка вывода для очереди, вывод всех талонов очереди
ostream& operator<<(ostream& os, queue<pair<string, int>> win){
    bool is_first = true;
    while (!empty(win)){
        if (!is_first){
            os << ", ";
        }
        os << win.front().first;
        win.pop();
        is_first = false;
    }
    return os;
}


// вывод информации о каждой очереди на окно
void Distribute(queue<pair<string, int>>& visitors,   // очередь посетителей
                vector<queue<pair<string, int>>>& windows,   // вектор окон с очередями
                vector<int>& win_time){  // вектор общего времени каждого окна
    
    while (!empty(visitors)){
            pair<string, int> vstr = visitors.front();  // берем первого человека в очереди
            visitors.pop();  // удаляем его талон из очереди
            
            vector<int>::iterator minWT = min_element(win_time.begin(), win_time.end());   // берем итератор окна с минимальным общим временем
            auto min_index = distance(win_time.begin(), minWT);  // находим индекс этого окна
            
            windows[min_index].push(vstr);   // добавляем талон в очередь
            win_time[min_index] += vstr.second;  // добавляем к общему времени
    }
    int number = 1;  // номер окна
    for (queue<pair<string, int>> win : windows){
        auto it =  find(windows.begin(), windows.end(), win);   // итератор текущего окна
        auto win_index = distance(windows.begin(), it);        // индекс текущего окна
        cout << ">>> Окно " << number << " (" << win_time[win_index] << " мин.): " << win << endl;
        number++;
    }
}

int main(){
    
    cout << ">>> В программе имеются команды: " << endl;
    cout << ">>> ENQUEUE <время визита> - добавление в очередь и выдача талона " << endl;
    cout << ">>> DISTRIBUTE - вывод информации об очереди в каждое окно" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << ">>> Введите количество окон" << endl;
    cout << "<<< ";
    
    stringstream serr;
    try {
        string input;
        getline(cin, input);  // Считываем всю строку
        int amount = stoi(input);  // Преобразуем в число;
        if (amount <=0){
            serr << "Некорректное число окон";
            throw invalid_argument(serr.str());
        }

        queue<pair<string, int>> visitors;   // очеред из посетителей {талон, время}
        
        vector<queue<pair<string, int>>> windows(amount);   // вектор очередей для каждого окна
        
        vector<int> win_time(amount, 0);   // суммарное время для каждого окна
        
        cout << "Создано " << amount << " окон. Введите нужную вам команду" << endl;
        
        while (true){
            cout << "<<< ";
            string command;
            getline(cin, command);
            stringstream s(command);
                        
            vector<string> line;
            string word;
            
            while (s >> word) {
                line.push_back(word);
            }
                        
            if (empty(line)) {
                continue;
            }
            Command cmd = parseCommand(line[0]);
            int visit_time;
            
            
            
            switch (cmd) {
                case Command::ENQUEUE:
                    if (line.size() != 2){
                        serr << ">>> Некорректно число аргументов для данной команды";
                        throw out_of_range(serr.str());
                    }
                    visit_time = stoi(line[1]);
                    if (visit_time <= 0){
                        serr << ">>> Некорректно введено время визита";
                        throw invalid_argument(serr.str());
                    }
                    Enqueue(visitors, visit_time);
                    break;
                        
                case Command::DISTRIBUTE:
                    if (line.size() != 1){
                        serr << ">>> Некорректно число аргументов для данной команды";
                        throw out_of_range(serr.str());
                    }
                    Distribute(visitors, windows, win_time);
                    break;
                        
                case Command::EXIT:
                    return 0;
                        
                case Command::UNKNOWN:
                    serr << ">>> Неизвестная команда";
                    throw invalid_argument(serr.str());
                    break;
            }
            
        }
    } catch (exception& s){
                cerr << s.what() << endl;
    }
    return 0;
}
