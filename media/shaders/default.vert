varying vec4 light;
varying vec3 normal, lightDir, eyeVec;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main()
{
    light = gl_Color;
    normal = normalMatrix * gl_Normal;

    vec3 vVertex = vec3(modelViewMatrix * gl_Vertex);
    lightDir = vec3(gl_LightSource[0].position.xyz - vVertex);
    eyeVec = -vVertex;

    gl_TexCoord[0] = gl_MultiTexCoord0;
    gl_Position = projectionMatrix * modelViewMatrix * gl_Vertex;
}

