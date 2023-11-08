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
        Shader* m_shader;
        VertexArray* m_va;
        VertexBuffer* m_vb;
        IndexBuffer* m_ib;
    public:
        Drawable(const char* shaderName, const bool isUnique, const void* vertexData, const size_t vertexDataSize, const unsigned int* indices, const size_t indicesCount, unsigned int usage, const BufferLayout& bufferLayout);
        ~Drawable();

        virtual void draw();
        virtual void setColor(const vec4<float>& color);

        Shader* getShader() const;
    };
} // namespace graphics

#endif