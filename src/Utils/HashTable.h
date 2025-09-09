#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
///< Extern Lib
#include "raylib.h"
///< CGame lib
#include "../Textures/Map.h"\
//////////////////////////////////////////////////////////////////
/**
 * @brief HashTable Item struct
 * 
 * This struct represents an item in the hash table.
 * It contains an ID and a Texture2D representing a tile.
 * 
 * @c id     ID of the Tile (int) \\
 * @c tile   Texture2D of the Tile.
 */
typedef struct _item
{
    int id;
    Texture2D tile;
}ItemHT;
/**
 * @brief HashTable struct
 * 
 * This struct represents a hash table.
 * It contains an array of pointers to ItemHT, the size of the table,
 * and the count of items currently stored in the table.
 * 
 * @c items  Array of pointers to ItemHT \\
 * @c size   Size of the HashTable (int) \\
 * @c count  Count of items in the HashTable (int)
 */
typedef struct _HT
{
    ItemHT** items;
    int size;
    int count;
}HashTable;
///////////////////////////////////////////////////////////////
/**
 * @brief Create a HashTable
 * 
 * This function creates a new hash table with a specified size.
 * It initializes the size, count, and allocates memory for the items array.
 * 
 * @param size  Size of the HashTable (int)
 * 
 * @return HashTable*  Pointer to the newly created HashTable.
 * 
 * This function allocates memory for a new HashTable structure,
 * initializes its size and count, and allocates memory for the items array.
 * The items array is initialized to hold pointers to ItemHT structures.
 */
HashTable* CreateHashTable(int);
/**
 * @brief Insert Item to HashTable
 * 
 * This function inserts an item into the hash table.
 * It creates a new ItemHT, sets its ID and tile texture,
 * and calculates the index using a hash function.
 * If a collision occurs, it uses linear probing to find the next available slot.
 * 
 * @param HashTable*                            ///< The main HashTable.
 * @param int                                   ///< ID, is the KEY for insert in the HashTable.
 * @param Image                                 ///< Image, is the tile to insert in the HashTable.
 * 
 * @return 'Void'.
 */
void InsertItem(HashTable*,int,Image);
/**
 * @brief Search item in the HashTable
 * 
 * This function searches for an item in the hash table by its ID.
 * It calculates the index using a hash function and uses linear probing to find the item.
 * If the item is found, it returns a pointer to the ItemHT; otherwise, it returns NULL.
 * 
 * @param HashTable*                            ///< The main HashTable.
 * @param int                                   ///< ID, is the KEY for search in the HashTable.
 * 
 * @return ItemHT*                             ///< Pointer to the found ItemHT, or NULL if not found.
 */
ItemHT* SearchItem(HashTable*,int);
/**
 * @brief Fill HashTable
 * 
 * This function fills the hash table with items from a TileMap.
 * It iterates through the tiles in the TileMap, checks if each tile is empty,
 * and if not, extracts the tile as a sub-image, inserts it into the hash table
 * 
 * @param HashTable*                            ///< The main HashTable to fill.
 * @param TileMap*                              ///< The TileMap containing the tiles to insert.
 * 
 * @return 'Void'.
 */
void FillHashTable(HashTable*,TileMap*);
/**
 * @brief HashFunction
 * 
 * This function calculates the hash index for a given key and size.
 * It uses the modulo operator to ensure the index is within the bounds of the hash table size
 * 
 * @param key   The key to hash (int) \\
 * @param size  The size of the hash table (int)
 * 
 * @return int  The calculated hash index.
 */
int HashFunction(int,int);
/**
 * @brief Free HashTable Item
 * 
 * This function frees the memory allocated for an ItemHT.
 * It unloads the texture associated with the item and then frees the item itself.
 * 
 * @param ItemHT*  Pointer to the ItemHT to free.
 * 
 * @return 'Void'.
 */
void FreeItem(ItemHT*);
/**
 * @brief Free HashTable
 * 
 * This function frees the memory allocated for a HashTable.
 * It iterates through the items array, frees each ItemHT,
 * and then frees the items array and the hash table itself.
 * 
 * @param HashTable*  Pointer to the HashTable to free.
 * 
 * @return 'Void'.
 */
void FreeHashTable(HashTable*);
//////////////////////////////////////////////////////////////////

