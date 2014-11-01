#ifndef HASH_GENERATOR_H
#define HASH_GENERATOR_H

#include "Hash.h"
#include <string>

class HashGenerator{
	public :
		static void generateIntegrityFile(std::string inputFileName, std::string outputFileName);
};

#endif
