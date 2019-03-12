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
    Mat4f& operator=(mat4&&);

    void look_at(vec3 const&, vec3 const&, vec3 const&);
    void normalize();
    void perspective(float, float, float, float, float);
    void rotate(float, vec3 const&);
    void scale(vec3 const&);
    void translate(vec3 const&);

    float const* first_elem() const;
private:
    mat4 mat_{1.0f};
};

#endif // !MATRIX_KERAM_CLASS_H_