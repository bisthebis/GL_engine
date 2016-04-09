cp src/test_main.cpp src/main.cpp
cmake .
make
rm src/main.cpp
mv -f Programme Tests
