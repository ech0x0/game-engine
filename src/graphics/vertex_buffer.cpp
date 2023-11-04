#include "vertex_buffer.hpp"

graphics::VertexBuffer::VertexBuffer(const void* data, const size_t size, const unsigned int usage)
    : m_id(0) {
    glCall(glGenBuffers(1, &m_id));
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
    glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

graphics::VertexBuffer::~VertexBuffer() {
    glCall(glDeleteBuffers(1, &m_id));
}

void graphics::VertexBuffer::bind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, m_id));
}

void graphics::VertexBuffer::unbind() const {
    glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
