<<<<<<< HEAD
#version 130
=======
#version 150

uniform mat4 model;
uniform mat4 camera;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform mat4 modelView;

out float transparency;

void main() 
{
    vec3 vNormal=vec3(0,0,1);
    N = normalMatrix*vNormal;
    L = (camera*lightPos).xyz-(modelView*vPosition).xyz;
    E = -(modelView*vPosition).xyz; //from pt to viewer

    vec3 vel = vPosition.xyz;
    vec3 pos=vec3(0,0,0);
    float t;
    if(global_time > startTime){
        t = mod(global_time - startTime,lifetime);
        pos = vel*t + 0.5*gravity*t*t;
				transparency = 1.0-t/(lifetime*lifetime);
    }
    gl_Position = projection*modelView*vec4(pos,1);

>>>>>>> dc6646583026f7f3b7449122db9cbd2be58b4c4c
} 
