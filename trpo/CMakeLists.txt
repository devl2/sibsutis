cmake_minimum_required(VERSION 3.10)
project(ahinea)

set(CMAKE_CXX_STANDARD 20)

set(SFML_STATIC_LIBRARIES FALSE)
set(BUILD_SHARED_LIBS TRUE)

file(GLOB SOURCES "app/game/*.cpp")

# Добавление исполняемого файла основного приложения
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include external/SFML/include)

# Добавление подкаталогов SFML и GoogleTest
add_subdirectory(external/googletest)
add_subdirectory(external/SFML)

# Подключение библиотек SFML
find_package(SFML-2.6.1 COMPONENTS graphics window system audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system sfml-audio)

# Настройка тестов
enable_testing()
add_executable(quiz_tests test.cpp)
target_link_libraries(quiz_tests gtest gtest_main)
add_test(NAME quiz_tests COMMAND quiz_tests)
