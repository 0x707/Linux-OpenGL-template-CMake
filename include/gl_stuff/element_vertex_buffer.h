#ifndef ELEMENT_VERTEX_BUFFER_KERAM_CLASS_H_
#define ELEMENT_VERTEX_BUFFER_KERAM_CLASS_H_

#include "../detail/array_f.h"

class EBO
{
public:
    template<std::size_t S1>
    EBO(unsigned(&)[S1]) noexcept;
    ~EBO() noexcept;

    EBO(EBO const&) = delete;
    EBO& operator=(EBO const&) = delete;
private:
    unsigned ebo_;
};

#include "element_vertex_buffer.inl"

#endif // !ELEMENT_VERTEX_BUFFER_KERAM_CLASS_H_

