#ifndef __UTILS_H__
#define __UTILS_H__

#include <string>

class Utils
{
public:
    static std::string Itoa(int i, int rdx = 10);
    static BYTE* ReadElfFile(const char *path);
};

#endif