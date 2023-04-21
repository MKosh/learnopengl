#version 330 core

out vec4 frag_color;
in vec2 TexCoord;
uniform sampler2D u_texture;
//uniform vec4 u_color;
void main() {
  //frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  frag_color = texture(u_texture, TexCoord);
};
