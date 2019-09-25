//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_VECTOR_H
#define MYNT_BASIC_ALGTHMS_VECTOR_H

#include "matrix.h"

#include <assert.h>
#include <initializer_list>

namespace mynt {

    /**
     * @brief column vector
     */
    class VectorX : public Matrix {
    public:
        VectorX(int n) : Matrix(n, 1) {}

        VectorX(const Matrix &mat) : Matrix(mat) { assert(mat.n == 1); }

        FLOAT &operator[](int idx) { return (*this)(idx, 0); }

        const FLOAT &operator[](int idx) const { return (*this)(idx, 0); }

        inline unsigned int size() const { return m; }
    };

    /**
     * @brief column vector
     */
    template<unsigned int _N>
    class Vector : public Matrix {
    public:
        Vector() : Matrix(_N, 1) {}

        Vector(std::initializer_list<FLOAT> vlist) : Matrix(_N, 1) {
            int i=0;
            for(auto a : vlist) {
                if(i==_N)
                    break;
                val[i][0] = a;
                ++i;
            }
            for(; i<_N; ++i)
                val[i][0] = 0.0;
        }

        Vector(const FLOAT *val) : Matrix(_N, 1, val) {}

        Vector(const Matrix &mat) : Matrix(mat) { assert(mat.m ==_N && mat.n == 1); }

        FLOAT &operator[](int idx) { return (*this)(idx, 0); }

        const FLOAT &operator[](int idx) const { return (*this)(idx, 0); }

        inline unsigned int size() const { return _N; }

        Vector operator*(const FLOAT &m) const { return Matrix(*this) * m; }

        Matrix operator*(const Vector &v) const { return Matrix(*this) * Matrix(v); }

        Vector operator/(const FLOAT &m) const { return Matrix(*this) / m; }

        void operator+=(const Vector &v) { *this = Matrix(*this) + Matrix(v); }

        void operator*=(const FLOAT &m) { *this = Matrix(*this) * m; }

        inline FLOAT l1norm() const {
            FLOAT norm = 0;
            for(int i=0; i<_N; ++i)
                norm += (*this)(i, 0);
            return norm;
        }

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

    /**
     * @brief Create a skew-symmetric matrix from a 3-element vector.
     * @param w
     * @note Performs the operation:
     *  w   ->  [  0 -w3  w2]
     *          [ w3   0 -w1]
     *          [-w2  w1   0]
     * @return
     */
    Matrix skew_symmetric(const Vector<3> &w);

    /**
     * @brief s * M
     * @param s
     * @param M
     * @return
     */
    Matrix operator*(FLOAT s, Matrix M);

    /**
     * @brief s * V
     * @param s
     * @param V
     * @return
     */
    template<unsigned int _M>
    Vector<_M> operator*(FLOAT s, Vector<_M> V)  { return V * s; }

    /**
     * @brief M * V
     * @param M
     * @param V
     * @return
     */
    template<unsigned int _M, unsigned int _N>
    static Vector<_M> operator*(const Matrix &M, const Vector<_N> &V) {
        assert(M.n == V.size() && M.m == _M);
        Vector<_M> v;
        for(int i=0; i<M.m; ++i) {
            FLOAT sum_i = 0.0;
            for(int j=0; j<M.n; ++j)
                sum_i += M(i,j) * V[j];
            v[i] = sum_i;
        }
        return v;
    }

    /**
     * @brief column Vector to Matrix
     * @param v1
     * @param v2
     * @return
     */
    Matrix vec2mat(const Vector2 &v1, const Vector2 &v2);

    Matrix vec2mat(const VectorX &v1, const VectorX &v2);
}

#endif //MYNT_BASIC_ALGTHMS_VECTOR_H
