#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>

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

        inline int rows() const { return m; }
        inline int cols() const { return n; }

        // assignment operator, copies contents of M
        Matrix &operator=(const Matrix &M);

        FLOAT &operator()(const int row, const int col);

        FLOAT &operator()(const int row, const int col) const;

//        Matrix &block(int i1, int j1, int mm, int nn) {
//#if 0
//            mat_ = new Matrix(mm, nn);
//            for(int i=0; i<mm; ++i)
//                mat_->val[i] = &val[i1+i][j1];
//            return *mat_;
////            mat_ptr_ = std::make_shared<Matrix>(Matrix(mm, nn));
////            for(int i=0; i<mm; ++i)
////                mat_ptr_->val[i] = &val[i1+i][j1];
////            return *mat_ptr_;
//#else
//            is_block_ = true;
//            i1_ = i1;
//            j1_ = j1;
//            mm_ = mm;
//            nn_ = nn;
//            return *this;
//#endif
//        }

        const Matrix block(int i1, int j1, int mm, int nn) const {
            if(0 == mm || 0 == nn)
                return Matrix(mm, nn);
            Matrix mat(mm, nn);
            mat = get_mat(i1, j1, i1+mm-1, j1+nn-1);
            return mat;
        }

//        template<unsigned int _M, unsigned int _N>
//        Matrix &block(int i1, int j1) {
//#if 0
//            mat_ = new Matrix(_M, _N);
//            for(int i=0; i<_M; ++i)
//                mat_->val[i] = &val[i1+i][j1];
//            return *mat_;
////            mat_ptr_ = std::make_shared<Matrix>(Matrix(_M, _N));
////            for(int i=0; i<_M; ++i)
////                mat_ptr_->val[i] = &val[i1+i][j1];
////            return *mat_ptr_;
//#else
//            is_block_ = true;
//            i1_ = i1;
//            j1_ = j1;
//            mm_ = _M;
//            nn_ = _N;
//            return *this;
//#endif
//        }

        template<unsigned int _M, unsigned int _N>
        const Matrix block(int i1, int j1) const {
            Matrix mat(_M, _N);
            mat = get_mat(i1, j1, i1+_M-1, j1+_N-1);
            return mat;
        }

        // copies submatrix of M into array 'val', default values copy whole row/column/matrix
        void get_data(FLOAT *val_, int32_t i1 = 0, int32_t j1 = 0, int32_t i2 = -1, int32_t j2 = -1);

        // set or get submatrices of current matrix
        Matrix get_mat(int32_t i1, int32_t j1, int32_t i2 = -1, int32_t j2 = -1) const;

        void set_mat(const int32_t i, const int32_t j, const Matrix &M);

        // set sub-matrix to scalar (default 0), -1 as end replaces whole row/column/matrix
        void set_val(FLOAT s, int32_t i1 = 0, int32_t j1 = 0, int32_t i2 = -1, int32_t j2 = -1);

        // set (part of) diagonal to scalar, -1 as end replaces whole diagonal
        void set_diag(FLOAT s, int32_t i1 = 0, int32_t i2 = -1);

        // clear matrix
        void zero();

        // extract columns with given index
        Matrix extract_cols(std::vector<int> idx) const;

        const Matrix row(int i) const;

        // create identity matrix
        static Matrix eye(const int32_t m);

        static Matrix identity(int32_t p, int32_t q);

        void eye();

        // create diagonal matrix with nx1 or 1xn matrix M as elements
        static Matrix diag(const Matrix &M);

        // returns the m-by-n matrix whose elements are taken column-wise from M
        static Matrix reshape(const Matrix &M, int32_t m, int32_t n);

        void conservative_resize(int32_t p, int32_t q);

        // simple arithmetic operations
        Matrix operator+(const Matrix &M) const; // add matrix
        Matrix operator-(const Matrix &M) const; // subtract matrix
        Matrix operator*(const Matrix &M) const; // multiply with matrix
        Matrix operator*(const FLOAT &s) const;  // multiply with scalar
        Matrix operator/(const Matrix &M) const; // divide elementwise by matrix (or vector)
        Matrix operator/(const FLOAT &s) const;  // divide by scalar
        void operator+=(const Matrix &M) { *this = (*this) + M; }
        Matrix operator-() const;                // negative matrix
        Matrix operator~() const;                // transpose
        Matrix transpose() const { return ~(*this); }
        FLOAT l2norm() const;                    // euclidean norm (vectors) / frobenius norm (matrices)
        FLOAT mean();                      // mean of all elements in matrix

        // complex arithmetic operations
        static Matrix cross(const Matrix &a, const Matrix &b);     // cross product of two vectors
        static Matrix inv(const Matrix &M);                        // invert matrix M
        Matrix inv();                                              // invert this matrix
        FLOAT det();                                               // returns determinant of matrix
        bool solve(const Matrix &M, FLOAT eps = 1e-20);            // solve linear system M*x=B, replaces *this and M
        bool lu(int32_t *idx, FLOAT &d, FLOAT eps = 1e-20);        // replace *this by lower upper decomposition
        void svd(Matrix &U, Matrix &W, Matrix &V);                 // singular value decomposition *this = U*diag(W)*V^T

        // print matrix to stream
        friend std::ostream &operator<<(std::ostream &out, const Matrix &M);

    private:
        void allocate_memory(const int32_t m_, const int32_t n_);
        void release_memory();

        inline FLOAT pythag(FLOAT a, FLOAT b);

    private:
        FLOAT **val;
        int32_t m, n;

//        Matrix *mat_ = nullptr;
////        std::shared_ptr<Matrix> mat_ptr_;
//
//        bool is_block_ = false;
//        int i1_;
//        int j1_;
//        int mm_;
//        int nn_;
    };
}

#endif // MATRIX_H
