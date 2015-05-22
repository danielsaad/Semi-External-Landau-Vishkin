# Semi-External-Landau-Vishkin
A Semi-External Landau Vishkin algorithm for solving the Approximated Pattern Matching Problem.


## Compiling
	In order to compile the Landau-Vishkin Library, one must have cmake installed with g++ 
	with version 4.8 or higher in order to support C++11.

	To compile the library and the example, one must execute the following commands:
	
	cd build
	cmake ..
	make
	make install
	
## Running 
	We have provided a full functional example of running the Landau Vishkin Algorithm, 
	Given a Text T, a Pattern P, the number of errors k and a output file output.

	See examle.cpp for more details.

	Before running the example, however, one must set the LD_LIBRARY_PATH environment variable:

	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<absolut path to lib folder within the project>