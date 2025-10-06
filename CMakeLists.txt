cmake_minimum_required(VERSION 3.25)
project(Project VERSION 1.0.0 LANGUAGES C CXX)

# --- 1. Opciones globales ---
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wconversion)
endif()
add_compile_definitions(ASSETS="${CMAKE_SOURCE_DIR}/assets")

# --- 2. Traer dependencias externas (RayLib) ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
set(BUILD_TOOLS    OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# --- Silenciar todos los warnings de Raylib ---
# Detecta el compilador y aplica las flags correctas solo a la librería raylib

if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(raylib PRIVATE -w)
elseif (MSVC)
    target_compile_options(raylib PRIVATE /W0)
endif()

# --- 3. Añadir ejecutable desde src/ ---
add_subdirectory(src)  # Aquí se define el target "Project"

# --- 4. Configuración del target existente ---
target_compile_definitions(Project PRIVATE $<$<CONFIG:Debug>:DEBUG>)
set_target_properties(Project PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/$<CONFIG>"
)
target_link_libraries(Project PRIVATE raylib)
