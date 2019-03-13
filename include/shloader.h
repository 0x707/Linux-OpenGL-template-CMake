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
    ShaderLoader() noexcept : file_{nullptr} {}
    explicit ShaderLoader(char const*) noexcept;
    ShaderLoader(ShaderLoader const*) = delete;
    ShaderLoader& operator=(ShaderLoader const&) = delete;
    ~ShaderLoader();

    void open(char const*) noexcept;
    void close() noexcept;
    char const* read() noexcept;
private:
    FILE* file_;
    char* content_ = nullptr;
};

class SimpleShader
{
public:
    template<typename... Cargs>
    explicit SimpleShader(Cargs const* ...) noexcept;

    ~SimpleShader();

    SimpleShader(SimpleShader const&) = delete;
    SimpleShader& operator=(SimpleShader const&) = delete;


    void uni_float(char const*, float) noexcept;
    void uni_int(char const*, int) noexcept;
    void uni_mat4fv(char const*, float const*) noexcept;
    //std::size_t const& get_program() const { return program_; }

    template<typename... Cargs>
    void reload(Cargs const*...) noexcept;
private:
    std::size_t shaders_[MAX_SHADERS];
    std::size_t program_;
    bool remains_active_;
    int index_ = -1;

    void check_errors() noexcept;
    void check_errors_program() noexcept;
    void init_shader(char const*) noexcept;
    void init_program() noexcept;
    void reset_index() noexcept { index_ = -1; }
    void stop_using() noexcept { glDeleteProgram(program_); }
    void use() noexcept { glUseProgram(program_); }

    template<typename C = char>
    void unpack(C const*) noexcept;
    template<typename C, typename... Cargs>
    void unpack(C const*, Cargs const* ...cargs) noexcept;
};

template<typename... Cargs>
SimpleShader::SimpleShader(Cargs const* ...cargs) noexcept
{
    unpack(cargs...);
    init_program();
}

template<typename C>
void SimpleShader::unpack(C const* carg) noexcept
{
    init_shader(carg);
}

template<typename C, typename... Cargs>
void SimpleShader::unpack(C const* carg, Cargs const* ...cargs) noexcept
{
    init_shader(carg);
    unpack(cargs...);
}

template<typename... Cargs>
void SimpleShader::reload(Cargs const* ...cargs) noexcept
{
    reset_index();
    unpack(cargs...);
    init_program();
}

#endif // !SHLOADER_CLASS_H_