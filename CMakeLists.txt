cmake_minimum_required(VERSION 3.19)
project(ASIO_LEARN)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -march=native -O0")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CMAKE_CXX_FLAGS} -Wall -g -ggdb")

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

include_directories(./include)

set(BOOST_ROOT /usr/local/boost)
set(Boost_NO_SYSTEM_PATHS ON)

##可以在官网上查看依赖
set(BOOST_COMPONENTS date_time chrono program_options regex system thread unit_test_framework)
#set(BOOSt_COMPONENTS regex system REQUIRED)

find_package(Boost 1.79.0 REQUIRED
        COMPONENTS ${BOOST_COMPONENTS})

if(Boost_FOUND)
    MESSAGE(Boost_VERSION)
    MESSAGE(Boost_LIB_VERSION)
endif()

add_executable(main main.cpp)
target_link_libraries(main ${Boost_LIBRARIES})

add_executable(0-1 src/0.基础入门/0-1.cpp)
target_link_libraries(0-1 ${Boost_LIBRARIES})

add_executable(0-2 src/0.基础入门/0-2.cpp)
target_link_libraries(0-2 ${Boost_LIBRARIES} -lpthread)

add_executable(0-3 src/0.基础入门/0-3.cpp)
target_link_libraries(0-3 ${Boost_LIBRARIES} -lpthread)

add_executable(0-4 src/0.基础入门/0-4.cpp)
target_link_libraries(0-4 ${Boost_LIBRARIES} -lpthread)


add_executable(0-5 src/0.基础入门/0-5.cpp)
target_link_libraries(0-4 ${Boost_LIBRARIES} -lpthread)












add_executable(1_timer_syn src/1.基础例子/1_timer_syn.cpp)
target_link_libraries(1_timer_syn ${Boost_LIBRARIES})
add_executable(2_timer_asyn src/1.基础例子/2_timer_asyn.cpp)
target_link_libraries(2_timer_asyn ${Boost_LIBRARIES})

add_executable(3_handler_arg src/1.基础例子/3_handler_arg.cpp)
target_link_libraries(3_handler_arg ${Boost_LIBRARIES})

add_executable(4_func_timer src/1.基础例子/4_func_timer.cpp)
target_link_libraries(4_func_timer ${Boost_LIBRARIES})

add_executable(5_multhread_syn src/1.基础例子/5_multhread_syn.cpp)
target_link_libraries(5_multhread_syn ${Boost_LIBRARIES} -lpthread)

add_executable(1_tcp_datetime src/2.套接字简介/1_tcp_datetime.cpp)
target_link_libraries(1_tcp_datetime ${Boost_LIBRARIES} -lpthread)
