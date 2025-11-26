# Tetris 3D
L'objectif de cet exercice est de créer un jeu Tetris en c++ et en utilisant la librairie d'OpenGL. Ce jeu devrait satisfaire les objectifs suivant:
1. Créer Le terrain de jeu.
2. Créer les pièces.
3. Faire apparaître les pièces au bon moment au bon endroit.
4. Faire tomber les pièces à intervalle régulier.
Permettre à l'utilisateur de déplacer les pièces lorsqu'il appuie sur certaines touches du clavier (par
exemple "A" pour la gauche et "E" pour la droite).
5- Lorsqu'une ligne est formée, la supprimer, et faire descendre les cubes qui sont au dessus
Le jeu a été conçu suivant l'architecture suivante:
[Diagram UML](https://github.com/AnasSALHI-GIS/Tetris3DSALHI/blob/main/image/UML.png)
## Resources
1- Ce jeu a été basé sur le code fournit par M.Geniet: https://gitlab.com/fgeniet/opengl_tp

2- [Learn OpenGL](https://learnopengl.com/)

3- [Une playlist Youtube qui explique la documentation d'OpenGL](https://www.youtube.com/playlist?list=PLPaoO-vpZnumdcb4tZc4x5Q-v7CkrQ6M-)
## Explication du code
### window.h et window.cpp
On a créé une classe window afin de pouvoir donner à l'utilisateur la possibilité de redimensioner sa fenêtre de jeu sans que le jeu disparaîsse grâce à 
```c++
static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
    bool wasWindowResized();
    void resetWindowResizedFlag();
    bool framebufferResized = false;
```
### FragmentShader et VertexShader
Ces deux syntaxes permettent aux shader de faire le lien entre le CPU et le GPU

```bash
//FragmentShder

#version 330 core

in vec3 fragmentColor;  

out vec4 color;

void main(){
    color = vec4(fragmentColor, 1.0); 
}
```

```bash
//VertexShader

#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;     

out vec3 fragmentColor;  

uniform mat4 MVP;

void main(){
    gl_Position = MVP * vec4(vertexPosition, 1.0);
    fragmentColor = vertexColor;
}
```

## Rendering System
On s'interesse dans cette partie à l'ensemble des méthodes qui permettent de créer les élements de base pour le jeu
### Les classes Object, VertexArray, VertexBuffer Renderer et Shader
Ces classes fournissent les codes de base pour traduire les matrices que le GPU peut traduire en des formes géomatriques comme des triangles ou des lignes
### Walls
Cette classe permet d'implémenter deux formes géometriques qui serveront comme des limites de l'espace de jeu de Tetris
```c++
generateRightColumn(vertices: vector<vec3>&, colors: vector<vec3>&) : void
generateLeftColumn(vertices: vector<vec3>&, colors: vector<vec3>&) : void
generateBottomColumn(vertices: vector<vec3>&, colors: vector<vec3>&) : void
generateAllEdges(edge_vertices: vector<vec3>&, edge_colors: vector<vec3>&) : void
```
## Logique du jeu
### Enumération: PièceType

Description
Énumération définissant les 6 types de pièces Tetris disponibles dans le jeu.
Valeurs
```c++
enum PieceType {
    Quatro,             // Pièce en forme de L (4 cubes)
    J1,                 // Pièce en forme de J (4 cubes)
    J2,                 // Pièce en forme de J inversé (4 cubes)
    T,                  // Pièce en forme de T (4 cubes)
    Sysmetrie_Quatro,   // Pièce en L inversé/symétrique (4 cubes)
    I                   // Pièce en ligne droite (4 cubes)
}
```
####Utilisation

Utilisée lors de la création d'une pièce pour définir sa forme
Permet de générer aléatoirement différents types de pièces
Détermine la forme initiale via `initializeShape()`
### CLASSE: Piece
Représente une pièce Tetris individuelle avec sa position, sa forme, et ses couleurs. Chaque pièce est composée de plusieurs cubes organisés selon un motif défini par son type.

#### `move(dx: float, dy: float) : void` et `setPosition(x: float, y: float) : void`
`move()`: Déplacement relatif (+dx, +dy) 
`setPosition()`: Position absolue (x, y)


#### `getCubeWorldPosition(cubeIndex: int) : vec3`

```c++
piece.setPosition(-0.5, 0.75);  // Place la pièce à une position précise
```
#### `getCubeWorldPosition(cubeIndex: int) : vec3`
Calcule et retourne la position absolue dans l'espace de jeu d'un cube spécifique de la pièce.
#### Les fonctions `getMaxX()`, `getMaxY()`, `getMinX()` et `getMinY()`
Retourne la coordonnée qui se situe à l'extrémité du cube 
#### `generateVertices(vertices: vector<vec3>&, colors: vector<vec3>&) : void`
Génère tous les vertices (sommets) nécessaires pour afficher la pièce en 3D avec OpenGL. Chaque cube de la pièce génère 36 vertices (6 faces × 6 vertices par face).
`vertices` : Référence vers le vecteur où ajouter les positions des vertices
`colors` : Référence vers le vecteur où ajouter les couleurs correspondantes
```c++
for (const auto& cell : shape) {
    float x = position.x + cell.x * CUBE_SIZE;
    float y = position.y + cell.y * CUBE_SIZE;
    generateCube(x, y, position.z, vertices, colors);
}
```
#### `generateEdges(edge_vertices: vector<vec3>&, edge_colors: vector<vec3>&) : void`

`edge_vertices` : Référence vers le vecteur pour les positions des arêtes
`edge_colors` : Référence vers le vecteur pour les couleurs des arêtes

```c++
for (const auto& cell : shape) {
    float x = position.x + cell.x * CUBE_SIZE;
    float y = position.y + cell.y * CUBE_SIZE;
    generateCubeEdges(x, y, position.z, edge_vertices, edge_colors);
}
```
```c++
std::vector<glm::vec3> edge_vertices;
std::vector<glm::vec3> edge_colors;
piece.generateEdges(edge_vertices, edge_colors);
// edge_vertices.size() == 96 pour une pièce de 4 cubes (4 × 24)
```

#### `initializeShape() : void`
Initialise le vecteur `shape` en fonction du `type` de la pièce. Définit les positions relatives de chaque cube.
#### `generateCube(x: float, y: float, z: float, vertices: vector<vec3>&, colors: vector<vec3>&) : void`
Génère les 36 vertices nécessaires pour dessiner un cube complet (6 faces, 2 triangles par face, 3 vertices par triangle).
#### `generateCubeEdges(x: float, y: float, z: float, edge_vertices: vector<vec3>&, edge_colors: vector<vec3>&) : void`
Génère 24 vertices représentant les 12 arêtes du cube (2 points par arête) pour le rendu wireframe.
### PieceManager
Gestionnaire centralisé de toutes les pièces du jeu (actives et verrouillées). Responsable de la gestion de la collection des pièces et des opérations collectives.
#### `addPiece(type: PieceType, position: vec3) : void`
Crée une nouvelle pièce et l'ajoute à la collection.

```c++
pieces.push_back(Piece(type, position));
```
#### `generateAllVertices(vertices: vector<vec3>&, colors: vector<vec3>&) : void`
Génère les vertices de TOUTES les pièces en une seule opération collective.
```c++
std::vector<glm::vec3> all_vertices;
std::vector<glm::vec3> all_colors;
manager.generateAllVertices(all_vertices, all_colors);
Object allPieces(all_vertices, all_colors);
allPieces.Draw();  // Un seul draw call
```
#### `generateAllEdges(edge_vertices: vector<vec3>&, edge_colors: vector<vec3>&) : void`
`edge_vertices`: Vecteur pour les vertices des arêtes
`edge_colors`: Vecteur pour les couleurs des arêtes

Rendu des contours de toutes les pièces

#### `movePiece(index: int, dx: float, dy: float) : void`
`index` : Index de la pièce dans le vecteur pieces
`dx, dy` : Déplacement horizontal et vertical
### TetrisGame 
Classe principale gérant toute la logique du jeu : gravité, collisions, spawn, verrouillage, et état du jeu.
`pieceManager : PieceManager`
Type : `PieceManager`
Gestionnaire de toutes les pièces du jeu. Il permet l'accès à toutes les pièces pour rendu et gestion

`currentPiece : Piece*`
Type : `Piece*` (pointeur)
Pointeur vers la pièce actuellement contrôlée par le joueur. Sa valeur `nullptr` si aucune pièce active

#####ATTRIBUTS PRIVÉS

`gravityTimer` : float
Type : `float`
Compteur de temps accumulé depuis la dernière application de gravité
`gravityDelay : float`
Type : `float`
Description : Délai entre chaque application de gravité
Usage : Contrôle la vitesse de chute des pièces
`occupiedCells : set<pair<int,int>>`
Type : `std::set<std::pair<int, int>>`

Grille virtuelle indiquant quelles cellules sont occupées par des pièces verrouillées
Format : Paires `(gridX, gridY)` en coordonnées de grille

#### `spawnNewPiece() : void`

Crée une nouvelle pièce aléatoire en haut du terrain et la définit comme pièce active.
```c++
float startX = (GAME_X_MIN + GAME_X_MAX) / 2.0f;  // Centre
float startY = GAME_Y_MAX - CUBE_SIZE;             // Haut
```
#### `update(deltaTime: float) : void`
`deltaTime`:  Temps écoulé depuis la dernière frame 
Méthode principale appelée à chaque frame pour mettre à jour la logique du jeu (principalement la gravité).
```c++
if (currentPiece == nullptr) return;

gravityTimer += deltaTime;

if (gravityTimer >= gravityDelay) {
    gravityTimer = 0.0f;  // Reset du timer
    
    if (canMovePiece(currentPiece, 0, -CUBE_SIZE)) {
        // Peut descendre
        currentPiece->move(0, -CUBE_SIZE);
    } else {
        // Sol atteint ou collision
        lockPiece();
        spawnNewPiece();
    }
}
```
```
Flux d'exécution :

Vérifie qu'il y a une pièce active
Accumule le temps écoulé
Si timer >= délai (0.5s) :
    Reset timer
    Teste si peut descendre
    Descend OU verrouille + spawn nouvelle
```
#### `moveCurrentPiece(dx: float, dy: float) : void`
Tente de déplacer la pièce active. Le mouvement est appliqué seulement s'il est valide (pas de collision).

#### `canMovePiece(piece: Piece*, dx: float, dy: float) : bool`

Teste si un mouvement est valide sans l'appliquer (méthode booléenne). Utilise une approche prédictive (essaye puis annule).

#### `isPositionValid(piece: Piece*) : bool`


Vérifie si la position actuelle d'une pièce est valide (dans les limites et pas de collision).

#### `lockPiece() : void`

Verrouille la pièce active (la fixe définitivement) en ajoutant tous ses cubes à la grille d'occupation.

#### `addPieceToGrid(piece: Piece*) : void`

`piece` : Pièce à ajouter à la grille
Ajoute tous les cubes d'une pièce à `occupiedCells`. (Alternative ou alias de `lockPiece`)

#### `worldToGrid(x: float, y: float) : pair<int,int>`
Convertit des coordonnées monde (float) en coordonnées de grille (int).

