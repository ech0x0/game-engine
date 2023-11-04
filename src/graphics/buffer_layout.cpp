#include "buffer_layout.hpp"

void graphics::BufferLayout::callVertexAttribPointer() const {
    for (unsigned int i = 0; i < attributes.size(); ++i) {
        glCall(glVertexAttribPointer(i, attributes[i].size, attributes[i].type, attributes[i].normalized, stride, attributes[i].offset));
        glCall(glEnableVertexAttribArray(i));
    }
}
