DIR=$PWD
cd $DIR && echo rm -rf build-gcc-release;
 mkdir build-gcc-release; cd build-gcc-release;
CC=/usr/bin/gcc CXX=/usr/bin/g++ cmake -DCMAKE_BUILD_TYPE=Release .. && make -j8 ;
cd $DIR  && rm -rf build-clang-release; mkdir build-clang-release; cd build-clang-release; CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -DCMAKE_BUILD_TYPE=Release .. && make -j8;

cd $DIR  && rm -rf build-gcc-debug;   mkdir build-gcc-debug;   cd build-gcc-debug;
CC=/usr/bin/gcc CXX=/usr/bin/g++ cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j8;
cd $DIR && rm -rf build-clang-debug; mkdir build-clang-debug; cd build-clang-debug; CC=/usr/bin/clang CXX=/usr/bin/clang++ cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j8;

cd $DIR
./build-gcc-release/test_zip gcc-release
./build-gcc-debug/test_zip   gcc-debug__
./build-clang-release/test_zip clang-release
./build-clang-debug/test_zip   clang-debug__
