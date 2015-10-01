#version 150
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

uniform vec2 screen_size;

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 vertex_color;

out vec4 varyingColor;
out vec4 varyingPosition;

void main()
{
    gl_Position = vec4(position.xy/screen_size,0,0);
    varyingPosition = vec4(position,0,0);
    varyingColor = vertex_color;
}