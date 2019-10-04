#CMake最低要求版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#检查编译根目录是否设置
if(NOT BUILD_ROOT)
	MESSAGE(FATAL_ERROR "build root not set!")
endif(NOT BUILD_ROOT)
message(STATUS "you set build root ${BUILD_ROOT}")

##初始化设置各前缀变量
set(PROJECT_NAME file_searcher)
set(LIBRARY_MAIN_NAME search)
set(FILE_SEARCHER_INCLUDE_DIR ${BUILD_ROOT}/include)
set(FILE_SEARCHER_SOURCE_DIR ${BUILD_ROOT}/src)
set(FILE_SEARCHER_SOURCE_LIBRARY_DIR ${BUILD_ROOT}/src/lib)
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT}/exec)
set(LIBRARY_OUTPUT_PATH ${BUILD_ROOT}/exec/lib)
#设置库文件查找目录
set(FILE_SEARCHER_LIBRARY_DIR ${BUILD_ROOT}/exec/lib)

#项目名
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#查找在某个路径下的所有源文件,并将文件存放到其后的变量中
aux_source_directory(${FILE_SEARCHER_SOURCE_DIR} FILE_SEARCHER_SRCS)
aux_source_directory(${FILE_SEARCHER_SOURCE_LIBRARY_DIR} FILE_SEARCHER_LIBS)
#指示后者变量中的文件需要被编译成一个共享库
add_library(${LIBRARY_MAIN_NAME} SHARED ${FILE_SEARCHER_LIBS})
#指示后者变量中的文件需要被编译成一个程序
add_executable(${PROJECT_NAME} ${FILE_SEARCHER_SRCS})

#设置头文件
include_directories(
	${FILE_SEARCHER_INCLUDE_DIR}
)

#用到的依赖库
#set(LIBRARY_DEPENDCY_LIST
#	search
#)
#依赖库查找路径
#set(LIBRARY_DEPENDCY_SEARCH_DIR
#	${FILE_SEARCHER_LIBRARY_DIR}
#)

#使用find_library来查找共享库
#foreach(LIB_TO_FIND ${LIBRARY_DEPENDCY_LIST})
#	find_library(LIB${LIB_TO_FIND}_PATH ${LIB_TO_FIND} PATHS ${LIBRARY_DEPENDCY_SEARCH_DIR} NO_DEFAULT_PATH)
#	if(NOT LIB${LIB_TO_FIND}_PATH)
#		message(FATAL_ERROR "${LIB_TO_FIND} need but not found")
#	endif(NOT LIB${LIB_TO_FIND}_PATH)
#	message(STATUS ${LIB_TO_FIND} " found")
#	set(LIB_LINK_PATH ${LIB_LINK_PATH} ${LIB${LIB_TO_FIND}_PATH})
#endforeach(LIB_TO_FIND)
#设置链接库
#link_directories(${BUILD_ROOT}/exec/lib)
target_link_libraries(${PROJECT_NAME} ${LIBRARY_MAIN_NAME} ${LIB_LINK_PATH})




