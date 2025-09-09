#pragma once
//////////////////////////////////////////////////////////////////////
///< C/C++ Libraries
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////
///< Struct definition for VectorItem
/**
 * @brief A dynamic array (vector) structure for storing elements of arbitrary type.
 * 
 * @note This structure is designed to hold elements of any type by using a void pointer for the items.
 * The size of each element is specified during initialization.
 */
typedef struct _vecItem
{
    void* item;                     ///< Item `void*`
    size_t itemSize;                ///< Iteam size `size_t`
}VectorItem;
///< Struct definition for Vector
typedef struct _vect
{
    VectorItem* itemsArray;         ///< ItemsArray*
    size_t capacity;                   ///< Capacity of array
    size_t size;                       ///< Size of the array
}Vector;
///< Struct definition for PairVector
/**
 * @brief Dynamic struct for create pair of date.
 */
typedef struct _twoTypes
{
    int iItem;                      ///< Firts item Int
    float fItem;                    ///< Second Item Float
}PairVector;

//////////////////////////////////////////////////////////////////////
/**
 * @brief Initialize a dynamic vector.
 * 
 * @param Vector* v          ///< Pointer to the vector to initialize
 * @param size_t itemSize    ///< Size of each element in the vector
 * 
 * @return @n `Void`
 * 
 * @note This function initializes the vector structure, setting its size and capacity to zero and allocating no memory initially.
 */
static inline void InitVector(Vector* v, int sizeVector)
{
    v = (Vector*)calloc(1, sizeof(Vector));
    v->itemsArray = (VectorItem*)calloc((size_t)sizeVector, sizeof(VectorItem));
    for(int i = 0; i < sizeVector; i++)
    {
        v->itemsArray[i].item = NULL;
        v->itemsArray[i].itemSize = 0;
    }
    v->capacity = (size_t)sizeVector;
    v->size = 0;
}
/**
 * @brief Add an element to the end of the vector.
 * 
 * @param Vector* v         ///< Pointer to the vector
 * @param void* element     ///< Pointer to the element to add
 * 
 * @return @n `Void`
 * 
 * @note The element is copied into the vector, so the original element can be freed or go out of scope after this call.
 */
static inline int PushBackVector(Vector* v, void* element, size_t sizeElement)
{
    if(v->size >= v->capacity) {
        size_t newCapacity = v->capacity ? v->capacity * 2 : 1;
        VectorItem* tempVector = (VectorItem*)realloc(v->itemsArray, newCapacity * sizeof(VectorItem));
        if(!tempVector)
            return 0;
        v->itemsArray = tempVector;
        v->capacity = newCapacity;
    }
    v->itemsArray[v->size] = (VectorItem){0};
    v->itemsArray[v->size].item = malloc(sizeElement);
    if (!v->itemsArray[v->size].item) return 0;
    memcpy(v->itemsArray[v->size].item, element, sizeElement);
    v->itemsArray[v->size].itemSize = sizeElement;
    v->size++;

    return 1;
}
/**
 * @brief Get an element from the vector by index.
 * 
 * @param Vector* v         ///< Pointer to the vector
 * @param int index        ///< Index of the element to retrieve
 * 
 * @return @n `void*` Pointer to the element at the specified index, or NULL if index is out of bounds
 * 
 * @note The returned pointer is valid as long as the vector is not modified (e.g., no further PushBackVector calls).
 */
static inline void* GetVector(Vector* v, int index) {
    auto final = (int)v->size;
    if(index < 0 || index >= final) return NULL;
    return v->itemsArray[index].item;
}
/**
 * @brief Free the memory allocated for the vector.
 * 
 * @param Vector* v         ///< Pointer to the vector to free
 * 
 * @return @n `Void`
 * 
 * @note This function frees the memory used by the vector and resets its fields.
 */
static inline void FreeVector(Vector* v) {
    auto final = (int)v->size;
    for(int i=0; i < final;i++)
    {
        free(v->itemsArray[i].item);
        v->itemsArray[i].itemSize = 0;
    }
    free(v->itemsArray);
    v->capacity = 0;
    v->size = 0;
}
/**
 * @brief Remove the last element from the vector.
 * 
 * @param Vector* v         ///< Pointer to the vector
 * 
 * @return @n `Void`
 * 
 * @note This function decreases the size of the vector by one, effectively removing the last element.
 */
static inline void PopBackVector(Vector* v){
    if(v->size > 0)
    {
        auto index = v->size  - 1;
        free(v->itemsArray[index].item);
        v->itemsArray[index].item = NULL;
        v->itemsArray[index].itemSize = 0;
        v->size--;
    }
}


//////////////////////////////////////////////////////////////////////