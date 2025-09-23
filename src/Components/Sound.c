#include "Sound.h"
Sound* sounds;
Music* music;
void InitSoundGame(void)
{
    char* soundPath = "assets/Sounds/UI/click-b.wav"; 

    sounds = (Sound*)calloc(1,sizeof(Sound));
    sounds[0] = LoadSound(soundPath);
}
void InitMusic(void)
{
    char* musicPath = "assets/Sounds/Music/";
    
}