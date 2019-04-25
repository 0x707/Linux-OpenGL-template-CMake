#include "camera.h"

using glm::vec3;
using glm::radians;
using glm::normalize;
using glm::cross;


constexpr float cYaw = -90.f;
constexpr float cPitch = 0.f;
constexpr float cSpeed = 2.5f;
constexpr float cSensitivity = 0.1f;
constexpr float cZoom = 45.f;

struct camera::pImpl
{
    pImpl(vec3 pos, vec3 wup, float yaw, float pitch)
        : pos_{pos}, world_up_{wup}, yaw_{yaw}, pitch_{pitch}
    {}

    void update_vectors();

    vec3 pos_;
    vec3 front_{0.f, 0.f, -1.f};
    vec3 up_;
    vec3 right_;
    vec3 world_up_;

    float yaw_;
    float pitch_;
    float mv_speed_ = cSpeed;
    float sensitivty = cSensitivity;
    float zoom_ = cZoom;
};

void camera::pImpl::update_vectors()
{
    front_.x = cos(radians(yaw_)) * cos(radians(pitch_));
    front_.y = sin(radians(pitch_));
    front_.z = sin(radians(yaw_)) * cos(radians(pitch_));
    front_ = normalize(front_);

    right_ = normalize(cross(front_, world_up_));
    up_ = normalize(cross(right_, front_));
}

camera::camera(vec3 pos, vec3 wup,
                float yaw = cYaw, float pitch = cPitch)
    : impl_{ std::make_unique<pImpl>(pos, wup, yaw, pitch)}
{
    impl_->update_vectors();
}

camera::~camera() noexcept = default;
