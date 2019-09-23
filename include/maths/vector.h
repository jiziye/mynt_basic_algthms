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
    class Vector {
    public:
        Vector() {
            v_ = Matrix(1, _N);
        }

        Vector(const FLOAT *val) {
            v_ = Matrix(1, _N, val);
        }

        Vector(const Matrix &mat) {
            assert(mat.m == 1 && mat.n == _N);
            v_ = mat;
        }

        Vector &operator=(const Vector &rhs) {
            if(this != &rhs) {
                assert(rhs.size() == _N);
                v_ = rhs.v_;
            }
            return *this;
        }

        FLOAT &operator[](int idx) { return v_(0, idx); }

        const FLOAT &operator[](int idx) const { return v_(0, idx); }

        inline unsigned int size() const { return _N; }

        Vector operator-() {
            v_ = -v_;
            return (*this);
        }

        Vector operator+(const Vector &rhs) {
            assert(_N == rhs.size());
            Vector v;
            v.v_ = v_ + rhs.v_;
            return v;
        }

        Vector operator-(const Vector &rhs) {
            assert(_N == rhs.size());
            Vector v;
            v.v_ = v_ - rhs.v_;
            return v;
        }

        Vector operator*(const FLOAT &m) {
            Vector v;
            v.v_ = v_ * m;
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
            v.v_ = v_ / m;
            return v;
        }

        inline FLOAT norm() { return v_.l2norm(); }

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

    private:
        Matrix v_;
    };
}

#endif //MYNT_BASIC_ALGTHMS_VECTOR_H
