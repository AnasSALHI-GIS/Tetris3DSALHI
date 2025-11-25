#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "pieceManager.h"
#include <set>


const float GAME_X_MIN = -1.0f+CUBE_SIZE/2.0f;              // Après colonne gauche
const float GAME_X_MAX = 0.00f+CUBE_SIZE/4.0f;// - CUBE_SIZE/2.0f;  // Avant colonne droite
const float GAME_Y_MIN = -1.0f + CUBE_SIZE*2.0f;          // Au-dessus de la barre
const float GAME_Y_MAX = 1.0f;                        // Haut de l'écran


class TetrisGame {
public:
    PieceManager pieceManager;
    Piece* currentPiece;
    
    TetrisGame();
    
    void spawnNewPiece();
    void update(float deltaTime);
    void moveCurrentPiece(float dx, float dy);
    
    bool canMovePiece(Piece* piece, float dx, float dy);
    bool isPositionValid(Piece* piece);
    void lockPiece();
    
private:
    float gravityTimer;
    float gravityDelay;
    
    std::set<std::pair<int, int>> occupiedCells;
    
    void addPieceToGrid(Piece* piece);
    bool isCellOccupied(int gridX, int gridY);
    std::pair<int, int> worldToGrid(float x, float y);
};

#endif // TETRIS_GAME_H