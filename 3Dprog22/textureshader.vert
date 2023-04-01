#version 410 core

layout(location = 0) in vec4 positionIn; // 1st attribute buffer = vertex positions
layout(location = 1) in vec3 colorIn; // 2nd attribute buffer = colors
layout(location = 2) in vec2 textureUV; // 3rd attribute buffer = uvs


out vec2 UV; //UV's sent to rest of pipeline
uniform mat4 pmatrix; // nye matriser 28/1 - Camera
uniform mat4 vmatrix; // nye matriser 28/1 - Camera
uniform mat4 matrix;  //the matrix for the model


void main() {
  UV = textureUV;
  gl_Position = pmatrix * vmatrix * matrix * positionIn;
}
