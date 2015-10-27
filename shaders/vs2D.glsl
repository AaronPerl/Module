#version 150
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

uniform ivec2 screen_size;

layout (location = 0) in vec3 position;
//layout (location = 1) in vec4 vertex_color;

out vec4 varyingColor;

void main()
{
	vec2 scaledPosition = 2 * (vec2(position.x, 0) - vec2(0,position.y))/screen_size;
    gl_Position = vec4(position.x, -position.y, 0, 0);//vec4(scaledPosition - vec2(1,1),0,0);
    varyingColor = vec4(1,0,0,1);
}