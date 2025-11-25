#include "walls.h"

// Constantes communes
const float CUBE_SIZE = 2.0f / 12.0f;         // Taille d'un cube
const float DEPTH = CUBE_SIZE * 5.0f / 10.0f; // Profondeur 3D
const int NBR_CUBES_VERTICAL = 12;            // Nombre de cubes verticaux
const int NBR_CUBES_HORIZONTAL = 7;           // Nombre de cubes horizontaux pour le bas

// Couleurs
const glm::vec3 CUBE_COLOR(0.8f, 0.8f, 0.8f);    // Gris clair
const glm::vec3 SIDE_COLOR(0.6f, 0.6f, 0.6f);    // Gris moyen
const glm::vec3 EDGE_COLOR(0.95f, 0.95f, 0.95f); // Blanc cassé

//////////////// COLONNE DROITE ///////////////
void generateRightColumn(std::vector<glm::vec3> &vertices,
                         std::vector<glm::vec3> &colors)
{
    const float X0 = 0.0f + 0.167f; // Position droite
    const float Y_START = -1.0f;   // + 2.0f/12.0f;   // Commence après la colonne du bas
    const float Y_END = 1.0f;      // Haut de la fenêtre
    const float Z = 0.0f;

    const float CUBE_WIDTH = 2.0f / 12.0f;     // Largeur du cube
    const float CUBE_HEIGHT = Y_END - Y_START; // Hauteur totale

    // 6 sommets pour 2 faces (avant + gauche)
    glm::vec3 v0(X0, Y_START, Z);
    glm::vec3 v1(X0 - CUBE_WIDTH/2.0f, Y_START, Z);
    glm::vec3 v2(X0 - CUBE_WIDTH/2.0f, Y_END, Z);
    glm::vec3 v3(X0, Y_END, Z);
    glm::vec3 v4(X0, Y_START, Z - DEPTH);
    glm::vec3 v5(X0, Y_END, Z - DEPTH);

    // Face AVANT
    vertices.push_back(v1);
    vertices.push_back(v0);
    vertices.push_back(v3);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);

    vertices.push_back(v1);
    vertices.push_back(v3);
    vertices.push_back(v2);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);

    // Face DROITE (profondeur)
    vertices.push_back(v4);
    vertices.push_back(v1);
    vertices.push_back(v5);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);

    vertices.push_back(v2);
    vertices.push_back(v1);
    vertices.push_back(v5);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);
}

/////////////////// COLONNE GAUCHE ///////////////////
void generateLeftColumn(std::vector<glm::vec3> &vertices,
                        std::vector<glm::vec3> &colors)
{
    const float X_START = -1.0f;                // Bord gauche
    const float X_END = -1.0f + 0.167f/2.0f;         // Largeur de la colonne
    const float Y_START = -1.0f + 2.0f / 12.0f; // Commence après la colonne du bas
    const float Y_END = 1.0f;                   // Haut de la fenêtre
    const float Z = 0.0f;

    const float CUBE_WIDTH = X_END - X_START; // 0.167f
    const float CUBE_HEIGHT = Y_END - Y_START;

    // 6 sommets pour 2 faces (avant + droite)
    glm::vec3 v0(X_START, Y_START, Z);
    glm::vec3 v1(X_END, Y_START, Z);
    glm::vec3 v2(X_END, Y_END, Z);
    glm::vec3 v3(X_START, Y_END, Z);
    glm::vec3 v4(X_END, Y_START, Z - DEPTH);
    glm::vec3 v5(X_END, Y_END, Z - DEPTH);

    // Face AVANT
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);

    vertices.push_back(v0);
    vertices.push_back(v2);
    vertices.push_back(v3);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);
    colors.push_back(CUBE_COLOR);

    // Face DROITE (profondeur)
    vertices.push_back(v1);
    vertices.push_back(v4);
    vertices.push_back(v5);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);

    vertices.push_back(v1);
    vertices.push_back(v5);
    vertices.push_back(v2);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);
    colors.push_back(SIDE_COLOR);
}

/////////////////// COLONNE HORIZONTALE DU BAS //////////////////
void generateBottomColumn(std::vector<glm::vec3> &vertices,
                          std::vector<glm::vec3> &colors)
{
    const float X_START = -1.0f; // Commence après la colonne gauche
    const float Y0 = -1.0f;      // Tout en bas
    const float Z = 0.0f;

    for (int i = 0; i < NBR_CUBES_HORIZONTAL ; i++)
    {
        float x = X_START + i * CUBE_SIZE;
        // Calculer la limite droite à partir de la colonne droite pour former un "|_" sans gap
        const float X_RIGHT = 0.0f + 0.167f;     // doit correspondre à la même valeur utilisée pour la colonne droite
        const float X_END = X_RIGHT - CUBE_SIZE; // bord gauche de la colonne droite
        // Arrêter si le cube dépasserait ce bord 
       

        // 6 sommets pour 2 faces (avant + dessus)
        glm::vec3 v0(x, Y0, Z);
        glm::vec3 v1(x + CUBE_SIZE, Y0, Z);
        glm::vec3 v2(x + CUBE_SIZE, Y0 + CUBE_SIZE, Z);
        glm::vec3 v3(x, Y0 + CUBE_SIZE, Z);
        glm::vec3 v4(x, Y0 + CUBE_SIZE, Z /*+ DEPTH*/);
        glm::vec3 v5(x + CUBE_SIZE, Y0 + CUBE_SIZE, Z /* + DEPTH*/);

        // Face AVANT
        vertices.push_back(v0);
        vertices.push_back(v1);
        vertices.push_back(v2);
        colors.push_back(CUBE_COLOR);
        colors.push_back(CUBE_COLOR);
        colors.push_back(CUBE_COLOR);

        vertices.push_back(v0);
        vertices.push_back(v2);
        vertices.push_back(v3);
        colors.push_back(CUBE_COLOR);
        colors.push_back(CUBE_COLOR);
        colors.push_back(CUBE_COLOR);

        // Face DESSUS (profondeur)
        vertices.push_back(v3);
        vertices.push_back(v4);
        vertices.push_back(v5);
        colors.push_back(SIDE_COLOR);
        colors.push_back(SIDE_COLOR);
        colors.push_back(SIDE_COLOR);

        vertices.push_back(v3);
        vertices.push_back(v5);
        vertices.push_back(v2);
        colors.push_back(SIDE_COLOR);
        colors.push_back(SIDE_COLOR);
        colors.push_back(SIDE_COLOR);
    }
}
/////////////////// ARÊTES POUR TOUTES LES COLONNES //////////////////
void generateAllEdges(std::vector<glm::vec3> &edge_vertices,
                      std::vector<glm::vec3> &edge_colors)
{
    // ARÊTES COLONNE DROITE
    const float X_RIGHT = 0.0f + 0.167f;
    const float Y_START = -1.0f + CUBE_SIZE; // Commence après le bas

    for (int i = 0; i < NBR_CUBES_VERTICAL - 1; i++)
    { // -1 car on saute le premier
        float y = Y_START + i * CUBE_SIZE;

        glm::vec3 v0(X_RIGHT, y, 0.0f);
        glm::vec3 v1(X_RIGHT - CUBE_SIZE/2.0f, y, 0.0f);
        
        const float COLUMN_WIDTH = 0.167f;
        glm::vec3 v2(X_RIGHT - CUBE_SIZE/2.0f, y + CUBE_SIZE, 0.0f);
        glm::vec3 v3(X_RIGHT, y + CUBE_SIZE, 0.0f);
        glm::vec3 v4(X_RIGHT, y, -DEPTH);
        glm::vec3 v5(X_RIGHT, y + CUBE_SIZE, -DEPTH);

        // Arêtes face avant
        edge_vertices.push_back(v0);
        edge_vertices.push_back(v1);
        edge_vertices.push_back(v1);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v0);

        

        for (int j = 0; j < 11; j++)
            edge_colors.push_back(EDGE_COLOR);
    }

    // ARÊTES COLONNE GAUCHE
    const float X_LEFT = -1.0f;

    for (int i = 0; i < NBR_CUBES_VERTICAL - 1; i++)
    { 
        float y = Y_START + i * CUBE_SIZE;

        glm::vec3 v0(X_LEFT, y, 0.0f);
        glm::vec3 v1(X_LEFT + CUBE_SIZE/2.0f, y, 0.0f);
        glm::vec3 v2(X_LEFT + CUBE_SIZE/2.0f, y + CUBE_SIZE, 0.0f);
        glm::vec3 v3(X_LEFT, y + CUBE_SIZE, 0.0f);
        glm::vec3 v4(X_LEFT + CUBE_SIZE/2.0f, y, DEPTH);
        glm::vec3 v5(X_LEFT + CUBE_SIZE/2.0f, y + CUBE_SIZE, DEPTH);

        // Arêtes face avant
        edge_vertices.push_back(v0);
        edge_vertices.push_back(v1);
        edge_vertices.push_back(v1);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v0);

      

        for (int j = 0; j < 11; j++)
            edge_colors.push_back(EDGE_COLOR);
    }

    // ARÊTES COLONNE HORIZONTALE (9 cubes carrés)
    const float X_START = -1.0f;
    const float Y_BOTTOM = -1.0f;


    float x = X_START;
    // const float X_RIGHT = 0.0f + 0.167f;
    const float X_END = X_RIGHT - CUBE_SIZE;

    while (x + CUBE_SIZE <= X_END + 0.167f)
    {
        glm::vec3 v0(x, Y_BOTTOM, 0.0f);
        glm::vec3 v1(x + CUBE_SIZE, Y_BOTTOM, 0.0f);
        glm::vec3 v2(x + CUBE_SIZE, Y_BOTTOM + CUBE_SIZE, 0.0f);
        glm::vec3 v3(x, Y_BOTTOM + CUBE_SIZE, 0.0f);
        glm::vec3 v4(x, Y_BOTTOM + CUBE_SIZE, DEPTH);
        glm::vec3 v5(x + CUBE_SIZE, Y_BOTTOM + CUBE_SIZE, DEPTH);

        // Arêtes face avant
        edge_vertices.push_back(v0);
        edge_vertices.push_back(v1);
        edge_vertices.push_back(v1);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v0);

        // Arêtes profondeur
        edge_vertices.push_back(v3);
        edge_vertices.push_back(v4);
        edge_vertices.push_back(v2);
        edge_vertices.push_back(v5);
        edge_vertices.push_back(v4);
        edge_vertices.push_back(v5);

        for (int j = 0; j < 11; j++)
            edge_colors.push_back(EDGE_COLOR);

        // Incrémenter x pour la prochaine itération
        x += CUBE_SIZE / 2;
    }
}