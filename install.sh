cd external/libdivsufsort-2.0.1
bash install.sh
cd ../../


cd external/malloc_count
bash install.sh
cd ../../

cd build
cmake ..
make
make install
cd ../