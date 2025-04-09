project(Project)

add_subdirectory(Main)
add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(Entity)
add_subdirectory(Utils)
add_subdirectory(Textures)
add_subdirectory(Scenes)

target_include_directories(Project PRIVATE ./)
