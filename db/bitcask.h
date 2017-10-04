#ifndef BITCASK_H
#define BITCASK_H

#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include "db/db_defines.h"
#include "conf/conf.h"

#define MAGICSIGN "DeerDB"
#define DELETESIGN "D0xD"

const int MAX_FILE_SIZE = 100;
const std::string DB_FILE_PREV = "kvlog.deer.";
const std::string DB_HINT_PREV = "hint.deer.";

struct BitCaskData {
    bool is_valid;

    time_t timestamp;

    int key_size;
    int value_size;

    std::string key;
    std::string value;
};

struct BitCaskIndex {

    time_t timestamp;

    int file_index;

    int data_size;
    long data_pos;
};

struct BitCaskHint {
    time_t timestamp;

    std::string key;

    int data_size;
    long data_pos;

    friend std::istream& operator>>(std::istream& is, BitCaskHint& hint){
        is >> hint.timestamp;
        is >> hint.key;
        is >> hint.data_size;
        is >> hint.data_pos;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const BitCaskHint& hint){
        os << hint.timestamp << " " 
           << hint.key << " " 
           << hint.data_size << " " 
           << hint.data_pos;
        return os;
    }
};


class BitCask
// TODO: 单例
{
public:
    
    BitCask();
    //~BitCask();

    bool do_get(std::string key);
    bool do_insert(std::string key, std::string value);
    bool do_update(std::string key, std::string value);
    bool do_delete(std::string key);

    void get_error();

private:
    void init();
    void init_with_hint(std::ifstream &hint);
    void init_without_hint();

    void init_new_kvlog(std::fstream &kvlog);
    void load_from_kvlog(std::fstream &kvlog);

    void init_bitcask_data(BitCaskData &kv, std::string key, std::string value);
    void init_bitcask_index(BitCaskData &kv, BitCaskIndex &index, long kv_pos);
    void init_bitcask_hint(BitCaskData &kv, BitCaskHint &hint, long kv_pos);
    long insert_into_kvlog(BitCaskData &kv);
    void insert_into_hint();
    void insert_into_index(std::string key, BitCaskIndex &index, BitCaskHint &hint);
    void delete_index(std::string key);

    const std::string get_file_name(int file_index);
    const std::string get_hint_name(int file_index);

private:
    Error error;

    std::unordered_map<std::string, BitCaskIndex> _index;
    std::unordered_map<std::string, BitCaskHint> _curr_hint;

    int _curr_file_index;
};

#endif
