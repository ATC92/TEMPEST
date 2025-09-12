#include "Sound.h"
Sound* sounds;
void InitSoundGame(void)
{
    char* soundPath = "assets/Sounds/UI/click-b.wav"; 

    sounds = (Sound*)calloc(1,sizeof(Sound));
    sounds[0] = LoadSound(soundPath);
}