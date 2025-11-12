#define STB_IMAGE_IMPLEMENTATION
#include"Texture.h"
#include <stb/stb_image.h>

Texture::Texture(const char* image, const char* texType, GLenum slot, GLenum format, GLenum pixelType)
{
    //Stocheaz tipul texturi pt a putea folosi si in alte functi

    type =texType;
 
    //generez un ID pentru textura
    glGenTextures(1, &ID);

    //activez unitatea de textura GL_Texture0
    glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

    //Setare parametri de wrapping(cum se repeta textura)
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //set parametri de filtrare
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


     //load and generate the texture
    int widthImg, heightImg, nrChannels;

    unsigned char* data = stbi_load(
    image,
    &widthImg,
    &heightImg,
    &nrChannels, 0);

    if(data)
    {
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
       glGenerateMipmap(GL_TEXTURE_2D);
       stbi_image_free(data);
    }
    else{
        std::cout << "Textura nu a fost gasita la calea: " << image << std::endl;
        std::cin.get();
        exit(EXIT_FAILURE); 
    }
  

}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}