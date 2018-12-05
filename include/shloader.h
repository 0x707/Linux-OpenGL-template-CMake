#include <stdio.h>

#ifndef SHLOADER_CLASS_H_
#define SHLOADER_CLASS_H_

enum class SHADER_TYPE { VERTEX, FRAGMENT };

class ShaderLoader
{
public:
    ShaderLoader() : file_{nullptr} {}
    explicit ShaderLoader(char const*);
    ShaderLoader(ShaderLoader const*) = delete;
    ShaderLoader& operator=(ShaderLoader const&) = delete;
    ~ShaderLoader();

    void open(char const*);
    void close();
    char const* read();
private:
    FILE* file_;
    char* content_ = nullptr;
};

class SimpleShader
{
public:
    SimpleShader(char const*, SHADER_TYPE);
    SimpleShader(SimpleShader const&) = delete;
    SimpleShader& operator=(SimpleShader const&) = delete;
    ~SimpleShader();
    unsigned& operator()();

    void delete_shader();
private:
    unsigned shader_;
    bool remains_active;

    void check_errors();
};

#endif // !SHLOADER_CLASS_H_