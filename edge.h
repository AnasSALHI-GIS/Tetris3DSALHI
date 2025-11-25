#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "vertexbuffer.h"

// Classe représentant une arête composée de segments de ligne entre des sommets

class Edge {
private:
    VertexBuffer* m_vb;
    unsigned int m_count;  // Nombre de vertices
    
public:
    Edge(const std::vector<glm::vec3>& vertices);
    ~Edge();
    
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    
    inline unsigned int GetCount() const { return m_count; }
};