#version 330 core

in vec3 normal;
in vec3 frag_pos;

out vec4 frag_color;

uniform vec3 object_color;
uniform vec3 light_color;
uniform vec3 light_pos;

void main() {

  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_pos - frag_pos);

  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * light_color;

  float ambient_strength = 0.2;
  vec3 ambient = ambient_strength * light_color;
  vec3 result = (ambient + diffuse) * object_color;
  
  gl_FragColor = vec4(result, 1.0f);
};
