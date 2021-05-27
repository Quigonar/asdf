cmake_minimum_required(VERSION 3.17)
project(GeneticPuzzle)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Piece.h Node.h Matrix.h List.h UtilityProgram.h MatrixNode.h GeneticAlgorithm.h servidor.cpp xmlParser.h)
#add_executable(GeneticPuzzle ${SOURCE_FILES})

set(EXECUTABLE_NAME "GeneticPuzzle")
set(EXECUTABLE_NAME2 "Server")
set(EXECUTABLE_NAME3 "Test")
add_executable(${EXECUTABLE_NAME} main.cpp)
add_executable(${EXECUTABLE_NAME2} servidor.cpp)
add_executable(${EXECUTABLE_NAME3} test.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    target_link_libraries(${EXECUTABLE_NAME2} ${SFML_LIBRARIES})
endif()

find_package(TinyXML)
if(TinyXML_FOUND)
    set(WITH_TINYXML TRUE)
    include_directories(${TinyXML_INCLUDE_DIRS})
    target_link_libraries(${EXECUTABLE_NAME2} ${TinyXML_LIBRARIES})
endif()



