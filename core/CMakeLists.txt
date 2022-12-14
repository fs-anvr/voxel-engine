cmake_minimum_required(VERSION 3.25)

project(
  Core 
  VERSION 0.0.1
  DESCRIPTION "Voxel engine core"
  LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if (IS_SUBPROJECT AND NOT DEFINED PROJECT_TESTING)
  message(STATUS "${PROJECT_NAME} не тестируется в режиме подмодуля")
  set(PROJECT_TESTING OFF)
endif()

if (IS_SUBPROJECT AND NOT DEFINED PROJECT_DOC)
  message(STATUS "${PROJECT_NAME} не создаёт документацию в режиме подмодуля")
endif()

option(PROJECT_TESTING "Включить модульное тестирование" ON)
option(PROJECT_COVERAGE "Включить измерение покрытия кода тестами" OFF)
option(PROJECT_DOC "Включить документирование" ON)

###################################################################################################
##
##      Опции компиляции
##
###################################################################################################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,GNU,CLang,AppleClang,ARMClang>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")

add_compile_options(
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wold-style-cast>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W4;-WX>>"
)

#TODO: больше опций компилятора
#TODO: debug / release

if (NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

###################################################################################################
##
##      Компилируемая библиотека
##
###################################################################################################

set(PUBLIC_INCLUDE
  include/Core.hpp
)

set(PRIVATE_SRC
  src/Core.cpp
)

add_library(${PROJECT_NAME} STATIC
  ${PUBLIC_INCLUDE}
  ${PRIVATE_SRC}
)

add_library("VoxelEngine::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)

add_subdirectory(Input ${CMAKE_CURRENT_BINARY_DIR}/Input)
add_subdirectory(EventSystem ${CMAKE_CURRENT_BINARY_DIR}/EventSystem)
add_subdirectory(Render ${CMAKE_CURRENT_BINARY_DIR}/Render)
add_subdirectory(Voxel ${CMAKE_CURRENT_BINARY_DIR}/Voxel)
add_subdirectory(Shaders ${CMAKE_CURRENT_BINARY_DIR}/Shaders)
add_subdirectory(IO ${CMAKE_CURRENT_BINARY_DIR}/IO)
add_subdirectory(ServiceLocator ${CMAKE_CURRENT_BINARY_DIR}/ServiceLocator)
add_subdirectory(Scene ${CMAKE_CURRENT_BINARY_DIR}/Scene)
add_subdirectory(Time ${CMAKE_CURRENT_BINARY_DIR}/Time)
add_subdirectory(App ${CMAKE_CURRENT_BINARY_DIR}/App)

target_link_libraries(${PROJECT_NAME}
  PUBLIC

    VoxelEngine::Input
    VoxelEngine::EventSystem
    VoxelEngine::Render
    VoxelEngine::Voxel
    VoxelEngine::Shaders
    VoxelEngine::IO
    VoxelEngine::ServiceLocator
    VoxelEngine::Scene
    VoxelEngine::Time
    VoxelEngine::App

    glfw # private??
    glm::glm # private??

  PRIVATE
    glad
)

###################################################################################################
##
##      Тесты
##
###################################################################################################

if (NOT PROJECT_TESTING)
  message(STATUS "Тестирование ${PROJECT_NAME} выключено")
else()
  #TODO: TESTS
  #add_subdirectory(test)
endif()

###################################################################################################
##
##      Документация
##
###################################################################################################

if (PROJECT_DOC)
  message(STATUS "Создание документации для ${PROJECT_NAME} выключено")
else()
  #TODO: DOCS
  #add_subdirectory(doc)
endif()