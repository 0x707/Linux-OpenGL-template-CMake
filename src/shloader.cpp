#include "shloader.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>
#include <cstring>

namespace {

    SHADER_TYPE get_shader_type(char const* shader_path)
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

}

ShaderLoader::ShaderLoader(char const* path)
{
    file_ = fopen(path, "rb");
    assert(file_ != nullptr);
}

ShaderLoader::~ShaderLoader()
{
    close();
}

void ShaderLoader::open(char const* path)
{
    if (file_ == nullptr) {
        file_ = fopen(path, "rb");
    }
    assert(file_ != nullptr);
}

void ShaderLoader::close()
{
    if (file_ != nullptr)
        fclose(file_);
    if (content_ != nullptr)
        delete[] content_;
    file_ = nullptr;
}

char const* ShaderLoader::read()
{
   if (file_ != nullptr) {
       fseek(file_, 0, SEEK_END);
       long fByteSize{ftell(file_)};
       fseek(file_, 0, SEEK_SET);

       content_ = new char[fByteSize + 1];
       fread(content_, sizeof(char), fByteSize, file_);
       if (ferror(file_)) {
           std::cerr << "Error while reading file.\n";
           assert(false);
       }
       content_[fByteSize] = '\0';
       return content_;
   }

}

// SIMPLE SHADER

unsigned& SimpleShader::operator()()
{
    static int i = -1;
    return shaders_[++i];
}

void SimpleShader::check_errors(int index)
{
    int const cMaxMsgLen = 512;
    int success;
	char infoLog[cMaxMsgLen];
	glGetShaderiv(shaders_[index], GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaders_[index], cMaxMsgLen, nullptr, infoLog);
		std::cerr << "Vertex: " << infoLog << std::endl;
        assert(false);
	}
}

void SimpleShader::check_errors_program()
{
    int const cMaxMsgLen = 512;
    int success;
	char infoLog[cMaxMsgLen];
	glGetProgramiv(program_, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program_, cMaxMsgLen, nullptr, infoLog);
		std::cerr << "Vertex: " << infoLog << std::endl;
        assert(false);
	}
}

void SimpleShader::init_shader(char const* shaderPath)
{
    static int index = -1;
    SHADER_TYPE shaderType{get_shader_type(shaderPath)};

    ShaderLoader sl{shaderPath};
    char const* shaderSource{sl.read()};

    assert(++index < MAX_SHADERS + 1);
    if (shaderType == SHADER_TYPE::VERTEX)
        shaders_[index] = glCreateShader(GL_VERTEX_SHADER);
    else if (shaderType == SHADER_TYPE::FRAGMENT)
        shaders_[index] = glCreateShader(GL_FRAGMENT_SHADER);
    else
        assert(false);

    glShaderSource(shaders_[index], 1, &shaderSource, nullptr);
    glCompileShader(shaders_[index]);

    check_errors(index);
    ++shaders_count_;
}

void SimpleShader::init_program()
{
    program_ = glCreateProgram();
    for (int i = 0; i < shaders_count_; ++i)
        glAttachShader(program_, shaders_[i]);
    glLinkProgram(program_);
    check_errors_program();

    for (int i = 0; i < shaders_count_; ++i)
        glDeleteShader(shaders_[i]);
}
