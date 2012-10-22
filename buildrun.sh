mkdir build
pushd build
cmake ..
make -j9
cp taksample ../bin
popd
./bin/taksample
