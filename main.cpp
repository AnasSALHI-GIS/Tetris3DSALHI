#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "window.h"
#include "walls.h"
#include "object.h" 
#include "tetrisGame.h"
#include "piece.h"
#include "pieceManager.h"
// #include <ctime>

using namespace std;
// 1er ajout 18:38

TetrisGame game;
bool keyLeftPressed = false;
bool keyRightPressed = false;
bool keyDownPressed = false;

// 2eme ajout 18:39

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT:
            if (!keyLeftPressed && game.currentPiece)
            {
                game.moveCurrentPiece(-CUBE_SIZE, 0.0f);
                keyLeftPressed = true;
            }
            break;
        case GLFW_KEY_RIGHT:
            if (!keyRightPressed && game.currentPiece)
            {
                game.moveCurrentPiece(CUBE_SIZE, 0.0f);
                keyRightPressed = true;
            }
            break;
        case GLFW_KEY_DOWN:
            if (!keyDownPressed && game.currentPiece)
            {
                game.moveCurrentPiece(0.0f, -CUBE_SIZE);
                keyDownPressed = true;
            }
            break;
        case GLFW_KEY_UP:
            if (game.currentPiece)
            {
                game.moveCurrentPiece(0.0f, CUBE_SIZE);
            }
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, true);
            break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_LEFT:
            keyLeftPressed = false;
            break;
        case GLFW_KEY_RIGHT:
            keyRightPressed = false;
            break;
        case GLFW_KEY_DOWN:
            keyDownPressed = false;
            break;
        }
    }
}


int main()
{
    string path = "/mnt/c/Users/wassi/OneDrive/Bureau/TSI/OpenGl/OpenGL/TP3corrigé/corrigé";

    /////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW/n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);               // antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    /////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Définition de la zone d'affichage (dans ce cas, on aimerait avoir l'écran tout entier)
    int width = 1919;
    int height = 1020;

    // Enfin on crée la fenêtre
    GLFWwindow *window = glfwCreateWindow(width, height, "OpenGL_API", NULL, NULL);
    glfwSwapInterval(1);

    // On vérifie que l'initialisation a bien marché
    if (window == NULL)
    {
        fprintf(stderr, "Erreur lors de la création de la fénêtre/n");
        glfwTerminate();
        return -1;
    }

    // Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);

    Window mWindow;
    // window est le context pour GLFW alors que mWindow est l'objet qu'on peut redimentionner
    // On assure la liaison entre window et mWindow par la fonction glfwSetWindowUserPointer
    glfwSetWindowUserPointer(window, &mWindow);

    // Fonction statique pour appeler la fenêtre mWindow modifiée
    glfwSetFramebufferSizeCallback(window, Window::framebufferResizeCallback);
    // 3eme ajout 18:40
    //  Définir le callback pour la gestion des touches
    glfwSetKeyCallback(window, keyCallback); // ← AJOUTER CETTE LIGNE
    /////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Initialisation de GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW/n");
        return -1;
    }

    // Active le test de profondeur
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    /////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;

    /////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path + "/shaders/SimpleVertexShader.vertexshader",
                  path + "/shaders/SimpleFragmentShader.fragmentshader");

    /////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

    /////////////////////////MATRICES MVP - PROJECTION 2.5D FIXE/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // 1. Matrice de Projection ORTHOGRAPHIQUE (2.5D - pas de perspective)
    glm::mat4 Projection = glm::ortho(
        -1.0f, // left
        1.0f,  // right
        -1.0f, // bottom
        1.0f,  // top
        0.1f,  // near
        10.0f  // far
    );

    // 2. Matrice de Vue (caméra fixe en vue 2.5D)
    glm::mat4 View = glm::lookAt(
        glm::vec3(1.5f, 0.0f, 3.0f), // Caméra légèrement à droite et en avant
        glm::vec3(0.0f, 0.0f, 0.0f), // Regarde le centre
        glm::vec3(0.0f, 1.0f, 0.0f)  // Vecteur "up"
    );

    // 3. Matrice de Modèle (pas de transformation)
    glm::mat4 Model = glm::mat4(1.0f);

    // 4. Matrice MVP (combinaison des trois)
    glm::mat4 MVP = Projection * View * Model;

    /////////////////////////Création de la colonne de cubes/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Générer les 3 colonnes (forme U)
    std::vector<glm::vec3> all_vertices;
    std::vector<glm::vec3> all_colors;

    generateRightColumn(all_vertices, all_colors);  // Colonne droite
    generateLeftColumn(all_vertices, all_colors);   // Colonne gauche
    generateBottomColumn(all_vertices, all_colors); // Barre horizontale

    // Créer l'objet avec toutes les colonnes
    Object allColumns(all_vertices, all_colors);

    // Arêtes pour toutes les colonnes
    std::vector<glm::vec3> edge_vertices;
    std::vector<glm::vec3> edge_colors;
    generateAllEdges(edge_vertices, edge_colors);

    Object edgesObject(edge_vertices, edge_colors);
    /////////////////////////Initialisation du jeu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // std::srand(std::time(nullptr)); // Initialiser le random
    game.spawnNewPiece();   // Créer la première pièce
    float lastFrame = 0.0f; // Pour le deltaTime

    /////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // On indique la couleur de fond
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f); // Fond gris foncé

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window))
    {
        /////////////////////////Calcul du delta time: utilisé pour le déplacement des objet////////////////////////////////////
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
       

        /////////////////////////Mettre à jour le jeu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        game.update(deltaTime);

        renderer.Clear();

        /////////////////////////Envoyer la matrice MVP au shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        shader.Bind();
        shader.SetUniformMat4f("MVP", MVP);

        /////////////////////////Dessiner les murs/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        renderer.Draw(va, allColumns, shader);

        // Dessiner les arêtes des murs en blanc
        shader.Bind();
        shader.SetUniformMat4f("MVP", MVP);
        edgesObject.Bind();
        glLineWidth(2.0f);
        glDrawArrays(GL_LINES, 0, edge_vertices.size());
        glLineWidth(1.0f);
  

        /////////////////////////Dessiner les pièces/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<glm::vec3> pieceVertices, pieceColors;
        game.pieceManager.generateAllVertices(pieceVertices, pieceColors);

        if (pieceVertices.size() > 0)
        {
            Object piecesObject(pieceVertices, pieceColors);
            shader.Bind();
            shader.SetUniformMat4f("MVP", MVP);
            renderer.Draw(va, piecesObject, shader);
        }
        /////////////////////////Dessiner les arêtes des pièces/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<glm::vec3> pieceEdgeVertices, pieceEdgeColors;
        game.pieceManager.generateAllEdges(pieceEdgeVertices, pieceEdgeColors);

        if (pieceEdgeVertices.size() > 0)
        {
            Object pieceEdgesObject(pieceEdgeVertices, pieceEdgeColors);
            shader.Bind();
            shader.SetUniformMat4f("MVP", MVP);
            pieceEdgesObject.Bind();
            glLineWidth(1.0f);
            glDrawArrays(GL_LINES, 0, pieceEdgeVertices.size());
            glLineWidth(1.0f);
        }
        /////////////////////////Fin de la boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        glfwSwapBuffers(window);
        glfwPollEvents();

        // Gestion du redimensionnement de la fenêtre pour ne pas perdre la scene et d'actualiser la matrice de projection
        if (mWindow.wasWindowResized())
        {
            glViewport(0, 0, mWindow.width, mWindow.height);
            mWindow.resetWindowResizedFlag();

            Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 10.0f);
            MVP = Projection * View * Model;
        }
    }

    glfwTerminate();

    return 0;
}