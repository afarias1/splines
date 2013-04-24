<<<<<<< HEAD
#version 130

=======
#version 150

uniform sampler2D Tex0;
in vec3 E;
in vec2 texCoord;
in float transparency;

out vec4 fragColor;


void main() 
{
    vec4 baseColor=vColor;
    baseColor = vColor*texture(Tex0,gl_PointCoord);
    //baseColor = vec4(baseC./o,baseColor.w);
    if(baseColor.a<0.5){
        discard;
    }
	
		//baseColor = vec4(transparency, transparency, transparency, 1);
	  //baseColor.a *= transparency;

    vec4 ambient, diffuse, specular;

    vec3 NN = normalize(N);
    vec3 EE = normalize(E);
    vec3 LL = normalize(L);
    vec3 H  = normalize(LL+EE);

    float Kd = max(dot(LL,NN),0.0);
    float Ks = pow(max(dot(NN,H),0.0),80);

    ambient = baseColor*0.5;
    diffuse = baseColor*Kd*0.5;
    specular = vec4(0,0,0,1);
    if(dot(LL,NN) > 0){ specular = vSColor*Ks*0.3; }

    fragColor = vec4((ambient+diffuse).xyz,transparency);
} 

