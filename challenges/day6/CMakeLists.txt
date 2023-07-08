configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt
               ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(Day6 main.cpp)
target_link_libraries(Day6 PRIVATE Boost::headers Boost::filesystem
                                   Boost::system)
