#include<iostream>
#include<cstdlib>
#include<vector>

#include"config.h"
#include"package_config.h"
#include"global.h"
#include"build_routine.h"


int main(int argc, char *argv[])
{
    Config::init();
    Package_Config *ubuild = new Package_Config;
    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            *ubuild = read_package((Config::get_ubuild_path() + argv[i] + ".ubuild").c_str());
            run(*ubuild);
        }
    }
    
    delete ubuild;
    return 0;
}
