#ifndef KERAM_CAMERA_CLASS_H_
#define KERAM_CAMERA_CLASS_H_

#include <memory>
#include <glm/glm.hpp>

enum class CAM_DIR {
    FRWD, BCWD, LEFT, RGHT };

constexpr float cYaw = -90.f;
constexpr float cPitch = 0.f;
constexpr float cSpeed = 2.5f;
constexpr float cSensitivity = 0.1f;
constexpr float cZoom = 45.f;

class camera
{
public:
    camera(glm::vec3, glm::vec3, float = cYaw, float = cPitch) noexcept;
    ~camera() noexcept;

    glm::mat4 view_matrix() const noexcept;
    void kb_input(CAM_DIR, float) noexcept;
    void ms_input(float, float) noexcept;
    void ms_scroll(float) noexcept;
    float get_zoom() const noexcept;
private:
    struct pImpl;
    std::unique_ptr<pImpl> impl_;
};

#endif // !KERAM_CAMERA_CLASS_H_