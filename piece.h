#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <glm/glm.hpp>
//

const float CUBE_SIZE = 1.0f / 12.0f;
const float DEPTH = CUBE_SIZE; //* 5.0f / 10.0f;

enum class PieceType {
    Quatro, J1, J2, T, Sysmetrie_Quatro, I
};

class Piece {
public:
    glm::vec3 position;
    PieceType type;
    std::vector<glm::ivec2> shape;
    glm::vec3 color;
    glm::vec3 sideColor;
    glm::vec3 edgeColor;

    Piece(PieceType t, glm::vec3 pos = glm::vec3(0.0f));
    
    
    void move(float dx, float dy);
    void setPosition(float x, float y);
    void setColor(glm::vec3 newColor);
    glm::vec3 getCubeWorldPosition(int cubeIndex) const;

    float getMinX() const;
    float getMaxX() const;
    float getMinY() const;
    float getMaxY() const;
    
    // Générer directement des vectors de glm::vec3 pour les vertices et couleurs
    void generateVertices(std::vector<glm::vec3> &vertices,
                         std::vector<glm::vec3> &colors) const;
    void generateEdges(std::vector<glm::vec3> &edge_vertices,
                      std::vector<glm::vec3> &edge_colors) const;

private:
    void initializeShape();
    void generateCube(float x, float y, float z,
                     std::vector<glm::vec3> &vertices,
                     std::vector<glm::vec3> &colors) const;
    void generateCubeEdges(float x, float y, float z,
                          std::vector<glm::vec3> &edge_vertices,
                          std::vector<glm::vec3> &edge_colors) const;
};

#endif // PIECE_H