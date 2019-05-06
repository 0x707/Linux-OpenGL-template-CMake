#include "common_utils.h"
#include "element_vertex_buffer.h"

template<std::size_t S1>
EBO::EBO(unsigned (&uav)[S1]) noexcept
{
    glGenBuffers(1, &ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uav), uav, GL_STATIC_DRAW);
}

EBO::~EBO() noexcept
{
    glDeleteBuffers(1, &ebo_);
}