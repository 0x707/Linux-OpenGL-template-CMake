#ifndef MATRIX_KERAM_CLASS_H_
#define MATRIX_KERAM_CLASS_H_

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

enum modif {
    TRNS, SCLE, ROTE
};

class Mat4f
{
public:
    Mat4f& operator=(mat4&&) noexcept;

    void look_at(vec3 const&, vec3 const&, vec3 const&) noexcept;
    void normalize() noexcept;
    void perspective(float, float, float, float, float) noexcept;
    void rotate(float, vec3 const&) noexcept;
    void scale(vec3 const&) noexcept;
    void translate(vec3 const&) noexcept;

    float const* first_elem() const noexcept;
private:
    mat4 mat_{1.0f};
};

#endif // !MATRIX_KERAM_CLASS_H_