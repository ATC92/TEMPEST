project(Project)

#todos los archivos agregados
file(GLOB_RECURSE gl_cpp RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(Project PRIVATE ${gl_cpp})

