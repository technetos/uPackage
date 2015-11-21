#include<cstdlib>
#include<cstring>
#include<fstream>
#include<vector>

#include"global.h"
#include"config.h"

std::string Config::upackage_root;
std::string Config::ubuild_path;
std::string Config::tarball_path;
std::string Config::source_path;
std::string Config::tracker_path;
std::string Config::cflags;
std::string Config::cxxflags;

void Config::init()
{
    upackage_root = "/var/upackage";
    
    /* +--------------------------------------------+
     * |Here we are checking to see if the user has |
     * |set the UPACKAGE_ROOT environment variable  |
     * |and if the value set is not ""              |
     * +--------------------------------------------+
     */
    if(getenv("UPACKAGE_ROOT") && strcmp(getenv("UPACKAGE_ROOT"), ""))
    {
        std::string env(getenv("UPACKAGE_ROOT"));
        
        /* +-----------------------------------------+
         * |Check to see if the user set environment |
         * |variable is correctly terminated by a '/'|
         * +-----------------------------------------+
         */
        if(env[env.size() - 1] == '/')
        {
            upackage_root = env;
        }
        else
        {
            /* +----------------------------------------------+
             * |The environment variable must not be correctly|
             * |terminated, lets fix that and move on.        |
             * +----------------------------------------------+
             */t
            upackage_root = env + "/";
        }
    }

    /* +----------------------------------------------------------+
     * |All of the directories in upackage are under upackage_root|
     * +----------------------------------------------------------+
     */
    /* +-------------------+
     * |These are defaults |
     * +-------------------+
     */
    ubuild_path = upackage_root + "ubuild/";
    tarball_path = upackage_root + "tarballs/";
    source_path = upackage_root + "sources/";
    tracker_path = upackage_root + "packages/";

    cflags = "";
    cxxflags = "";

    /* +--------------------------------------------------+
     * |Now we read in the global config file for upackage|
     * +--------------------------------------------------+
     */
    std::vector<std::string> file = read("/etc/upackage.conf");

    /* +----------------------------------------------------+
     * |If the file size is <= 0 then the file must be empty|
     * +----------------------------------------------------+
     */
    if(file.size() <= 0)
    {
        return;
    }
    
    /* If we are here, then the file size is > 0, now lets parse it */

    /* +------------------------------------------+
     * |An integer vector for storing line numbers|
     * +------------------------------------------+
     */
    std::vector<int> line;
    
    /* +------------------------------------------------------+
     * |An integer vector for storing the position of each ':'|
     * +------------------------------------------------------+
     */
    std::vector<int> pos;
    
    for(int i = 0; i < file.size(); i++)
    {
        /* +---------------------+
         * |Locate all of the ':'|
         * +---------------------+
         */
        if(file[i].find_first_of(":") + 1 > 0)
        {
            /* +----------------------------------------------+
             * |Store the position and line number of each ':'|
             * +----------------------------------------------+
             */
            pos.push_back(file[i].find_first_of(":"));
            line.push_back(i);
        }
    }
    
    /* +--------------------------------------------+
     * |A string for storing the data before the ':'|
     * +--------------------------------------------+
     */
    std::string key;
    
    /* +-------------------------------------------+
     * |A string for storing the data after the ':'|
     * +-------------------------------------------+
     */
    std::string value;

    line.push_back(file.size());

    for(int i = 0; i < pos.size(); i++)
    {
        /* +----------------------------------+
         * |The key is the data before the ':'|
         * +----------------------------------+
         */
        key = file[line[i]].substr(0, pos[i]);
        
        /* +-----------------------------------+
         * |The value is the data after the ':'|
         * +-----------------------------------+
         */
        value = file[line[i]].substr(pos[i] + 1);

        for(int j = line[i] + 1; j < line[i + 1]; j++)
        {
            if(file[j].length() > 0)
            {
                value = value + "\n" + file[j];
            }
        }
        if(!strcmp(key.c_str(), "CFLAGS")
                || !strcmp(key.c_str(), "cflags"))
        {
            cflags = value;
        }
        if(!strcmp(key.c_str(), "CXXFLAGS")
                || !strcmp(key.c_str(), "cxxflags"))
        {
            cxxflags = value;
        }
    }
}
