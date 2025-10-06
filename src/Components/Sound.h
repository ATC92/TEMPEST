///////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////
///< TEMPEST Lib
#include "../Engine/Flags.h"
#include "../Scenes/ScenesManager.h"
///////////////////////////////////////////////////////////////
typedef enum _MusicType
{
    MS_NONE = -1,
    MS_MAINMENU,
    MS_GAMESTATE
}MusicType;
///////////////////////////////////////////////////////////////
///< Public Variables
extern Sound* sounds;
extern Music* music;
extern bool fading;
extern MusicType currentMusic;
extern float masterVolume;
///////////////////////////////////////////////////////////////
/**
 * @brief Initialize the sound effects for the game.
 * This function loads sound files and prepares them for playback.
 * 
 * @param void 
 * 
 * @return void
 * 
 * @note Make sure to call `DestroySoundGame` to free resources when done.
 */
void InitSounds(void);
/**
 * @brief Free resources allocated for sound effects.
 * This function unloads sound files and frees memory.
 * 
 * @param void
 * 
 * @return void
 * 
 * @note Call this function when sound effects are no longer needed.
 */
void DestroySounds(void);
///////////////////////////////////////////////////////////////
/**
 * @brief Initialize the music tracks for the game.
 * This function loads music files and prepares them for playback.
 * 
 * @param void
 * 
 * @return void
 * 
 * @note Make sure to call `DestroyMusic` to free resources when done.
 */
void InitMusic(void);
/**
 * @brief Change the currently playing music track.
 * This function stops the current track and starts a new one.
 * 
 * @return void
 * 
 * @note Ensure that the indices provided are valid.
 */
void ChangeMusic();
/**
 * @brief Handle the fading effect between music tracks.
 * This function gradually decreases the volume of the current track
 * 
 * @param currentMusic The index of the currently playing music track.
 * @param nextMusic The index of the next music track to play.
 * 
 * @return void
 * 
 * @note Call this function in the main update loop to achieve the fading effect.
 */
void FaidingMusic(MusicType currentMusic, MusicType nextMusic);
/**
 * @brief Update the music playback based on the current scene.
 * This function should be called regularly to ensure smooth music playback.
 * 
 * @param typeScene The current scene type to determine which music to update.
 * 
 * @return void
 * 
 * @note Call this function in the main update loop of your game.
 */
void UpdateMusicScene(ManagerScenes typeScene);
/**
 * @brief Free resources allocated for music tracks.
 * This function unloads music files and frees memory.
 * 
 * @param void
 * 
 * @return void
 * 
 * @note Call this function when music tracks are no longer needed.
 */
void DestroyMusic(void);
///////////////////////////////////////////////////////////////
