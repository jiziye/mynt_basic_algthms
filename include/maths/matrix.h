#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#include "common.h"

namespace mynt {

    class Matrix {
    public:
        // constructor / deconstructor
        Matrix();                                                    // init empty 0x0 matrix
        Matrix(const int32_t m, const int32_t n);                    // init empty mxn matrix
        Matrix(const int32_t m, const int32_t n, const FLOAT *val_); // init mxn matrix with values from array 'val'
        Matrix(const Matrix &M);                                     // creates deepcopy of M

        ~Matrix();

        // assignment operator, copies contents of M
        Matrix &operator=(const Matrix &M);

        FLOAT &operator()(const int row, const int col);

        FLOAT &operator()(const int row, const int col) const;

        // copies submatrix of M into array 'val', default values copy whole row/column/matrix
        void get_data(FLOAT *val_, int32_t i1 = 0, int32_t j1 = 0, int32_t i2 = -1, int32_t j2 = -1);

        // set or get submatrices of current matrix
        Matrix get_mat(int32_t i1, int32_t j1, int32_t i2 = -1, int32_t j2 = -1) const;

        void set_mat(const Matrix &M, const int32_t i, const int32_t j);

        // set sub-matrix to scalar (default 0), -1 as end replaces whole row/column/matrix
        void set_val(FLOAT s, int32_t i1 = 0, int32_t j1 = 0, int32_t i2 = -1, int32_t j2 = -1);

        // set (part of) diagonal to scalar, -1 as end replaces whole diagonal
        void set_diag(FLOAT s, int32_t i1 = 0, int32_t i2 = -1);

        // clear matrix
        void zero();

        // extract columns with given index
        Matrix extract_cols(std::vector<int> idx);

        // create identity matrix
        static Matrix eye(const int32_t m);

        void eye();

        // create diagonal matrix with nx1 or 1xn matrix M as elements
        static Matrix diag(const Matrix &M);

        // returns the m-by-n matrix whose elements are taken column-wise from M
        static Matrix reshape(const Matrix &M, int32_t m, int32_t n);

        // simple arithmetic operations
        Matrix operator+(const Matrix &M) const; // add matrix
        Matrix operator-(const Matrix &M) const; // subtract matrix
        Matrix operator*(const Matrix &M) const; // multiply with matrix
        Matrix operator*(const FLOAT &s) const;  // multiply with scalar
        Matrix operator/(const Matrix &M) const; // divide elementwise by matrix (or vector)
        Matrix operator/(const FLOAT &s) const;  // divide by scalar
        Matrix operator-() const;                // negative matrix
        Matrix operator~() const;                // transpose
        Matrix transpose() const { return ~(*this); }
        FLOAT l2norm() const;                    // euclidean norm (vectors) / frobenius norm (matrices)
        FLOAT mean();                      // mean of all elements in matrix

        // complex arithmetic operations
        static Matrix cross(const Matrix &a, const Matrix &b);     // cross product of two vectors
        static Matrix inv(const Matrix &M);                        // invert matrix M
        bool inv();                                                // invert this matrix
        FLOAT det();                                               // returns determinant of matrix
        bool solve(const Matrix &M, FLOAT eps = 1e-20);            // solve linear system M*x=B, replaces *this and M
        bool lu(int32_t *idx, FLOAT &d, FLOAT eps = 1e-20);        // replace *this by lower upper decomposition
        void svd(Matrix &U, Matrix &W, Matrix &V);                 // singular value decomposition *this = U*diag(W)*V^T

        // print matrix to stream
        friend std::ostream &operator<<(std::ostream &out, const Matrix &M);

        // direct data access
        FLOAT **val;
        int32_t m, n;

    private:
        void allocate_memory(const int32_t m_, const int32_t n_);
        void release_memory();

        inline FLOAT pythag(FLOAT a, FLOAT b);
    };
}

#endif // MATRIX_H
