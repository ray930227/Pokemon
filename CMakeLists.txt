cmake_minimum_required(VERSION 3.16)
project(Pokemon)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(PTSD)
add_library(Framework ${PTSD_SRC_FILES} $<TARGET_OBJECTS:PracticalToolsForSimpleDesign>)

include(files.cmake)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
list(TRANSFORM SRC_FILES PREPEND ${SRC_DIR}/)
list(TRANSFORM INCLUDE_FILES PREPEND ${INCLUDE_DIR}/)

# file(GLOB_RECURSE SRC_FILES src/*)
# file(GLOB_RECURSE HEADER_FILES include/*)

add_executable(${PROJECT_NAME}
    ${SRC_DIR}/main.cpp
    ${SRC_FILES}
    ${HEADER_FILES}
    include/PokemonBag.hpp
    src/PokemonBag.cpp
    include/EventManager.hpp
    src/EventManager.cpp
    include/UI/EvolutionUI.hpp
    include/UI/FightSkillUI.hpp
    include/UI/LoadingUI.hpp
    include/UI/PokeBagUI.hpp
    src/UI/EvolutionUI.cpp
    src/UI/FightSkillUI.cpp
    src/UI/LoadingUI.cpp
    src/UI/PokeBagUI.cpp
    include/TFBox.hpp
    src/TFBox.cpp
    include/ItemBag.hpp
    src/ItemBag.cpp
    include/UI/FightMainUI.hpp
    src/UI/FightMainUI.cpp
    include/UI/ShopUI.hpp
    src/UI/ShopUI.cpp
    include/UI/ReplaceSkillUI.hpp
    src/UI/ReplaceSkillUI.cpp
    include/UI/FightTextUI.hpp
    src/UI/FightTextUI.cpp
    include/SFXSystem.hpp
    src/SFXSystem.cpp
    src/UI/PokeFaintedUI.cpp
    include/UI/PokeFaintedUI.hpp
    include/UI/SettingUI.hpp
    src/UI/SettingUI.cpp
    include/UI/ComputerUI.hpp
    src/UI/ComputerUI.cpp
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Resources")
else()
    message(FATAL_ERROR "relative RESOURCE_DIR is WIP, Please use `-DCMAKE_BUILD_TYPE=Debug` build for now.")
    # target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_DIR="${CMAKE_INSTALL_PREFIX}/Resources")
endif()

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${DEPENDENCY_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/PTSD/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(Framework
    ${DEPENDENCY_LINK_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2main
    Framework
)
