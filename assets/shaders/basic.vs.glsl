#version 330 core
layout(location = 0) in vec2 pos;

const float xScale = 1920.f;
const float yScale = 1080.f;

void main() {
    gl_Position = vec4(pos.x / xScale, pos.y / yScale, 1.0, 1.0); 
}