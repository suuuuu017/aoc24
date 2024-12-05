#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sstream>
#include <set>

using namespace std;

bool ifLegal(vector<int> job, map<int, set<int>> dict){
    while(!job.empty()){
        int currP = job.front();
        job.erase(job.begin());
        if(dict[currP].size() > 0){
            for(const auto& pre : dict[currP]){
                auto ifFind = find(job.begin(), job.end(), pre);
                if(ifFind != job.end()){
                    return false;
                }
            }
        }
    }
    return true;
}

vector<int> fixOrdering(vector<int> job, map<int, set<int>> dict){
    vector<int> correctOrder;
    while(!job.empty()){
        int currP = job.front();
        int didAnything = false;
        for(const auto& pre : dict[currP]){
            auto ifFind = find(job.begin(), job.end(), pre);
            if(ifFind != job.end()){
                didAnything = true;
                job.erase(ifFind);
                job.insert(job.begin(), pre);
            }
        }
        if(!didAnything){
            correctOrder.push_back(currP);
            job.erase(job.begin());
        }
    }
    return correctOrder;
}

int main(int argc, char* argv[]) {

    map<int, set<int>> dict;

    vector<vector<int>> toPrint;

    string filename = argv[1];
    ifstream file(filename);
    string line;

    bool section = true;
    while (getline(file, line)) {
        if(line.empty()){
            section = false;
            continue;
        }
        if(section){
            istringstream curr(line);
            string first;
            getline(curr, first, '|');
            string second;
            getline(curr, second, '|');
            dict[stoi(second)].insert(stoi(first));
        }
        else{
            istringstream curr(line);
            string tmp;
            vector<int> tmptmp;
            while(getline(curr, tmp, ',')){
                tmptmp.push_back(stoi(tmp));
            }
            toPrint.push_back(tmptmp);
        }
    }
    file.close();

//    for(auto iter = dict.begin(); iter != dict.end(); iter++){
//        cout << "Number: " << iter->first << ", Values: ";
//        for(auto i = iter->second.begin(); i != iter->second.end(); i++){
//            cout << *i  << " ";
//        }
//        cout << endl;
//    }

    int res = 0;
//    for(auto iter = toPrint.begin(); iter != toPrint.end(); iter++){
//       if(ifLegal(*iter, dict)){
//           res = res + (*iter)[(*iter).size() / 2];
//       }
//    }

    for(auto iter = toPrint.begin(); iter != toPrint.end(); iter++){
        if(!ifLegal(*iter, dict)){
            vector<int> correctOrder = fixOrdering(*iter, dict);
            res = res + correctOrder[correctOrder.size() / 2];
//            for(const auto & i : correctOrder){
//                cout << i << " ";
//            }
//            cout << endl;
        }
    }

    cout << "Result: " << res << endl;

    return 0;
}