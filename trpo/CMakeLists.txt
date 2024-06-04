# Подключение Google Test
add_subdirectory(app/googletest-main) # Путь к каталогу с Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Создание исполняемого файла для тестов
add_executable(quiz test.cpp)

# Целевые библиотеки для тестов
target_link_libraries(quiz gtest gtest_main)