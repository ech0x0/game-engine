#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "graphics_base.hpp"
#include "shader.hpp"
#include "drawable.hpp"
#include "../data_types/vec2.hpp"

#include <list>
#include <deque>

namespace graphics {
    class Camera {
    private:
        vec2<float> m_pos;
        float m_scale;

        std::list<Shader*> m_shaders;
        std::deque<Drawable*> m_drawables;
    public:
        Camera();
        Camera(const vec2<float> pos);
        Camera(const vec2<float> pos, const float scale);

        vec2<float> getPos() const;
        void setPos(const vec2<float> pos);
        void move(const vec2<float> offset);

        float getScale() const;
        void setScale(const float scale);

        void addShader(Shader* shader);

        void draw(Drawable* drawable);
        void drawAll();
    private:
        void setUniform1fToAllShaders(const char* name, const float value);
        void setUniform2fToAllShaders(const char* name, const vec2<float> value);
    };
} // namespace graphics

#endif