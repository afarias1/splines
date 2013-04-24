#version 130

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform mat4 modelView;
uniform float global_time;
uniform vec3 gravity = vec3(0,-1.2,0);

uniform vec4 lightPos;

in vec3 velocity;
in float startTime;


out vec3 N;
out vec3 L;
out vec3 E;


void main() 
{

    N = normalMatrix*vec3(0,0,1);
       vec4 vPosition = vec4(velocity,1);
    L = (camera*lightPos).xyz-(modelView*vPosition).xyz;
    E = -(modelView*vPosition).xyz; //from pt to viewer

    texCoord = vTexture;

    gl_Position = projection*modelView*vPosition;
} 
