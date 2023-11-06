#include "drawable.hpp"

graphics::Drawable::Drawable(const char* shaderName, const bool isUnique, const void* vertexData, const size_t vertexDataSize, const unsigned int* indices, const size_t indicesCount, unsigned int usage, const BufferLayout& bufferLayout) {
    shader = new Shader(shaderName, isUnique);
    va = new VertexArray();
    vb = new VertexBuffer(vertexData, vertexDataSize, usage);
    ib = new IndexBuffer(indices, indicesCount, usage);

    bufferLayout.callVertexAttribPointer();

    vb->unbind();
    va->unbind();
    ib->unbind();
}

graphics::Drawable::~Drawable() {
    delete shader;
    delete va;
    delete vb;
    delete ib;
}

void graphics::Drawable::draw() {
    shader->bind();
    ib->bind();
    va->bind();

    glCall(glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, 0));

    shader->unbind();
    va->unbind();
    ib->unbind();
}

void graphics::Drawable::setColor(const vec4<float>& color) {
    shader->setUniform4f("u_color", color);
}
