#include "object.h"

#include <iostream>
#include "renderer.h"
#include "glm/gtx/transform.hpp"

#include <exception>

// Création d'un objet à partir de ses vertices et couleurs: Ca permet de créer des objets 3D personnalisés
//Avantage: manipuler facilement les sommets et couleurs


Object::Object(std::vector<glm::vec3> vertices, std::vector<glm::vec3> colors) 
    : m_vb(0), m_colorb(0)
{
    m_vb = new VertexBuffer(vertices);
    m_colorb = new VertexBuffer(colors);  
}

Object::~Object()
{
    delete m_vb;
    delete m_colorb;
}

void Object::Bind() const
{
    m_vb->Bind(0);        // positions
    m_colorb->Bind(1);    // couleurs
}

void Object::Unbind() const
{
    m_vb->Unbind();
    m_colorb->Unbind();
}

void Object::Draw() const
{
    GLCall(glDrawArrays(GL_TRIANGLES, 0, m_vb->getSize()));
}
