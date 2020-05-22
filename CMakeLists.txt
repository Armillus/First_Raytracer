cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(raytracer)

## Conan setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

## Enable Google test library
enable_testing()

## Setting flags for linux, finding the thread package.
if (UNIX)
    find_package(Threads)
    set(CMAKE_CXX_FLAGS "-g3 -Ofast -pipe -Wall -Wextra -std=c++17 -fopenmp --coverage")
endif()

## Add valgring flag
if (MSVC)
    add_compile_options(/Wall /WX-)
endif()

## Core sources
set(SRC_CORE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Core.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Graphics/SFML/SfmlLibrary.cpp
)

## Material sources
set(SRC_MATERIAL
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Materials/Color/Color.cpp
)

set(SRC_OBJECTS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Objects/Primitives/Sphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Objects/Primitives/Plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Objects/Primitives/Triangle.cpp
)

set(SRC_TEXTURES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Textures/SfmlTexture.cpp
)

## Renderer sources
set(SRC_RENDERER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/RayTracer/RayTracer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/FrameBuffer/FrameBuffer.cpp
    )

## Scene sources
set(SRC_SCENE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Scene/Scene.cpp
)

## View sources
set(SRC_VIEW
    ${CMAKE_CURRENT_SOURCE_DIR}/src/View/Camera/Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/View/Viewer/Viewer.cpp
)

## Parser sources
set(SRC_PARSER
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser/Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser/JsonParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser/ObjParser.cpp
)

##Test sources
set(SRC_UNIT_TEST
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Materials/UnitTest_Color.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Lights/UnitTest_DirectionalLight.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Lights/UnitTest_SphericalLight.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Objects/UnitTest_Plane.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Objects/UnitTest_Sphere.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Objects/UnitTest_Triangle.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Maths/UnitTest_vector3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Maths/UnitTest_Trigo.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Scene/UnitTest_Scene.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tests/View/UnitTest_Camera.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/View/UnitTest_Viewer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/View/UnitTest_Resolution.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Parser/UnitTest_Parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Parser/UnitTest_JsonParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Parser/UnitTest_ObjParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/View/UnitTest_RayTracer.cpp
)

## Include headers to program
include_directories(

    # Core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Events
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Graphics
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/Graphics/SFML

    # Lights
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Lights

    # Materials
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Materials
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Materials/Color

    # Textures
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Textures

    # Maths
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Maths

    # Objects
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Objects
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Objects/Primitives

    # Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/Rays
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/RayTracer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/FrameBuffer

    # Scene
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Scene

    # View
    ${CMAKE_CURRENT_SOURCE_DIR}/src/View
    ${CMAKE_CURRENT_SOURCE_DIR}/src/View/Camera
    ${CMAKE_CURRENT_SOURCE_DIR}/src/View/Viewer

    # Parser
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Parser
    ${CONAN_INCLUDE_DIRS_NLOHMANN_JSON}
    ${CONAN_INCLUDE_DIRS_TINYOBJLOADER}

    ## Mocks
#    ${CMAKE_CURRENT_SOURCE_DIR}/tests/Mocks

)

## Final executable
add_executable(raytracer
    ${SRC_CORE}
    ${SRC_MATERIAL}
    ${SRC_TEXTURES}
    ${SRC_OBJECTS}
    ${SRC_RENDERER}
    ${SRC_SCENE}
    ${SRC_VIEW}
    ${SRC_PARSER}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

include(GoogleTest)

##change binary directory for unit_test
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

## Unit Test executable
add_executable(unit_tests
    ${SRC_CORE}
    ${SRC_MATERIAL}
    ${SRC_TEXTURES}
    ${SRC_OBJECTS}
    ${SRC_RENDERER}
    ${SRC_SCENE}
    ${SRC_VIEW}
    ${SRC_PARSER}
    ${SRC_UNIT_TEST}
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp
)

if (UNIX)
    set_target_properties (raytracer
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
else()
    set_target_properties (raytracer
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/
    )
endif()

## Linking libraries
target_link_libraries(raytracer
    CONAN_PKG::sfml
    ${CMAKE_THREAD_LIBS_INIT}
)

## Linking libraries
target_link_libraries(unit_tests PUBLIC
    CONAN_PKG::gtest
    # CONAN_PKG::gmock
    CONAN_PKG::sfml
    ${CMAKE_THREAD_LIBS_INIT}
)
