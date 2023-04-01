#version 410 core

in vec4 color;              //color received from the pipeline (and vertex shader)
out vec4 fragmentColor;     //color sent to fragment on screen

uniform float ambientStrength = 0.8f;
uniform vec4 ambientColor = vec4(1, 0, 0, 0);

void main()
{
    fragmentColor = color;

    //fragmentColor = color * ambientStrength * ambientColor;   //color given to current fragment (pixel)
}
