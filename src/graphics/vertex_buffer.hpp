#pragma once
#ifndef VERTEX_BUFFER_HPP
#define VERTEX_BUFFER_HPP

#include "graphics_base.hpp"
#include <cstddef>

namespace graphics {
    class VertexBuffer {
    private:
        unsigned int m_id;
    public:
        // usage = GL_STREAM_DRAW if buffer is going to be changed completely frequently
        //       = GL_STATIC_DRAW if buffer is not going to be changed frequently
        //       = GL_DYNAMIC_DRAW if buffer is going to be changed partially frequently
        VertexBuffer(const void* data, const size_t size, const unsigned int usage);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    };
} // namespace graphics

#endif