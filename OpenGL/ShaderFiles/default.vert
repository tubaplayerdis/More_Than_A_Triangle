#version 460 core
//Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
//texture coords
layout (location = 2) in vec2 aTex;

//outputs color fo fragment shader
out vec3 color;

//outputs texture coordinates
out vec2 texCoord;

uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * vec4(aPos, 1.0);
   color = aColor;
   texCoord = aTex;
}