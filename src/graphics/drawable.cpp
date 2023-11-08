#include "drawable.hpp"

graphics::Drawable::Drawable(const char* shaderName, const bool isUnique, const void* vertexData, const size_t vertexDataSize, const unsigned int* indices, const size_t indicesCount, unsigned int usage, const BufferLayout& bufferLayout) {
    m_shader = new Shader(shaderName, isUnique);
    m_va = new VertexArray();
    m_vb = new VertexBuffer(vertexData, vertexDataSize, usage);
    m_ib = new IndexBuffer(indices, indicesCount, usage);

    bufferLayout.callVertexAttribPointer();

    m_vb->unbind();
    m_va->unbind();
    m_ib->unbind();
}

graphics::Drawable::~Drawable() {
    delete m_shader;
    delete m_va;
    delete m_vb;
    delete m_ib;
}

void graphics::Drawable::draw() {
    m_shader->bind();
    m_ib->bind();
    m_va->bind();

    glCall(glDrawElements(GL_TRIANGLES, m_ib->getCount(), GL_UNSIGNED_INT, 0));

    m_shader->unbind();
    m_va->unbind();
    m_ib->unbind();
}

void graphics::Drawable::setColor(const vec4<float>& color) {
    m_shader->setUniform4f("u_color", color);
}

graphics::Shader* graphics::Drawable::getShader() const {
    return m_shader;
}
