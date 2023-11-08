#include "camera.hpp"
#include <algorithm>

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

void graphics::Camera::addShader(Shader* shader) {
    m_shaders.push_front(shader);
    shader->setUniform2f("u_cameraPos", m_pos);
    shader->setUniform1f("u_cameraScale", m_scale);
}

void graphics::Camera::draw(Drawable* drawable) {
    m_drawables.push_back(drawable);
}

void graphics::Camera::drawAll() {
    while (!m_drawables.empty()) {
        m_drawables.front()->draw();
        m_drawables.pop_front();
    }
}

void graphics::Camera::setUniform1fToAllShaders(const char* name, const float value) {
    for (auto it = m_shaders.begin(); it != m_shaders.end();) {
        if ((*it) == nullptr) it = m_shaders.erase(it);
        else {
            (*it)->setUniform1f(name, value);
            ++it;
        }
    }
}

void graphics::Camera::setUniform2fToAllShaders(const char* name, const vec2<float> value) {
    for (auto it = m_shaders.begin(); it != m_shaders.end();) {
        if ((*it) == nullptr) it = m_shaders.erase(it);
        else {
            (*it)->setUniform2f(name, value);
            ++it;
        }
    }
}
