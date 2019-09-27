#CMake最低要求版本
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#检查编译根目录是否设置
if(NOT BUILD_ROOT)
	MESSAGE(FATAL_ERROR "build root not set!")
endif(NOT BUILD_ROOT)
message(STATUS "you set build root ${BUILD_ROOT}")

##初始化设置各前缀变量
set(PROJECT_NAME file_searcher)
set(FILE_SEARCHER_INCLUDE_DIR ${BUILD_ROOT}/include)
set(FILE_SEARCHER_SOURCE_DIR ${BUILD_ROOT}/src)
set(EXECUTABLE_OUTPUT_PATH ${BUILD_ROOT}/exec)
#设置库文件查找目录(依赖库保留，目前应该是用不到)
set(FILE_SEARCHER_LIBRARY_DIR ${BUILD_ROOT}/lib)

#项目名
project(${PROJECT_NAME})
#查找在某个路径下的所有源文件,并将文件存放到其后的变量中
aux_source_directory(${FILE_SEARCHER_SOURCE_DIR} FILE_SEARCHER_SRCS)
#指示后者变量中的文件需要被编译成一个程序
add_executable(${PROJECT_NAME} ${FILE_SEARCHER_SRCS})

#设置头文件
include_directories(
	${FILE_SEARCHER_INCLUDE_DIR}
)

#用到的依赖库(依赖库保留，目前应该是用不到)
#set(LIBRARY_DEPENDCY_LIST
#	libz.so.1
#)
#依赖库查找路径(依赖库保留，目前应该是用不到)
#set(LIBRARY_DEPENDCY_SEARCH_DIR
#	/lib/x86_64-linux-gnu
#)

#使用find_library来查找共享库(依赖库保留，目前应该是用不到)
#foreach(LIB_TO_FIND ${LIBRARY_DEPENDCY_LIST})
#	find_library(LIB${LIB_TO_FIND}_PATH ${LIB_TO_FIND} PATHS ${LIBRARY_DEPENDCY_SEARCH_DIR} NO_DEFAULT_PATH)
#	message(${LIB_TO_FIND})
#	if(NOT LIB${LIB_TO_FIND}_PATH)
#		message(FATAL_ERROR "${LIB_TO_FIND} need but not found")
#	endif(NOT LIB${LIB_TO_FIND}_PATH) 
#	message(STATUS ${LIB_TO_FIND} " found")
#	set(LIB_LINK_PATH ${LIB_LINK_PATH} LIB${LIB_TO_FIND}_PATH)
#endforeach(LIB_TO_FIND)
#设置链接库(依赖库保留，目前应该是用不到)
#target_link_libraries(${PROJECT_NAME} ${LIB_LINK_PATH})




