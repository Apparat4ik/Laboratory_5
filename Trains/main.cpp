#include "header.h"
#include "functions.cpp"


int main(){
    set<Train> all_trains;
    set<Town> all_towns;
    PrintInstruction();
    
    while (true){
        cout << "> ";
        string command;
        getline(cin, command);
        istringstream s(command);
                                
        vector<string> line;
        string word;
                    
        while (s >> word) {
            line.push_back(word);
        }
                                
        if (empty(line)) {
            continue;
        }
        Command cmd = parseCommand(line[0]);
        line.erase(line.begin());
        
        string train_name;
        set<string> towns;
        string town_name;
        
        stringstream serr;
        try {
            switch (cmd){
                case Command::CREATE_TRAIN:
                    ArgumentCheck(line.size(), 2);
                    
                    train_name = line[0];
                    line.erase(line.begin());
                    towns = FromVecToSet(line);
                    CreateTrain(train_name, towns, all_trains, all_towns);
                    break;
                    
                case Command::TRAINS_FOR_TOWN:
                    ArgumentCheck(line.size(), 1);
                    
                    town_name = line[0];
                    TrainsForTown(town_name, all_trains);
                    break;
                    
                case Command::TOWNS_FOR_TRAIN:
                    ArgumentCheck(line.size(), 1);
                    
                    train_name = line[0];
                    TownsForTrain(train_name, all_towns);
                    break;
                    
                case Command::TRAINS:
                    TrainsInfo(all_trains);
                    break;
                    
                case Command::EXIT:
                    return 0;
                    
                case Command::UNKNOWN:
                    serr << "Неизвестная команда";
                    throw invalid_argument(serr.str());
                    break;
            }
        } catch (exception& s){
            cerr << s.what() << endl;
        }
    }
    return 0;
}
