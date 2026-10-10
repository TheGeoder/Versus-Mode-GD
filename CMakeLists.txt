cmake_minimum_required(VERSION 3.25)

# 1. Initialize the project (Make sure this matches your mod.json name)
project(MyMobileMod)

# 2. Tell CMake to use the Geode SDK
find_package(Geode REQUIRED)

# 3. Add your C++ source file
add_geode_mod(
    ${PROJECT_NAME}
    SOURCES
        main.cpp
)

# 4. (Optional) If you have any image sprites/assets, uncomment the line below:
# setup_geode_mod(${PROJECT_NAME})
