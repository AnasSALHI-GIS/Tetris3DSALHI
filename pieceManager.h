#ifndef PIECE_MANAGER_H
#define PIECE_MANAGER_H

#include "piece.h"
#include <vector>
// Classe pour gérer plusieurs pièces

class PieceManager {
public:
    std::vector<Piece> pieces;

    void addPiece(PieceType type, glm::vec3 position);
    
    void generateAllVertices(std::vector<glm::vec3> &vertices,
                           std::vector<glm::vec3> &colors);
    
    void generateAllEdges(std::vector<glm::vec3> &edge_vertices,
                        std::vector<glm::vec3> &edge_colors);
    
    void movePiece(int index, float dx, float dy);
    
    Piece* getPiece(int index);
    
    void clear();
    
    size_t getPieceCount() const { return pieces.size(); }
};

#endif // PIECE_MANAGER_H