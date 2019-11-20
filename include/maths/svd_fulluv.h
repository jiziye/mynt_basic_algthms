//
// Created by cg on 11/20/19.
//

#ifndef MSCKF_VIO_MYNT_SVD_FULLUV_H
#define MSCKF_VIO_MYNT_SVD_FULLUV_H

#include "matrix.h"

namespace mynt {

    void svd_fulluv(mynt::Matrix& Input, mynt::Matrix& Output_w, mynt::Matrix& Output_u, mynt::Matrix &Output_vt);
}

#endif //MSCKF_VIO_MYNT_SVD_FULLUV_H
