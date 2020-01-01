## Project Properties
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(concurrencyTests)

SET(APPLICATION_NAME "concurrencyTests")
SET(APPLICATION_VERSION_STRING 0.1)

## Project Output Paths
SET(MAINFOLDER ${PROJECT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/../build/bin")

## Project Search Paths
LIST(APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
SET(CMAKE_MODULE_PATH "${MAINFOLDER}/cmake")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

INCLUDE_DIRECTORIES("${MAINFOLDER}/thirdParty/catch") #catch.hpp

## example project Sources
FILE(GLOB_RECURSE EXAMPLE_SRCS01 ${MAINFOLDER}/experiments/01BasicBenchmarks.cpp ${MAINFOLDER}/experiments/basicBenchmarks/*.cpp )
FILE(GLOB_RECURSE EXAMPLE_SRCS02 ${MAINFOLDER}/experiments/02BasicBenchmarks.cpp ${MAINFOLDER}/experiments/tsPatternBookBenchmarks/*.cpp )
FILE(GLOB_RECURSE EXAMPLE_SRCS03 ${MAINFOLDER}/experiments/03FalseSharingTest.cpp )
FILE(GLOB_RECURSE EXAMPLE_SRCS04 ${MAINFOLDER}/experiments/04NoFalseSharingTest.cpp )
FILE(GLOB_RECURSE EXAMPLE_SRCS05 ${MAINFOLDER}/experiments/05CacheLinePingPong.cpp )
FILE(GLOB_RECURSE EXAMPLE_SRCS06 ${MAINFOLDER}/experiments/06NoCacheLinePingPong.cpp )
FILE(GLOB_RECURSE EXAMPLE_SRCS07 ${MAINFOLDER}/experiments/07exceptions.cpp ${MAINFOLDER}/experiments/exceptions/*.cpp )
## Project Dependencies

## Use compiler debugging flags per default
INCLUDE(CxxFlags)
set(CMAKE_CXX_STANDARD 17)
IF(CMAKE_BUILD_TYPE MATCHES debug)
   message("debug build")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -std=c++1z -g  -pthread")
ELSEIF(CMAKE_BUILD_TYPE MATCHES threadSanitizer)
   message("threadSanitizer build")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -fsanitize=thread -g -O1")
ELSEIF(CMAKE_BUILD_TYPE MATCHES release)
   message("release build")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -std=c++1z -g  -pthread")
ELSE()
   message("release build with march=native")
   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -std=c++1z -g -march=native -pthread")
ENDIF()



set(BUILD_TESTING true CACHE BOOL "Enable building of tests.")

## Creating Binaries for examples
SET(PROJECT_LIBS ${CMAKE_DL_LIBS} )

SET(EXAMPLE1_NAME "01BasicBenchmarks")
SET(EXAMPLE1_BIN ${EXAMPLE1_NAME})
ADD_EXECUTABLE(${EXAMPLE1_BIN} ${MAINFOLDER}/experiments/01BasicBenchmarks.cpp ${EXAMPLE_SRCS01})

SET(EXAMPLE2_NAME "02BasicBenchmarks")
SET(EXAMPLE2_BIN ${EXAMPLE2_NAME})
ADD_EXECUTABLE(${EXAMPLE2_BIN} ${MAINFOLDER}/experiments/02tsPatternBookBenchmarks.cpp ${EXAMPLE_SRCS02})

SET(EXAMPLE3_NAME "03FalseSharingTest")
SET(EXAMPLE3_BIN ${EXAMPLE3_NAME})
ADD_EXECUTABLE(${EXAMPLE3_BIN} ${MAINFOLDER}/experiments/03FalseSharingTest.cpp ${EXAMPLE_SRCS03})

SET(EXAMPLE4_NAME "04NoFalseSharingTest")
SET(EXAMPLE4_BIN ${EXAMPLE4_NAME})
ADD_EXECUTABLE(${EXAMPLE4_BIN} ${MAINFOLDER}/experiments/04NoFalseSharingTest.cpp ${EXAMPLE_SRCS04})

SET(EXAMPLE5_NAME "05CacheLinePingPong")
SET(EXAMPLE5_BIN ${EXAMPLE5_NAME})
ADD_EXECUTABLE(${EXAMPLE5_BIN} ${MAINFOLDER}/experiments/05CacheLinePingPong.cpp ${EXAMPLE_SRCS05})

SET(EXAMPLE6_NAME "06NoCacheLinePingPong")
SET(EXAMPLE6_BIN ${EXAMPLE6_NAME})
ADD_EXECUTABLE(${EXAMPLE6_BIN} ${MAINFOLDER}/experiments/06NoCacheLinePingPong.cpp ${EXAMPLE_SRCS06})

SET(EXAMPLE7_NAME "07exceptions")
SET(EXAMPLE7_BIN ${EXAMPLE7_NAME})
ADD_EXECUTABLE(${EXAMPLE7_BIN} ${MAINFOLDER}/experiments/07exceptions.cpp ${EXAMPLE_SRCS07})

TARGET_LINK_LIBRARIES(${EXAMPLE1_BIN} ${PROJECT_LIBS})
TARGET_LINK_LIBRARIES(${EXAMPLE2_BIN} ${PROJECT_LIBS})
TARGET_LINK_LIBRARIES(${EXAMPLE3_BIN} ${PROJECT_LIBS})
TARGET_LINK_LIBRARIES(${EXAMPLE4_BIN} ${PROJECT_LIBS})
TARGET_LINK_LIBRARIES(${EXAMPLE5_BIN} ${PROJECT_LIBS})
TARGET_LINK_LIBRARIES(${EXAMPLE6_BIN} ${PROJECT_LIBS})
TARGET_LINK_LIBRARIES(${EXAMPLE7_BIN} ${PROJECT_LIBS})
INSTALL(TARGETS ${EXAMPLE_BIN} DESTINATION bin)


macro(create_test TARGET_NAME SOURCE DEPENDENCIES)
    add_executable(${TARGET_NAME} ${SOURCE})
    target_link_libraries(
        ${TARGET_NAME}
        ${DEPENDENCIES}
        catchMain
        )
endmacro()

if (BUILD_TESTING)
    ADD_LIBRARY(catchMain ./unitTests/00CatchMain.cpp)
    enable_testing()
    create_test(unitTestsBook ./unitTests/unitTestsBook.cpp ${PROJECT_LIBS})
    create_test(unitTests ./unitTests/unitTests.cpp ${PROJECT_LIBS})
endif (BUILD_TESTING)
