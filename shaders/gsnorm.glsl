#version 150
layout(triangles) in;

// Three lines will be generated: 6 vertices
layout(line_strip, max_vertices=6) out;

uniform mat4       view_matrix;
uniform mat4 projection_matrix;
uniform mat4      model_matrix;
uniform mat4        mvp_matrix;
uniform mat4	   norm_matrix;

in Vertex
{
  vec4 normal;
  vec4 color;
} vertex[];

out vec4 vertex_color;

void main()
{
  int i;
  for(i=0; i<gl_in.length(); i++)
  {
  	float normal_length = 0.7;
    vec3 P = gl_in[i].gl_Position.xyz;
    vec3 N = vertex[i].normal.xyz;
    
    gl_Position = mvp_matrix * vec4(P, 1.0);
    vertex_color = vertex[i].color;
    EmitVertex();
    
    gl_Position = mvp_matrix * vec4(P + N * normal_length, 1.0);
    vertex_color = vertex[i].color;
    EmitVertex();
    
    EndPrimitive();
  }
}