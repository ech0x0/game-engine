#include "drawable.hpp"

graphics::Drawable::Drawable(const void* vertexData, const size_t vertexDataSize, const unsigned int* indices, const size_t indicesCount, unsigned int usage, const BufferLayout& bufferLayout) {
    shader = new Shader("../res/shaders/basic");
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

    glCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0));

    shader->unbind();
    va->unbind();
    ib->unbind();
}
