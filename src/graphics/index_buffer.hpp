#pragma once
#ifndef INDEX_BUFFER_HPP
#define INDEX_BUFFER_HPP

#include "graphics_base.hpp"

namespace graphics {
    class IndexBuffer {
    private:
        unsigned int m_id;
        unsigned int m_count;
    public:
        // usage = GL_STREAM_DRAW if buffer is going to be changed completely frequently
        //       = GL_STATIC_DRAW if buffer is not going to be changed frequently
        //       = GL_DYNAMIC_DRAW if buffer is going to be changed partially frequently
        IndexBuffer(const unsigned int* data, const unsigned int count, const unsigned int usage);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;
    };
} // namespace graphics

#endif