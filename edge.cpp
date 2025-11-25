#include "edge.h"
#include "renderer.h"


//On aimerait créer une arête à partir d'une liste de sommets

Edge::Edge(const std::vector<glm::vec3>& vertices) : m_vb(nullptr), m_count(vertices.size())
{
    m_vb = new VertexBuffer(vertices);
}

Edge::~Edge()
{
    delete m_vb;
}

void Edge::Bind() const
{
    m_vb->Bind(0);  // Bind sur l'attribut 0 (position)
}

void Edge::Unbind() const
{
    m_vb->Unbind();
}

void Edge::Draw() const
{
    GLCall(glDrawArrays(GL_LINES, 0, m_count));
}