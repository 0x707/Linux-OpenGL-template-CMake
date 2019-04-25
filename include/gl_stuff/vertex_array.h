#ifndef VERTEX_ARRAY_KERAM_CLASS_H_
#define VERTEX_ARRAY_KERAM_CLASS_H_

#include "common_utils.h"

class VAO
{
public:
    VAO() noexcept { glGenVertexArrays(1, &vao_); bind(); }
    ~VAO() noexcept { glDeleteVertexArrays(1, &vao_); }

    VAO(VAO const&) = delete;
    VAO& operator=(VAO const&) = delete;

    void bind() noexcept { bind_vert_array(vao_); }
private:
    unsigned vao_;
};

// in glGenVertexArrays FIRST ARG is amount of VAO to generate
// and the SECOND ARG is an address of unsigned's array, where
// vaos are stored; consider later use of array; for now it is
// hardcoded behavior of generating one vao only

#endif // !VERTEX_ARRAY_KERAM_CLASS_H_
