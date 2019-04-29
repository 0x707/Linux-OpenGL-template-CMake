#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

using glm::vec3;
using glm::radians;
using glm::normalize;
using glm::cross;

struct camera::pImpl
{
    pImpl(vec3 pos, vec3 wup, float yaw, float pitch)
        : pos_{pos}, world_up_{wup}, yaw_{yaw}, pitch_{pitch}
    {}

    void update_vectors() noexcept;
    glm::mat4 view_matrix() const noexcept;
    void keyboard_input(CAM_DIR, float) noexcept;
    void mouse_input(float, float) noexcept;
    void mouse_scroll(float) noexcept;

    vec3 pos_;
    vec3 front_{0.f, 0.f, -1.f};
    vec3 up_;
    vec3 right_;
    vec3 world_up_;

    float yaw_;
    float pitch_;
    float mv_speed_ = cSpeed;
    float sensitivty_ = cSensitivity;
    float zoom_ = cZoom;
};

void camera::pImpl::update_vectors() noexcept
{
    front_.x = cos(radians(yaw_)) * cos(radians(pitch_));
    front_.y = sin(radians(pitch_));
    front_.z = sin(radians(yaw_)) * cos(radians(pitch_));
    front_ = normalize(front_);

    right_ = normalize(cross(front_, world_up_));
    up_ = normalize(cross(right_, front_));
}

glm::mat4 camera::pImpl::view_matrix() const noexcept
{
    return glm::lookAt(pos_, pos_ + front_, up_);
}

void camera::pImpl::keyboard_input(CAM_DIR dir, float dt_time) noexcept
{
    float velocity = mv_speed_ * dt_time;
    if (dir == CAM_DIR::FRWD)
        pos_ += front_ * velocity;
    if (dir == CAM_DIR::BCWD)
        pos_ -= front_ * velocity;
    if (dir == CAM_DIR::LEFT)
        pos_ -= right_ * velocity;
    if (dir == CAM_DIR::RGHT)
        pos_ += right_ * velocity;
}

void camera::pImpl::mouse_input(float xoff, float yoff) noexcept
{
    yaw_ += xoff * sensitivty_;
    pitch_ += yoff * sensitivty_;

    if (pitch_ > 89.99f)
        pitch_ = 89.99f;
    if (pitch_ < -89.99)
        pitch_ = -89.99;

    update_vectors();
}

void camera::pImpl::mouse_scroll(float yoff) noexcept
{
    if (zoom_ > 1.f && zoom_ < 45.f)
        zoom_ -= yoff;
    if (zoom_ <= 1.f)
        zoom_ = 1.f;
    else if (zoom_ >= 45.f)
        zoom_ = 45.f;
}

/**
 * CAMERA CLASS
 */

camera::camera(vec3 pos, vec3 wup,
                float yaw, float pitch) noexcept
    : impl_{ std::make_unique<pImpl>(pos, wup, yaw, pitch)}
{
    impl_->update_vectors();
}

camera::~camera() noexcept = default;

glm::mat4 camera::view_matrix() const noexcept
{
    return impl_->view_matrix();
}

void camera::kb_input(CAM_DIR dir, float dt_time) noexcept
{
    impl_->keyboard_input(dir, dt_time);
}

void camera::ms_input(float xoff, float yoff) noexcept
{
    impl_->mouse_input(xoff, yoff);    
}

void camera::ms_scroll(float yoff) noexcept
{
    impl_->mouse_scroll(yoff);
}

float camera::get_zoom() const noexcept
{
    return impl_->zoom_;
}
