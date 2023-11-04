#pragma once
#ifndef VERTEX_ARRAY_HPP
#define VERTEX_ARRAY_HPP

#include "graphics_base.hpp"

namespace graphics {
    class VertexArray {
    private:
        unsigned int m_id;
    public:
        VertexArray();
        ~VertexArray();

        void bind() const;
        void unbind() const;
    };
} // namespace graphics

#endif