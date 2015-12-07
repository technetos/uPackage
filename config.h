#ifndef _CONFIG_H
#define _CONFIG_H

#include<sys/utsname.h>

#include"global.h"

class Config
{
    private:
        // The top level directory for upackage 
        static std::string upackage_root;
        
        // The directory for the build files (ubuilds)
        static std::string ubuild_path;

        // The directory that we put our source tarballs in
        static std::string tarball_path;
        
        // The directory that we use for storing the tracker files
        static std::string tracker_path;

        // The directory the we put scripts in
        static std::string script_path;

        // The prefix passed to configure
        static std::string prefix;

        // The system wide default man path
        static std::string man_path;

        // The system wide doc path
        static std::string doc_path;

    public:
        // Public Getters
        static std::string get_upackage_root()
        {
            return upackage_root;
        }
        static std::string get_ubuild_path()
        {
            return ubuild_path;
        }
        static std::string get_tarball_path()
        {
            return tarball_path;
        }
        static std::string get_tracker_path()
        {
            return tracker_path;
        }
        static std::string get_script_path()
        {
            return script_path;
        }
        static std::string get_prefix()
        {
            return prefix;
        }
        static std::string get_man_path()
        {
            return man_path;
        }
        static std::string get_doc_path()
        {
            return doc_path;
        }
        static std::string get_arch()
        {
            struct utsname buffer; 

            std::string ret;

            if(uname(&buffer) != 0)
            {
                err("uname", 1);
            }

            ret = buffer.machine;

            return ret;
        }
        // The init function is used to setup the inital config variables
        static void init();
};
#endif
