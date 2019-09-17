//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_YIMG_H
#define MYNT_BASIC_ALGTHMS_YIMG_H

#include "common.h"
#include "cv/types.h"

namespace mynt {

    template <class _T>
    class YImg {
    public:
        YImg() : size_(0,0), data_(nullptr) {}

        YImg(unsigned int w, unsigned int h) {
            size_.width = w;
            size_.height = h;
            data_ = new _T[size_.area()];
        }

        YImg(const Size &size) {
            size_ = size;
            data_ = new _T[size_.area()];
        }

        inline _T *data() const {return data_;}

        inline bool empty() const {return data_==nullptr;}

        inline Size size() const {return size_;}

        bool copy(YImg &img_dst) {
            if(img_dst.empty())
                return false;
            if(img_dst.size() != size())
                return false;
            memcpy(img_dst.data(), data(), size().area()*sizeof(_T));
            return true;
        }

        ~YImg() {
            DELETE_NEW_OBJ(data_)
        }

    private:
        Size size_;
        _T *data_;
    };
}

#endif //MYNT_BASIC_ALGTHMS_YIMG_H
