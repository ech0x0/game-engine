#pragma once
#ifndef VEC2_HPP
#define VEC2_HPP

template <class T>
struct vec2 {
    T x, y;

    vec2& operator+=(const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
};

#endif