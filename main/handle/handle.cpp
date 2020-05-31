
#include "handle.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>


bool Handle::set_key(const char * key, const char * value){
    //append only -- hdd write friendly
    this->outfile_stream << key << "=" << value <<"\n";
    this->outfile_stream.flush();
    return true;
}

std::string Handle::get_key(const char * search_key){
    std::string line;
    this->infile_stream.clear();
    this->infile_stream.seekg(0, std::ios::beg);

    std::string result = "";
    while(this->infile_stream.good() && !this->infile_stream.eof()){
        getline(this->infile_stream, line);

        std::vector<std::string> results;
        boost::split(results, line, boost::is_any_of("="));
        if(results[0].compare(search_key)==0){
            result = results[1];
        }
    }

    return result;
}


