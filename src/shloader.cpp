#include "shloader.h"
#include <glad/glad.h>
#include <iostream>
#include <cassert>

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

SimpleShader::SimpleShader(char const* path, SHADER_TYPE shaderType)
    : remains_active{ true }
{
    ShaderLoader sl{path};
    char const* shaderSource{sl.read()};

    if (shaderType == SHADER_TYPE::VERTEX)
        shader_ = glCreateShader(GL_VERTEX_SHADER);
    else
        shader_ = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader_, 1, &shaderSource, nullptr);
    glCompileShader(shader_);

    check_errors();
}

SimpleShader::~SimpleShader()
{
    delete_shader();
}

void SimpleShader::delete_shader()
{
    if (remains_active)
        glDeleteShader(shader_);
    remains_active = false;
}

unsigned& SimpleShader::operator()()
{
    return shader_;
}

void SimpleShader::check_errors()
{
    int const cMaxMsgLen = 512;
    int success;
	char infoLog[cMaxMsgLen];
	glGetShaderiv(shader_, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_, cMaxMsgLen, nullptr, infoLog);
		std::cerr << "Vertex: " << infoLog << std::endl;
        assert(false);
	}
}
