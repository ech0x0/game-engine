#include "shader.hpp"

graphics::Shader::Shader(const std::string& name)
    : m_name("../res/shaders/" + name), m_id(0) {
    glCall(m_id = glCreateProgram());

    shaderSource source = parseShader();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, source.vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.fragmentShaderSource);

    glCall(glAttachShader(m_id, vs));
    glCall(glAttachShader(m_id, fs));
    glCall(glLinkProgram(m_id));
    glCall(glValidateProgram(m_id));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));
}

graphics::Shader::~Shader() {
    glCall(glDeleteProgram(m_id));
}

void graphics::Shader::bind() const {
    glCall(glUseProgram(m_id));
}

void graphics::Shader::unbind() const {
    glCall(glUseProgram(0));
}

void graphics::Shader::setUniform1f(const std::string& name, float value) {
    glCall(glUniform1f(getUniformLocation(name), value));
}

void graphics::Shader::setUniform2f(const std::string& name, vec2<float> value) {
    glCall(glUniform2f(getUniformLocation(name), value.x, value.y));
}

void graphics::Shader::setUniform3f(const std::string& name, vec3<float> value) {
    glCall(glUniform3f(getUniformLocation(name), value.x, value.y, value.z));
}
void graphics::Shader::setUniform4f(const std::string& name, vec4<float> value) {
    glCall(glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w));
}

int graphics::Shader::getUniformLocation(const std::string& name) {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) return m_uniformLocationCache[name];

    glCall(int location = glGetUniformLocation(m_id, name.c_str()));
    if (location == -1) {
        printf("Warning: Uniform ");
        printf("%s", name.c_str());
        printf(" does not exist!\n");
    }

    m_uniformLocationCache[name] = location;

    return location;
}

std::string fileToString(const std::string& filePath) {
    FILE* filePtr = fopen(filePath.c_str(), "rb");

    if (!filePtr) {
        fprintf(stderr, "File ");
        fprintf(stderr, "%s", filePath.c_str());
        fprintf(stderr, " does not exist!\n");

        return std::string();
    }

    fseek(filePtr, 0, SEEK_END);
    long size = ftell(filePtr);
    rewind(filePtr);

    char* buffer = (char*)malloc(size);
    fread(buffer, 1, size, filePtr);

    std::string str(buffer);
    free(buffer);

    return str;
}

graphics::Shader::shaderSource graphics::Shader::parseShader() {
    shaderSource source;

    source.vertexShaderSource = fileToString(m_name + "-vertex.glsl");
    source.fragmentShaderSource = fileToString(m_name + "-fragment.glsl");

    return source;
}

unsigned int graphics::Shader::compileShader(const GLenum type, const std::string& source) {
    glCall(unsigned int id = glCreateShader(type));

    const char* src = source.c_str();
    glCall(glShaderSource(id, 1, &src, 0));
    glCall(glCompileShader(id));

    int result;
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* message = (char*)malloc(length);
        glCall(glGetShaderInfoLog(id, length, &length, message));

        fprintf(stderr, "Failed to compile ");
        fprintf(stderr, type == GL_VERTEX_SHADER ? "vertex" : "fragment");
        fprintf(stderr, " shader:\n");
        fprintf(stderr, "%s\n", message);

        free(message);

        glCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
