# 1. Versiunea minima si numele proiectului - OBLIGATORIU LA INCEPUT
cmake_minimum_required(VERSION 3.10)
project(Triangle)

# 2. Gasim pachetele de sistem (OpenGL)
find_package(OpenGL REQUIRED)

# 3. Definim directoarele "include" (unde sunt fisierele .h)
# Pentru bibliotecile locale (GLFW, GLAD)
include_directories(include) 
# Pentru Assimp (calea ta absoluta)
include_directories("C:/Users/Amalia/Desktop/assimp-master/include")

# 4. Definim directoarele "lib" (unde sunt fisierele .a / .lib)
# Pentru bibliotecile locale (libglfw3.a)
link_directories(lib)
# Pentru Assimp (calea ta absoluta)
link_directories("C:/Users/Amalia/Desktop/assimp-master/build_assimp/lib")

# 5. Cream executabilul
# Foarte bine ca ai inclus si src/glad.c aici!
add_executable(
    Triangle
    src/main.cpp
    src/glad.c
    src/ShaderClass.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/Texture.cpp
    src/Camera.cpp
    src/Mesh.cpp
)

target_include_directories(Triangle PUBLIC include)

# 6. Legam (link-uim) bibliotecile de executabil
target_link_libraries(
    Triangle
    PRIVATE
    assimp   # Spunem ca avem nevoie de biblioteca "assimp"
    opengl32
    glfw3    # Spunem ca avem nevoie de biblioteca "glfw3"
)