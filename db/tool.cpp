#include <iostream>
#include <string>
#include <algorithm>
#include <iterator> 
#include <vector>

#include "db/interface.h" 
#include "db/deerdb.h"


void split(std::string& s, std::vector<std::string>& sv, const char delim = ' ') {
    std::string value;
    std::string delim_str(1, delim);

    for(auto it = s.begin(); it != s.end(); ++it){
        char curr_char = *it;
        if(curr_char != delim){
            value += std::string(1, curr_char);
        }
        else if(value != ""){
            sv.push_back(value);
            value.clear();
        }
    }

    if(value != ""){
        sv.push_back(value);
    }
}


int main() {
    DeerDB deerdb;
    std::string command;
    std::string action, key, value;
    while(std::getline(std::cin, command)) {

        std::vector<std::string> sv;
        split(command, sv, ' ');

        action = sv[0];
        key = sv[1];
        if(sv.size() < 3){
            value = "";
        }
        else{
        value = sv[2];
        }

        route(deerdb, action, key, value);
    }
    return 0;
}
