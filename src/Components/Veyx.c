///////////////////////////////////////////////////////////
#include "Veyx.h"
#include<string.h>
///////////////////////////////////////////////////////////
///< Public declarations
Veyx* VeyxRegistry;
size_t countVeyx;
///////////////////////////////////////////////////////////
void InitVeyxRegistry(void)
{
    countVeyx = 0;
    VeyxRegistry = (Veyx*)calloc(10,sizeof(Veyx));
    if(VeyxRegistry == NULL)
        TraceLog(LOG_ERROR,"Not create dinamyc memory to VeyxRegistry");
}
void DestroyVeyxRegistry(void)
{
    // for(size_t i=0; i<50;i++)
    // {
    //     UnloadTexture(VeyxRegistry[i].animation->spriteSheet);
    // }
    free(VeyxRegistry);
}

void LoadVeyxData(char* path)
{
    FILE *fDataVeyx = fopen(path,"r");
    
    char line[500];

    if(fDataVeyx == NULL)
        TraceLog(LOG_ERROR,"Archive VeyxData not open.");
    else
        TraceLog(LOG_INFO, "Archive VeyxData Loaded correctly");
    
    while(fgets(line, sizeof(line), fDataVeyx) != NULL)
    {
        int i = 0;
        char *token = strtok(line, "|");
        while(token != NULL) 
        {
            switch(i) 
            {
                case 0: 
                    strncpy(VeyxRegistry[countVeyx].name, token, sizeof(VeyxRegistry[countVeyx].name)-1); 
                    VeyxRegistry[countVeyx].name[sizeof(VeyxRegistry[countVeyx].name)-1] = '\0';
                    break;
                case 1: 
                    strncpy(VeyxRegistry[countVeyx].origin, token, sizeof(VeyxRegistry[countVeyx].origin)-1); 
                    VeyxRegistry[countVeyx].origin[sizeof(VeyxRegistry[countVeyx].origin)-1] = '\0';
                    break;
                case 2: 
                    strncpy(VeyxRegistry[countVeyx].description, token, sizeof(VeyxRegistry[countVeyx].description)-1); 
                    VeyxRegistry[countVeyx].description[sizeof(VeyxRegistry[countVeyx].description)-1] = '\0';
                    break;
                case 3: VeyxRegistry[countVeyx].life = (uint8_t)atoi(token); break;
                case 4: VeyxRegistry[countVeyx].mana = (uint8_t)atoi(token); break;
                case 5: VeyxRegistry[countVeyx].speed = (uint8_t)atoi(token); break;
                case 6: VeyxRegistry[countVeyx].defense = (uint8_t)atoi(token); break;
                case 7: VeyxRegistry[countVeyx].physical_attack = (uint8_t)atoi(token); break;
                case 8: VeyxRegistry[countVeyx].magic_attack = (uint8_t)atoi(token); break;
                case 9: VeyxRegistry[countVeyx].type[0] = atoi(token); break;
                case 10: VeyxRegistry[countVeyx].type[1] = atoi(token); break;
            }
            token = strtok(NULL, "|");
            i++;
        }
        // TraceLog(LOG_INFO, "-->>>Loading Veyx #%zu", countVeyx);
        // TraceLog(LOG_INFO, ":::-> Name\t %s",VeyxRegistry[countVeyx].name);
        // TraceLog(LOG_INFO, ":::-> Origin\t %s",VeyxRegistry[countVeyx].origin);
        // TraceLog(LOG_INFO, ":::-> Description\t %s",VeyxRegistry[countVeyx].description);
        // TraceLog(LOG_INFO, ":::-> Life\t %u",VeyxRegistry[countVeyx].life);
        // TraceLog(LOG_INFO, ":::-> Mana\t %u",VeyxRegistry[countVeyx].mana);
        // TraceLog(LOG_INFO, ":::-> Speed\t %u",VeyxRegistry[countVeyx].speed);
        // TraceLog(LOG_INFO, ":::-> Defense\t %u",VeyxRegistry[countVeyx].defense);
        // TraceLog(LOG_INFO, ":::-> pA\t\t %u",VeyxRegistry[countVeyx].physical_attack);
        // TraceLog(LOG_INFO, ":::-> mA\t\t %u",VeyxRegistry[countVeyx].magic_attack);
        // TraceLog(LOG_INFO, ":::-> T-1\t\t %d",VeyxRegistry[countVeyx].type[0]);
        // TraceLog(LOG_INFO, ":::-> T-2\t\t %d",VeyxRegistry[countVeyx].type[1]);
        char* path = TextFormat(ASSETS "/Veyx/%s/%s-Icon.png",VeyxRegistry[countVeyx].name,VeyxRegistry[countVeyx].name);
        if(IsPathFile(TextFormat(ASSETS "/Veyx/%s/%s-Icon.png",VeyxRegistry[countVeyx].name,VeyxRegistry[countVeyx].name)))
            VeyxRegistry[countVeyx].iconText = LoadTexture(path);
        countVeyx++;
        //TextFormat("assets/Veyx/%s/%s-Icon.png",VeyxRegistry[countVeyx].name,VeyxRegistry[countVeyx].name)
    }


    fclose(fDataVeyx);
}
///////////////////////////////////////////////////////////
