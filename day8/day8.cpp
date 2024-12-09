#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

void find(map<char, vector<vector<int>>> ant, set<vector<int>> & res, int row, int col){
    int antR = row;
    int antC = col;

    for(const auto & a : ant){
        int l = a.second.size();
//        cout << " l is " << l << endl;
        if(l <= 1){
            return;
        }
        for(int i = 0; i < l; i++){
            res.insert(a.second[i]);
        }
        for(int i = 0; i < l - 1; i++){
            for(int j = i + 1; j < l; j++){
                int x1 = a.second[i][0];
                int y1 = a.second[i][1];
                int x2 = a.second[j][0];
                int y2 = a.second[j][1];

                int dx = x1 - x2;
                int dy = y1 - y2;

                int x = x1 + dx;
                int y = y1 + dy;

//                cout << "x1 is " << x1 << "y1 is " << y1 << endl;
//                cout << "x2 is " << x2 << "y2 is " << y2 << endl;
//                cout << "dx is " << dx << " dy is " << dy << endl;
//                cout << "x is " << x << " y is " << y << endl;

                // --- part 1 --
//                if(x >= 0 && x < antR && y >= 0 && y < antC){
//                    res.insert({x, y});
//                }

                // --- part 2 --
                while(x >= 0 && x < antR && y >= 0 && y < antC){
//                    cout << "x is " << x << " y is " << y << endl;
                    res.insert({x, y});
                    x = x + dx;
                    y = y + dy;
                }

                x = x2 - dx;
                y = y2 - dy;

//                cout << "x is " << x << " y is " << y << endl;
//                cout << endl;

                // --- part 1 ---
//                if(x >= 0 && x < antR && y >= 0 && y < antC){
//                    res.insert({x, y});
//                }

                // --- part 2 ---
                while(x >= 0 && x < antR && y >= 0 && y < antC){
//                    cout << "x is " << x << " y is " << y << endl;
                    res.insert({x, y});
                    x = x - dx;
                    y = y - dy;
                }
//                cout << endl;
            }
        }
    }
}


int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream file(filename);
    string line;

    map<char, vector<vector<int>>> ant;

    int row = 0;
    int col = 0;

    int c = 0;

    while (getline(file, line)) {
        char scan;
        vector<char> tmp;

        c = 0;

        istringstream stream(line);

        while (stream >> scan) {
            if(scan == '.'){
                c++;
                continue;
            }
            ant[scan].push_back({row, c});
            c++;
        }
        col = c;
        row++;
    }

    file.close();

    for(auto & a : ant){
        cout << a.first << " ";
        cout << a.second.size() << endl;
        for(auto & b : a.second){
            cout << "(" << b[0] << ", " << b[1] << ") ";
        }
        cout << endl;
    }

    set<vector<int>> res;
    find(ant, res, row, col);
    cout << "Result: " << res.size() << endl;

    return 0;
}