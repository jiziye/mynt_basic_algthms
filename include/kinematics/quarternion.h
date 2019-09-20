//
// Created by cg on 9/16/19.
//

#ifndef MYNT_BASIC_ALGTHMS_QUARTERNION_H
#define MYNT_BASIC_ALGTHMS_QUARTERNION_H

#include <assert.h>
#include <cmath>

#include "maths/math_basics.h"

namespace mynt {

#define Q_HAMILTON 0 // 0 for JPL, 1 for HAMILTON

    /**
     * @brief Hamilton and JPL Quarternion
     */
    class Quarternion {
    public:
        Quarternion();

        Quarternion(FLOAT w, FLOAT x, FLOAT y, FLOAT z);

        Quarternion(const Vector &v4);

        FLOAT w() const {
#if Q_HAMILTON
            return v4_[0];
#else
            return v4_[3];
#endif
        }

        FLOAT x() const {
#if Q_HAMILTON
            return v4_[1];
#else
            return v4_[0];
#endif
        }

        FLOAT y() const {
#if Q_HAMILTON
            return v4_[2];
#else
            return v4_[1];
#endif
        }

        FLOAT z() const {
#if Q_HAMILTON
            return v4_[3];
#else
            return v4_[2];
#endif
        }

        Vector vec() const {
#if Q_HAMILTON
            const Vector &q_vec = v4_.block(1, 3);
            return q_vec;
#else
            const Vector &q_vec = v4_.block(0, 3);
            return q_vec;
#endif
        }

        /**
         * @brief quarternion normalize
         */
        inline Quarternion normalized() {
            FLOAT l2norm = v4_.norm();
            return this->v4_ / l2norm;
        }

        /**
         * @brief unit random quarternion, ref: http://planning.cs.uiuc.edu/node198.html
         * @return
         */
        static Quarternion unit_random() {
            double u1 = rand() / double(RAND_MAX); // [0, 1]
            double u2 = rand() / double(RAND_MAX) * M_2_PI;
            double u3 = rand() / double(RAND_MAX) * M_2_PI;
            double a = std::sqrt(1 - u1);
            double b = std::sqrt(u1);
            // TODO: Hamilton ?
            return Quarternion(a*sin(u2), a*cos(u2), b*sin(u3), b*cos(u3)).normalized();
        }

        /**
         * @brief Convert a quaternion to the corresponding rotation matrix
         * @note Pay attention to the convention used. The function follows the conversion in
         *      "Indirect Kalman Filter for 3D Attitude Estimation: A Tutorial for Quaternion Algebra", Equation (78).
         *
         *       The input quaternion should be in the form [q1, q2, q3, q4(scalar)]^T
         * @return
         */
        Matrix rotation_matrix() const;

        Matrix left_product_matrix() const;

        Quarternion operator*(const Quarternion &q) {
            Vector v4 = this->left_product_matrix() * q.v4_;
            return Quarternion(v4).normalized();
        }

        friend std::ostream &operator<<(std::ostream &out, Quarternion q) {
#if Q_HAMILTON
            out << "[" << q.w() << ", " << q.x() << ", " << q.y() << ", " << q.z() << "]";
#else
            out << "[" << q.x() << ", " << q.y() << ", " << q.z() << ", " << q.w() << "]";
#endif
            return out;
        }

    private:
        Vector v4_;
    };
}

#endif //MYNT_BASIC_ALGTHMS_QUARTERNION_H
