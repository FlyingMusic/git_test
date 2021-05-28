cmake_minimum_required(VERSION 2.6)

#if(COMMAND ls)
#    MESSAGE(STATUS "ls can be used")
#else()
#    MESSAGE(STATUS "ls can't be used")
#endif()

#if(EXISTS ./CMakeCache2.txt)
#    MESSAGE(STATUS "./CMakeCache.txt is exist")
#else()
#    MESSAGE(STATUS "./CMakeCache.txt is not exist")
#endif()

#SET(VAR "AAA\;BBB\;CCC")
#set(VAR "${VAR}\;DDD\;EEE")
#MESSAGE(STATUS "VAR:${VAR}")

#foreach(v ${VAR})
#    MESSAGE(${v})
#endforeach()

#string(TIMESTAMP CTIME "%Y-%m-%d %H:%M:%S")
#add_definitions(-D_COMPILE_TIME_="${CTIME}")
#MESSAGE(STATUS "Compile Time:${CTIME}")

MESSAGE(STATUS "CMAKE_INSTALL_RPATH:${CMAKE_INSTALL_RPATH}")
MESSAGE(STATUS "CMAKE_INSTALL_PREFIX:${CMAKE_INSTALL_PREFIX}")
