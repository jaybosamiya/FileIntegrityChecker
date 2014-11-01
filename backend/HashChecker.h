#ifndef HASH_CHECKER_H
#define HASH_CHECKER_H

#include "HashGenerator.h"
#include <string>

class HashChecker{
	public :
		static bool check(std::string original_file, std::string hash_from_hashgenerator);
};

#endif
