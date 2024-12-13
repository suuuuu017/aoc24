#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <cmath>

using namespace std;

pair<int, int> find(vector<vector<char>> farm, vector<vector<int>> & visited, int x, int y){
    int area = 0;
    int length = 0;
    queue<pair<int, int>> q;
    q.push({x, y});
    // visited[x][y] = 1;

    // area = area + 1;
    // length = length + 4;
    while(!q.empty()){
        auto curr = q.front();
        q.pop();
        auto currX = curr.first;
        auto currY = curr.second;
        if(visited[currX][currY] == 1){
            continue;
        }
        visited[currX][currY] = 1;
//        cout << " letter is " << farm[x][y] << " x " << currX << " y " << currY << endl;

        area = area + 1;
        length = length + 4;

        if(currX - 1 >= 0 && visited[currX - 1][currY] != 1 &&
           farm[currX - 1][currY] == farm[currX][currY]){
            q.push({currX - 1, currY});
            length = length - 2;
        }
        if(currX + 1 < visited.size() && visited[currX + 1][currY] != 1 &&
           farm[currX + 1][currY] == farm[currX][currY]){
            q.push({currX + 1, currY});
            length = length - 2;
        }
        if(currY - 1 >= 0 && visited[currX][currY - 1] != 1 &&
           farm[currX][currY - 1] == farm[currX][currY]){
            q.push({currX, currY - 1});
            length = length - 2;
        }
        if(currY + 1 < visited[0].size() && visited[currX][currY + 1] != 1 &&
           farm[currX][currY + 1] == farm[currX][currY]){
            q.push({currX, currY + 1});
            length = length - 2;
        }
    }
    pair<int, int> r = {area, length};
    return r;
}

int main(int argc, char* argv[]) {
    vector<vector<char>> farm;

    string filename = argv[1];
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream stream(line);
        vector<char> l;
        char scan;
        while (stream >> scan) {
            l.push_back(scan - '0');
        }
        farm.push_back(l);
    }
    file.close();

    int res = 0;

    vector<int> tmp(farm[0].size(), 0);
    vector<vector<int>> visited(farm.size(), tmp);

    for(int i = 0; i < farm.size(); i++){
        for(int j = 0; j < farm[0].size(); j++){
            if(visited[i][j] != 1){
                auto curr = find(farm, visited, i, j);
//                cout <<" plant is " << farm[i][j] <<  " area is " << curr.first << " length is " << curr.second << endl;
                res = res + curr.first * curr.second;
            }
        }
    }
    cout << res << endl;

    return 0;
}