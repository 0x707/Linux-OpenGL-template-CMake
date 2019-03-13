#include "shloader.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>
#include <cstring>

namespace {

    SHADER_TYPE get_shader_type(char const* shader_path) noexcept
    {
        char const* index{ shader_path };
        while (*(++index) != '\0');
        while (*(--index) != '.');
        assert(*index == '.');
        
        if (strcmp(++index, "vert") == 0)
            return SHADER_TYPE::VERTEX;
        if (strcmp(index, "frag") == 0)
            return SHADER_TYPE::FRAGMENT;

        assert(false);
    }

} // namespace anonymous

ShaderLoader::ShaderLoader(char const* path) noexcept
{
    file_ = fopen(path, "rb");
    assert(file_ != nullptr);
}

ShaderLoader::~ShaderLoader()
{
    close();
}

void ShaderLoader::open(char const* path) noexcept
{
    if (file_ == nullptr)
        file_ = fopen(path, "rb");
    assert(file_ != nullptr);
}

void ShaderLoader::close() noexcept
{
    if (file_ != nullptr)
        fclose(file_);
    if (content_ != nullptr)
        delete[] content_;
    file_ = nullptr;
    content_ = nullptr;
}

char const* ShaderLoader::read() noexcept
{
   if (file_ != nullptr) {
       fseek(file_, 0, SEEK_END);
       long f_byte_size{ftell(file_)};
       fseek(file_, 0, SEEK_SET);

       content_ = new char[f_byte_size + 1];
       fread(content_, sizeof(char), f_byte_size, file_);
       if (ferror(file_)) {
           std::cerr << "Error while reading file.\n";
           assert(false);
       }
       content_[f_byte_size] = '\0';
       return content_;
   }
   return "";
}

// SIMPLE SHADER

SimpleShader::~SimpleShader()
{
    stop_using();
}

void SimpleShader::check_errors() noexcept
{
    int const cMaxMsgLen = 512;
    int success;
	char infoLog[cMaxMsgLen];
	glGetShaderiv(shaders_[index_], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaders_[index_], cMaxMsgLen, nullptr, infoLog);
		std::cerr << "Vertex: " << infoLog << std::endl;
        assert(false);
	}
}

void SimpleShader::check_errors_program() noexcept
{
    int const cMaxMsgLen = 512;
    int success;
	char infoLog[cMaxMsgLen];
	glGetProgramiv(program_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program_, cMaxMsgLen, nullptr, infoLog);
		std::cerr << "Program: " << infoLog << std::endl;
        assert(false);
	}
}

void SimpleShader::init_shader(char const* shaderPath) noexcept
{
    SHADER_TYPE shaderType{get_shader_type(shaderPath)};

    ShaderLoader sl{shaderPath};
    char const* shaderSource{sl.read()};

    assert(++index_ < MAX_SHADERS);
    switch (shaderType) {
        case SHADER_TYPE::VERTEX:
            shaders_[index_] = glCreateShader(GL_VERTEX_SHADER);
            break;
        case SHADER_TYPE::FRAGMENT:
            shaders_[index_] = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            assert(false);
    }

    glShaderSource(shaders_[index_], 1, &shaderSource, nullptr);
    glCompileShader(shaders_[index_]);

    check_errors();
}

void SimpleShader::init_program() noexcept
{
    stop_using();
    program_ = glCreateProgram();
    for (int i = 0; i <= index_; ++i)
        glAttachShader(program_, shaders_[i]);
    glLinkProgram(program_);
    check_errors_program();

    for (int i = 0; i <= index_; ++i)
        glDeleteShader(shaders_[i]);

    reset_index();
    use();
}

void SimpleShader::uni_float(char const* uni_name, float val) noexcept
{
    glUniform1f(glGetUniformLocation(program_, uni_name), val);
}

void SimpleShader::uni_int(char const* uni_name, int val) noexcept
{
    glUniform1i(glGetUniformLocation(program_, uni_name), val);
}

void SimpleShader::uni_mat4fv(char const* uni_name, float const* mat_ptr) noexcept
{
    glUniformMatrix4fv(glGetUniformLocation(program_, uni_name), 1, GL_FALSE, mat_ptr);
}
