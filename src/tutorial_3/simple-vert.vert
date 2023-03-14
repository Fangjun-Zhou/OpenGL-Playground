#version 330 core

layout(location = 0) in vec3 v_in_pos;
layout(location = 1) in vec4 v_in_color;

uniform mat4 u_mvp;

out vec4 v_out_color;

void main() {
    v_out_color = v_in_color;

    gl_Position = u_mvp * vec4(v_in_pos, 1);
}