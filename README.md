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

To compile the library and the example, one must run the following script:

```shell
bash install.sh
```

It is necessary to have cmake instaled and g++ with support to c++11.

## Running 
We have provided a full functional example of running the Landau Vishkin Algorithm, which is instaled in the bin folder
after the previous command.

This examples executes  variations of such algorithm presented in our library.
To execute one must do
```shell
/example <text-file> <pattern-file> <number of errors> <output-file> <variation>
```


## Description of Experiments
A full paper describing experiments is available in a pdf file called
"Daniel Saad Nogueira Nunes Mauricio Ayala-Rincon Semi External Landau Vishkin Full Paper.pdf"