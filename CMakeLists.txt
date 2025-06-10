cmake_minimum_required(VERSION 3.22)
project(Project LANGUAGES C CXX)  # Agregar soporte para C y C++

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Solo para GCC o Clang
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=float-conversion -Wall")
endif()

# Configurar segun el tipo de compilacion
set(BIN "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BIN}/${CMAKE_BUILD_TYPE}")
#${CMAKE_BINARY_DIR}/bin/$<CONFIG>

# Definiciones de compilacion
add_compile_definitions(ASSETS="${CMAKE_SOURCE_DIR}/assets")

# -----------------------------------------------
# Configuracion de dependencias externas (RayLib y cJson)
# -----------------------------------------------
include(FetchContent)
####################################################
##      RayLib
####################################################
FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
    GIT_SHALLOW TRUE
)
# Configuracion para RayLib
message(STATUS "Descargando RayLib...")
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_TOOLS OFF CACHE BOOL "" FORCE)   
FetchContent_MakeAvailable(raylib)

message(STATUS "Librerias onfiguradas correctamente.")

# -----------------------------------------------
# Configurar ejecutable y enlazar librerias
# -----------------------------------------------
add_subdirectory(src)

target_link_libraries(Project PRIVATE raylib)
# -----------------------------------------------
# Configuracion de instalacion
# -----------------------------------------------
install(TARGETS Project 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets" DESTINATION .)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION .)