#include "matrix.h"
#include <glm/gtc/matrix_transform.hpp>
#include <utility>

Mat4f& Mat4f::operator=(mat4&& mat) noexcept
{
    mat_ = std::move(mat);
    return *this;
}

float const* Mat4f::first_elem() const noexcept
{
    return &mat_[0][0];
}

void Mat4f::look_at(vec3 const& pos, vec3 const& target,
    vec3 const& up) noexcept
{
    mat_ = glm::lookAt(pos, target, up);
}

void Mat4f::normalize() noexcept
{
    mat_ = mat4{ 1.0f };
}

void Mat4f::perspective(float fov, float width, float height,
    float near, float far) noexcept
{
    mat_ = glm::perspective(fov, width / height, near, far);
}

void Mat4f::rotate(float t, vec3 const& v) noexcept
{
    mat_ = glm::rotate(mat_, t, v);
}

void Mat4f::scale(vec3 const& v) noexcept
{
    mat_ = glm::scale(mat_, v);
}

void Mat4f::translate(vec3 const& v) noexcept
{
    mat_ = glm::translate(mat_, v);
}