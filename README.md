# Semi-External-Landau-Vishkin
A Semi-External Landau Vishkin algorithm for solving the Approximated Pattern Matching Problem.


## Compiling
	In order to compile the Landau-Vishkin Library, one must have cmake installed with g++ 
	with version 4.8 or higher in order to support C++11.

	First install libdivsufort by executing the following commands:

	```shell
	cd external
	cd libdivsufsort-2.0.1
	bash install.sh
	```

	To compile the library and the example, one must execute the following commands:
	
	```shell
	cd build
	cmake ..
	make
	make install
	```
## Running 
	We have provided a full functional example of running the Landau Vishkin Algorithm, 
	Given a Text T, a Pattern P, the number of errors k and a output file output.

	In the folder example.