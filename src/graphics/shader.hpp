#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include "graphics_base.hpp"

#include "../data_types/vec2.hpp"
#include "../data_types/vec3.hpp"
#include "../data_types/vec4.hpp"

namespace graphics {
    class Shader {
    private:
        unsigned int m_id;
        bool m_isUnique;
    public:
        Shader(const char* name, bool isUnique = true);
        ~Shader();

        void bind() const;
        void unbind() const;

        void setUniform1f(const char* name, float value);
        void setUniform2f(const char* name, vec2<float> value);
        void setUniform3f(const char* name, vec3<float> value);
        void setUniform4f(const char* name, vec4<float> value);
    private:
        int getUniformLocation(const char* name);
    };

    void setUniform1fToAllShaders(const char* name, float value);
    void setUniform2fToAllShaders(const char* name, vec2<float> value);
    void setUniform3fToAllShaders(const char* name, vec3<float> value);
    void setUniform4fToAllShaders(const char* name, vec4<float> value);
} // namespace graphics

#endif