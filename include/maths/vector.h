//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_VECTOR_H
#define MYNT_BASIC_ALGTHMS_VECTOR_H

#include "matrix.h"

#include <assert.h>

namespace mynt {

    /**
     * @brief column vector
     */
    template<unsigned int _N>
    class Vector : public Matrix {
    public:
        Vector() : Matrix(_N, 1) {}

        Vector(const FLOAT *val) : Matrix(_N, 1, val) {}

        Vector(const Matrix &mat) : Matrix(mat) { assert(mat.m == 1 && mat.n == _N); }

        FLOAT &operator[](int idx) { return (*this)(idx, 0); }

        const FLOAT &operator[](int idx) const { return (*this)(idx, 0); }

        inline unsigned int size() const { return _N; }

        Vector operator*(const FLOAT &m) const { return Matrix(*this) * m; }

        Matrix operator*(const Vector &v) const { return Matrix(*this) * Matrix(v); }

        Vector operator/(const FLOAT &m) const { return Matrix(*this) / m; }

        Vector transpose() const { return ~Matrix(*this); }

        inline FLOAT dot(const Vector &v) {
            assert(_N == v.size());
            FLOAT sum = 0.0;
            for(int i=0; i<v.size(); ++i)
                sum += (*this)[i] * v[i];
            return sum;
        }

        template<unsigned int _M>
        inline Vector<_M> block(int idx) const { return this->get_mat(idx, 0, idx+_M-1, 0); }

        inline FLOAT max_coeff(int &i_max) {
            FLOAT max = 0.0;
            i_max = 0;
            for(int i=0; i<size(); ++i) {
                if((*this)[i]>max) {
                    max = (*this)[i];
                    i_max = i;
                }
            }
            return max;
        }
    };

    typedef Vector<2> Vector2;
    typedef Vector<3> Vector3;
    typedef Vector<4> Vector4;
    typedef Vector<5> Vector5;
    typedef Vector<6> Vector6;
}

#endif //MYNT_BASIC_ALGTHMS_VECTOR_H
