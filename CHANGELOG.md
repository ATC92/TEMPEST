# Changelog

**Author:** ATC92

## [0.2.4] - 2025-10-15
### ADDED
- [High]    Veyx data: the game now loads Veyx information from a .data file.
- [Medium]  Bestiary information, now you can see the Veyx information.

### CHANGED
- [High]    Optimized game save and load system.
- [High]    The game now properly reinitializes when exiting and starting again.
- [Medium]  Added exit animation to the BestiaryScene scroll.
- [Low]     Added compile variables to /TEMPEST. ASSETS compile definition now works.

### BUG FIXED
- Nothing to report for now.

### PLANNED
- [High]    Implement the Fight System.
- [High]    Add the Boss System.
- [Medium]  Add more details to the map.
- [Low]     Add unique sounds for each Veyx.

--------------------------------------------------------------

## [0.2.2] - 2025-10-06

### ADDED
- [High]    Veyx structs and data loading.
- [Medium]  Volume control in the Options Menu.
- [Medium]  Parallax effect in the Main Menu.
- [Medium]  Scrollable UI for the Bestiary Scene.
- [Medium]  Fade effect for the Options Menu when the previous scene is GameState.
- [Low]     New cursor sprite.

### CHANGED
- [High]    Optimized game logic and rendering.
- [High]    GameInit now starts in the LoadingScene.
- [Low]     Button sprite for FullScreen updated.

### BUG FIXED
- [Low]     Increased the collision box size of the 'Return' button.
- [Low]     Fixed textures in the Bestiary Scene that were drawing behind the scroll.

### PLANNED
- [High]    Implement the Fight System.
- [High]    Add the Boss System.
- [Medium]  Add more details to the map.
- [Low]     Add sounds for each Veyx.
 
--------------------------------------------------------------

## [0.2.0] - 2025-09-27
### ADDED
- [High]    Animation Engine, for all NPC and Player.
- [Medium]  Music to the MainMenu and GAMESTATE.
- [Low]     Rectangle progress for the music volume.

### CHANGED
- [High]    Scene render, now is more optimized.

### BUG FIXED
- [High]    LoadingScene used to stop the entire game before the scene ended; now it updates correctly each frame.

### PLANNED
- [High]    Implement Fight System.
- [High]    Veyx implementation for the game.
- [Medium]  Add more textures.                
- [Medium]  Add more details on the map.
- [Low]     Add sounds for each Veyx