//
// Created by Bife on 17/01/2023.
//

#include "utils.h"
#include <cstdlib>
#include <fstream>

#ifndef FGO_DATA_DIR
#define FGO_DATA_DIR "../CHARACTERS"
#endif

bool checkIsDouble(const string &inputString) {
    if (inputString.empty()) return false;
    char *end = nullptr;
    strtod(inputString.c_str(), &end);
    return end != inputString.c_str() && *end == '\0';
}

string trim(const string &s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

string readLine() {
    string line;
    if (!getline(cin, line)) {
        cout << endl << "Input ended, closing the simulator." << endl;
        exit(0);
    }
    return trim(line);
}

char readKey() {
    string line = readLine();
    if (line.empty()) return '\0';
    return (char) tolower((unsigned char) line[0]);
}

void waitForEnter(const string &message) {
    cout << endl << message;
    readLine();
}

string padRight(const string &s, size_t width) {
    if (s.size() >= width) return s.substr(0, width);
    return s + string(width - s.size(), ' ');
}

string dataPath(const string &relative) {
    return string(FGO_DATA_DIR) + "/" + relative;
}

bool readLines(const string &path, vector<string> &lines) {
    ifstream file(path);
    if (file.fail()) return false;
    string line;
    while (getline(file, line))
        lines.push_back(trim(line));
    return true;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
