#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

int findTrail(vector<vector<int>> topo, int r, int c, int x, int y){
    int res = 0;
    queue<vector<int>> q;
    q.push({x, y, 0});
    vector<vector<int>> visited = topo;
    visited[x][y] = -1;

    while(!q.empty()){
        auto curr = q.front();
        q.pop();

        if(curr[2] == 9){
            res++;
            continue;
        }

        if(curr[0] - 1 >= 0 && topo[curr[0] - 1][curr[1]] == curr[2] + 1 && visited[curr[0] - 1][curr[1]] != -1){
            q.push({curr[0] - 1, curr[1], curr[2] + 1});
//            visited[curr[0] - 1][curr[1]] = -1;
        }
        if(curr[0] + 1 < r && topo[curr[0] + 1][curr[1]] == curr[2] + 1 && visited[curr[0] + 1][curr[1]] != -1){
            q.push({curr[0] + 1, curr[1], curr[2] + 1});
//            visited[curr[0] + 1][curr[1]] = -1;
        }
        if(curr[1] - 1 >= 0 && topo[curr[0]][curr[1] - 1] == curr[2] + 1 && visited[curr[0]][curr[1] - 1] != -1){
            q.push({curr[0], curr[1] - 1, curr[2] + 1});
//            visited[curr[0]][curr[1] - 1] = -1;
        }
        if(curr[1] + 1 < c && topo[curr[0]][curr[1] + 1] == curr[2] + 1  && visited[curr[0]][curr[1] + 1] != -1){
            q.push({curr[0], curr[1] + 1, curr[2] + 1});
//            visited[curr[0]][curr[1] + 1] = -1;
        }

    }

    return res;
}

int main(int argc, char* argv[]) {

    vector<vector<int>> topo;

    string filename = argv[1];
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        istringstream stream(line);
        vector<int> l;
        char scan;
        while (stream >> scan) {
            l.push_back(scan - '0');
        }
        topo.push_back(l);
    }
    file.close();

    int r = topo.size();
    int c = topo[0].size();

    int res = 0;
    for(int i = 0; i < topo.size(); i++) {
        for(int j = 0; j < topo[0].size(); j++){
            if(topo[i][j] == 0){
//                cout << "i " << i << " " << j << " " << findTrail(topo, r, c, i, j) << endl;
                res = res + findTrail(topo, r, c, i, j);
            }
        }
    }
    cout << res << endl;
    return 0;
}