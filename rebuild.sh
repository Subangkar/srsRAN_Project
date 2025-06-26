#cd srsRAN_Project
rm -rf build
mkdir build
cd build
# export CC=gcc-9
# export CXX=g++-9
#cmake ../
cmake ../ -DENABLE_EXPORT=ON -DENABLE_ZEROMQ=ON
make -j 12
#make test -j $(nproc)
