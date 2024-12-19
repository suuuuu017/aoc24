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

void simulate(vector<vector<char>> & maze, vector<char> dir, vector<int> & robot){
    map<char, vector<int>> lookup = {
                                    {'^', {-1, 0}},
                                    {'v', {1, 0}},
                                    {'<', {0, -1}},
                                    {'>', {0, 1}}
                                    };
    for(int i = 0; i < dir.size(); i++){
        int tmpX = robot[0] + lookup[dir[i]][0];
        int tmpY = robot[1] + lookup[dir[i]][1];
        if(maze[tmpX][tmpY] == '#'){
            continue;
        }
        else if(maze[tmpX][tmpY] == 'O'){
            while(maze[tmpX][tmpY] != '#'){
                tmpX += lookup[dir[i]][0];
                tmpY += lookup[dir[i]][1];
                if(maze[tmpX][tmpY] == '.' || maze[tmpX][tmpY] == '@'){
                    maze[tmpX][tmpY] = 'O';
                    maze[robot[0] + lookup[dir[i]][0]][robot[1] + lookup[dir[i]][1]] = '.';
                    robot[0] += lookup[dir[i]][0];
                    robot[1] += lookup[dir[i]][1];
                    maze[robot[0]][robot[1]] = '.';
                    break;
                }
            }
        }
        else{
            robot[0] = tmpX;
            robot[1] = tmpY;
        }
    }
}

int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream file(filename);
    string line;

    vector<int> robot;
    vector<pair<int, int>> box;
    vector<pair<int, int>> obs;

    vector<vector<char>> maze;
    vector<char> dir;

    int row = 0;
    int col = 0;

    int section = 0;

    while (getline(file, line)) {

        if (line.empty()) {
            section = 1;
            continue;
        }

        if (section == 0) {
            char scan;

            col = 0;

            istringstream stream(line);

            vector<char> tmp;

            while (stream >> scan) {
                tmp.push_back(scan);

                if (scan == '@') {
                    robot.push_back(row);
                    robot.push_back(col);
                }

                if (scan == 'O') {
                    pair<int, int> b;
                    b.first = row;
                    b.second = col;
                    box.push_back(b);
                }

                if (scan == '#') {
                    pair<int, int> o;
                    o.first = row;
                    o.second = col;
                    obs.push_back(o);
                }

                col++;
            }

            maze.push_back(tmp);

            row++;
        }

        if(section == 1){
            char scan;

            istringstream stream(line);

            while (stream >> scan) {
                dir.push_back(scan);
            }
        }
    }

    file.close();

//    cout << "robot start at " << robot[0] << " " << robot[1] << endl;
//    for(int i = 0; i < box.size(); i++){
//        cout << "boxes at " << box[i].first << " " << box[i].second << endl;
//    }
//    for(int i = 0; i < obs.size(); i++){
//        cout << "obstacles at " << obs[i].first << " " << obs[i].second << endl;
//    }
//
//    for(int i = 0; i < maze.size(); i++){
//        for(int j = 0; j < maze[0].size(); j++){
//            cout << maze[i][j];
//        }
//        cout << endl;
//    }
//    for(int i = 0; i < dir.size(); i++){
//        cout << dir[i];
//    }
//    cout << endl;

    simulate(maze, dir, robot);

    int res = 0;
    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[0].size(); j++){
            cout << maze[i][j];
            if(maze[i][j] == 'O'){
                res = res + i * 100 + j;
            }
        }
        cout << endl;
    }

    cout << "result is " << res << endl;
    return 0;
}