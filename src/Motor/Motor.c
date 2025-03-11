#include "Motor.h"

sTile World[WORLD_TILE_WIDTH][WORLD_TILE_HEIGHT];
Texture2D textures[MAX_TEXTURES];
Texture2D textures_player[MAX_TEXTURES];
Camera2D camera = {0};
Entity player = {0};

void InitGame()
{
    //
    InitAudioDevice();
    // The Tilemap is 203x186, so 16x16 each tile
    // The tilemap is 12 width and 11 Height Tiles.
    Image image = LoadImage("assets/Tilemap/tilemap_packed.png");
    // The CharacterMap is 918*203, so 16x16 each tile
    // The CharacterMap is 57 width and 12 Height Tiles
    Image image2 = LoadImage("assets/Player/roguelikeChar_transparent.png");
    textures_player[TEXTURE_TILEMAP] = LoadTextureFromImage(image2);
    textures[TEXTURE_TILEMAP] = LoadTextureFromImage(image);
    UnloadImage(image);
    UnloadImage(image2);

    for (int i = 0; i < WORLD_TILE_WIDTH; i++)
    {
        for(int j = 0; j < WORLD_TILE_HEIGHT; j++)
        {
            World[i][j] = (sTile)
            {
                .x = i,
                .y = j,
            };
        }
    }

    // Player
    player = GenEntity(PLAYER, "Hero", 100.f,20.f,2.f,20.f);
    player.EntityData.Player.position = (Vector2){TILE_WIDTH * 3, TILE_HEIGHT * 3};

    camera.target = player.EntityData.Player.position;
    camera.zoom = 3.0f;
    camera.rotation = 0.0f;
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
}

void DeInitGame()
{
    for (int i = 0; i < MAX_TEXTURES; i++)
    {
        UnloadTexture(textures[i]);
        UnloadTexture(textures_player[i]);
    }
    //
    CloseAudioDevice();
}

void GameRender()
{
    // Enter 2D mode
    BeginMode2D(camera);
    sTile tile;
    int texture_index_x=0;
    int texture_index_y=0;
    for (int i = 0; i < WORLD_TILE_WIDTH; i++)
    {
        for (int j = 0; j < WORLD_TILE_HEIGHT; j++)
        {
            tile = World[i][j];
            texture_index_x = 1;
            texture_index_y = 0;
            Rectangle source = {(float)texture_index_x * TILE_WIDTH, (float)texture_index_y * TILE_HEIGHT, (float)TILE_WIDTH, (float)TILE_HEIGHT};
            Rectangle dest = {(float)(tile.x * TILE_WIDTH), (float)(tile.y * TILE_HEIGHT), (float)TILE_WIDTH, (float)TILE_HEIGHT};
            Vector2 origin = {0 , 0};
            DrawTexturePro(textures[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE);
        }
    }
    // Player
    Rectangle source = {(float)(1 * TILE_WIDTH), (float)(7 * TILE_HEIGHT), (float)TILE_WIDTH, (float)TILE_HEIGHT};
    Rectangle dest = {(float)(camera.target.x), (float)(camera.target.y), (float)TILE_WIDTH, (float)TILE_HEIGHT};
    Vector2 origin = {0 , 0};
    DrawTexturePro(textures_player[TEXTURE_TILEMAP], source, dest, origin, 0.0f, WHITE);
    
    EndMode2D();

    DrawRectangle(5,5,330,120,Fade(SKYBLUE, 0.5f));
    DrawRectangleLines(5,5,330,120,BLUE);

    DrawText(TextFormat("Camera Target: (%06.2f, %06.2f)",camera.target.x, camera.target.y),15,10,14,YELLOW);
    DrawText(TextFormat("Camera Zoom: %06.2f ", camera.zoom),15,30,14,YELLOW);
}

void GameUpdate()
{
    float wheel = GetMouseWheelMove();
    if(wheel != 0)
    {
        const float zoomIncrement = 0.125f;
        camera.zoom += (wheel + zoomIncrement);
        if(camera.zoom < 3.0f) camera.zoom = 3.0f;
        if(camera.zoom > 8.0f) camera.zoom = 8.0f;
    }

    camera.target = player.EntityData.Player.position;
}

void updateMovement()
{
    if(IsKeyDown(KEY_A))
        player.EntityData.Player.position.x -= player.EntityData.Player.speed;
    else if (IsKeyDown(KEY_D))
        player.EntityData.Player.position.x += player.EntityData.Player.speed;
    else if(IsKeyDown(KEY_W))
        player.EntityData.Player.position.y -= player.EntityData.Player.speed;
    else if(IsKeyDown(KEY_S))
        player.EntityData.Player.position.y += player.EntityData.Player.speed;

    if(IsKeyDown(KEY_LEFT_SHIFT))
        player.EntityData.Player.speed = 3.f;
    else if(IsKeyReleased(KEY_LEFT_SHIFT))
        player.EntityData.Player.speed = 2.f;
}


