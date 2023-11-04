#include "vertex_array.hpp"

graphics::VertexArray::VertexArray()
    : m_id(0) {
    glCall(glGenVertexArrays(1, &m_id));
    glCall(glBindVertexArray(m_id));
}

graphics::VertexArray::~VertexArray() {
    glCall(glDeleteVertexArrays(1, &m_id));
}

void graphics::VertexArray::bind() const {
    glCall(glBindVertexArray(m_id));
}

void graphics::VertexArray::unbind() const {
    glCall(glBindVertexArray(0));
}
