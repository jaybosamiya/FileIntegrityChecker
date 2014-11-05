#include "HashChecker.h"

#include <iostream>
#include <fstream>


bool HashChecker::check(std::string original_file, std::string hash_from_hashgenerator){
    std::string line;
    FileReader * myfilereader = new FileReader();
    if(myfilereader->set_file(original_file.c_str())){
        std::string file_string, old_md5_hash, old_sha1_hash, new_md5_hash, new_sha1_hash;

        file_string = myfilereader->get_data();

        //calculating new hashes
        new_md5_hash = "md5 " + md5(file_string);
        new_sha1_hash = "sha1 " + sha1(file_string);

        myfilereader->set_file(hash_from_hashgenerator.c_str());
        //Ignore first line (MAGIC VALUE of .integrity format)
        myfilereader->get_line();

        //getting hashes from integretity file
        old_md5_hash = myfilereader->get_line();
        old_sha1_hash = myfilereader->get_line();

        return old_md5_hash == new_md5_hash && old_sha1_hash == new_sha1_hash;
    }
    return false;
}
