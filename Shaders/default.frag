#version 330 core

//Outputs colors in RGBA
out vec4 FragColor;

// Inputs the color from the Vertex Shader

in vec3 color;
in vec2 TexCoord;

uniform sampler2D tex0;

//uniform sampler2D texture1;
//uniform sampler2D texture2;

uniform sampler2D diffuse0;
//uniform sampler2D specular0;

uniform vec3 camPos;


void main()
{
//FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);
//FragColor = vec4(color, 1.0f);

//FragColor = texture(tex0, TexCoord);
//FragColor = texture(tex0, TexCoord) * vec4(color, 1.0);  

FragColor = texture(diffuse0, TexCoord);

}