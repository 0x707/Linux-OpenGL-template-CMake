#include <glad/glad.h>
#include <cstdio>
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

    ~SimpleShader();

    SimpleShader(SimpleShader const&) = delete;
    SimpleShader& operator=(SimpleShader const&) = delete;


    void uni_float(char const*, float);
    void uni_int(char const*, int);
    void uni_mat4fv(char const*, float const*);
    std::size_t const& get_program() const { return program_; }

    template<typename... Cargs>
    void reload(Cargs const*...);
private:
    std::size_t shaders_[MAX_SHADERS];
    std::size_t program_;
    bool remains_active_;
    int index_ = -1;

    void check_errors();
    void check_errors_program();
    void init_shader(char const*);
    void init_program();
    void reset_index() { index_ = -1; }
    void stop_using() { glDeleteProgram(program_); }
    void use() { glUseProgram(program_); }

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

template<typename... Cargs>
void SimpleShader::reload(Cargs const* ...cargs)
{
    reset_index();
    unpack(cargs...);
    init_program();
}

#endif // !SHLOADER_CLASS_H_