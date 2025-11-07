project(TEMPEST)

add_subdirectory(Main)
add_subdirectory(Engine)
add_subdirectory(Game)
add_subdirectory(Components)
add_subdirectory(Utils)
add_subdirectory(Scenes)

target_include_directories(TEMPEST PRIVATE ./)
