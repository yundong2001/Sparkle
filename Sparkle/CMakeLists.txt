cmake_minimum_required(VERSION 3.16)

macro(ADD path)
    file(GLOB ${path}_SOURCE ${path}/*.cpp)
    file(GLOB ${path}_HEADER ${path}/*.h)
    set(Sparkle_SOURCE ${Sparkle_SOURCE} ${${path}_SOURCE})
    set(Sparkle_HEADER ${Sparkle_HEADER} ${${path}_HEADER})
endmacro()

ADD(Common)
ADD(Render)
ADD(Event)
ADD(Log)
ADD(Framework)
ADD(Platform/Vulkan)
ADD(Platform/Window)
ADD(RHI)
ADD(Macro)


add_library(Sparkle STATIC)
set(SOURCE ${Sparkle_SOURCE} ${Sparkle_HEADER})
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCE})

#message(${Sparkle_SOURCE})

target_precompile_headers(Sparkle PRIVATE PCH/PCH.h)

target_include_directories(Sparkle PUBLIC .)

target_sources(Sparkle PRIVATE ${Sparkle_SOURCE})

target_link_libraries(Sparkle ${3RDLIB})

set_target_properties(Sparkle PROPERTIES FOLDER Sparkle)

set(Sparkle_PATH ${CMAKE_CURRENT_SOURCE_DIR}
        CACHE INTERNAL "Sparkle PATH")


# Main
add_executable(SparkleRenderEngine)

target_include_directories(SparkleRenderEngine PUBLIC .)

target_sources(SparkleRenderEngine PRIVATE Framework/main.cpp)

target_link_libraries(SparkleRenderEngine Sparkle)

set_target_properties(SparkleRenderEngine PROPERTIES FOLDER Sparkle)