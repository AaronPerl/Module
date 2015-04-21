#version 150
in vec4 gxl3d_Position;
in vec4 gxl3d_Normal;

out Vertex
{
  vec4 normal;
  vec4 color;
} vertex;

void main()
{
  gl_Position = gxl3d_Position;
  vertex.normal = gxl3d_Normal;
  vertex.color =  vec4(1.0, 1.0, 0.0, 1.0);
}