#version 130

in vec4 vPosition;
uniform float time;

void
main()
{
    vec4 displacement = vec4(0.0);
    displacement.y = 0.5*sin(time);
    gl_Position =  vPosition + displacement;
}
