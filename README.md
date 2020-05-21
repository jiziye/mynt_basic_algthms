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
  make doc
  ```

## Run

* run unit test

  ```sh
  cd build
  ./unit_test/test_xxx
  ```

## Modules

### Maths

* Basic Math Methods
  - [x] Random Number
  - [ ] Interpolation
    - [ ] Linear Interpolation
    - [ ] Bilinear Interpolation

* Data Structures & Methods
  - [x] Matrix
  - [x] Vector

### Computer Vision

* Data Structure & Methods
  - [x] Size
  - [ ] Point2
  - [ ] RGB
* 2D Image & Methods
  - [ ] YImg class
    - [x] Copy
    - [ ] ROI Extraction
    - [ ] Zoom In & Out
    - [ ] Mean Filter
    - [ ] Gaussian Filter
    - [ ] Image Pyramid
* 2D Features
  - Key Points
    - [ ] FAST
    - [ ] ORB
  - Discriptors
  - Line
    - [ ] Edge
    - [ ] Straight Line
* 3D PointCloud
  - [ ] Point3
  - [ ] PointCloud
* Camera
  - [ ] Camera Models
* Binocular Stereo Vision
  - [ ] Stereo Match
  - [ ] Disparity Compute
  - [ ] Disparity --> Depth
  - [ ] Depth --> PointCloud

### Kinematics

**Note**: approximate treatment about **small angle**.

* [ ] Rotation Matrix
* [ ] Quarternion (Hamilton)
* [ ] Euler Angle
* [ ] Convertor
