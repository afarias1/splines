#version 130

uniform sampler2D Tex0;

in vec4 color;
in vec2 texCoord;

out vec4 fragColor;


void main() 
{ 
    fragColor = texture(Tex0,texCoord);
    //fragColor = vec4(texCoord.x,texCoord.y,0,1.);
    //fragColor = color;
} 

