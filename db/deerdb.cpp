#include "db/deerdb.h"

#include <string>

DeerDB::DeerDB(){
}

bool DeerDB::get_data(std::string key) {
    engine.do_get(key);
    return true;
}

bool DeerDB::insert_data(std::string key, std::string value) {
    engine.do_insert(key, value);
    return true;
}

bool DeerDB::update_data(std::string key, std::string value) {
    engine.do_update(key, value);
    return true;
}

bool DeerDB::delete_data(std::string key) {
    engine.do_delete(key);
    return true;
}
