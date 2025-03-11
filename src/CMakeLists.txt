project(Project)

add_subdirectory(Main)
add_subdirectory(Motor)
add_subdirectory(Juego)
add_subdirectory(Entity)
add_subdirectory(Funcionalidades)

target_include_directories(Project PRIVATE ./)
