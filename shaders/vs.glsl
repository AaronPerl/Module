#version 150
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_explicit_attrib_location : enable

uniform mat4       view_matrix;
uniform mat4 projection_matrix;
uniform mat4      model_matrix;
uniform mat4        mvp_matrix;
uniform mat4	   norm_matrix;
uniform vec4	  eye_position;
uniform vec4		eye_normal;

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 normal;

out vec4 varyingPosition;
out vec4 varyingNormal;

mat4 rotationMatrix(vec3 axis, float angle)
{
	axis = normalize(axis);
	float s = sin(angle);
	float c = cos(angle);
	float oc = 1.0 - c;
	return mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
	oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,
	oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,
	0.0, 0.0, 0.0, 1.0);
}

void main()
{
	vec4 tempPos = mvp_matrix * position;
    //gl_Position = tempPos*rotationMatrix(vec3(0,0,1),0.7*sqrt(tempPos.x*tempPos.x+tempPos.y*tempPos.y)); //twist
    //gl_Position = tempPos + .5*vec4(0,cos(tempPos.x*3),0,0); //dali
    gl_Position = tempPos;
    varyingPosition = model_matrix * position;
    varyingNormal = normalize(norm_matrix*normal);
}