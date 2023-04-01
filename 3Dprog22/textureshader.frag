#version 410 core

in vec2 UV; //color received from the pipeline (and vertex shader)

out vec4 fragmentColor; //color sent to fragment on screen
uniform sampler2D textureSampler;

void main()
{
   fragmentColor = texture(textureSampler, UV);
}
