#ifndef DEERDB_H
#define DEERDB_H

#include <string>

#include "db/bitcask.h"

class DeerDB
// TODO:单例
{
public:
    DeerDB();
    //~DeerDB();

    bool get_data(std::string key);
    bool insert_data(std::string key, std::string value);
    bool update_data(std::string key, std::string value);
    bool delete_data(std::string key);

private:
    BitCask engine;
};

#endif
