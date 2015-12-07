#ifndef __GLOBAL_H
#define __GLOBAL_H

#include<string>
#include<vector>

// These are global functions
std::vector<std::string> read(const std::string);
bool write(const std::string, const std::string, bool overwrite = 0);
void err(std::string, int level = 0);


#endif
