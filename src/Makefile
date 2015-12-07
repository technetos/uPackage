all: upackage

upackage: main
	g++ *.o

main: config.o global.o package_config.o build_routine.o
	g++ -c main.cpp

config: global.o
	g++ -c config.cpp

global:
	g++ -c global.cpp

build_routine: config.o package_config.o global.o
	g++ -c build_routine.cpp

package_config: global.o
	g++ -c package_config.cpp

clean:
	rm *.o a.out
