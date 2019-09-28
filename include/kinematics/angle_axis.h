//
// Created by cg on 9/27/19.
//

#ifndef MSCKF_VIO_MYNT_ANGLE_AXIS_H
#define MSCKF_VIO_MYNT_ANGLE_AXIS_H

#include "maths/vector.h"

namespace mynt {

    class AngleAxis {
    public:
        const FLOAT angle() const { return angle_; }

        FLOAT &angle() { return angle_; }

        const Vector3 axis() const { return axis_; }

        Vector3 &axis() { return axis_; }

    private:
        FLOAT angle_;
        Vector3 axis_;
    };
}

#endif //MSCKF_VIO_MYNT_ANGLE_AXIS_H
