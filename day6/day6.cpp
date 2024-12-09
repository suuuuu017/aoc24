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

int findObs(int num, string dir, vector<vector<char>> maze, vector<pair<int, int>> obs, int curr){
    int closest = INT_MAX;
    bool flag = false;
    for(int i = 0; i < obs.size(); i++){
        if(dir == "up"){
            if(obs[i].second == num && obs[i].first < curr){
                if(!flag){
                    closest = obs[i].first;
                    flag = true;
                }
                else if(obs[i].first > closest){
                    closest = obs[i].first;
                }
            }
        }
        if(dir == "down"){
            if(obs[i].second == num && obs[i].first > curr) {
                if(!flag){
                    closest = obs[i].first;
                    flag = true;
                }
                else if(obs[i].first < closest){
                    closest = obs[i].first;
                }
            }
        }
        if(dir == "left"){
            if(obs[i].first == num && obs[i].second < curr){
                if(!flag){
                    closest = obs[i].second;
                    flag = true;
                }
                else if(obs[i].second > closest){
                    closest = obs[i].second;
                }
            }
        }
        if(dir == "right"){
            if(obs[i].first == num && obs[i].second > curr){
                if(!flag){
                    closest = obs[i].second;
                    flag = true;
                }
                else if(obs[i].second < closest){
                    closest = obs[i].second;
                }
            }
        }
    }

    return closest;
}

bool findPath(vector<vector<char>> maze,  pair<int, int> guardS, vector<pair<int, int>> obs){
    string dir = "up";
    int guardX = guardS.first;
    int guardY = guardS.second;

    int res = 0;

    vector<int> tmp(maze[0].size(), 0);
    vector<vector<int>> visited(maze.size(), tmp);

    vector<int> tmp2(maze[0].size(), -1);
    vector<vector<int>> oldvisited(maze.size(), tmp2);

    while(true){
//        cout << dir << " " << guardX << " " << guardY << endl;

        if(dir == "up"){
            int num = guardY;
            int curr = guardX;
            int closest = findObs(num, dir, maze, obs, curr);
            if(closest == INT_MAX){
                for(int i = guardX; i >= 0; i--){
                    visited[i][guardY] = 1;
                }
                break;
            }
            else{
                dir = "right";
                for(int i = guardX; i > closest; i--){
                    visited[i][guardY] = 1;
                }
                if(visited == oldvisited && closest + 1 != guardX){
                    return true;
                }
                else{
                    oldvisited = visited;
                }
                guardX = closest + 1;
            }
        }
        else if(dir == "down"){
            int num = guardY;
            int curr = guardX;
            int closest = findObs(num, dir, maze, obs, curr);
            if(closest == INT_MAX){
                for(int i = guardX; i < maze.size(); i++){
                    visited[i][guardY] = 1;
                }
                break;
            }
            else{
                dir = "left";
                for(int i = guardX; i < closest; i++){
                    visited[i][guardY] = 1;
                }
                if(visited == oldvisited && closest - 1 != guardX){
                    return true;
                }
                else{
                    oldvisited = visited;
                }
                guardX = closest - 1;
            }
        }
        else if(dir == "right"){
            int num = guardX;
            int curr = guardY;
            int closest = findObs(num, dir, maze, obs, curr);
            if(closest == INT_MAX){
                for(int i = guardY; i < maze[0].size(); i++){
                    visited[guardX][i] = 1;
                }
                break;
            }
            else{
                dir = "down";
                for(int i = guardY; i < closest; i++){
                    visited[guardX][i] = 1;
                }
                if(visited == oldvisited && closest - 1 != guardY){
                    return true;
                }
                else{
                    oldvisited = visited;
                }
                guardY = closest - 1;
            }
        }
        else if(dir == "left"){
            int num = guardX;
            int curr = guardY;
            int closest = findObs(num, dir, maze, obs, curr);
            if(closest == INT_MAX){
                for(int i = guardY; i >= 0; i--){
                    visited[guardX][i] = 1;
                }
                break;
            }
            else{
                dir = "up";
                for(int i = guardY; i > closest; i--){
                    visited[guardX][i] = 1;
                }
                if(visited == oldvisited && closest + 1 != guardY){
                    return true;
                }
                else{
                    oldvisited = visited;
                }
                guardY = closest + 1;
            }
        }
    }

//    for (const auto& innerVec : visited) {
//        for(const auto& inner : innerVec){
//            res = res + inner;
//            cout << inner << " ";
//        }
//        cout << endl;
//    }

    return false;
}

int simulate(vector<vector<char>> maze,  pair<int, int> guardS){
    string dir = "up";
    int guardX = guardS.first;
    int guardY = guardS.second;

    vector<int> tmp(maze[0].size(), 0);
    vector<vector<int>> visited(maze.size(), tmp);

    while(guardX >= 1 && guardX <= maze.size() - 2
            && guardY >= 1 && guardY <= maze[0].size() - 2){
        visited[guardX][guardY] = 1;
        if(dir == "up"){
            if(maze[guardX-1][guardY] != '#'){
                guardX--;
            }
            else{
                dir = "right";
            }
        }
        else if(dir == "down"){
            if(maze[guardX+1][guardY] != '#'){
                guardX++;
            }
            else{
                dir = "left";
            }
        }
        else if(dir == "left"){
            if(maze[guardX][guardY-1] != '#'){
                guardY--;
            }
            else{
                dir = "up";
            }
        }
        else if(dir == "right"){
            if(maze[guardX][guardY+1] != '#'){
                guardY++;
            }
            else{
                dir = "down";
            }
        }
    }
    visited[guardX][guardY] = 1;

    int res = 0;
    for (const auto& innerVec : visited) {
        for(const auto& inner : innerVec){
            res = res + inner;
//            cout << inner << " ";
        }
//        cout << endl;
    }
    return res;
}

pair<pair<int, int>, string> simulate2(vector<vector<char>> maze,  pair<int, int> guardS, string dir){
    int guardX = guardS.first;
    int guardY = guardS.second;

    int step = 1;

    if(guardX >= 1 && guardX <= maze.size() - 2
          && guardY >= 1 && guardY <= maze[0].size() - 2){
        while(step != 0) {
            if (dir == "up") {
                if (maze[guardX - 1][guardY] != '#') {
                    guardX--;
                    step--;
                } else {
                    dir = "right";
                }
            } else if (dir == "down") {
                if (maze[guardX + 1][guardY] != '#') {
                    guardX++;
                    step--;
                } else {
                    dir = "left";
                }
            } else if (dir == "left") {
                if (maze[guardX][guardY - 1] != '#') {
                    guardY--;
                    step--;
                } else {
                    dir = "up";
                }
            } else if (dir == "right") {
                if (maze[guardX][guardY + 1] != '#') {
                    guardY++;
                    step--;
                } else {
                    dir = "down";
                }
            }
        }
        return {{guardX, guardY}, dir};
    }

    return {{INT_MAX, INT_MAX}, "exit"};
}

int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream file(filename);
    string line;

    vector<vector<char>> maze;
    pair<int, int> guardS;
    vector<pair<int, int>> obs;

    int row = 0;
    int col = 0;

    while (getline(file, line)) {
        char scan;
        vector<char> tmp;

        col = 0;

        istringstream stream(line);

        while(stream >> scan){
            tmp.push_back(scan);

            if(scan == '^'){
                guardS.first = row;
                guardS.second = col;
            }

            if(scan == '#'){
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

    file.close();

//    for(int i = 0; i < maze.size(); i++){
//        for(int j = 0; j < maze[0].size(); j++){
//            cout << maze[i][j];
//        }
//        cout << endl;
//    }
//
//    cout << "guard start at " << guardS.first << " " << guardS.second << endl;
//    for(int i = 0; i < obs.size(); i++){
//        cout << "obstacle at " << obs[i].first << " " << obs[i].second << endl;
//    }

//    cout << findPath(maze, guardS, obs) << endl;
//    int poss = 0;
//    for(int i = 0; i < maze.size(); i++){
//        for(int j = 0; j < maze[0].size(); j++){
//            if(maze[i][j] == '.' ) {
//                vector<pair<int, int>> newObs = obs;
//                vector<vector<char>> newMaze = maze;
//                newMaze[i][j] = '#';
//                newObs.push_back(make_pair(i, j));
//                if (findPath(newMaze, guardS, newObs)) {
//                    cout << i << " " << j << " " << endl;
//                    poss++;
//                }
//            }
//        }
//    }
//    cout << poss << endl;

    int poss = 0;

    int initX = guardS.first;
    int initY = guardS.second;

    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[0].size(); j++){
            if(maze[i][j] == '.' ) {
                cout << i << " " << j << " " << endl;
                vector<vector<char>> newMaze = maze;
                newMaze[i][j] = '#';
                pair<pair<int, int>, string> slowTmp;
                pair<int, int> slow = guardS;
                string slowDir = "up";
                slowTmp = {slow, slowDir};

                pair<pair<int, int>, string> fastTmp;
                pair<int, int> fast = guardS;
                string fastDir = "up";
                fastTmp = {fast, fastDir};

                while(true){
                    slowTmp = simulate2(newMaze, slowTmp.first, slowTmp.second);

                    fastTmp = simulate2(newMaze, fastTmp.first, fastTmp.second);
                    if(fastTmp.second == "exit"){
                        break;
                    }

                    fastTmp = simulate2(newMaze, fastTmp.first, fastTmp.second);
                    if(fastTmp.second == "exit"){
                        break;
                    }

                    if(slowTmp == fastTmp){
//                        cout << "slow is " << slowTmp.first.first << " " << slowTmp.first.second << endl;
//                        cout << "fast is " << fastTmp.first.first << " " << fastTmp.first.second << endl;
                        cout << i << " " << j << endl;
                        poss++;
                        break;
                    }
                }
            }
        }
    }
    cout << poss << endl;

//    cout << simulate(maze, guardS) << endl;
    return 0;
}