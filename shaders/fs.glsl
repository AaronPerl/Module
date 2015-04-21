#version 150

uniform mat4       view_matrix;
uniform mat4 projection_matrix;
uniform mat4      model_matrix;
uniform mat4        mvp_matrix;
uniform mat4	   norm_matrix;
uniform vec4	  eye_position;
uniform vec4		eye_normal;

in vec4 varyingPosition;
in vec4 varyingNormal;

out vec4 gl_FragColor;

struct lightSource
{
  vec3 position;
  vec3 diffuse;
  vec3 specular;
};

lightSource light0 = lightSource(
  vec3(0.0,  3.0,  2.0),
  vec3(1.0,  1.0,  1.0),
  vec3(1.0,  1.0,  1.0)
);

vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);
 
struct material
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

material frontMaterial = material(
  vec4(0.3, 0.2, 0.2, 1.0),
  vec4(1.0, 0.0, 0.0, 1.0),
  vec4(1.0, 1.0, 1.0, 1.0),
  64.0
);
 
void main()
{
	//if (fract(sin(dot(varyingPosition.xy ,vec2(12.9898,78.233))) * 43758.5453)>0.8)
		//discard;
	vec3 lightVector = normalize(light0.position.xyz - varyingPosition.xyz);
	float diffFactor = dot(varyingNormal.xyz, lightVector);
	diffFactor = clamp(diffFactor, 0, 1);
	vec3 reflectedLight = normalize(reflect(lightVector, varyingNormal.xyz));
	vec3 eyeDirection = normalize(eye_position.xyz-varyingPosition.xyz);
	float specFactor = dot(reflectedLight, eyeDirection);
	specFactor = pow(clamp(specFactor, 0, 1), frontMaterial.shininess);
	gl_FragColor = 	scene_ambient * frontMaterial.ambient +
					diffFactor * frontMaterial.diffuse 	* vec4(light0.diffuse,1) + 
					specFactor * frontMaterial.specular * vec4(light0.specular,1);
}