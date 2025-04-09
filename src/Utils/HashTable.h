#pragma once
///< C/C++ Lib
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
///< Extern Lib
#include "raylib.h"
///< CGame lib
/// @brief Item of the HashTable
/// @param char* key
/// @param char* value
typedef struct _item
{
    int id;
    Texture2D tile;
}ItemHT;
/// @brief HashTable Main struct
typedef struct _HT
{
    ItemHT** items;
    int size;
    int count;
}HashTable;
///////////////////////////////////////////////////////////////
/**
 * @brief Init HashTable
 * @param int               ///< Size of the HashTable
 */
HashTable* CreateHashTable(int);
/**
 * @brief Insert Item to HashTable
 * 
 * @param HasTable*                 ///< Main HashTable
 * @param int                       ///< ID of the Tile.
 * @param Texture2D                 ///< Texture2D to save the Tile.
 */
void InsertItem(HashTable*,int,Image);
/**
 * @brief Search item in the HashTable
 * @param HashTable*                            ///< The main HashTable.
 * @param int                                   ///< ID, is the KEY for search in the HashTable.
 */
ItemHT* SearchItem(HashTable*,int);
/**
 * 
 */
bool IsTileEmpty(Image,int,int);
/**
 * 
 */
void PrintHashTable(HashTable*);
/**
 * 
 */
int HashFunction(int,int);
/**
 * 
 */
void FreeItem(ItemHT*);
/**
 * 
 */
void FreeHashTable(HashTable*);


