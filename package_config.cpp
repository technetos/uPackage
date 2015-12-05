#include<iostream>
#include<cstring>
#include<vector>

#include"global.h"
#include"package_config.h"

Package_Config read_package(std::string packagefile)
{
    Package_Config package;

    // Read in a ubuild
    std::vector<std::string> file = read(packagefile);
    
    if(file.size() <= 0)
    {
        return package;
    }
    
    std::vector<int> line;
    std::vector<int> pos;

    for(int i=0; i < file.size(); i++)
    {
        // find a comment, do nothing
        file[i] = file[i].substr(0, file[i].find_first_of("#"));

        if(file[i].find_first_of(":") + 1 > 0)
        {
            pos.push_back(file[i].find_first_of(":"));
            
            line.push_back(i);
        }
    }

    std::string key;
    std::string value;

    line.push_back(file.size());

    for(int i = 0; i < pos.size(); i++)
    {
        key = file[line[i]].substr(0, pos[i]);
        value = file[line[i]].substr(pos[i] + 1);
        for(int j = line[i] + 1; j < line[i + 1]; j++)
        {
            if(file[j].length() > 0)
            {
                value = value + "\n" + file[j];
            }
        }
        if(!strcmp(key.c_str(), "name"))
        {
            package.set_name(value);
        }
        if(!strcmp(key.c_str(), "version"))
        {
            package.set_version(value);
        }
        if(!strcmp(key.c_str(), "configure"))
        {
            package.set_configure(value);
        }
        if(!strcmp(key.c_str(), "make"))
        {
            package.set_make(value);
        }
        if(!strcmp(key.c_str(), "make_install"))
        {
            package.set_make_install(value);
        }
        if(!strcmp(key.c_str(), "archive_name"))
        {
            package.set_archive_name(value);
        }
        if(!strcmp(key.c_str(), "source"))
        {
            package.set_source(value);
        }
        if(!strcmp(key.c_str(), "preinstall"))
        {
            package.set_preinstall(value);
        }
        if(!strcmp(key.c_str(), "postinstall"))
        {
            package.set_postinstall(value);
        }
    }
    return package;
}
