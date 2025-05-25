#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <iomanip>

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



void Enqueue(map<string, int>& times, const int& visit_time){
    mt19937 rand;
    string ticket_num = to_string(rand() % 1000);
    while (ticket_num.size() < 3){
        ticket_num = '0' + ticket_num;
    }
    string ticket = 'T' + ticket_num;
    times[ticket] = visit_time;
    cout << ticket << endl;
}

void Distribute(map<string, int>& times, map<int, map<string, int>>& windows){
    for (pair<int, map<string, int>> win : windows){
        int total_time = 0;
        for (pair<string, int> num : win.second){
            total_time += num.second;
        }
    }
}

int main(){
    cout << "Введите количество окон" << endl;
      int amount;
      int number = 0;
      cin >> amount;
      vector<int> vc(amount);
      map<int, map<string, int>> windows;
      for (pair<int, map<string, int>> win : windows){
          win.first = number++;
          for (pair<string, int> num : win.second){
              num.second = 0;
          }
      }
    map<string, int> times;
    Enqueue(times, 3);
    
    
    return 0;
}
