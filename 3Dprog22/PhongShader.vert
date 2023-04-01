#version 410 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec4 color;
out vec2 uv;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

vec3 ambient;
vec3 diffuse;
vec3 specular;
float shininess;

uniform vec3 Color;
uniform vec3 lightPosition;
uniform vec3 viewPos;

void main()
{
    gl_Position = pMatrix * vMatrix * mMatrix * vec4(vertexPosition, 1.0);

    vec3 lightColor = vec3(1.0, 1.0, 1.0);

    //Material
    ambient = vec3(0.02, 0.17, 0.02);
    diffuse = vec3(0.07, 0.6, 0.07);
    specular = vec3(0.6, 0.7, 0.6);
    shininess = 0.6;


    //-----


    // calculations
    vec3 fragPos = vec3(mMatrix * vec4(vertexPosition, 1.0));
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 lightDir = normalize(lightPosition - fragPos);
    vec3 norm = normalize(vertexNormal);


    //-----


    // ambient lighting
    vec3 mAmbient = ambient * lightColor;

    // Specular
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 mSpecular = specular * spec * lightColor;

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 mDiffuse = diff * lightColor * diffuse;


    //-----


    //Result
    vec3 result = (mAmbient + mDiffuse + mSpecular) * Color;
    color = vec4(result, 1.0);
}
