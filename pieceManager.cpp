#include "pieceManager.h"

void PieceManager::addPiece(PieceType type, glm::vec3 position) {
    pieces.emplace_back(type, position);
}

void PieceManager::generateAllVertices(std::vector<glm::vec3> &vertices,
                                      std::vector<glm::vec3> &colors) {
    vertices.clear();
    colors.clear();
    for(auto& piece : pieces) {
        piece.generateVertices(vertices, colors);
    }
}
// Générer les arêtes pour toutes les pièces
void PieceManager::generateAllEdges(std::vector<glm::vec3> &edge_vertices,
                                   std::vector<glm::vec3> &edge_colors) {
    edge_vertices.clear();
    edge_colors.clear();
    for(auto& piece : pieces) {
        piece.generateEdges(edge_vertices, edge_colors);
    }
}
// Déplacer une pièce spécifique
void PieceManager::movePiece(int index, float dx, float dy) {
    if(index >= 0 && index < pieces.size()) {
        pieces[index].move(dx, dy);
    }
}
// Obtenir un pointeur vers une pièce spécifique (Système de sac spécifique au Tetris)
Piece* PieceManager::getPiece(int index) {
    if(index >= 0 && index < pieces.size()) {
        return &pieces[index];
    }
    return nullptr;
}
// Vider toutes les pièces
void PieceManager::clear() {
    pieces.clear();
}