#include "shloader.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>
#include <cstring>

namespace {

    SHADER_TYPE get_shader_type(char const* shader_path)
    {
        char const* index_{ shader_path };
        while (*(++index_) != '\0');
        while (*(--index_) != '.');
        assert(*index_ == '.');
        
        if (strcmp(++index_, "vert") == 0)
            return SHADER_TYPE::VERTEX;
        if (strcmp(index_, "frag") == 0)
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
    content_ = nullptr;
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

void SimpleShader::check_errors()
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
    SHADER_TYPE shaderType{get_shader_type(shaderPath)};

    ShaderLoader sl{shaderPath};
    char const* shaderSource{sl.read()};

    assert(++index_ < MAX_SHADERS + 1);
    if (shaderType == SHADER_TYPE::VERTEX)
        shaders_[index_] = glCreateShader(GL_VERTEX_SHADER);
    else if (shaderType == SHADER_TYPE::FRAGMENT)
        shaders_[index_] = glCreateShader(GL_FRAGMENT_SHADER);
    else
        assert(false);

    glShaderSource(shaders_[index_], 1, &shaderSource, nullptr);
    glCompileShader(shaders_[index_]);

    check_errors();
}

void SimpleShader::init_program()
{
    program_ = glCreateProgram();
    for (int i = 0; i < index_ + 1; ++i)
        glAttachShader(program_, shaders_[i]);
    glLinkProgram(program_);
    check_errors_program();

    for (int i = 0; i < index_ + 1; ++i)
        glDeleteShader(shaders_[i]);
}

void SimpleShader::uni_float(char const* uni_name, float val)
{
    glUniform1f(glGetUniformLocation(program_, uni_name), val);
}

void SimpleShader::uni_int(char const* uni_name, int val)
{
    glUniform1i(glGetUniformLocation(program_, uni_name), val);
}
