project(Project)

add_subdirectory(Main)
add_subdirectory(Engine)
add_subdirectory(Game)
<<<<<<< HEAD
add_subdirectory(Components)
add_subdirectory(Utils)
=======
add_subdirectory(Entity)
add_subdirectory(Utils)
add_subdirectory(Textures)
>>>>>>> origin/main
add_subdirectory(Scenes)

target_include_directories(Project PRIVATE ./)
