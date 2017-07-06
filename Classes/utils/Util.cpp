#include "Util.hpp"

string CharVectorToString(vector<char> *buffer) {
    string rst;
    for (char ch : *buffer) {
        rst.push_back(ch);
    }
    return rst;
}

string getSessionIdFromHeader(string head) {
    regex nlp("\\r\\n");
    string header = regex_replace(head, nlp, " ");
    regex pattern(".*GAMESESSIONID=(.*) Content-Type.*");
    cmatch result;
    bool valid = regex_match(header.c_str(), result, pattern);
    
    if (!valid) {
        return "";
    }
    return result[1];
}
