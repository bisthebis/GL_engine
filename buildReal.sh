cp src/real_main.cpp src/main.cpp
cmake .
make
rm src/main.cpp
mv -f Programme App
