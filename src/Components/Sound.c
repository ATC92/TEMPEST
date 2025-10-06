//////////////////////////////////////////////////////////
#include "Sound.h"
//////////////////////////////////////////////////////////
///< Public declarations
Sound* sounds;
Music* music;
MusicType currentMusic;
bool fading = false;
float masterVolume = 1.0f;
///< Private declarations
static size_t totalMusic;
static size_t totalSounds;
static float musicVolume = 1.0f;
static float targetVolume = 1.0f;
static float fadeSpeed = 0.05f;
//////////////////////////////////////////////////////////
void InitSounds(void)
{
    ///!<---------- Sounds Paths ---------->
    char* soundPath = "assets/FX/UI/click-b.wav";
    ///< Total Sounds loaded
    totalSounds = 1;
    ///< Memory allocation for the sounds 
    sounds = (Sound*)calloc(totalSounds,sizeof(Sound));
    Sound guiClick= LoadSound(soundPath);
    ///!<-------- Loading Sounds ---------->
    if(!IsSoundValid(guiClick))
        TraceLog(LOG_ERROR,"Sound not loaded: [%s]",soundPath);
    else
        sounds[0] = guiClick;

}
void DestroySounds(void)
{
    for (size_t i = 0; i < totalSounds; i++)
        UnloadSound(sounds[i]);
    free(sounds);
}
//////////////////////////////////////////////////////////
///< Music Part
void InitMusic(void)
{
    ///!<---------- Music Paths ---------->
    char* musicPathMainMenu = "assets/FX/Music/fantasy_music/Intro.mp3";
    char* musicPathGameState = "assets/FX/Music/fantasy_music/Adventure.mp3";
    ///< Total Music loaded
    totalMusic = 2;
    currentMusic = MS_MAINMENU;
    ///< Memory allocation for the music 
    music = (Music*)calloc(totalMusic,sizeof(Music));
    Music mMainMenu = LoadMusicStream(musicPathMainMenu);
    Music mGameState = LoadMusicStream(musicPathGameState);
    ///!<-------- Loading Music ---------->
    if(!IsMusicValid(mMainMenu))
        TraceLog(LOG_ERROR, "Music [0] not valid, %s",musicPathMainMenu);
    else 
        music[0] = mMainMenu;
    if(!IsMusicValid(mGameState))
        TraceLog(LOG_ERROR, "Music [1] not valid, %s",musicPathGameState); 
    else 
        music[1] = mGameState;

}
void ChangeMusic()
{
    targetVolume = 0.0f;
    fading = true;
}
void UpdateMusicScene(ManagerScenes typeScene)
{
    if(currentMusic != MS_NONE)
        SetMusicVolume(music[currentMusic], masterVolume);
    switch(typeScene)
    {
        case sGAMESTATE:
            currentMusic = MS_GAMESTATE;
            if(fading)
                FaidingMusic(MS_MAINMENU, MS_GAMESTATE);
            else
                UpdateMusicStream(music[currentMusic]);
            break;
        case sMAINMENU:
            currentMusic = MS_MAINMENU;
            if(fading)
                FaidingMusic(MS_GAMESTATE,MS_MAINMENU);
            else 
                UpdateMusicStream(music[currentMusic]);
            break;
        case sOPTIONMENU:
            currentMusic = scenes->previousScene == sMAINMENU ? MS_MAINMENU : MS_GAMESTATE;
            UpdateMusicStream(music[currentMusic]);
            break;
        case sBESTIARY:
            currentMusic = MS_MAINMENU;
            UpdateMusicStream(music[currentMusic]);
            break;
        default:
            // TraceLog(LOG_FATAL,"Error, Music problem: [%d]",currentMusic);
            break;
    }
}
void FaidingMusic(MusicType currentMusic, MusicType nextMusic)
{
    if (fading) {
        if (musicVolume > targetVolume)
        {
            ///< Fade out
            musicVolume -= fadeSpeed;
            if (musicVolume < targetVolume) musicVolume = targetVolume;
            if (currentMusic != MS_NONE)
                SetMusicVolume(music[currentMusic], musicVolume);
        } else if (musicVolume < targetVolume)
        {
            ///< Fade in
            musicVolume += fadeSpeed;
            if (musicVolume > targetVolume) musicVolume = targetVolume;
            if (currentMusic != MS_NONE)
                SetMusicVolume(music[currentMusic], musicVolume);
        } else {
            ///< We are at target volume
            if (targetVolume == 0.0f)
            {
                ///< End of fade out, switch music
                if (currentMusic != MS_NONE) StopMusicStream(music[currentMusic]);
                currentMusic = nextMusic;
                if (currentMusic != MS_NONE) {
                    PlayMusicStream(music[currentMusic]);
                    SetMusicVolume(music[currentMusic], 0.0f);
                }
                targetVolume = 1.0f;
            } else 
            {
                ///< End of fade in
                fading = false;
            }
        }
    }
}
void DestroyMusic(void)
{
    for(size_t i=0; i<totalMusic; i++)
        UnloadMusicStream(music[i]);
    free(music);
}
//////////////////////////////////////////////////////////