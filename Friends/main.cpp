#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct FriendsSystem {
    unordered_map<string, unordered_set<string>> friendships;
    
    void addFriendship(const string& person1, const string& person2) {    // добавление друзей
        friendships[person1].insert(person2);
        friendships[person2].insert(person1);
    }
    
    int countFriends(const string& person) {   // сколько друзей
        auto it = friendships.find(person);
        if (it != friendships.end()) {
            return it->second.size();
        }
        return 0;
    }
    
    bool areFriends(const string& person1, const string& person2) {   // друзья ли?
        auto it = friendships.find(person1);
        if (it != friendships.end()) {
            return it->second.find(person2) != it->second.end();
        }
        return false;
    }
};

int main() {
    int n; // число вводов
    cin >> n;
    cin.ignore(); // Игнорируем символ новой строки после числа
    
    FriendsSystem system;
    
    vector<int> cnt(n);  // вектор для числа итераций
    
    for (int i : cnt) {
        string line;
        getline(cin, line);
        
        // Разбираем команду
        size_t firstSpace = line.find(' ');
        string command = line.substr(0, firstSpace);  // обрезание строки
        
        if (command == "FRIENDS") {
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string person1 = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string person2 = line.substr(secondSpace + 1);
            system.addFriendship(person1, person2);
        }
        else if (command == "COUNT") {
            string person = line.substr(firstSpace + 1);
            cout << system.countFriends(person) << endl;
        }
        else if (command == "QUESTION") {
            size_t secondSpace = line.find(' ', firstSpace + 1);
            string person1 = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
            string person2 = line.substr(secondSpace + 1);
            cout << (system.areFriends(person1, person2) ? "YES" : "NO") << endl;
        }
    }
    
    return 0;
}
