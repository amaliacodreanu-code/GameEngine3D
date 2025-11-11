#include"Mesh.h"

Mesh:: Mesh(std::vector<Vertex>& vertices,
           std::vector<GLuint>& indices, 
           std::vector<Texture> &textures)
{

    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;


    //Copy paste than initialization of VAO from main.cpp and modify the variable


     VAO.Bind();

    // Create the Vertex Buffer Object (VBO) and link vertex data
    VBO VBO(vertices);
    EBO EBO(indices);

    // Link VBO attributes (layout 0: positions, layout 1: colors) to VAO
    // This function now belongs to the VAO class
    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT,sizeof(Vertex), (void*)0); 
    VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT,sizeof(Vertex), (void*)(3 * sizeof(float)));
    VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT,sizeof(Vertex), (void*)(6 * sizeof(float))); 


    // Unbind all objects to prevent accidental modification
    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind(); 

}

void Mesh::Draw(Shader& shader, Camera& camera) 
{
    shader.Activate();
    VAO.Bind();

    unsigned int diffuse = 0;
   
   
    for(unsigned int i = 0; i < textures.size(); i++) 
    {
        std::string num = std::to_string(i);
        std::string name = "diffuse" + num;
        
        //send texture to shader
        textures[i].texUnit(shader, name.c_str(), i);
        textures[i].Bind();

    } 

   glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
   camera.Matrix(shader, "camMatrix");
	

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
} 
