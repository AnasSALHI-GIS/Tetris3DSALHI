#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>


#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include <GLFW/glfw3.h>

class Shader
{
public:
    Shader(std::string VertexShaderFilePath, std::string FragmentShaderFilePath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
unsigned int GetUniformLocation(const std::string& name);

private:
    GLuint LoadShaders(const std::string vertex_file_path,const std::string fragment_file_path);
    std::string m_VertexShaderFilePath;
    std::string m_FragmentShaderFilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

};

#endif // SHADER_H
