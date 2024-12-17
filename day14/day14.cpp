#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <cmath>
#include <set>
#include <climits>

using namespace std;

pair<int, int> move(pair<int, int> curr, int sec, pair<int, int> vel, int r, int c){
    int x = curr.second;
    int y = curr.first;

    int nX = ((x + vel.second * sec) % r + r) % r;
    int nY = ((y + vel.first * sec) % c + c) % c;

    return {nX, nY};
}

int main(int argc, char* argv[]) {
//    pair<int, int> curr = {2, 4};
//    int sec = 5;
//    pair<int, int> vel = {2, -3};
//    int r = 7;
//    int c = 11;
//
//    pair<int, int> res = move(curr, sec, vel, r, c);
//    cout << res.first << " " << res.second << endl;

    int sec = 6000;
    int r = 103;
    int c = 101;
    map<pair<int, int>, int> m;

    int quat1 = 110;
    int quat2 = 0;
    int quat3 = 110;
    int quat4 = 0;

    string filename = argv[1];
    ifstream file(filename);

//    int r = 7;
//    int c = 11;
    for(sec = 7410; sec < 7810; sec = sec + 5) {
//        if(abs(quat1 + quat3 - (quat2 + quat4)) < 100){
            cout << sec << endl;
            for (int i = 0; i < r; i++) {
                for (int j = 0; j < c; j++) {
                    if (m.find({i, j}) != m.end()) {
                        cout << "#";
                    }
                    else {
                        cout << " ";
                    }
                }
                cout << endl;
            }
//        }

        m.clear();
        file.clear();
        file.seekg(0);

        quat1 = 0;
        quat2 = 0;
        quat3 = 0;
        quat4 = 0;

        string line;
        while (getline(file, line)) {
            for (char &ch: line) {
                if (ch == '=' || ch == ',' || ch == 'p' || ch == 'v') {
                    ch = ' ';
                }
            }
            istringstream stream(line);

            pair<int, int> curr;
            pair<int, int> vel;
            stream >> curr.first >> curr.second >> vel.first >> vel.second;
//        cout << curr.first << " " << curr.second << endl;
//        cout << vel.first << " " << vel.second << endl;

            pair<int, int> res = move(curr, sec, vel, r, c);
            m[res]++;
        }


        for (auto itr: m) {
            if (itr.first.first < r / 2 && itr.first.second < c / 2) {
//            cout << "quat 1 " << itr.first.first << " " << itr.first.second << endl;
                quat1 += itr.second;
            }
            if (itr.first.first < r / 2 && itr.first.second > c / 2) {
//            cout << "quat 2 " << itr.first.first << " " << itr.first.second << endl;
                quat2 += itr.second;
            }
            if (itr.first.first > r / 2 && itr.first.second < c / 2) {
//            cout << "quat 3 " << itr.first.first << " " << itr.first.second << endl;
                quat3 += itr.second;
            }
            if (itr.first.first > r / 2 && itr.first.second > c / 2) {
//            cout << "quat 4 " << itr.first.first << " " << itr.first.second << endl;
                quat4 += itr.second;
            }
//        cout << itr.first.first << "," << itr.first.second << " : " << itr.second << endl;
        }
        cout << "Quarter 1 : " << quat1 << endl;
        cout << "Quarter 2 : " << quat2 << endl;
        cout << "Quarter 3 : " << quat3 << endl;
        cout << "Quarter 4 : " << quat4 << endl;
//        long res = quat1 * quat2 * quat3 * quat4;
//        cout << res << endl;

    }
    file.close();

    return 0;
}