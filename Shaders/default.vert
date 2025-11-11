#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexture;

out vec3 color;
out vec2 TexCoord; 
//import the camera matrix from the main function
uniform mat4 camMatrix;


void main()
{
 	
	//gl_Position = vec4(aPos,1.0);
    //gl_Position = proj * view *model * vec4(aPos,1.0);

	gl_Position = camMatrix * vec4(aPos, 1.0f); 

	// Assigns the colors from the Vertex Data to "color"
	
	color = aColor;
	TexCoord = aTexture; 
}
