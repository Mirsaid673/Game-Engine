#version 330 core

out vec4 out_color;

in vec3 color;
in vec2 o_tex_coord;

uniform sampler2D tex;

void main() 
{ 
    out_color = mix(vec4(color, 1),texture(tex, o_tex_coord), 0.5); 
}