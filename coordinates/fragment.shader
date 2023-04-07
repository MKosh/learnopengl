#version 330 core
out vec4 frag_color;

in vec2 TexCoord;

uniform sampler2D u_texture;

void main() {
  frag_color = texture(u_texture, TexCoord);
};
