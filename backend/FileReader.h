#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <fstream>

class FileReader{
    private :
		std::string file_name;
		std::ifstream file;
	public :
        bool set_file(std::string f_n);
        std::string get_data();
        std::string get_line();
};

#endif
