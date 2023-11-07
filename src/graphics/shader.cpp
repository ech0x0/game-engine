#include "shader.hpp"

#include <string>
#include <unordered_map>

static char* fileToString(const char* filePath) {
    FILE* filePtr = fopen(filePath, "rb");

    if (!filePtr) {
        fprintf(stderr, "File ");
        fprintf(stderr, "%s", filePath);
        fprintf(stderr, " does not exist!\n");

        return nullptr;
    }

    fseek(filePtr, 0, SEEK_END);
    long size = ftell(filePtr);
    rewind(filePtr);

    char* buffer = (char*)malloc(size);
    fread(buffer, 1, size, filePtr);

    return buffer;
}

static unsigned int compileShader(const GLenum type, const char* source) {
    glCall(unsigned int id = glCreateShader(type));

    glCall(glShaderSource(id, 1, &source, 0));
    glCall(glCompileShader(id));

    int result;
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

        char* message = (char*)malloc(length);
        glCall(glGetShaderInfoLog(id, length, &length, message));

        printError(("Failed to compile " + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader: " + std::string(message)).c_str());

        free(message);

        glCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

static unsigned int createNewShaderFromSource(const char* shaderName, bool* compileSucceded) {
    glCall(unsigned int id = glCreateProgram());

    char* vertexShaderSource = fileToString(("../assets/shaders/" + std::string(shaderName) + ".vs.glsl").c_str());
    char* fragmentShaderSource = fileToString(("../assets/shaders/" + std::string(shaderName) + ".fs.glsl").c_str());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    if (vs != 0 && fs != 0) *compileSucceded = true;
    else *compileSucceded = false;

    free(vertexShaderSource);
    free(fragmentShaderSource);

    glCall(glAttachShader(id, vs));
    glCall(glAttachShader(id, fs));
    glCall(glLinkProgram(id));
    glCall(glValidateProgram(id));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));

    return id;
}

static unsigned int createNewShaderFromBinary(unsigned int binaryFormat, int binaryLength, void* shaderBinary) {
    glCall(unsigned int id = glCreateProgram());

    glCall(glProgramBinary(id, binaryFormat, shaderBinary, binaryLength));
    glCall(glValidateProgram(id));

    return id;
}

static void cacheShader(unsigned int id, const char* name) {
    int binaryLength;
    glGetProgramiv(id, GL_PROGRAM_BINARY_LENGTH, &binaryLength);

    unsigned int binaryFormat;
    void* shaderBinary = malloc(binaryLength);
    glGetProgramBinary(id, binaryLength, &binaryLength, &binaryFormat, shaderBinary);

    FILE* shaderFile = fopen(("shader_cache/" + std::string(name)).c_str(), "wb");

    if (shaderFile) {
        unsigned int gameVersion = GAME_VERSION;
        fwrite(&gameVersion, sizeof(unsigned int), 1, shaderFile);
        fwrite(&binaryFormat, sizeof(unsigned int), 1, shaderFile);
        fwrite(&binaryLength, sizeof(unsigned int), 1, shaderFile);
        fwrite(shaderBinary, sizeof(char), binaryLength, shaderFile);
        fclose(shaderFile);
    } else {
        printError(("Failed to open shader cache file \"" + std::string(name) + "\" for writing").c_str());
    }

    free(shaderBinary);
}

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>
void createDir(const char* dirName) {
    CreateDirectory(dirName, NULL);
}

#else

#include <sys/stat.h>
void createDir(const char* dirName) {
    mkdir(dirName, S_IRWXU | S_IRWXG | S_IRWXO);
}

#endif

static FILE* openShaderCache(const char* name) {
    createDir("shader_cache");
    FILE* shaderFile = fopen(("shader_cache/" + std::string(name)).c_str(), "rb");

    // check if shader cache exists
    if (shaderFile) {
        // check if shader cache is valid
        unsigned int versionNumber;
        fread(&versionNumber, sizeof(unsigned int), 1, shaderFile);

        if (versionNumber != GAME_VERSION) {
            fclose(shaderFile);
            return 0;
        }

        return shaderFile;
    } else {
        return 0;
    }
}

static unsigned int createUniqueShader(const char* name) {
    unsigned int id;

    FILE* shaderFile = openShaderCache(name);
    if (shaderFile) {
        // Read binary format and length
        int binaryLength;
        unsigned int binaryFormat;
        fread(&binaryFormat, sizeof(unsigned int), 1, shaderFile);
        fread(&binaryLength, sizeof(int), 1, shaderFile);

        void* shaderBinary = malloc(binaryLength);

        // Read binary from the cache file
        fread(shaderBinary, sizeof(char), binaryLength, shaderFile);
        fclose(shaderFile);

        id = createNewShaderFromBinary(binaryFormat, binaryLength, shaderBinary);

        free(shaderBinary);
    } else {
        bool compileSucceded;
        id = createNewShaderFromSource(name, &compileSucceded);
        if (compileSucceded) cacheShader(id, name);
    }

    return id;
}

// std::string -> shader name
// unsigned int -> shader id
// unsigned int -> shader use counter
std::unordered_map<std::string, unsigned int> sharedShadersIds;
std::unordered_map<unsigned int, unsigned int> sharedShadersCounters;

static unsigned int createSharedShader(const char* name) {
    if (sharedShadersIds.find(std::string(name)) != sharedShadersIds.end()) {
        unsigned int id = sharedShadersIds[std::string(name)];
        if (sharedShadersCounters[id] != 0) {
            sharedShadersCounters[id]++;
            return id;
        }
    }

    unsigned int id = createUniqueShader(name);
    sharedShadersIds[std::string(name)] = id;
    sharedShadersCounters[id] = 1;
    return id;
}

static unsigned int createShader(const char* name, const bool isUnique) {
    if (isUnique) {
        return createUniqueShader(name);
    }
    return createSharedShader(name);
}

static void destroyUniqueShader(unsigned int id) {
    glCall(glDeleteProgram(id));
}

static void destroySharedShader(unsigned int id) {
    sharedShadersCounters[id]--;
    if (sharedShadersCounters[id] == 0) destroyUniqueShader(id);
}

static void destroyShader(unsigned int id, const bool isUnique) {
    if (isUnique) destroyUniqueShader(id);
    else destroySharedShader(id);
}

std::unordered_map<unsigned int, std::unordered_map<std::string, int>> uniformLocationCache;
static int getShaderUniformLocation(unsigned int id, const std::string& uniformName) {
    std::unordered_map<std::string, int>& locationCache = uniformLocationCache[id];
    const auto find = locationCache.find(uniformName);

    if (find != locationCache.end()) return locationCache[uniformName];

    glCall(int location = glGetUniformLocation(id, uniformName.c_str()));
    if (location == -1) {
        printf("Warning: Uniform %s does not exist!\n", uniformName.c_str());
    }

    locationCache[uniformName] = location;

    return location;
}

static void setShaderUniform1f(const int id, const char* name, float value) {
    glCall(glUniform1f(getShaderUniformLocation(id, name), value));
}

static void setShaderUniform2f(const int id, const char* name, vec2<float> value) {
    glCall(glUniform2f(getShaderUniformLocation(id, name), value.x, value.y));
}

static void setShaderUniform3f(const int id, const char* name, vec3<float> value) {
    glCall(glUniform3f(getShaderUniformLocation(id, name), value.x, value.y, value.z));
}

static void setShaderUniform4f(const int id, const char* name, vec4<float> value) {
    glCall(glUniform4f(getShaderUniformLocation(id, name), value.x, value.y, value.z, value.w));
}

graphics::Shader::Shader(const char* name, bool isUnique) {
    m_id = createShader(name, isUnique);
    m_isUnique = isUnique;
}

graphics::Shader::~Shader() {
    destroyShader(m_id, m_isUnique);
}

void graphics::Shader::bind() const {
    glCall(glUseProgram(m_id));
}

void graphics::Shader::unbind() const {
    glCall(glUseProgram(0));
}

void graphics::Shader::setUniform1f(const char* name, float value) {
    bind();
    setShaderUniform1f(m_id, name, value);
    unbind();
}

void graphics::Shader::setUniform2f(const char* name, vec2<float> value) {
    bind();
    setShaderUniform2f(m_id, name, value);
    unbind();
}

void graphics::Shader::setUniform3f(const char* name, vec3<float> value) {
    bind();
    setShaderUniform3f(m_id, name, value);
    unbind();
}

void graphics::Shader::setUniform4f(const char* name, vec4<float> value) {
    bind();
    setShaderUniform4f(m_id, name, value);
    unbind();
}

int graphics::Shader::getUniformLocation(const char* name) {
    return getShaderUniformLocation(m_id, name);
}
