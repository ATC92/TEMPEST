//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Dialog.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LoadDialogs(const char *path, DialogTree *tree)
{
    FILE *f = fopen(path, "r");
    if (!f) return;

    char line[512];
    tree->cantidad = 0;

    while (fgets(line, sizeof(line), f))
    {
        if (line[0] == '#' || strlen(line) < 3) 
            continue; // comentario o vacío

        Dialog d;
        char *tok = strtok(line, "|");
        if (!tok) continue;
        d.id = atoi(tok);

        tok = strtok(NULL, "|"); 
        strncpy(d.texto, tok, MAX_TEXT);
        tok = strtok(NULL, "|"); 
        strncpy(d.opcion1, tok, MAX_OPTION);
        tok = strtok(NULL, "|"); 
        strncpy(d.opcion2, tok, MAX_OPTION);
        tok = strtok(NULL, "|"); 
        d.destino1 = atoi(tok);
        tok = strtok(NULL, "|"); 
        d.destino2 = atoi(tok);

        tree->dialogos[tree->cantidad++] = d;
    }
    fclose(f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////