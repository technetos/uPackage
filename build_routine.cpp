#include<iostream>
#include<cstdlib>
#include<cstring>
#include<unistd.h>
#include<sys/stat.h>

#include"global.h"
#include"config.h"
#include"package_config.h"
#include"build_routine.h"

bool run(Package_Config package)
{
    // The directory containing the tarball'd source
    std::string tarball_dir = Config::get_tarball_path();
    
    // The name of the source archive
    std::string tarfile = package.get_archive_name();
    
    // The directory we use for package compilation is /tmp/uPackage-build
    std::string build_root = "/tmp/uPackage-build/";
    
    // Remove the existing build root
    system(("rm -r " + build_root).c_str());
    
    // Create a new build root
    if(mkdir(build_root.c_str(), S_IWUSR) != 0)
    {
        err("Could not create " + build_root, 1);
    }
    // Extract the archive into the build root
    if(system(("tar xf " + tarball_dir + tarfile + " -C " + build_root).c_str()) != 0)
    {
        err("Could not extract tarball", 1);
    }
    // Cd into the extracted source
    if(chdir((build_root + "/" + package.get_source()).c_str()) != 0)
    {
        err("Cannot cd into " + build_root + package.get_source(), 1);
    }
    // Fix the permissions on the package files
    if(system((Config::get_script_path() + "fix_perms.sh").c_str()) != 0)
    {
        err("could not fix package permissions", 1);
    }

    // CONFIGURE
    //-------------------------------------------------------------------------------
    // If the user defined a configure param, run the normal configure + the user defined param
    if(package.get_configure().length() > 0)
    {
        if(system(("./configure --prefix=" + Config::get_prefix() \
                        + " " \
                        + "--mandir=" + Config::get_man_path() \
                        + " " \
                        + "--docdir=" + Config::get_doc_path() + "/" \
                        + package.get_name() \
                        + "-" \
                        + package.get_version() \
                        + " " \
                        + "--build=" + Config::get_arch() + "-slackware-linux" \
                        + " " \
                        + package.get_configure()).c_str()) != 0)
        {
            err("configure failed" + package.get_configure(), 1);
        }
    } 
    else
    {
        // Otherwise run the normal configure command
        if(system(("./configure --prefix=" + Config::get_prefix() \
                        + " " \
                        + "--mandir=" + Config::get_man_path() \
                        + " " \
                        + "--docdir=" + Config::get_doc_path() + "/" \
                        + package.get_name() \
                        + "-" \
                        + package.get_version() \
                        + " " \
                        + "--build=" + Config::get_arch() + "-slackware-linux").c_str()) != 0)
        {
            err("configure failed", 1);
        }
    }

    // MAKE
    // ------------------------------------------------------------------------------
    // If the user defined a make param run make + the user defined param
    if(package.get_make().length() > 0)
    {
        if(system(("make " + package.get_make()).c_str()) != 0)
        {
            err("make failed", 1);
        }
    }
    else
    {
        // Otherwise we just run make
        if(system("make") != 0)
        {
            err("make failed", 1);
        }
    }

    // MAKE INSTALL
    // ------------------------------------------------------------------------------
    // If the user defined a make install param run make install + the user defined param
    if(package.get_make_install().length() > 0)
    {
        if(system(("make install DESTDIR=" + package.get_make_install()).c_str()) != 0)
        {
            err("make install DESTDIR=" + package.get_make_install() + " failed.", 1);
        }
    }
    else
    {
        // Otherwise we install into the default temp location
        if(system(("make install DESTDIR=" \
                        + build_root \
                        + "package-" + package.get_name() \
                        + "-" \
                        + package.get_version()).c_str()) != 0)
        {
            err("make install DESTDIR=" \
                    + build_root \
                    + "package-" + package.get_name() \
                    + "-" \
                    + package.get_version() \
                    + " failed.", 1);
        }
    }
    // ------------------------------------------------------------------------------
    // Fix and organize the man pages
    if(system((Config::get_script_path() \
                    // This is the script we are running
                    + "fix_man.sh" \
                    + " " + \
                    
                    // This is the first arg
                    (build_root \
                     + "package-" \
                     + package.get_name() \
                     + "-" \
                     + package.get_version()).c_str()
                    
                    // The space between arg1 and arg2
                    + " " + \
                    
                    // This is the second arg
                    (build_root \
                     + "package-" \
                     + package.get_name() \
                     + "-" \
                     + package.get_version() \
                     + Config::get_man_path()).c_str()).c_str()) != 0)
    {
        err("could not fix man pages.", 1);
    }
/*
    if(chdir((build_root + "/package-" + package.get_name() + "-" + package.get_version()).c_str()) != 0)
    {
        err("could not cd into package directory", 1);
    }
    
    if(system(("makepkg -l y -c n /tmp/" \
                    + package.get_name() \
                    + "-" \
                    + package.get_version() \
                    + Config::get_arch() \
                    + ".tgz").c_str()) != 0)
    {
        err("makepkg failed", 1);
    }*/
    return 1;
}
