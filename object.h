#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"

class Object
{
private:
    VertexBuffer* m_vb;        // Buffer pour les positions
    VertexBuffer* m_colorb;    // Buffer pour les couleurs

public:
    Object(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors);
    ~Object();

    void Bind() const;
    void Unbind() const;
    void Draw() const;
};
#endif // OBJECT_H
