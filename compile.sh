BUILD_ROOT=`pwd`
#建立工程编译目录
if [ -z $1 ]; then
	mkdir -p build
	cd build
	#CMakeLists.txt文件所在的上级目录
	cmake .. -DBUILD_ROOT="$BUILD_ROOT"
	make
elif [ $1 = "clean" ]; then
	rm -rf build
elif [ $1 = "-h" ]; then
	echo "Usage:"
	echo "$0 		build this project"
	echo "$0 clean 	clean this project"
fi
