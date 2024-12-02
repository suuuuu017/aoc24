#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

using namespace std;

int main() {
    std::string filename = "input.txt";

    std::vector<int> leftCol;
    std::vector<int> rightCol;

    std::ifstream file(filename);

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int left, right;
        iss >> left >> right;
        leftCol.push_back(left);
        rightCol.push_back(right);
    }

    file.close();


    // --- Part 1 ---
    sort(leftCol.begin(), leftCol.end());
    sort(rightCol.begin(), rightCol.end());

    int result = 0;
    for(int i = 0; i < leftCol.size(); i++) {
        result = result + abs(leftCol[i] - rightCol[i]);
    }

    cout << result << std::endl;


    // --- Part 2 ---
    int result = 0;
    map<int, int> count;
    for(int i = 0; i < rightCol.size(); i++){
        count[rightCol[i]]++;
    }
    for(int i = 0; i < leftCol.size(); i++){
        if(count.find(leftCol[i]) != count.end()){
            result = result + leftCol[i] * count[leftCol[i]];
        }
    }
    cout << result << std::endl;
    return 0;
}
