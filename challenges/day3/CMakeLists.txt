configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(Day3 main.cpp)
target_link_libraries(Day3 
    PRIVATE Boost::headers Boost::filesystem Boost::system)