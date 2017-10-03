#include "db/interface.h"

#include<string>

#include "db/deerdb.h"

using namespace std;

string route(DeerDB &deerdb, string command, string key, string value) {
    string response;
    if (command == GET_COMMAND)
        deerdb.get_data(key);
    else if (command == INSERT_COMMAND)
        deerdb.insert_data(key, value);
    else if (command == UPDATE_COMMMAND)
        deerdb.update_data(key, value);
    else if(command == DELETE_COMMAND)
        deerdb.delete_data(key);
    else
        cout << "command error" << endl;

    return response;
}
