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
#include <unordered_set>

using namespace std;

struct compare {
    bool operator()(tuple<vector<int>, int, int, string> a, tuple<vector<int>, int, int, string> b)  {
        return get<1>(a) > get<1>(b);
    }
};

int findPath(vector<int> start, vector<int> end, vector<vector<char>> maze){
    vector<pair<vector<int>, string>> directions = {
                                                    {{-1, 0}, "north"},
                                                    {{1, 0}, "south"},
                                                    {{0, -1}, "west"},
                                                    {{0, 1}, "east"}
                                                    };

    unordered_set<string> visited;
    // A * search
    priority_queue<tuple<vector<int>, int, int, string>, vector<tuple<vector<int>, int, int, string>>, compare> pq;
    pq.push({start, abs(end[0] - start[0]) + abs(end[1] - start[1]), 0, "east"});
//    pq.push({start, abs(end[0] - start[0]), 0, "east"});

    while(!pq.empty()){
        auto [current, fakecost, cost, currentDir] = pq.top();
        pq.pop();

        int x = current[0], y = current[1];
        if (x == end[0] && y == end[1]) {
            return cost;
        }

        string pos = to_string(x) + "," + to_string(y) + "," + currentDir;
        if (visited.find(pos) != visited.end()){
            continue;
        }

        visited.insert(pos);

        for (const auto& dir : directions) {
            int nx = x + dir.first[0];
            int ny = y + dir.first[1];
            string nextDir = dir.second;

            if (nx >= 0 && nx < maze.size() && ny >= 0 && ny < maze[0].size() && maze[nx][ny] != '#') {
                int stepCost = 1;
                int turnCost = (currentDir != nextDir) ? 1000 : 0;
                int heuristic = (abs(end[0] - nx) + abs(end[1] - ny));
//                int heuristic = abs(end[0] - nx);
                pq.push({{nx, ny}, cost + stepCost + turnCost + heuristic, cost + stepCost + turnCost, nextDir});
            }
        }

    }

    return -1;
}

int main(int argc, char* argv[]) {

    string filename = argv[1];
    ifstream file(filename);
    string line;

    vector<int> start;
    vector<int> end;

    vector<vector<char>> maze;

    int row = 0;
    int col = 0;

    while (getline(file, line)) {
        char scan;

        col = 0;

        istringstream stream(line);

        vector<char> tmp;

        while (stream >> scan) {
            tmp.push_back(scan);

            if(scan == 'S'){
                start = {row, col};
            }
            else if(scan == 'E'){
                end = {row, col};
            }

            col++;
        }

        maze.push_back(tmp);

        row++;
    }

    file.close();

    cout << "start is " << start[0] << " " << start[1] << endl;
    cout << "end is " << end[0] << " " << end[1] << endl;

    for(int i = 0; i < maze.size(); i++){
        for(int j = 0; j < maze[0].size(); j++){
            cout << maze[i][j];
        }
        cout << endl;
    }

    cout << "Shortest path cost is " << findPath(start, end, maze) << endl;
    return 0;
}