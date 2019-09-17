# MYNT Basic Algorithms

## Build

* build main project

  ```sh
  mkdir build
  cd build
  cmake ..
  make -j2
  ```

* build with unit test (need to install **GTest** first)

  ```sh
  mkdir build
  cd build
  cmake .. -DBUILD_TEST=ON
  make -j2
  ```

* build doc with doxygen (need to install **doxygen** first and **latex** optionally)

  ```sh
  mkdir build
  cd build
  cmake .. -DBUILD_DOC=ON
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

* Matrix
* Vector

### Computer Vision
* YImg class

### Kinematics
* Rotation Matrix
* Quarternion