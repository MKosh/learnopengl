#version 330 core

out vec4 frag_color;

in vec2 tex_coords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;

void main() {
  //frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  frag_color = texture(texture_diffuse1, tex_coords);
};
