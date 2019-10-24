//
// Created by cg on 9/17/19.
//

#ifndef MYNT_BASIC_ALGTHMS_YIMG_H
#define MYNT_BASIC_ALGTHMS_YIMG_H

#include "common.h"
#include "cv/types.h"

namespace mynt {

    template<class _T>
    class YImg {
    public:
        YImg() : size_(0, 0), data_(nullptr) {}

        YImg(unsigned int w, unsigned int h) {
            allocate_memory(w, h);
        }

        YImg(const Size &size) {
            allocate_memory(size.width, size.height);
        }

        inline _T *data() const { return data_[0]; }

        inline bool empty() const { return data_ == nullptr; }

        inline Size size() const { return size_; }

        bool copy(YImg &img_dst) {
            if (img_dst.empty())
                return false;
            if (img_dst.size() != size())
                return false;
            memcpy(img_dst.data(), data(), size().area() * sizeof(_T));
            return true;
        }

        ~YImg() {
            release_memory();
        }

    private:
        void allocate_memory(const int32_t w, const int32_t h) {
            size_.width = w;
            size_.height = h;

            if (w == 0 || h == 0) {
                data_ = nullptr;
                return;
            }

            data_ = new _T*[size_.height];
            data_[0] = new _T[size_.area()]();
            for (int32_t i = 1; i < size_.height; i++)
                data_[i] = data_[i - 1] + size_.width;
        }

        void release_memory() {
            if (data_ != nullptr) {
                delete[] data_[0];
                delete[] data_;
            }
        }

    private:
        Size size_;
        _T **data_;
    };
}

#endif //MYNT_BASIC_ALGTHMS_YIMG_H
