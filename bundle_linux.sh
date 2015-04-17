#!/bin/bash

echo test

# update make and rebuild in release mode
echo ==================================================================
echo Rebuilding in release
echo ==================================================================
./genproj.sh
make -j9 config="release"

# make sure the bundleelf tool is built
echo
echo ==================================================================
echo Building bundleelf tool
echo ==================================================================
cd tak/tools/bundleelf && ./genproj.sh && cd -
make -C tak/tools/bundleelf

echo
echo ==================================================================
echo Creating the bundle
echo ==================================================================
BUNDLE_DIR=./bundle_linux
echo $BUNDLE_DIR
rm -rf $BUNDLE_DIR
mkdir -p $BUNDLE_DIR
pushd $BUNDLE_DIR

cp -R ../media .

mkdir bin
cp ../bin/pong3d bin
cd bin
../../tak/tools/bundleelf/bundleelf pong3d
cd ..


ELFLOADER=$(readelf -l ./bin/pong3d | grep "program interpreter" | cut -d':' -f2 | cut -d']' -f1 | cut -d' ' -f2)
ELFLOADERNAME=$(echo /lib64/ld-linux-x86-64.so.2 | sed 's/\/lib64\///')

cp $ELFLOADER bin/

rm bin/libGL.so.*
rm bin/libGLU.so.*

echo "./bin/$ELFLOADERNAME ./bin/pong3d" > run.sh
chmod +x run.sh

popd

tar czvf bundle_linux.tar.gz $BUNDLE_DIR
