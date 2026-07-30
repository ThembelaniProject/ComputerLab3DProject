#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    unsigned int vertex =
        compileShader(GL_VERTEX_SHADER, vertexCode.c_str());

    unsigned int fragment =
        compileShader(GL_FRAGMENT_SHADER, fragmentCode.c_str());

    ID = glCreateProgram();

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);

    glLinkProgram(ID);

    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const
{
    glUseProgram(ID);
}

std::string Shader::readFile(const char* path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cout << "Cannot open shader: "
            << path
            << std::endl;

        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

unsigned int Shader::compileShader(
    unsigned int type,
    const char* source)
{
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);

    glCompileShader(shader);

    checkCompileErrors(shader, "SHADER");

    return shader;
}

void Shader::checkCompileErrors(
    unsigned int object,
    const std::string& type)
{
    int success;

    char infoLog[1024];

    if (type == "PROGRAM")
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(
                object,
                1024,
                NULL,
                infoLog);

            std::cout
                << "Program Link Error\n"
                << infoLog
                << std::endl;
        }
    }
    else
    {
        glGetShaderiv(
            object,
            GL_COMPILE_STATUS,
            &success);

        if (!success)
        {
            glGetShaderInfoLog(
                object,
                1024,
                NULL,
                infoLog);

            std::cout
                << "Shader Compile Error\n"
                << infoLog
                << std::endl;
        }
    }
}

void Shader::setBool(
    const std::string& name,
    bool value) const
{
    glUniform1i(
        glGetUniformLocation(ID, name.c_str()),
        (int)value);
}

void Shader::setInt(
    const std::string& name,
    int value) const
{
    glUniform1i(
        glGetUniformLocation(ID, name.c_str()),
        value);
}

void Shader::setFloat(
    const std::string& name,
    float value) const
{
    glUniform1f(
        glGetUniformLocation(ID, name.c_str()),
        value);
}

void Shader::setVec3(
    const std::string& name,
    const glm::vec3& value) const
{
    glUniform3fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        glm::value_ptr(value));
}

void Shader::setVec3(
    const std::string& name,
    float x,
    float y,
    float z) const
{
    glUniform3f(
        glGetUniformLocation(ID, name.c_str()),
        x,
        y,
        z
    );
}

void Shader::setMat4(
    const std::string& name,
    const glm::mat4& mat) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name.c_str()),
        1,
        GL_FALSE,
        glm::value_ptr(mat));
}