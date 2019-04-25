#ifndef VERTEX_BUFFER_KERAM_CLASS_H_
#define VERTEX_BUFFER_KERAM_CLASS_H_

#include "../detail/array_f.h"

class VBO
{
public:
    VBO(VBO const&) = delete;
    VBO& operator=(VBO const&) = delete;
    ~VBO() noexcept;

    template<std::size_t S1, std::size_t S2>
    VBO(array_f<S1, S2> const&) noexcept;
   
    template<std::size_t S1, std::size_t S2>
    void fill_data(array_f<S1, S2> const&) noexcept;

private:
    unsigned vbo_;
};

#include "vertex_buffer.inl"

#endif // !VERTEX_BUFFER_KERAM_CLASS_H_

