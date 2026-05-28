set(PROJECT_NAME CustomString)

# main executable
set(SOURCE_FILES 
    CustomString/String.cpp CustomString/String.h
)

add_executable(${PROJECT_NAME} CustomString/main.cpp)

add_library(${PROJECT_NAME}Lib ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}Lib)

# tests
add_executable(${PROJECT_NAME}TestRunner Tests/StringTests.cpp)
target_link_libraries(${PROJECT_NAME}TestRunner PRIVATE ${PROJECT_NAME}Lib)
target_include_directories(${PROJECT_NAME}TestRunner PRIVATE ${doctest_SOURCE_DIR})

enable_testing()
add_test(NAME StringTests COMMAND ${PROJECT_NAME}TestRunner)

# some properties
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER String)
set_target_properties(${PROJECT_NAME}Lib PROPERTIES FOLDER String)