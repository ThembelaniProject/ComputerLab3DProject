#include "Texture.h"

#include <glad/glad.h>
#include "stb_image.h"

#include <iostream>

Texture::Texture(const char* path)
{
    // Create texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Wrapping
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT);

    // Filtering
    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR);

    glTexParameteri(GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR);

    // Flip image vertically
    stbi_set_flip_vertically_on_load(true);

    int width, height, channels;

    unsigned char* data = stbi_load(
        path,
        &width,
        &height,
        &channels,
        0);

    if (data)
    {
        GLenum format;

        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else
            format = GL_RGBA;

        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    if (data)
    {
        std::cout << "SUCCESS: "
            << path
            << " "
            << width
            << "x"
            << height
            << std::endl;
    }
    else
    {
        std::cout << "FAILED: "
            << path
            << std::endl;

        std::cout << "Reason: "
            << stbi_failure_reason()
            << std::endl;
    }

    stbi_image_free(data);
}

void Texture::Bind(unsigned int unit) const
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, ID);
}
