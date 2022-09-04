cmake_minimum_required(VERSION 3.22)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# About Vulkan&SPIRV
#################################################################################

# Vulkan
##################################################################

find_package(Vulkan REQUIRED FATAL_ERROR)
set(LIB ${LIB} ${Vulkan_LIBRARIES})
set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} ${Vulkan_INCLUDE_DIRS})
message(STATUS "Vulkan_Found:${Vulkan_FOUND}")

# glslang
##################################################################
set(ENABLE_CTEST FALSE)

add_subdirectory(glslang)
set(LIB ${LIB} glslang glslang-default-resource-limits SPIRV)
set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} glslang)

# SPRIV-Cross
##################################################################
set(SPIRV_CROSS_ENABLE_TESTS FALSE)

#add_subdirectory(SPIRV-Cross)
#set(LIB ${LIB} spirv-cross)
#set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} SPIRV-Cross)

# About Window&image
##################################################################################

# GLFW
##################################################################
set(GLFW_BUILD_EXAMPLES FALSE)
set(GLFW_BUILD_TESTS FALSE)
set(GLFW_BUILD_DOCS FALSE)

add_subdirectory(glfw)
set(LIB ${LIB} glfw)
set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} glfw/include)

# imgui
##################################################################

set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} imgui)

# stb_image
##################################################################

set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} stb)

# About Math
##################################################################################

#glm
##################################################################
set(BUILD_TESTING FLASE)

add_subdirectory(glm)
set(LIB ${LIB} glm::glm)
set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} glm)

# About log
##################################################################################

#spdlog
##################################################################
set(SPDLOG_BUILD_TESTS FALSE)

add_subdirectory(spdlog)
set(LIB ${LIB} spdlog::spdlog)
set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} spdlog/include)

# About Model load
##################################################################################

#assimp
##################################################################
set(ASSIMP_BUILD_SAMPLES FALSE)
set(ASSIMP_BUILD_TESTS FALSE)
set(ASSIMP_INSTALL FALSE)
set(ASSIMP_BUILD_ASSIMP_TOOLS FALSE)
set(ASSIMP_BUILD_DOCS FALSE)


#add_subdirectory(assimp)
#set(LIB ${LIB} assimp::assimp)
#set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} assimp/include)



# Config All 3rd lib
###################################################################################
###################################################################################
set(3RD_INCLUDE_DIRECTION ${3RD_INCLUDE_DIRECTION} CACHE INTERNAL "All thirdparty include")

set(3RDLIB ${LIB} CACHE INTERNAL "All thirdparty lib")