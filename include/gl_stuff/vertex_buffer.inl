#include "common_utils.h"
#include "vertex_buffer.h"

VBO::~VBO() noexcept
{
    glDeleteBuffers(1, &vbo_);
}

// CONSIDER LATER USE OF ARRAY FOR CONSTRUCTING VERTEX RELATED OBJECTS
template<std::size_t S1, std::size_t S2>
VBO::VBO(array_f<S1, S2> const& af) noexcept
{
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, af.sizeof_content(), af.data(), GL_STATIC_DRAW);
}

template<std::size_t S1, std::size_t S2>
void VBO::fill_data(array_f<S1, S2> const& af) noexcept
{
    for (std::size_t attrib = 0; attrib < S2; ++attrib) {
        glVertexAttribPointer(attrib, af.stride(attrib), GL_FLOAT, GL_FALSE, af.sizeof_offset(), (void*)af.read_from_here(attrib));
        glEnableVertexAttribArray(attrib);
    }
}
