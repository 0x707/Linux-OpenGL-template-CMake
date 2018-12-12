#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 Pos;
out vec3 Col;

void main()
{
    gl_Position = vec4(aPos.xyz, 1.0);
    Pos = aPos;
    Col = aCol;
}