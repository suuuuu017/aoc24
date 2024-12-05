#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sstream>


using namespace std;

bool find(int x, int y, int xdir, int ydir, int rsize, int csize, vector<vector<char>> screen){
    map<int, char> dict;
    dict[0] = 'X';
    dict[1] = 'M';
    dict[2] = 'A';
    dict[3] = 'S';
    if(screen[x][y] != dict[0]){
        return false;
    }
//    cout << x << " " << y << endl;
    for(int i = 1; i < 4; i++){
        int newX = x + xdir;
        int newY = y + ydir;
        if(newX >= 0 && newX < rsize && newY >= 0 && newY < csize){
            if(screen[newX][newY] == dict[i]){
                x = newX;
                y = newY;
                continue;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
//    cout << "search direction is " << xdir << " " << ydir << endl;
    return true;
}

vector<vector<char>> xmas = {{'M', '.', 'S'},
                             {'.', 'A', '.'},
                             {'M', '.', 'S'}};

vector<vector<char>> xmas2 = {{'S', '.', 'M'},
                              {'.', 'A', '.'},
                              {'S', '.', 'M'}};

vector<vector<char>> xmas3 = {{'S', '.', 'S'},
                              {'.', 'A', '.'},
                              {'M', '.', 'M'}};

vector<vector<char>> xmas4 = {{'M', '.', 'M'},
                              {'.', 'A', '.'},
                              {'S', '.', 'S'}};

bool window(int x, int y, vector<vector<char>> screen, vector<vector<char>> pattern){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(pattern[i][j] == '.'){
                continue;
            }
            else{
                if(screen[x+i][y+j] == pattern[i][j]){
                    continue;
                }
                else{
                    return false;
                }
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]){

    vector<vector<char>> screen;

    string filename = argv[1];
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream stream(line);
        vector<char> l;
        char scan;
        while (stream >> scan) {
            l.push_back(scan);
        }
        screen.push_back(l);
    }
    file.close();

    int r = screen.size();
    int c = screen[0].size();

    int res = 0;
//    for(int i = 0; i < r; i++){
//        for(int j = 0; j < c; j++){
//            if(find(i, j, 0, 1, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, 0, -1, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, 1, 0, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, -1, 0, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, 1, 1, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, -1, -1, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, 1, -1, r, c, screen)){
//                res++;
//            }
//
//            if(find(i, j, -1, 1, r, c, screen)){
//                res++;
//            }
//
//        }
//    }

    for(int i = 0; i <= r - 3; i++){
        for(int j = 0; j <= c - 3; j++){
            if(window(i, j, screen, xmas)){
                res++;
            }
            if(window(i, j, screen, xmas2)){
                res++;
            }
            if(window(i, j, screen, xmas3)){
                res++;
            }
            if(window(i, j, screen, xmas4)){
                res++;
            }
        }
    }
    
    cout << res << endl;

}