#pragma once
#ifndef BUFFER_LAYOUT_HPP
#define BUFFER_LAYOUT_HPP

#include "graphics_base.hpp"
#include <vector>

namespace graphics {
    /*
    VertexAttributes example for a buffer with vertices of class Vertex

    class Vertex {
        float x, y, z;
        float r, g, b, w;
    };

    BufferLayout has 2 VertexAttributes

    VertexAttribute 0: size = 3
                       type = GL_FLOAT
                       normalized = GL_FALSE
                       pointer = 0 | = offsetof(Vertex, x)
                    1: size = 4
                       type = GL_FLOAT
                       normalized = GL_FALSE
                       offset = 12 | = offsetof(Vertex, r)

    We can use offsetof(class member) instead of using magic constants

    This is going to equate to 2 glVertexAttribPointer calls:
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0)
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12)
    */

    struct VertexAttribute {
        int size;    // number of components(type specified next) per attribute
        GLenum type; // float, int, etc.
        bool normalized;
        void* offset; // number of bytes to get to this attribute from the previous one
    };

    // stride is the size of a vertex in bytes or sizeof(vertex class)
    struct BufferLayout {
        int stride;
        void callVertexAttribPointer() const;
        std::vector<VertexAttribute> attributes;
    };
} // namespace graphics

#endif