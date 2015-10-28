#version 150
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

uniform ivec2 screen_size;

layout (location = 0) in vec4 position;
//layout (location = 1) in vec4 vertex_color;

out vec4 varyingColor;

void main()
{
	vec2 scaledPosition = 2 * (position.xy/(vec2(800,600))) - vec2(1,1);
    gl_Position = vec4(scaledPosition*vec2(1,-1),0,1);
    varyingColor = vec4(1,1,1,1);
}