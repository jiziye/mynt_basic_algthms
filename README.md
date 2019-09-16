# MYNT Basic Algorithms

## Build

* build main project
  ```sh
  mkdir build
  cd build
  cmake ..
  make -j2
  ```

* build with unit test (need to install **GTest**  first)
  ```sh
  mkdir build
  cd build
  cmake .. -DUnitTest=true
  make -j2
  ```

## Run

* run unit test
  ```sh
  cd build
  ./unit_test/test_xxx
  ```

## Modules

### Maths

### Computer Vision

### Kinematics