//
// Created by cg on 9/16/19.
//

#ifndef MYNT_BASIC_ALGTHMS_QUARTERNION_H
#define MYNT_BASIC_ALGTHMS_QUARTERNION_H

#include <assert.h>
#include <cmath>

#include "maths/vector.h"

namespace mynt {

    /**
     * @brief Hamilton Quarternion, right-handed
     */
    class Quarternion {
    public:
        Quarternion() {
            v4_ = Vector(4);
            v4_[0] = 1.0;
            v4_[1] = 0.0;
            v4_[2] = 0.0;
            v4_[3] = 0.0;
        }

        Quarternion(FLOAT w, FLOAT x, FLOAT y, FLOAT z) {
            v4_ = Vector(4);
            v4_[0] = w;
            v4_[1] = x;
            v4_[2] = y;
            v4_[3] = z;
            std::cout << "v4_: " << v4_ << std::endl;
        }

        FLOAT w() { return v4_[0]; }

        FLOAT x() { return v4_[1]; }

        FLOAT y() { return v4_[2]; }

        FLOAT z() { return v4_[3]; }

        Quarternion(Vector v4) {
            assert(v4.size() == 4);
            v4_ = v4;
        }

        /**
         * @brief quarternion normalize
         */
        Quarternion normalized() {
            FLOAT l2norm = v4_.norm();
            return this->v4_ / l2norm;
        }

        static Quarternion unit_random() {
            double u1 = rand() / double(RAND_MAX); // [0, 1]
            double u2 = rand() / double(RAND_MAX) * M_2_PI;
            double u3 = rand() / double(RAND_MAX) * M_2_PI;
            double a = std::sqrt(1 - u1);
            double b = std::sqrt(u1);
            return Quarternion(a*sin(u2), a*cos(u2), b*sin(u3), b*cos(u3)).normalized();
        }

        friend std::ostream &operator<<(std::ostream &out, Quarternion q) {
            out << "[" << q.x() << ", " << q.y() << ", " << q.z() << ", " << q.w() << "]";
            return out;
        }

    private:
        Vector v4_;
    };
}

#endif //MYNT_BASIC_ALGTHMS_QUARTERNION_H
