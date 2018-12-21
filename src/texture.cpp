#include <glad/glad.h>
#include "stb_image.h"
#include "texture.h"
#include <cassert>

TextureLoader::TextureLoader(char const* path)
    : buffer_{ stbi_load(path, &width_, &height_, &no_channels_, 0) }
{
    assert(buffer_ != nullptr);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer_);
    glGenerateMipmap(GL_TEXTURE_2D);
}

TextureLoader::~TextureLoader()
{
    free_buffer();
}

void TextureLoader::free_buffer()
{
    if (buffer_ != nullptr)
        stbi_image_free(buffer_);
    buffer_ = nullptr;
}

// TEXTURE

Texture2d::Texture2d(char const* path)
{
    static int index = -1;
    glGenTextures(++index, &tex_holder_);
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, tex_holder_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    TextureLoader loader{ path };
}
