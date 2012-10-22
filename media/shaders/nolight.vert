varying vec4 light;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

void main()
{
    light = gl_Color;
    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = projectionMatrix * modelViewMatrix * gl_Vertex;
}

