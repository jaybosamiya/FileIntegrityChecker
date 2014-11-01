#include "FileReader.h"
#include <iostream>

#define IOS std::ios

bool FileReader::set_file(std::string f_n){
    file_name = f_n;
    file.open(file_name.c_str(), IOS::binary);
    return file!=NULL;
}
std::string FileReader::get_data(){
    std::string data;
    std::string line;
    if (file.is_open()){
        while(getline(file,line) ){
          data += line;
        }
    file.close();
    }
    return data;
}
std::string FileReader::get_line(){
    std::string line;
    if(file.is_open()) getline(file,line);
    return line;
}
