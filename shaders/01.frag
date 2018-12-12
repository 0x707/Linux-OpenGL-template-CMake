#version 330 core
out vec4 FragColor;

in vec3 Pos;
in vec3 Col;
uniform float u_time;

void main()
{
    float x = 1.0f/ Pos.x;
    float y = 1.0f/ Pos.y;
    float x1 = gl_FragCoord.x / 800.f;
    float y1 = gl_FragCoord.y / 600.f;
    float tv = (sin(u_time * 1.3f));
    float tv1 = (cos(u_time * 1.3f));

    FragColor = vec4(Col.rgb, 1.0f);
    //FragColor = vec4(1.0, y, 0.0f, 1.0f); // Wroclaw's flag
}