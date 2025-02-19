#ifndef __SYLAR_NONCOPYABLE_H__
#define __SYLAR_NONCOPYABLE_H__

namespace sherry{
class Noncopyable{
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}

#endif