#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stack>

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

void simulate2(vector<vector<char>> & maze, vector<char> dir, vector<int> & robot){
    map<char, vector<int>> lookup = {
            {'^', {-1, 0}},
            {'v', {1, 0}},
            {'<', {0, -1}},
            {'>', {0, 1}}
    };
    for(int i = 0; i < dir.size(); i++) {
        int tmpX = robot[0] + lookup[dir[i]][0];
        int tmpY = robot[1] + lookup[dir[i]][1];
//        cout << "here " << tmpX << " " << tmpY << endl;

        if (maze[tmpX][tmpY] == '#') {
            continue;
        }
        else if(maze[tmpX][tmpY] == '[' || maze[tmpX][tmpY] == ']'){
//            cout << "here " << tmpX << " " << tmpY << endl;
            if(dir[i] == '<' || dir[i] == '>'){
                stack<vector<int>> s;
                while(maze[tmpX][tmpY] != '#'){
                    tmpX += lookup[dir[i]][0];
                    tmpY += lookup[dir[i]][1];
                    cout << "here " << tmpX << " " << tmpY << endl;
                    s.push({tmpX, tmpY});
                    if(maze[tmpX][tmpY] == '.' || maze[tmpX][tmpY] == '@'){
                        bool f = true;
                        while(!s.empty()){
                            int currX = s.top()[0];
                            int currY = s.top()[1];
                            if(dir[i] == '<' && f){
                                maze[currX][currY] = '[';
                                f = false;
                            }
                            else if(dir[i] == '<' && !f){
                                maze[currX][currY] = ']';
                                f = true;
                            }
                            else if(dir[i] == '>' && f){
                                maze[currX][currY] = ']';
                                f = false;
                            }
                            else if(dir[i] == '>' && !f){
                                maze[currX][currY] = '[';
                                f = true;
                            }
                            s.pop();
                        }
                        robot[0] += lookup[dir[i]][0];
                        robot[1] += lookup[dir[i]][1];
                        maze[robot[0]][robot[1]] = '.';
                        break;
                    }
                }
            }
            if(dir[i] == '^' || dir[i] == 'v'){
                vector<vector<int>> radius;
                radius.push_back({tmpX, tmpY});
                if(maze[tmpX][tmpY] == '['){
                    radius.push_back({tmpX, tmpY + 1});
                }
                else if(maze[tmpX][tmpY] == ']'){
                    radius.push_back({tmpX, tmpY - 1});
                }
                while(radius.empty()){
                    int currX = radius.front()[0];
                    int currY = radius.front()[1];
                    radius.erase(radius.begin());
                    int nextX = currX + lookup[dir[i]][0];
                    if(maze[nextX][currY] == '#'){
                        break;
                    }
                    if(maze[nextX][currY] != maze[currX][currY]){
                        if(maze[nextX][currY] == '['){
                            radius.push_back({nextX, currY + 1});
                        }
                        else if(maze[nextX][currY] == ']'){
                            radius.push_back({nextX, currY - 1});
                        }
                        radius.push_back({nextX, currY});
                    }
                    if(maze[nextX][currY] == maze[currX][currY]){
                        radius.push_back({nextX, currY});
                    }
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
    int part = stoi(argv[2]);

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
                if(part == 1) {
                    tmp.push_back(scan);
                }

                if (scan == '@') {
                    robot.push_back(row);
                    robot.push_back(col);
                    if(part == 2) {
                        tmp.push_back(scan);
                        tmp.push_back('.');
                    }
                }

                if (scan == 'O') {
                    pair<int, int> b;
                    b.first = row;
                    b.second = col;
                    box.push_back(b);
                    if(part == 2) {
                        tmp.push_back('[');
                        tmp.push_back(']');
                    }
                }

                if (scan == '#') {
                    pair<int, int> o;
                    o.first = row;
                    o.second = col;
                    obs.push_back(o);
                    if(part == 2) {
                        tmp.push_back(scan);
                        tmp.push_back('#');
                    }
                }

                if(part == 2) {
                    if (scan == '.') {
                        tmp.push_back('.');
                        tmp.push_back('.');
                    }
                    col++;
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
    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[0].size(); j++){
            cout << maze[i][j];
        }
        cout << endl;
    }
//    for(int i = 0; i < dir.size(); i++){
//        cout << dir[i];
//    }
//    cout << endl;

    if(part == 1) {
        simulate(maze, dir, robot);

        int res = 0;
        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[0].size(); j++) {
                cout << maze[i][j];
                if (maze[i][j] == 'O') {
                    res = res + i * 100 + j;
                }
            }
            cout << endl;
        }

        cout << "result is " << res << endl;
    }

    if(part == 2) {
        simulate2(maze, dir, robot);

        for (int i = 0; i < maze.size(); i++) {
            for (int j = 0; j < maze[0].size(); j++) {
                cout << maze[i][j];
            }
            cout << endl;
        }

    }
    return 0;
}