#ifndef __PACKAGE_CONFIG_H
#define __PACKAGE_CONFIG_H

#include<vector>

class Package_Config
{
    private:
        // The name of the package
        std::string name;

        // The version of the package
        std::string version;

        // The patches to be applied
        std::vector<std::string> patches;

        // The configure options
        std::string configure;

        // The make options
        std::string make;

        // The make install options
        std::string make_install;

        // The name of the archived source
        std::string archive_name;

        // The name of the unarchived source
        std::string source;
    public:
        Package_Config(){};
        ~Package_Config(){};

        std::string get_name() const
        {
            return name;
        }

        std::string get_version() const
        {
            return version;
        }

        std::vector<std::string> get_patches()
        {
            return patches;
        }

        std::string get_configure() const
        {
            return configure;
        }

        std::string get_make() const
        {
            return make;
        }

        std::string get_make_install() const
        {
            return make_install;
        }

        std::string get_archive_name() const
        {
            return archive_name;
        }

        std::string get_source() const
        {
            return source;
        }

        void set_name(const std::string s)
        {
            name = s;
        }

        void set_version(const std::string s)
        {
            version = s;
        }

        void set_patches(const std::vector<std::string> vs)
        {
            patches = vs;
        }

        void set_configure(const std::string s)
        {
            configure = s;
        }

        void set_make(const std::string s)
        {
            make = s;
        }

        void set_make_install(const std::string s)
        {
            make_install = s;
        }

        void set_archive_name(const std::string s)
        {
            archive_name = s;
        }

        void set_source(const std::string s)
        {
            source = s;
        }
};

Package_Config read_package(std::string);
#endif

