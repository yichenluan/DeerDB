#include "db/bitcask.h"

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>


BitCask::BitCask() {
    //TODO
    _curr_file_index = 1;
    init();
}

//BitCask::~BitCask() {
    ////TODO
//}

void BitCask:: init() {
    std::ifstream hint;
    hint.open("hint.bin", std::ios::binary);
    if (hint) {
        init_with_hint(hint);
        hint.close();
    }
    else {
        init_without_hint();
    }
}

bool BitCask::do_get(std::string key) {
    auto it = _index.find(key);
    if(it == _index.end()){
        std::cout <<"Can't find key in DeerDB" << std::endl;
        return false;
    }
    BitCaskIndex index_info = it->second;

    std::fstream current_kvlog;
    current_kvlog.open(
            get_file_name(index_info.file_index), 
            std::ios::binary | std::ios::in
        );
    if(!current_kvlog){
        return false;
    }

    current_kvlog.seekg(index_info.data_pos, std::ios::beg);
    BitCaskData kv_data;
    current_kvlog.read((char *)(&kv_data), sizeof(kv_data));
    std::string get_value = kv_data.value;
    current_kvlog.close();
    std::cout <<get_value<<std::endl;
    return true;
}

bool BitCask::do_insert(std::string key, std::string value) {
    //TODO
    BitCaskData kv;
    long kv_pos;
    init_bitcask_data(kv, key, value);

    kv_pos = insert_into_kvlog(kv);

    BitCaskIndex index;
    init_bitcask_index(kv, index, kv_pos);

    insert_into_index(key, index);

    return true;
}

bool BitCask::do_update(std::string key, std::string value) {
    BitCaskData kv;
    long kv_pos;
    init_bitcask_data(kv, key, value);

    kv_pos = insert_into_kvlog(kv);

    BitCaskIndex index;
    init_bitcask_index(kv, index, kv_pos);

    insert_into_index(key, index);

    return true;
}

bool BitCask::do_delete(std::string key) {
    BitCaskData kv;
    init_bitcask_data(kv, key, std::string(DELETESIGN));
    kv.is_valid = false;


    insert_into_kvlog(kv);

    delete_index(key);

    return true;
}

void BitCask::get_error() {
    //TODO
}

void BitCask::init_with_hint(std::ifstream &hint){

}

void BitCask::init_without_hint() {
    std::fstream kvlog;
    kvlog.open(
            get_file_name(_curr_file_index), 
            std::ios::binary | std::ios::app
        );
    std::cout <<get_file_name(_curr_file_index)<<std::endl;
    if(!kvlog) {
        // TODO:ERROR CODE
        return ;
    }
    if(!kvlog.tellg()) {
        init_new_kvlog(kvlog);
    }
    else {
        load_from_kvlog(kvlog);
    }
    kvlog.close();
}

void BitCask::init_new_kvlog(std::fstream &kvlog) {
    std::string magic_sign(MAGICSIGN);
    kvlog.write((char *)(&magic_sign), sizeof(magic_sign));
}

void BitCask::load_from_kvlog(std::fstream &kvlog) {

}

void BitCask::init_bitcask_data(BitCaskData &kv, std::string key, std::string value) {
    kv.is_valid = true;
    kv.key = key;
    kv.value = value;
    kv.key_size = static_cast<int>(sizeof(key));
    kv.value_size = static_cast<int>(sizeof(value));
    kv.timestamp = time(0);
    return;
}

void BitCask::init_bitcask_index(BitCaskData &kv, BitCaskIndex &index, long kv_pos) {
    index.timestamp = time(0);
    index.data_size = static_cast<int>(sizeof(kv));
    index.data_pos = kv_pos;
    index.file_index = _curr_file_index;
    return;
}

long BitCask::insert_into_kvlog(BitCaskData &kv) {
    std::fstream curr_kvlog;
    curr_kvlog.open(
            get_file_name(_curr_file_index), 
            std::ios::binary | std::ios::app | std::ios::in
        );
    if(!curr_kvlog) {
        return -1;
    }
    long kv_pos = curr_kvlog.tellg();
    if(kv_pos + sizeof(kv) > MAX_FILE_SIZE){
        curr_kvlog.close();
        _curr_file_index += 1;
        curr_kvlog.open(
                get_file_name(_curr_file_index), 
                std::ios::binary | std::ios::app | std::ios::in
            );
        init_new_kvlog(curr_kvlog);
        kv_pos = curr_kvlog.tellg();
    }
    curr_kvlog.write((char *)(&kv), sizeof(kv));
    curr_kvlog.close();
    return kv_pos;
}

void BitCask::insert_into_index(std::string key, BitCaskIndex &index) {
    _index[key] = index;
    return;
}

void BitCask::delete_index(std::string key) {
    auto it = _index.find(key);
    if(it == _index.end()) {
        //TODO
        return;
    }
    _index.erase(it);
    return;
}

const std::string BitCask::get_file_name(int file_index) {
    const std::string file_name = DB_FILE_PATH + DB_FILE_PREV + std::to_string(file_index);
    return file_name;
}
