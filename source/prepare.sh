workingDirectory=$PWD
mkdir -p build
mkdir -p build/debug
mkdir -p build/release
cd build/debug
cmake ../.. -DCMAKE_BUILD_TYPE=debug
cd ../release
cmake ../.. -DCMAKE_BUILD_TYPE=release
cd "$workingDirectory/external/cppunit"
./configure
make
make check
