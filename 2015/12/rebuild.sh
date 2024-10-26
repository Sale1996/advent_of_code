cd build
rm -rf *
cmake ..
make
cp ../input.txt ./
./program