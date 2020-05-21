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
        Vector() : Matrix(1, _N) {}

        Vector(const FLOAT *val) : Matrix(1, _N, val) {}

        Vector(const Matrix &mat) : Matrix(mat) {
            assert(mat.m == 1 && mat.n == _N);
        }

        FLOAT &operator[](int idx) { return (*this)(0, idx); }

        const FLOAT &operator[](int idx) const { return (*this)(0, idx); }

        inline unsigned int size() const { return _N; }

        Vector operator*(const FLOAT &m) {
            Vector v;
            for(int i=0; i<this->size(); ++i)
                v[i] = (*this)[i] * m;
            return v;
        }

        Matrix operator*(const Vector &v) const {
            int m = _N;
            int n = v.size();
            Matrix mat(m, n);
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < n; ++j)
                    mat(i, j) = (*this)[i] * v[j];
            return mat;
        }

        Vector operator/(const FLOAT &m) const {
            Vector v;
            for(int i=0; i<this->size(); ++i)
                v[i] = (*this)[i] / m;
            return v;
        }

        inline FLOAT norm() { return this->l2norm(); }

        inline FLOAT dot(const Vector &v) {
            assert(_N == v.size());
            FLOAT sum = 0.0;
            for(int i=0; i<v.size(); ++i)
                sum += (*this)[i] * v[i];
            return sum;
        }

        template<unsigned int _M>
        inline Vector<_M> block(int idx) const {
            assert(idx>=0 && idx<_N);
            assert(idx+_M <= _N);
            Vector<_M> v;
            for(int i=0; i<_M; ++i)
                v[i] = (*this)[idx+i];
            return v;
        }

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

        friend std::ostream &operator<<(std::ostream &out, Vector &v) {
            if(_N == 0)
                out << "[empty Vector]";
            else {
                out << "[";
                for(int i=0; i<_N-1; ++i)
                    out << v[i] << ", ";
                out << v[_N-1] << "]";
            }
            return out;
        }
    };
}

#endif //MYNT_BASIC_ALGTHMS_VECTOR_H
