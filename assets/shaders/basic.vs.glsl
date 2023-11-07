#version 330 core
layout(location = 0) in vec2 pos;

uniform vec2 u_cameraPos;
uniform float u_cameraScale;

const vec2 positionScale = vec2(1920, 1080);

void main() {
    gl_Position = vec4((pos - u_cameraPos) / positionScale * u_cameraScale, 1.0, 1.0); 
}