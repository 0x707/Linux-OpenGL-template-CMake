#version 330 core
out vec4 FragColor;

in vec3 Pos;
in vec3 Col;
in vec2 Tex;
uniform float u_time;
uniform sampler2D theTex;
uniform sampler2D theKej;
uniform sampler2D pikachu;

void main()
{
    float x = 1.0f/ Pos.x;
    float y = 1.0f/ Pos.y;
    float x1 = gl_FragCoord.x / 800.f;
    float y1 = gl_FragCoord.y / 600.f;
    float tv = (sin(u_time * 3.3f));
    float tv1 = (cos(u_time * 13.3f));

    FragColor = texture(pikachu, Tex);
    //FragColor = texture(pikachu, Tex) * vec4(Col.r * tv1 + 0.24f, Col.g * tv, Col.b * (tv * tv1), 1.0f); // pikameme
    //FragColor = texture(theKej, Tex); // simple Kej
    //FragColor = texture(theKej, vec2(1.0f - Tex.x * 8, Tex.y * 8)) * vec4(Col.r * tv, Col.g * tv1, Col.b, 1.0f); // a lot of disco Kejs
    //FragColor = mix(texture(theTex, Tex), texture(theKej, Tex), 0.65) * vec4(Col.r * tv1, Col.g * tv, Col.b * x1,1.0f); // disco Kej
    //FragColor = texture(theTex, vec2(1.0f - Tex.x, Tex.y)) * vec4(Col.r * tv1, Col.g * tv, Col.b * x1,1.0f); // RCHS disco
    //FragColor = texture(theTex, vec2(1.0f - Tex.x, Tex.y)); // RCHS
    //FragColor = vec4(Col.r, 0.0f, 0.0f, 1.0f);
    //FragColor = vec4(1.0, y, 0.0f, 1.0f); // Wroclaw's flag
}