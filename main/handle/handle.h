//
// Created by peiyulin on 2020/5/30.
//

#ifndef TRACERDB_HANDLE_H
#define TRACERDB_HANDLE_H
#include <string>
#include <fstream>
#include <iostream>

class Handle {
public:
    std::string get_key(const char * search_key);
    bool set_key(const char * search_key, const char * value);


    Handle(const char * table_name) {
        this->table_name = std::string(table_name);
        this->table_file_path = this->default_file_path+"/"+this->table_name+".tdb";
        this->outfile_stream.open(this->table_file_path, std::ios_base::app); // append instead of overwrite
        this->infile_stream.open(this->table_file_path); // append instead of overwrite

        if((!this->outfile_stream.is_open()) || (!this->infile_stream.is_open())){
            std::cout << "Cannot open file " << this->table_file_path << std::endl;
        }
    }

private:
    const std::string default_file_path = "/Users/peiyulin/TracerDB/datafile";
    std::string table_name;
    std::string table_file_path;
    std::ofstream outfile_stream;
    std::ifstream infile_stream;
};


class SetResult {
public:
    bool is_ok;
    char * error_message;
};


#endif //TRACERDB_HANDLE_H