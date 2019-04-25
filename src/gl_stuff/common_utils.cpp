#include "gl_stuff/common_utils.h"

void bind_vert_array(unsigned& varr) noexcept
{
	glBindVertexArray(varr);
}

void bind_vert_buffer(unsigned& buf) noexcept
{
    glBindBuffer(GL_ARRAY_BUFFER, buf);
}

void bind_elem_buffer(unsigned& buf) noexcept
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf);
}

void unbind_vertex_array() noexcept
{
    glBindVertexArray(0);
}