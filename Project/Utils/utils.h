//
// Created by Bife on 17/01/2023.
//

#ifndef FGO_SIM_UTILS_H
#define FGO_SIM_UTILS_H
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool checkIsDouble(const string &inputString);

// ---- Input ----
// Every read from the keyboard goes through these functions (always line based),
// so there are never leftover '\n' characters in the buffer.
// If the input ends (EOF), the program exits cleanly.

// Reads a full line (without the trailing '\r' / '\n') and trims spaces
string readLine();
// Reads a line and returns its first character in lowercase ('\0' if the line is empty)
char readKey();
// Waits for the user to press Enter
void waitForEnter(const string &message = "Press Enter to continue...");

// ---- Text ----
string trim(const string &s);
// Pads (or cuts) the text so that it has exactly `width` characters
string padRight(const string &s, size_t width);

// ---- Data files ----
// Path to the CHARACTERS folder (set by CMake with FGO_DATA_DIR)
string dataPath(const string &relative);
// Reads every line of a file. Returns false if the file can't be opened
bool readLines(const string &path, vector<string> &lines);

// ---- Screen ----
void clearScreen();

#endif //FGO_SIM_UTILS_H
