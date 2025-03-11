cmake_minimum_required(VERSION 3.22)
project(Project LANGUAGES C)  # Agregar CXX para codigo C++

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Configuracion de salida de binarios
set(BIN "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}")

# Definiciones de compilacion
add_compile_definitions(ASSETS="${CMAKE_SOURCE_DIR}/assets")

# Configuracion para RayLib
message(STATUS "Descargando RayLib...")
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"  # Usar version especifica para mayor estabilidad
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)


# Configurar opciones de RayLib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_TOOLS OFF CACHE BOOL "" FORCE)    

FetchContent_MakeAvailable(raylib)
message(STATUS "RayLib configurado correctamente")

# Configurar ejecutable
add_subdirectory(src)

# src/CMakeLists.txt, asegurate de vincular raylib
# Ejemplo si tu target se llama "myapp"
target_link_libraries(Project PRIVATE raylib)