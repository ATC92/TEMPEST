cmake_minimum_required(VERSION 3.22)
project(Project LANGUAGES C CXX)  # Agregar soporte para C y C++

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

# Solo para GCC o Clang
if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error=float-conversion")
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

####################################################
##      cJSON
####################################################
FetchContent_Declare(
    cjson
    GIT_REPOSITORY "https://github.com/DaveGamble/cJSON"
    GIT_TAG "v1.7.18"
    GIT_SHALLOW TRUE
)
# Configuracion para cJson
message(STATUS "Descargando cJson...")
set(CJSON_INSTALL FALSE CACHE INTERNAL "" FORCE)
set(ENABLE_CJSON_TEST FALSE CACHE INTERNAL "" FORCE)
set(ENABLE_CJSON_UNINSTALL FALSE CACHE INTERNAL "" FORCE)
set(ENABLE_CJSON_BUILD_TOOLS FALSE CACHE INTERNAL "" FORCE)
set(ENABLE_CJSON_BUILD_SHARED_AND_STATIC FALSE CACHE INTERNAL "" FORCE)

FetchContent_MakeAvailable(cjson)
if (TARGET cjson)
    set_target_properties(cjson PROPERTIES EXCLUDE_FROM_ALL TRUE EXCLUDE_FROM_DEFAULT_BUILD TRUE)
endif()


message(STATUS "RayLib y cJson configurados correctamente.")

# -----------------------------------------------
# Configurar ejecutable y enlazar librerias
# -----------------------------------------------
add_subdirectory(src)

target_link_libraries(Project PRIVATE raylib cjson)
target_include_directories(Project PRIVATE ${cjson_SOURCE_DIR})

# -----------------------------------------------
# Configuracion de instalacion
# -----------------------------------------------
install(TARGETS Project 
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Install cJSON header file
install(FILES "${cjson_SOURCE_DIR}/cJSON.h" DESTINATION include/cjson)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets" DESTINATION bin)
install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION bin)

# -----------------------------------------------
# Configuracion de empaquetado con CPack (Solo en Release)
# -----------------------------------------------
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configurando compilacion en Release: Desactivando warnings")
    # GCC y Clang
    if (CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -w")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -w")
    endif()
    # MSVC (Visual Studio)
    if (MSVC)
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /w")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /w")
    endif()


    ## CPACK
    include(CPack)
    
    set(CPACK_GENERATOR "ZIP") 
    set(CPACK_PACKAGE_NAME "CGame")
    set(CPACK_PACKAGE_VERSION "0.0.1")
    set(CPACK_PACKAGE_DESCRIPTION "Game development with RayLib")
    set(CPACK_PACKAGE_VENDOR "ATC")
    set(CPACK_PACKAGE_CONTACT "a2201636@uabc.edu.mx")
    set(CPACK_PACKAGE_DIRECTORY "${CMAKE_BINARY_DIR}/release")
    set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)

    # Generar paquete ZIP con todos los archivos necesarios
    install(TARGETS Project DESTINATION bin)
    install(DIRECTORY "${CMAKE_SOURCE_DIR}/assets" DESTINATION bin/assets)
    install(FILES "${CMAKE_SOURCE_DIR}/README.md" DESTINATION bin)

    # Generar el paquete
    cpack_add_component(Project DISPLAY_NAME "Juego Completo")
endif()
