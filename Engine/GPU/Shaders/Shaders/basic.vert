#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_normal;
layout (location = 9) in vec2 a_tex_coord;

out vec3 normal;
out vec2 tex_coord;
out vec3 frag_pos;
out vec3 view_pos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    gl_Position = proj * view * model * vec4(a_pos, 1);
    normal = mat3(transpose(inverse(model))) * a_normal;
    tex_coord = a_tex_coord;
    frag_pos = vec3(model * vec4(a_pos, 1));
    view_pos = -view[3].xyz;
}