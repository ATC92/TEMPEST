#pragma once
///< C/C++ Lib
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
///< CGame Lib
#include "../Components/Textures.h"
#include "../Utils/Information.h"
// #include "MenuScene.h"
//////////////////////////////////////////////////////////////////
/**
 * @brief Scenes Manager
 * 
 * ---
 * 
 * Contains:
 * 
 * @c MainMenu = 0 \\
 * @c GameState = 1 \\
 * @c OptionMenu = 2 \\
 * @c ConfigurationMenu = 3 \\
 * @c LoadScreen = 4
 * 
 * This enum defines the different scenes in the game.
 * Each scene represents a different state or screen in the game.
 */
typedef enum _scn
{
    sMAINMENU,
    sGAMESTATE,
    sOPTIONMENU,
    sCONFIGURATIONMENU,
    sLOADSCREEN,
    sBESTIARY,
    sEXIT_GAME
}ManagerScenes;
/**
 * @brief Scene Struct
 * 
 * ---
 * 
 * Contains:
 * 
 * @c infScene   Information of the Scene \\
 * @c Size       Size of the Scene
 * 
 * * This struct represents a scene in the game.
 * * It contains information about the scene and can hold textures or GUI elements.
 * * The `infScene` field holds the scene's metadata, while the `Size`
 * * field can be used to define the dimensions of the scene.
 */
typedef struct _scene
{
    bool* ActivedScenes;
    ManagerScenes typeScene;
    ManagerScenes previousScene;
}Scene;
//////////////////////////////////////////////////////////////////
/**
 * @brief Scenes Manager Array
 * This variable holds the current scene in the game.
 * It is used to manage transitions between different scenes.
 */
extern Scene* scenes;
//////////////////////////////////////////////////////////////////
/**
 * @brief Function Prototypes for Scenes Manager
 * 
 * These functions are used to initialize scenes, create new scenes,
 * change the current scene, and retrieve information about the current scene.
 * 
 * @param void
 * 
 * @return void
 */
void InitScenesManager(void);
/**
 * @brief Create a new Scene
 * 
 * This function creates a new scene with the specified name, information, log, and type.
 * 
 * @param type        Type of the scene (ManagerScenes)
 * 
 * @return Scene*    Pointer to the newly created scene
 * 
 * This function allocates memory for a new scene, initializes its fields,
 * and returns a pointer to the scene.
 */
Scene* CreateScene(ManagerScenes type);
/**
 * @brief Change the current scene
 * 
 * This function changes the current scene to the specified next scene.
 * 
 * @param ManagerScenes       The next scene to switch to (ManagerScenes)
 * 
 * This function updates the `scenes` variable to point to the new scene,
 * effectively changing the game's current state.
 */
void ChangeScene(ManagerScenes next);
/**
 * @brief Get the current scene
 * 
 * This function retrieves the current scene's information.
 * 
 * @param Scene        The current scene (Scene)
 * 
 * @return Int          ID of the Scene.
 * 
 * This function returns the `InformationScene` struct associated with the current scene,
 * which includes the name, information, log, and type of the scene.
 * 
 */
int GetCurrentScene(Scene current);




//////////////////////////////////////////////////////////////////
