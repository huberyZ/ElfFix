#ifndef __ELF_HEADER__
#define __ELF_HEADER__

#include "elf.h"
#include <string>

class CElfHeader
{
public:
    CElfHeader();

    ~CElfHeader();
    
public:
    bool InitHeader(std::string content);

    std::string HeaderInfo();

    int Size(){ return sizeof(Elf32_Ehdr); }

    Elf32_Ehdr GetHeader(){ return elfHeader; };
private:

    bool isValid();

    std::string getElfType(Elf32_Half type);
private:
    Elf32_Ehdr elfHeader;
};
#endif
