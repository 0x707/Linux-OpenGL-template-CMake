#include <glad/glad.h>
#include <stdio.h>
#include <cassert>

#ifndef SHLOADER_CLASS_H_
#define SHLOADER_CLASS_H_

enum class SHADER_TYPE { VERTEX, FRAGMENT };
constexpr int MAX_SHADERS{16};

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
    template<typename... Cargs>
    SimpleShader(Cargs const* ...);

    SimpleShader(SimpleShader const&) = delete;
    SimpleShader& operator=(SimpleShader const&) = delete;
    unsigned& operator()();

    void use() { glUseProgram(program_); }
    void stop_using(); // not implemented yet

    void uni_float(char const*, float);
    void uni_int(char const*, int);

private:
    unsigned shaders_[MAX_SHADERS];
    unsigned program_;
    bool remains_active_;
    int shaders_count_ = 0;

    void check_errors(int);
    void check_errors_program();
    void init_shader(char const*);
    void init_program();

    template<typename C = char>
    void unpack(C const*);
    template<typename C, typename... Cargs>
    void unpack(C const*, Cargs const* ...cargs);
};

template<typename... Cargs>
SimpleShader::SimpleShader(Cargs const* ...cargs)
{
    unpack(cargs...);
    init_program();
}

template<typename C>
void SimpleShader::unpack(C const* carg)
{
    init_shader(carg);
}

template<typename C, typename... Cargs>
void SimpleShader::unpack(C const* carg, Cargs const* ...cargs)
{
    init_shader(carg);
    unpack(cargs...);
}

#endif // !SHLOADER_CLASS_H_