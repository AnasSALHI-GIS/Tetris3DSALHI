#include "piece.h"

//On a choisi de regrouper toutes les fonctions pour la pièce dans ce fichier piece.cpp (Création et déplacement)

Piece::Piece(PieceType t, glm::vec3 pos)
    : type(t), position(pos),
      color(0.5f, 0.5f, 0.8f),
      sideColor(0.3f, 0.3f, 0.6f),
      edgeColor(0.7f, 0.7f, 0.9f) {
    initializeShape();
}

void Piece::initializeShape() {
    shape.clear();
    switch(type) {
        case PieceType::Quatro:
            shape = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
            break;
        case PieceType::J1:
            shape = {{0, 0}, {0, 1}, {0, 2}, {1, 0}};
            break;
        case PieceType::J2:
            shape = {{0, 0}, {0, 1}, {0, 2}, {1, 0}};
            break;
        case PieceType::T:

        shape = {{0, 0}, {1, 0}, {2, 0}, {1, 1}};
            break;
        case PieceType::Sysmetrie_Quatro:
            shape = {{0, 0}, {0, 1}, {1, 1}, {1, 2}};
            break;
        case PieceType::I:
            // Déjà OK (commence à x=0)
            shape = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
            break;
    }
}

void Piece::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void Piece::setPosition(float x, float y) {
    position.x = x;
    position.y = y;
}

void Piece::setColor(glm::vec3 newColor) {
    color = newColor;
    sideColor = glm::clamp(newColor * 0.6f, 0.0f, 1.0f);
    edgeColor = glm::clamp(newColor * 1.2f, 0.0f, 1.0f);
}
// Obtenir la position  d'un cube spécifique dans la pièce par rapport à la scene du jeu définie entre le mur gauche (X=-1) et le mur droit (X=0)

glm::vec3 Piece::getCubeWorldPosition(int cubeIndex) const {
    if(cubeIndex < 0 || cubeIndex >= shape.size()) {
        return position;
    }
    return glm::vec3(
        position.x + shape[cubeIndex].x * CUBE_SIZE/2.0f,
        position.y + shape[cubeIndex].y * CUBE_SIZE,
        position.z
    );
}
// Générer les vertices et couleurs pour tous les cubes de la pièce

void Piece::generateVertices(std::vector<glm::vec3> &vertices,
                            std::vector<glm::vec3> &colors) const {
    for(const auto& cubePos : shape) {
        float x = position.x + cubePos.x * CUBE_SIZE/2.0f;
        float y = position.y + cubePos.y * CUBE_SIZE;
        float z = position.z;
        
        generateCube(x, y, z, vertices, colors);
    }
}
// Générer les arêtes pour tous les cubes de la pièce

void Piece::generateEdges(std::vector<glm::vec3> &edge_vertices,
                         std::vector<glm::vec3> &edge_colors) const {
    for(const auto& cubePos : shape) {
        float x = position.x + cubePos.x * CUBE_SIZE/2.0f;
        float y = position.y + cubePos.y * CUBE_SIZE;
        float z = position.z;
        
        generateCubeEdges(x, y, z, edge_vertices, edge_colors);
    }
}

// Générer un cube à la position (x, y, z)
void Piece::generateCube(float x, float y, float z,
                        std::vector<glm::vec3> &vertices,
                        std::vector<glm::vec3> &colors) const {
    // 8 sommets du cube
    glm::vec3 v0(x, y, z+CUBE_SIZE/4.0f);
    glm::vec3 v1(x + CUBE_SIZE/2.0f, y, z+CUBE_SIZE/4.0f);
    glm::vec3 v2(x + CUBE_SIZE/2.0f, y + CUBE_SIZE, z+CUBE_SIZE/4.0f);
    glm::vec3 v3(x, y + CUBE_SIZE, z+CUBE_SIZE/4.0f);
    glm::vec3 v4(x, y, z+CUBE_SIZE/4.0f - DEPTH);
    glm::vec3 v5(x + CUBE_SIZE/2.0f, y, z+CUBE_SIZE/4.0f - DEPTH);
    glm::vec3 v6(x + CUBE_SIZE/2.0f, y + CUBE_SIZE, z+CUBE_SIZE/4.0f - DEPTH);
    glm::vec3 v7(x, y + CUBE_SIZE, z+CUBE_SIZE/4.0f - DEPTH);
    
    // Face AVANT (2 triangles)
    vertices.push_back(v0); vertices.push_back(v1); vertices.push_back(v2);
    colors.push_back(color); colors.push_back(color); colors.push_back(color);
    
    vertices.push_back(v0); vertices.push_back(v2); vertices.push_back(v3);
    colors.push_back(color); colors.push_back(color); colors.push_back(color);
    
    // Face DESSUS (2 triangles)
    vertices.push_back(v3); vertices.push_back(v2); vertices.push_back(v6);
    colors.push_back(sideColor); colors.push_back(sideColor); colors.push_back(sideColor);
    
    vertices.push_back(v3); vertices.push_back(v6); vertices.push_back(v7);
    colors.push_back(sideColor); colors.push_back(sideColor); colors.push_back(sideColor);
    
    // Face DROITE (2 triangles)
    vertices.push_back(v1); vertices.push_back(v5); vertices.push_back(v6);
    colors.push_back(sideColor); colors.push_back(sideColor); colors.push_back(sideColor);
    
    vertices.push_back(v1); vertices.push_back(v6); vertices.push_back(v2);
    colors.push_back(sideColor); colors.push_back(sideColor); colors.push_back(sideColor);
}

// Générer les arêtes d'un cube à la position (x, y, z)
void Piece::generateCubeEdges(float x, float y, float z,
                             std::vector<glm::vec3> &edge_vertices,
                             std::vector<glm::vec3> &edge_colors) const {
    glm::vec3 v0(x, y, z+CUBE_SIZE/4.0f);                                    // Bas-gauche
    glm::vec3 v1(x + CUBE_SIZE/2.0f, y, z+CUBE_SIZE/4.0f);                  // Bas-droite ← AJOUTER + CUBE_SIZE/2.0f
    glm::vec3 v2(x + CUBE_SIZE/2.0f, y + CUBE_SIZE, z+CUBE_SIZE/4.0f);      // Haut-droite ← AJOUTER + CUBE_SIZE/2.0f
    glm::vec3 v3(x, y + CUBE_SIZE, z+CUBE_SIZE/4.0f);
    glm::vec3 blackColor(0.0f, 0.0f, 0.0f);
    
    // 4 lignes pour former un carré
    edge_vertices.push_back(v0); edge_vertices.push_back(v1);
    edge_colors.push_back(blackColor); edge_colors.push_back(blackColor);
    
    edge_vertices.push_back(v1); edge_vertices.push_back(v2);
    edge_colors.push_back(blackColor); edge_colors.push_back(blackColor);
    
    edge_vertices.push_back(v2); edge_vertices.push_back(v3);
    edge_colors.push_back(blackColor); edge_colors.push_back(blackColor);
    
    edge_vertices.push_back(v3); edge_vertices.push_back(v0);
    edge_colors.push_back(blackColor); edge_colors.push_back(blackColor);
}

// Obtenir les limites de la pièce

float Piece::getMinX() const {
    if (shape.empty()) return position.x;
    
    float minX = shape[0].x;
    for (const auto& cube : shape) {
        if (cube.x < minX) minX = cube.x;
    }
    return position.x + minX * CUBE_SIZE/2.0f;
}

float Piece::getMaxX() const {
    if (shape.empty()) return position.x;
    
    float maxX = shape[0].x;
    for (const auto& cube : shape) {
        if (cube.x > maxX) maxX = cube.x;
    }
    return position.x + (maxX + 1) * CUBE_SIZE*0.5f;
}

float Piece::getMinY() const {
    if (shape.empty()) return position.y;
    
    float minY = shape[0].y;
    for (const auto& cube : shape) {
        if (cube.y < minY) minY = cube.y;
    }
    return position.y + minY * CUBE_SIZE;
}

float Piece::getMaxY() const {
    if (shape.empty()) return position.y;
    
    float maxY = shape[0].y;
    for (const auto& cube : shape) {
        if (cube.y > maxY) maxY = cube.y;
    }
    return position.y + (maxY + 1) * CUBE_SIZE;
}


