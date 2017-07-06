#ifndef Util_hpp
#define Util_hpp

#include <string>
#include <regex>
using namespace std;

string CharVectorToString(vector<char> *buffer);

string getSessionIdFromHeader(string head);

#endif
