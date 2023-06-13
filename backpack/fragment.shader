#version 330 core

out vec4 FragColor;

in vec2 tex_coords;
in vec3 normal;
in vec3 frag_pos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_height1;

void main() {
  //frag_color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  FragColor = texture(texture_diffuse1, tex_coords);
};
