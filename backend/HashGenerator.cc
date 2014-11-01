#include "Hash.h"
#include "HashGenerator.h"

#include <iostream>
#include <fstream>

void HashGenerator::generateIntegrityFile(std::string inputFileName, std::string outputFileName){
    FileReader * myfilereader = new FileReader();
    if(myfilereader->set_file(inputFileName.c_str())){
        std::string stringOfinputFile = myfilereader->get_data();

        Hash *h1, *h2;
        h1 = new Hash_md5(stringOfinputFile);
        h2 = new Hash_sha1(stringOfinputFile);

        std::ofstream outputFile (outputFileName.c_str());

        outputFile<<".IntregityFile of : "<<inputFileName<<std::endl<<std::endl;
        outputFile<<"Hashes are "<<std::endl;
        outputFile<<h1->get_hash_type()<<" : "<<h1->get_hash_value()<<std::endl;
        outputFile<<h2->get_hash_type()<<" : "<<h2->get_hash_value()<<std::endl;

        outputFile.close();
    }else{
        return;
    }
}
