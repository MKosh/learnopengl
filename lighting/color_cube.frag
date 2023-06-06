#version 330 core

struct Material {
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform Light light;
uniform Material material;

in vec3 normal;
in vec3 frag_pos;

out vec4 frag_color;

// uniform vec3 object_color;
// uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() {
  // ambient

  // diffuse
  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_pos - frag_pos);
  float diff = max(dot(norm, light_dir), 0.0);

  // specular
  vec3 view_dir = normalize(view_pos - frag_pos);
  vec3 reflect_dir = reflect(-light_dir, norm);
  float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
  
  vec3 ambient = light.ambient * material.ambient;
  vec3 diffuse = light.diffuse * (diff * material.diffuse);
  vec3 specular = light.specular * (spec * material.specular);

  vec3 result = (ambient + diffuse + specular);
  
  gl_FragColor = vec4(result, 1.0f);
};
