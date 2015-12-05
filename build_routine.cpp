#include<iostream>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<sys/stat.h>

#include"global.h"

#include"search.h"
#include"config.h"
#include"package_config.h"
#include"build_routine.h"

#define MIN(x,y) x < y ? x : y
#define MAX(x,y) x > y ? x : y

bool run(Package_Config package)
{
    std::string tarball_dir = Config::get_tarball_path();
    
    std::string tarfile = package.get_archive_name();

    /* +-------------------------------------------------------------------+
     * |The directory we use for package compilation is /tmp/uPackage-build|
     * +-------------------------------------------------------------------+
     */
    std::string build_root = "/usr/data/code/uPackage/temp_dir/package-" + package.get_name() + "-" + package.get_version();
    
    system(("rm -r " + build_root).c_str());

    mkdir("/usr/data/code/uPackage/temp_dir/", S_IWUSR);

    if(mkdir(build_root.c_str(), S_IWUSR) != 0)
    {
        err("Could not create " + build_root, 1);
    }
    
    if(system(("tar xf " + tarball_dir + tarfile + " -C " + build_root).c_str()) != 0)
    {
        err("Could not extract tarball", 1);
    }

    std::string extracted_source = package.get_source(); 
    
    if(chdir((build_root + "/" + extracted_source).c_str()) != 0)
    {
        err("Cannot cd into " + build_root + extracted_source, 1);
    }

    if(package.get_preinstall().length() > 0)
    {
        if(system(package.get_preinstall().c_str()) != 0)
        {
            err("Pre-install failed", 1);
        }
    }
    if(package.get_configure().length() > 0)
    {
        if(system((
                        // /usr
                        "./configure --prefix=" + Config::get_prefix() \
                        
                        // /usr/man
                        + " " + "--mandir=" + Config::get_manpath() \
                        
                        // /usr/doc/ + name + version
                        + " " + "--docdir=" + Config::get_docpath() + "/" \
                        + package.get_name() + "-" + package.get_version() \
                        
                        // x86_64-slackware-linux
                        + " " + "--build=" + Config::get_arch() + "-slackware-linux" \
                        + " " + package.get_configure()
                        
                        ).c_str()) != 0)
        {
            err("configure " + package.get_configure(), 1);
        }
    }
    else
    {
        if(system((
                        // /usr
                        "./configure --prefix=" + Config::get_prefix() \

                        // /usr/man
                        + " " + "--mandir=" + Config::get_manpath() \
                        
                        // /usr/doc/ + name + version
                        + " " + "--docdir=" + Config::get_docpath() + "/" \
                        + package.get_name() + "-" + package.get_version() \
                        
                        // x86_64-slackware-linux
                        + " " + "--build=" + Config::get_arch() + "-slackware-linux"

                        ).c_str()) != 0)
        {
            err("configure", 1);
        }
    }

    if(package.get_make().length() > 0)
    {
        if(system(("make " + package.get_make()).c_str()) != 0)
        {
            err("make failed", 1);
        }
    }
    else
    {
        if(system("make") != 0)
        {
            err("make failed", 1);
        }
    }

    return 1;
}
