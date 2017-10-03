#ifndef INTERFACE_H
#define INTERFACE_H

#include<string>

#include "db/deerdb.h"

using namespace std;

const std::string GET_COMMAND("get");
const std::string INSERT_COMMAND("insert");
const std::string UPDATE_COMMMAND("update");
const std::string DELETE_COMMAND("delete");

string route(DeerDB &deerdb, string command, string key, string value);

#endif
