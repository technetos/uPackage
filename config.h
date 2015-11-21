#ifndef _CONFIG_H
#define _CONFIG_H

class Config
{
    private:
        /* +-------------------------------------+
         * |The top level directory for upackage |
         * +-------------------------------------+
         */
        static std::string upackage_root;
        
        /* +-------------------------------------------+
         * |The directory for the build files (ubuilds)|
         * +-------------------------------------------+
         */
        static std::string ubuild_path;

        /* +------------------------------------------------+
         * |The directory that we put our source tarballs in|
         * +------------------------------------------------+
         */
        static std::string tarball_path;
        
        /* +-----------------------------------------------------------------+
         * |The directory that the sources in 'tarball_path' are extracted to|
         * +-----------------------------------------------------------------+
         */
        static std::string source_path;
        
        /* +-------------------------------------------------------+
         * |The directory that we use for storing the tracker files|
         * +-------------------------------------------------------+
         */
        static std::string tracker_path;
        
        /* +------------------+
         * |The compiler flags|
         * +------------------+
         */
        static std::string cflags;
        static std::string cxxflags;
    public:
        /* +--------------+
         * |Public Getters|
         * +--------------+
         */
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
        static std::string get_source_path()
        {
            return source_path;
        }
        static std::string get_tracker_path()
        {
            return tracker_path;
        }
        static std::string get_cflags()
        {
            return cflags;
        }
        static std::string get_cxxflags()
        {
            return cxxflags;
        }
        /* +--------------------------------------------------------------+
         * |The init function is used to setup the inital config variables|
         * +--------------------------------------------------------------+
         */
        static void init();
};
#endif
