#ifndef HASH_H
#define HASH_H

#include <string>
#include "md5.h"
#include "sha1.h"
#include "FileReader.h"

class Hash{
    protected:
        const std::string hash_type;
        std::string hash_value;
        Hash(std::string ht) : hash_type(ht) {}
    public:
        std::string get_hash_type();
        std::string get_hash_value();
        virtual std::string hash(std::string data) = 0;
};

class Hash_md5 : public Hash{
	public :
	Hash_md5(std::string s) : Hash("md5"){hash_value = hash(s);}
	std::string hash(std::string data){return md5(data);}
};

class Hash_sha1 : public Hash{
	public :
	Hash_sha1(std::string s) : Hash("sha1") {hash_value = hash(s);}
	std::string hash(std::string data){return sha1(data);}
};

#endif
