#ifndef WALLS_H
#define WALLS_H

#include <vector>
#include <glm/glm.hpp>

// Colonne verticale DROITE (celle qui existe déjà)
void generateRightColumn(std::vector<glm::vec3> &vertices, 
                         std::vector<glm::vec3> &colors);

// Colonne verticale GAUCHE (symétrique à droite)
void generateLeftColumn(std::vector<glm::vec3> &vertices, 
                        std::vector<glm::vec3> &colors);

// Colonne HORIZONTALE en bas (relie les deux colonnes)
void generateBottomColumn(std::vector<glm::vec3> &vertices, 
                          std::vector<glm::vec3> &colors);

// Générer les arêtes pour TOUTES les colonnes
void generateAllEdges(std::vector<glm::vec3>& edge_vertices,
                     std::vector<glm::vec3>& edge_colors);

#endif // WALLS_H