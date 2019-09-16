//
// Created by cg on 9/16/19.
//

#ifndef MYNT_BASIC_ALGTHMS_TYPES_H
#define MYNT_BASIC_ALGTHMS_TYPES_H

namespace mynt {

    struct Size {
        unsigned int width;
        unsigned int height;

        Size() {width = height = 0;}

        Size(unsigned int w, unsigned int h) : width(w), height(h) {}

        Size(const Size &size) : width(size.width), height(size.height) {}

        bool operator==(const Size &rhs) const {
            return width == rhs.width && height == rhs.height;
        }

        bool operator!=(const Size &rhs) const {
            return width != rhs.width || height != rhs.height;
        }

        Size &operator=(const Size &rhs) {
            if(this == &rhs)
                return *this;
            width  = rhs.width;
            height = rhs.height;
            return *this;
        }

        Size operator+(const Size &rhs) const {
            Size size;
            size.width  = width  + rhs.width;
            size.height = height + rhs.height;
            return size;
        }

        Size operator-(const Size &rhs) const {
            Size size;
            size.width  = width  - rhs.width;
            size.height = height - rhs.height;
            return size;
        }

        Size operator*(int n) const {
            Size size;
            size.width  = width  * n;
            size.height = height * n;
            return size;
        }

        Size operator/(int n) const {
            Size size;
            size.width  = width  / n;
            size.height = height / n;
            return size;
        }

        friend std::ostream &operator<<(std::ostream &os, const Size &size){
            return os << "[" << size.width << "," << size.height << "]";
        }

        inline unsigned int area() const {
            return width * height;
        }
    };
}

#endif //MYNT_BASIC_ALGTHMS_TYPES_H
