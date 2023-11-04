#pragma once
#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "graphics_base.hpp"
#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "buffer_layout.hpp"

namespace graphics {
    class Drawable {
    private:
        Shader* shader;
        VertexArray* va;
        VertexBuffer* vb;
        IndexBuffer* ib;
    public:
        Drawable(const void* vertexData, const size_t vertexDataSize, const unsigned int* indices, const size_t indicesCount, unsigned int usage, const BufferLayout& bufferLayout);
        ~Drawable();

        virtual void draw();
    };
} // namespace graphics

#endif