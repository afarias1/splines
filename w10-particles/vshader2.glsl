#version 130

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform mat4 modelView;

uniform vec4 lightPos;

uniform float global_time;
uniform vec3 gravity = vec3(0,-1.2,0);


in vec3 velocity;
in float startTime;

out vec3 N;
out vec3 L;
out vec3 E;

void main() 
{
    N = normalMatrix*vec3(0,0,1);
    vec4 vPosition = vec4(0,0,0,1);

    float t;
    vec3 pos3;
    if(global_time > startTime){
        t = mod(global_time - startTime,2);
        pos3 = velocity*t + 0.5*gravity*t*t;
        vPosition=vec4(pos3,1);
    }

    L = (camera*lightPos).xyz-(modelView*vPosition).xyz;
    E = -(modelView*vPosition).xyz; //from pt to viewer

    gl_Position = projection*modelView*vPosition;
} 
