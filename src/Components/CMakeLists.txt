project(TEMPEST)

#todos los archivos agregados
file(GLOB_RECURSE gl_c RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

target_sources(TEMPEST PRIVATE ${gl_c})

