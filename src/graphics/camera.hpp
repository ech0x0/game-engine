#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "graphics_base.hpp"
#include "../data_types/vec2.hpp"

namespace graphics {
    class Camera {
    private:
        vec2<float> m_pos;
        float m_scale;
    public:
        Camera();
        Camera(const vec2<float> pos);
        Camera(const vec2<float> pos, const float scale);

        vec2<float> getPos() const;
        void setPos(const vec2<float> pos);
        void move(const vec2<float> offset);

        float getScale() const;
        void setScale(const float scale);

        void updateUniforms() const;
    };
} // namespace graphics

#endif