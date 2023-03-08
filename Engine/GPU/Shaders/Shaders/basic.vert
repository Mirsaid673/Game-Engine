#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 5) in vec3 a_color;
layout (location = 9) in vec2 a_tex_coord;

out vec3 color;
out vec2 o_tex_coord;

uniform mat4 PVM;

void main()
{
    gl_Position = PVM * vec4(a_pos, 1);
    color = a_color;
    o_tex_coord = a_tex_coord;
}