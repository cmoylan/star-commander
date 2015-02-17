#version 150 core
 
in vec2 texcoord;
out vec4 outColor;
uniform sampler2D tex;
uniform vec4 color;
 
void main() {
  outColor = vec4(1, 1, 1, texture(tex, texcoord).r) * color;
}