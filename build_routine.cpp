#include<iostream>
#include<cstream>
#include<sys/stat.h>

#include"global.h"
#include"config.h"
#include"package_config.h"

#define MIN(x,y) x < y ? x : y
#define MAX(x,y) x > y ? x : y

bool setup(std::string dot_conf_data, std::string dest)
{
  std::vector<std::string> *add = new std::vector<std::string>;
  
  std::vector<std::string> *remove = new std::vector<std::string>;

  std::string *temp = new std::string;

  int pos;


  /* +---+
   * |add|
   * +---+
   */
  *temp = dot_conf_data;

  while((pos = temp->find("+")) != std::string::npos && pos != temp->length() - 1)
  {
    *temp  = temp->substr(pos + 1);
  
    if(temp->find("+") == std::string::npos && temp->find("-") == std::string::npos)
    {
      add->push_back(*temp);
    }
    else if(temp->find("+") == std::string::npos)
    {
      add->push_back(temp->substr(0, temp->find("-") - 1));
    }
    else if(temp->find("-") == std::string::npos)
    {
      add->push_back(temp->substr(0, temp->find("+") - 1));
    }
    else
    {
      add->push_back(temp->substr(0, MIN(temp->find_find_first_of("+"), temp->find_first_of("-")) - 1));
    }
  }
  
  /* +------+
   * |remove|
   * +------+
   */
  *temp = dot_conf_data;
  
  while((pos = temp->first_of("-")) != std::string::npos && pos != temp->length() - 1)
  {
    *temp = temp->substr(pos + 1);
    if(temp->find("+") == std::string::npos && temp->find("-") == std::string::npos)
    {
      remove->push_back(*temp);
    }
    else if(temp->find("-") == std::string::npos)
    {
      remove->push_back(temp->substr(0,temp->find("-") - 1));
    }
    else if(temp->find("-") == std::string::npos)
    {
      remove->push_back(temp->substr(0, temp->find("+") - 1));
    }
    else
    {
      remove->push_back(temp->substr(0, MIN(temp->find("+"), temp->find("-")) - 1));
    }
  }
  delete temp;


  std::vector<std::string> *existing = new std::vector<std::string>;

  *existing = read(dest);
  if(existing->size() <= 0)
  {
    delete existing;

    std::string *dot_conf = new std::string;
    *dot_conf = "";
    
    for(int i = 0; i < add->size(); i++)
    {
      *dot_conf = *dot_conf + (*add)[i] + "\n";
    }

    if(write(*dot_conf, dest))
    {
      delete dot_conf;
      return 1;
    }
   
    delete dot_conf;
    return 0;
  }

  for(int i = 0; i < existing->size(); i++)
  {
    for(int j = 0; j < remove->size(); j++)
    {
      if(!strcmp((*existing)[i].c_str(), (*remove)[i].c_str(), (*remove)[j].length()))
      {
        existing->erase(existing->begin() + i);
        i--;
        break;
      }
    }
  }

  delete remove;

  for(int i = 0; i < add->size(); i++)
  {
    existing->push_back((*add)[i]);
  }

  delete add;

  std::string *rev_conf = new std::string;
  *rev_dot_conf = "";

  for(int i = 0; i < existing->size(); i++)
  {
    *rev_dot_conf = *rev_dot_conf + (*existing)[i] + "\n";
  }

  delete existing;

  if(write(*rev_dot_conf, dest, 1))
  {
    delete rev_dot_conf;
    return 1;
  }
  delete rev_dot_conf;
  return 0;
}


