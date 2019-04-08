#ifndef UTILS_H
#define UTILS_H

#include <string>
using namespace std;

#include "BaseballCard.h"
using namespace model;

#define ENUM_TO_STR(ENUM) std::string(#ENUM)

const string toUpperCase(string text);
int toInt(const string& text, const char* errorMessage);
string enumToString(BaseballCard::Condition);

#endif // UTILS_H
