//////////////////////////////////////////////////////////////////
#pragma once
//////////////////////////////////////////////////////////////////
#include "../Engine/Flags.h"
//////////////////////////////////////////////////////////////////
extern Camera2D camera;
//////////////////////////////////////////////////////////////////
/**
 * 
 */
Camera2D InitCamera(void);
/**
 * @brief Mouse Wheel Update
 * 
 * @param Camera2D*           ///< Camera 2D reference
 * 
 * @return @n `Void`  
 */
void UpdateCameraWheel(Camera2D* camera);
/**
 * @brief Lock the camera to a specific zone
 * 
 * @param camera       Pointer to the Camera2D structure
 * @param zoneSize     Size of the zone to lock the camera to
 * 
 * @return @n `Void`
 * 
 * This function ensures that the camera's target position does not exceed the boundaries of the specified zone size.
 * It adjusts the camera's target position to keep it within the defined zone, preventing it from
 * going out of bounds based on the screen dimensions and camera zoom level.
 * 
 */
void LockCameraToZone(Camera2D*,Rectangle);
/**
 * 
 */
void SmoothCameraMovement(Camera2D* camera, float smoothFactor, Rectangle target);
//////////////////////////////////////////////////////////////////