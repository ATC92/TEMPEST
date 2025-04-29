#include "HashTable.h"
#include "../Textures/Textures.h"
/**
 * 
 */
HashTable* CreateHashTable(int size)
{
    // Creates a new HashTable.
    HashTable* table = (HashTable*)calloc(1,sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (ItemHT**)calloc(table->size, sizeof(ItemHT*));
    return table;
}
/**
 * 
 */
void InsertItem(HashTable* ht, int id, Image tile)
{
    ItemHT* item = (ItemHT*)calloc(1,sizeof(ItemHT));
    item->id = id;
    item->tile = LoadTextureFromImage(tile);
    int index = HashFunction(id, ht->size);
    // Linear probing en caso de colisión
    while (ht->items[index] != NULL && ht->items[index]->id != id)
        index = (index + 1) % ht->size;
    if (ht->items[index] == NULL)
        ht->count++;
    ht->items[index] = item;
}
/**
 * 
 */
ItemHT* SearchItem(HashTable* ht, int id)
{
    int index = HashFunction(id, ht->size);
    while (ht->items[index] != NULL) {
        if (ht->items[index]->id == id)
            return ht->items[index];
        index = (index + 1) % ht->size;
    }
    return NULL;
}
/**
 * 
 */
void FillHashTable(HashTable* _HT, TileMap* _TM)
{
    ///< 
    int countTiles = 1;
    int tilesX = _TM->tmImage.width / TILE_SIZE;
    int tilesY = _TM->tmImage.height / TILE_SIZE;
    ///<
    for (int y = 0; y < tilesY; y++)
    {
        for (int x = 0; x < tilesX; x++)
        {
            int tileX = x * TILE_SIZE;
            int tileY = y * TILE_SIZE;
            if (!IsTileEmpty(_TM->tmImage, tileX, tileY))
            {
                // Extraer tile como subimagen
                Image tile = ImageFromImage(_TM->tmImage, (Rectangle){ tileX, tileY, TILE_SIZE, TILE_SIZE });
                InsertItem(_HT,countTiles,tile);
                UnloadImage(tile);
                countTiles++;
            }
        }
    }
    UnloadImage(_TM->tmImage);
}
/**
 * 
 */
/**
 * 
 */
void PrintHashTable(HashTable* _HT)
{
    for (int i = 0; i < _HT->size; i++)
    {
        if (_HT->items[i] != NULL)
        {
            if (IsTextureValid(_HT->items[i]->tile))
                printf("\nItem: %d | ID: %d | Valid Texture", i, _HT->items[i]->id);
            else
                printf("\nItem: %d | ID: %d | Invalid Texture", i, _HT->items[i]->id);
        }
    }
}
/**
 * 
 */
int HashFunction(int key, int size)
{
    return key % size;
}
/**
 * 
 */
void FreeItem(ItemHT* item)
{
    // Frees an item.
    UnloadTexture(item->tile);
    free(item);
}
/**
 * 
 */
void FreeHashTable(HashTable* table)
{
    // Frees the table.
    for (int i = 0; i < table->size; i++)
    {
        ItemHT* item = table->items[i];
        if (item != NULL)
            FreeItem(item);
    }
    free(table->items);
    free(table);
}