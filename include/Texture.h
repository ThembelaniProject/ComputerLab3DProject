#pragma once

class Texture
{
public:
    Texture(const char* path);

    void Bind(unsigned int unit = 0) const;

private:
    unsigned int ID;
};