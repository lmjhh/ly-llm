 设置 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和版本
project(ly-llm VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # 禁用编译器特定的扩展（如 GNU 扩展）
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# 设置构建类型（如果未指定，默认为 Release）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# 打印构建类型
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# 查找 PyTorch 的 CMake 配置
find_package(Torch REQUIRED)
find_package(Python COMPONENTS Development REQUIRED)

set(THIRD_PATH "src/third")
# 设置 xfastertransformer 的路径
set(XFT_PATH "/root/miniconda3/envs/ly/lib/python3.12/site-packages/xfastertransformer-devel")

# 查找动态库
find_library(XFT_LIBRARY NAMES xfastertransformer PATHS ${XFT_PATH}/lib NO_DEFAULT_PATH)
if (NOT XFT_LIBRARY)
    message(FATAL_ERROR "xfastertransformer library not found!")
endif()

# 打印找到的库路径
message(STATUS "Found XFT_LIBRARY: ${XFT_LIBRARY}")

file(GLOB_RECURSE SRC_FILES "src/*.cc")

# 添加可执行文件
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})

# 添加头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE src)
# 将 PyTorch 的头文件路径添加到目标
target_include_directories(${PROJECT_NAME} PRIVATE ${TORCH_INCLUDE_DIRS} ${Python_INCLUDE_DIRS} ${XFT_PATH}/include)

# 链接 python 库
target_link_libraries(${PROJECT_NAME} PRIVATE ${TORCH_LIBRARIES} ${Python_LIBRARIES} stdc++ ${XFT_LIBRARY})

# 添加编译选项
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -O3 -mavx512f -mavx512bw -mavx512vl)

# 添加预处理器定义
# target_compile_definitions(${PROJECT_NAME} PRIVATE MY_DEFINE=1)

# 如果需要支持安装规则
# install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# 如果需要支持测试
# enable_testing()
# add_test(NAME MyTest COMMAND ${PROJECT_NAME})

# 如果需要支持静态库或动态库
# add_library(MyLibrary STATIC src/library.cpp)
# target_link_libraries(${PROJECT_NAME} PRIVATE MyLibrary)

# 如果需要从子目录添加模块
# add_subdirectory(src/submodule)

# 如果需要下载外部依赖项，可以使用 FetchContent
# include(FetchContent)
# FetchContent_Declare(
#     googletest
#     GIT_REPOSITORY https://github.com/google/googletest.git
#     GIT_TAG release-1.12.1
# )
# FetchContent_MakeAvailable(googletest)