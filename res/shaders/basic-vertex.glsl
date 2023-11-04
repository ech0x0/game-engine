#version 330 core
layout(location = 0) in vec2 pos;

const float xSize = 1920.f;
const float ySize = 1080.f;

void main() {
    gl_Position = vec4(pos.x / xSize, pos.y / ySize, 1.0, 1.0); 
}