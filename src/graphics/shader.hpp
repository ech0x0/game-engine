#pragma once
#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>
#include "graphics_base.hpp"
#include "../data_types/vec4.hpp"

namespace graphics {
    class Shader {
    private:
        std::string m_name;
        unsigned int m_id;

        std::unordered_map<std::string, int> m_uniformLocationCache;
    public:
        Shader(const std::string& name);
        ~Shader();

        void bind() const;
        void unbind() const;

        void setUniform4f(const std::string& name, vec4<float> value);
    private:
        struct shaderSource {
            std::string vertexShaderSource;
            std::string fragmentShaderSource;
        };
        shaderSource parseShader();
        unsigned int compileShader(const GLenum type, const std::string& source);

        int getUniformLocation(const std::string& name);
    };
} // namespace graphics

#endif