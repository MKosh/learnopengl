#version 330 core

out vec4 frag_color;
//uniform vec4 u_color;
in vec3 our_color;
in vec2 texCoord;
uniform sampler2D tex0;
void main() {
  //frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  frag_color = texture(tex0, texCoord);
};
