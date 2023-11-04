#include "index_buffer.hpp"

graphics::IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count, const unsigned int usage)
    : m_id(0), m_count(count) {
    glCall(glGenBuffers(1, &m_id));
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
    glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data, usage));
}

graphics::IndexBuffer::~IndexBuffer() {
    glCall(glDeleteBuffers(1, &m_id));
}

void graphics::IndexBuffer::bind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id));
}

void graphics::IndexBuffer::unbind() const {
    glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
