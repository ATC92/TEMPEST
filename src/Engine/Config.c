////////////////////////////////////////////////////////////////////////////
#include "Config.h"
////////////////////////////////////////////////////////////////////////////
///< Public definition
GameConfig gameConfig;
////////////////////////////////////////////////////////////////////////////
void SaveConfig(GameConfig cfg, const char* filename)
{
    
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Error al abrir config.txt");
        return;
    }

    fprintf(f, "fullscreen=%d\n", cfg.fullscreen);
    fprintf(f, "width=%d\n", cfg.width);
    fprintf(f, "height=%d\n", cfg.height);
    fprintf(f, "volume=%f\n", cfg.volume);
    fclose(f);
}
////////////////////////////////////////////////////////////////////////////
GameConfig LoadConfig(const char* filename)
{
    GameConfig cfg = {0, 720, 1280, 1.0f};
    FILE* f = fopen(filename, "r");
    if (!f)
    {
        perror("ERRO Config.txt");
        return cfg;
    }

    char line[128];
    while (fgets(line, sizeof(line), f)) {
        char key[50], value[50];
        if (line[0] == '\n' || line[0] == '#' || line[0] == ';')
            continue;
        if (sscanf(line, "%49[^=]=%49s", key, value) == 2) {
            if (strcmp(key, "fullscreen") == 0) cfg.fullscreen = atoi(value);
            else if (strcmp(key, "width") == 0) cfg.width = atoi(value);
            else if (strcmp(key, "height") == 0) cfg.height = atoi(value);
            else if (strcmp(key, "volume") == 0) cfg.volume = (float)atof(value);
        }
    }

    fclose(f);
    return cfg;
}
////////////////////////////////////////////////////////////////////////////
