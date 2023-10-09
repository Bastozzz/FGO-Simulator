//
// Created by Bife on 17/01/2023.
//

#include "utils.h"

bool checkIsDouble(string inputString) {
    char* end;
    if (end == inputString.c_str() || *end != '\0') return false;
    return true;
}