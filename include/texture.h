#ifndef TEXTURE_KERAM_CLASS_H_
#define TEXTURE_KERAM_CLASS_H_

constexpr int MAX_TEX_NO{9};

class TextureLoader
{
public:
    explicit TextureLoader(char const*);
    ~TextureLoader();
    TextureLoader(TextureLoader const&) = delete;
    TextureLoader& operator&(TextureLoader const&) = delete;
    void free_buffer();
private:
    unsigned char* buffer_ = nullptr;
    int width_;
    int height_;
    int no_channels_;
};

class Texture2d // consider making it singleton or someething better + use array for holding textures
{
public:
    Texture2d(char const*);
    ~Texture2d();
private:
    unsigned tex_holder_;
    static int index_;
};

#endif// !TEXTURE_KERAM_CLASS_H_