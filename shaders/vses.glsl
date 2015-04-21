attribute vec4 position;

uniform mat4       view_matrix;
uniform mat4 projection_matrix;
uniform mat4      model_matrix;
uniform mat4        mvp_matrix;

void main()
{
    gl_Position = mvp_matrix * position;
}