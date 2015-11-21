#include<iostream>
#include<cstdlib>
#include<fstream>
#include<sys/stat.h>

#include"global.h"

std::vector<std::string> read(const std::string src)
{
  std::ifstream text_file;
 
  std::vector<std::string> ret;
  
  text_file.open(src.c_str());
  
  std::string text;
  
  if(!text_file)
  {
    return ret;
  }
  while(getline(text_file, text))
  {
    ret.push_back(text);
  }
  text_file.close();
  
  return ret;
}

bool write(const std::string data, const std::string dest, bool overwrite)
{
  std::ofstream text;
  /* +-------------------------------------+
   * | check if we overwite the file or not|
   * +-------------------------------------+
   */
  if(overwrite)
  {
    text.open(dest.c_str(), std::ios::trunc);
  }
  else
  {
    text.open(dest.c_str(), std::ios::app);
  }
  if(!text)
  {
    return 0;
  }
  text << data;
  text.close();
  return 1;
}

