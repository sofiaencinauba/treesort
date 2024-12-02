cmake_minimum_required(VERSION 3.22)
project(AYED_TPG_2C2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

# Configuracion para correcto camino hacia los archivos de informacion a usar en el programa
set(FILES_DIRECTORY "${CMAKE_SOURCE_DIR}/files")
add_compile_definitions(FILES_DIRECTORY="${FILES_DIRECTORY}")

add_compile_options(-Wall -Werror -Wconversion)

include_directories(include)

# Tienen que agregar acá todos los archivos que necesiten compilar, con el siguiente formato:
#   directorio/archivo1.cpp
#   directorio/archivo2.cpp
#   ...
set(ARCHIVOS_FUENTE
        include/Vector.hpp
        include/Diccionario.hpp
        include/NodoDiccionario.hpp
        
)

add_executable(AYED_TPG_2C2024
        ${ARCHIVOS_FUENTE}
        main.cpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")
