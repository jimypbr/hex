# Readme

Hex written in C++(11). Currently just has a CLI UI.
AI uses Monte Carlo Tree Search.

Screenshot!:

```
1   -  -  W  W  B  B  B   1
 2   -  -  B  W  W  W  W   2
  3   -  -  W  -  W  B  W   3
   4   -  -  -  W  B  B  W   4
    5   -  -  W  B  -  B  W   5
     6   -  B  B  -  -  B  W   6
      7   B  -  -  -  -  W  B   7
           1  2  3  4  5  6  7  
Winner is WHITE!
```

## Build Instructions

```
$ cd build
$ cmake ..
$ make hex
$ ./hex
```

On Ubuntu:

```
$ cd build
$ cmake -DCMAKE_CXX_COMPILER=clang++ ..
$ make hex
$ ./hex
```

## TODO
* Add Pie Rule.
* Add colour to the cli mode!
* Implement parallel pure monte carlo
* Implement parallel MCTS
* Refactor build system see: https://blog.conan.io/2016/05/10/Programming-C++-with-the-4-Cs-Clang,-CMake,-CLion-and-Conan.html

## License
Copyright James Briggs &copy;

