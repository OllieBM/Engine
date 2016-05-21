I recomment using CMake to build the project files

$ cmake -H path/to/build/ -B path/to/where/you/want/binarys
 example: running from the root folder contining build,include and source run:
 $ cmake -Hbuild/ -Bbin/
 and the projcet files will be built in a new /bin folder
