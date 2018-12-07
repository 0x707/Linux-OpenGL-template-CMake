#version 330 core
out vec4 FragColor;

in vec3 Pos;
uniform float u_time;

void main()
{
    float x = 800.0f/ Pos.x;
    float y = 600.0f/ Pos.y;    
    float tv = abs(sin(u_time));

    FragColor = vec4(tv, y, 0.0f, 1.0f);
    //FragColor = vec4(1.0, y, 0.0f, 1.0f); // Wroclaw's flag
}