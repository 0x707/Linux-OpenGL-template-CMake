#ifndef KERAM_CAMERA_CLASS_H_
#define KERAM_CAMERA_CLASS_H_

#include <memory>
#include <glm/glm.hpp>

class camera
{
public:
    camera(glm::vec3, glm::vec3, float, float);
    ~camera() noexcept;
private:
    struct pImpl;
    std::unique_ptr<pImpl> impl_;
};

#endif // !KERAM_CAMERA_CLASS_H_