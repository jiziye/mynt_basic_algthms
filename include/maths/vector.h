//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_VECTOR_H
#define MYNT_BASIC_ALGTHMS_VECTOR_H

#include "matrix.h"

namespace mynt {

    class Vector {
    public:
        Vector() {
            n_ = 0;
        }

        Vector(unsigned int n) {
            v_ = Matrix(1, n);
            n_ = n;
        }

        Vector(unsigned int n, const FLOAT *val) {
            v_ = Matrix(1, n, val);
            n_ = n;
        }

        Vector &operator=(const Vector &rhs) {
            if(this != &rhs) {
                if(n_ != rhs.size())
                    n_ = rhs.size();
                v_ = rhs.v_;
            }
            return *this;
        }

        FLOAT &operator[](int n) {
            return v_(0, n);
        }

        FLOAT &operator[](int n) const {
            return v_(0, n);
        }

        unsigned int size() const {
            return n_;
        }

        Vector operator+(const Vector &rhs) {
            Vector v;
            v.v_ = v_ + rhs.v_;
            v.n_ = rhs.size();
            return v;
        }

        Vector operator-(const Vector &rhs) {
            Vector v;
            v.v_ = v_ - rhs.v_;
            v.n_ = rhs.size();
            return v;
        }

        Vector operator*(const FLOAT &m) {
            Vector v;
            v.v_ = v_ * m;
            v.n_ = n_;
            return v;
        }

        Vector operator/(const FLOAT &m) {
            Vector v;
            v.v_ = v_ / m;
            v.n_ = n_;
            return v;
        }

        inline FLOAT norm() {
            return v_.l2norm();
        }

        friend std::ostream &operator<<(std::ostream &out, Vector &v) {
            if(v.n_ == 0)
                out << "[empty Vector]";
            else {
                out << "[";
                for(int i=0; i<v.n_-1; ++i)
                    out << v[i] << ", ";
                out << v[v.n_-1] << "]";
            }
            return out;
        }

    private:
        Matrix v_;
        unsigned int n_;
    };
}

#endif //MYNT_BASIC_ALGTHMS_VECTOR_H
