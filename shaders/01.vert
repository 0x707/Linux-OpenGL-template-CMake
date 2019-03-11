#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aCol;

out vec3 Pos;
out vec3 Col;
out vec2 Tex;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    // multiplication order matters while using view, why?
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
    Pos = aPos;
    Col = aCol;
    Tex = aTex;
    //Tex = vec2(aTex.x, 1.0f - aTex.y);
}