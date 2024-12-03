#include <iostream>
#include <fstream>
#include <iterator>
#include <regex>
#include <string>

using namespace std;

int main(){
    string filename = "input.txt";

    ifstream file(filename);

    string fileContent((istreambuf_iterator<char>(file)),
                       istreambuf_iterator<char>());

    file.close();

//    cout << fileContent << endl;

    regex doPattern(R"(do\(\))");
    regex dontPattern(R"(don't\(\))");

    auto doBegin = std::sregex_iterator(fileContent.begin(), fileContent.end(), doPattern);
    auto doEnd = std::sregex_iterator();

    vector<int> dos = {0};

    for(sregex_iterator it = doBegin; it != doEnd; ++it){
        smatch m = * it;
        dos.push_back(m.position(0));
    }

    auto dontBegin = std::sregex_iterator(fileContent.begin(), fileContent.end(), dontPattern);
    auto dontEnd = std::sregex_iterator();

    vector<int> donts;

    for(sregex_iterator it = dontBegin; it != dontEnd; ++it){
        smatch m = * it;
        donts.push_back(m.position(0));
    }

    donts.push_back(fileContent.size());

//    string processedString = fileContent.substr(0, 1224);
    string processedString;

    int i = 0;
    int j = 0;
    int startPos = dos[0];
    int endPos = 0;
    while(i < dos.size() && j < donts.size()){
        while(i < dos.size() && startPos < endPos){
            i++;
            startPos = dos[i];
        }
        if(i == dos.size()){
            break;
        }
        endPos = donts[j];
        while(j < donts.size() && endPos < startPos){
            j++;
            endPos = donts[j];
        }
        if(j == dos.size()){
            break;
        }
//        cout << " start end pair is  " << startPos << " " << endPos << endl;
        processedString = processedString + fileContent.substr(startPos, endPos - startPos);
        startPos = dos[i];
    }

//    cout << "current start position is " << startPos << " end position is " << endPos << endl;
//    cout << "current start position is " << i << " end position is " << j << endl;

//    if(i == dos.size() && j <= donts.size() - 1){
//        processedString = processedString + fileContent.substr(dos[i - 1], donts[j] - dos[i - 1]);
//    }

    regex pattern(R"(mul\((\d+),(\d+)\))");

//    auto wordsBegin = std::sregex_iterator(fileContent.begin(), fileContent.end(), pattern);
//    auto wordsEnd = std::sregex_iterator();

    auto wordsBegin = std::sregex_iterator(processedString.begin(), processedString.end(), pattern);
    auto wordsEnd = std::sregex_iterator();

    int res = 0;
    for(sregex_iterator i = wordsBegin; i != wordsEnd; ++i){
        smatch match = *i;
        res = stoi(match[1]) * stoi(match[2]) + res;
    }

//    cout << processedString << endl;

    cout << "Result: " << res << endl;
//
//    cout << " do size " << dos.size() << endl;
//    for(int i = 0; i < dos.size(); ++i){
//        cout << " " << dos[i];
//    }
//    cout << endl;
//    cout << "dont size " << donts.size() << endl;
//
//    for(int i = 0; i < donts.size(); ++i){
//        cout << " " << donts[i];
//    }
//    cout << endl;

    return 0;
}

