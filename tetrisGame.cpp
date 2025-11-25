#include "tetrisGame.h"
#include <cstdlib>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>

TetrisGame::TetrisGame()
    : currentPiece(nullptr), gravityTimer(0.0f), gravityDelay(0.5f)
{
    std::srand(static_cast<unsigned int>(glfwGetTime() * 1000.0));
}
// Faire apparaître une nouvelle pièce au sommet du terrain
void TetrisGame::spawnNewPiece()
{
    float centerX = (GAME_X_MIN + GAME_X_MAX) / 2.0f;
    glm::vec3 startPos(centerX, GAME_Y_MAX - CUBE_SIZE * 3, 0.0f);

    PieceType types[] = {PieceType::Quatro, PieceType::J1, PieceType::J2,
                         PieceType::T, PieceType::Sysmetrie_Quatro, PieceType::I};
    PieceType randomType = types[std::rand() % 6];

    pieceManager.addPiece(randomType, startPos);
    currentPiece = pieceManager.getPiece(pieceManager.getPieceCount() - 1);

    glm::vec3 colors[] = {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 1.0f, 1.0f)};
    currentPiece->setColor(colors[std::rand() % 6]);
}
// Mettre à jour le jeu
void TetrisGame::update(float deltaTime)
{
    if (currentPiece)
    {
        gravityTimer += deltaTime;

        if (gravityTimer >= gravityDelay)
        {
            if (canMovePiece(currentPiece, 0.0f, -CUBE_SIZE))
            {
                currentPiece->move(0.0f, -CUBE_SIZE);
            }
            else
            {
                lockPiece();
                spawnNewPiece();
            }
            gravityTimer = 0.0f;
        }
    }
}
// Déplacer la pièce actuelle si possible
void TetrisGame::moveCurrentPiece(float dx, float dy)
{
    if (currentPiece && canMovePiece(currentPiece, dx, dy))
    {
        currentPiece->move(dx, dy);
    }
}
// Vérifier si une pièce peut se déplacer à la nouvelle position
bool TetrisGame::canMovePiece(Piece *piece, float dx, float dy)
{
    if (!piece)
        return false;

    glm::vec3 oldPos = piece->position;
    piece->position.x += dx;
    piece->position.y += dy;

    bool valid = isPositionValid(piece);
    piece->position = oldPos;

    return valid;
}
// Vérifier si la position actuelle de la pièce est valide
bool TetrisGame::isPositionValid(Piece *piece)
{
    if (!piece)
        return false;

    for (const auto &cubePos : piece->shape)
    {
        float worldX = piece->position.x + cubePos.x * CUBE_SIZE;
        float worldY = piece->position.y + cubePos.y * CUBE_SIZE;

        // Vérifier les limites du terrain
        if (worldX < GAME_X_MIN - 0.001f)
            return false;
        if (worldX > GAME_X_MAX + CUBE_SIZE + 0.001f)
            return false;
        if (worldY < GAME_Y_MIN - 0.001f)
            return false;
        if (worldY > GAME_Y_MAX + 0.001f)
            return false;

        // Vérifier la collision avec les pièces déjà posées
        auto gridPos = worldToGrid(worldX, worldY);
        if (isCellOccupied(gridPos.first, gridPos.second))
        {
            return false;
        }
    }

    return true;
}
// Verrouiller la pièce actuelle dans la grille
void TetrisGame::lockPiece()
{
    if (!currentPiece)
        return;

    addPieceToGrid(currentPiece);
    currentPiece = nullptr;
}
// Ajouter les cubes de la pièce à la grille des cellules occupées
void TetrisGame::addPieceToGrid(Piece *piece)
{
    if (!piece)
        return;

    for (const auto &cubePos : piece->shape)
    {
        float worldX = piece->position.x + cubePos.x * CUBE_SIZE / 2.0f;
        float worldY = piece->position.y + cubePos.y * CUBE_SIZE;

        auto gridPos = worldToGrid(worldX, worldY);

        occupiedCells.insert(gridPos);
    }
}
// Vérifier si une cellule de la grille est occupée
bool TetrisGame::isCellOccupied(int gridX, int gridY)
{
    return occupiedCells.find({gridX, gridY}) != occupiedCells.end();
}
// Convertir les coordonnées du monde en indices de la grille
std::pair<int, int> TetrisGame::worldToGrid(float x, float y)
{
    // Arrondir à la demi-unité de CUBE_SIZE près pour éviter les problèmes de précision
    float epsilon = 0.0001f;

    // Normaliser les coordonnées par rapport à l'origine de la grille
    float normalizedX = x - GAME_X_MIN + 0;
    float normalizedY = y - GAME_Y_MIN + 0;

    // Convertir en indices de grille
    int gridX = static_cast<int>(std::round(normalizedX / (CUBE_SIZE / 2.0f)));
    int gridY = static_cast<int>(std::round(normalizedY / CUBE_SIZE));

    return {gridX, gridY};
}