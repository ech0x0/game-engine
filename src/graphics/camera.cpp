#include "camera.hpp"

#include "shader.hpp"

graphics::Camera::Camera()
    : m_scale(1.f) {
    m_pos = { 0.f, 0.f };
}

graphics::Camera::Camera(const vec2<float> pos)
    : m_pos(pos), m_scale(1.f) {
}

graphics::Camera::Camera(const vec2<float> pos, const float scale)
    : m_pos(pos), m_scale(scale) {
}

vec2<float> graphics::Camera::getPos() const {
    return m_pos;
}

void graphics::Camera::setPos(const vec2<float> pos) {
    m_pos = pos;
    setUniform2fToAllShaders("u_cameraPos", m_pos);
}

void graphics::Camera::move(const vec2<float> offset) {
    m_pos += offset;
    setUniform2fToAllShaders("u_cameraPos", m_pos);
}

float graphics::Camera::getScale() const {
    return m_scale;
}

void graphics::Camera::setScale(const float scale) {
    m_scale = scale;
    setUniform1fToAllShaders("u_cameraScale", m_scale);
}

void graphics::Camera::updateUniforms() const {
    setUniform2fToAllShaders("u_cameraPos", m_pos);
    setUniform1fToAllShaders("u_cameraScale", m_scale);
}