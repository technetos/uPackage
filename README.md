# uPackage - Pronounced ("ooopackage")
---------

### uPackage is a general purpose package manager for linux.  

# The Problem

>   The linux distribution I favor the most is called Slackware.  Its old, minimal,
and rock soid.  The SlackWare package manager is called slackpkg.  Slackpkg
is written mostly in bash and handles the slackware package base very well.  To that
end, slackpkg is a good package manager.  

__**Where slackpkg falls short is when you dont have a prebuilt package or a SlackBuild.**__

>   SlackBuilds are bash scripts that use other extra files and a source tarball to build a
package.  If you dont have a precreated SlackBuild from slackbuilds.org or somewhere else
then you have to write one yourself.  

__**To install a package that is not prepackaged you have to write a small program.**__

>   That sucks!  It takes alot of time to write a package, time that could be spent using
the software your trying so hard to install.  

__*uPackage solves these problems and more*__
# Data Design

>   uPackage defines the following directories underneath a main root directory:

>   The man root directory path is defined as /opt/upackage by default.  The
environment variable UPACKAGE_ROOT is used to change where the root path is defined.

##### ubuild/

>   This directory is for the ubuild files that dictate how a package should
be compiled.  

##### tarballs/

>   This directory is for the archived sources for packages that are going to
be built.  

##### packages/

>   This is where the package tracking files go.  Each file contains the full
path of every file installed by a package.  Each package has one tracking file
and the filename is the name of the package + the version.

##### /tmp/uPackage-build/

>   This is where the source is compiled and the compiled package is placed.  

# Algorithm
>   uPackage is broken up into multiple C++ classes.  Each class uses its own
algorithm during execution.  

#### config

    `config.h` `config.cpp`
    Depends on global
    The config class is used to do initial setup and processing of global (system wide) options.  
#### global

    `global.h` `global.cpp`
    The global functions are basic convience functions to make things easier
#### build routine

    `build_routine.h` `build_routine.cpp`
    Depends on global, config, package_config
    The build_routine function is used orchestrate the configure, make, make install process for a source.  
##### package config

    `package_config.cpp` `package_config.h` 
    Depends on global, config 
    The package_config class is used to parse the ubuild for a package.  

# It doesnt work yet....

>   uPackage will compile a package given a ubuild and a source archive, but thats all so far.  
