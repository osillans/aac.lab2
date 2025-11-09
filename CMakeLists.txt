cmake_minimum_required(VERSION 3.10)
project(StringSearchAlgorithms LANGUAGES CXX)

# Використовуємо стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Додаємо попередження компілятора
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Основна програма
add_executable(main_program
    main.cpp
)

# Юніт-тести
add_executable(unit_tests
    tests.cpp
    main.cpp   # підключаємо main.cpp
)

set_target_properties(main_program PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set_target_properties(unit_tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)