#version 460

struct TerrainSubMaterial {
  float height;
  float primary_uv;
  float secondary_uv;
  float edge0;
  float edge1;
};

layout(location = 0) uniform bool wireframe;
layout(location = 1) uniform float mix_area_width;
layout(location = 2) uniform int display_type;

layout(location = 3) uniform vec3 light_position;

layout(location = 6) uniform TerrainSubMaterial snow_material;
layout(location = 11) uniform TerrainSubMaterial ground_material;
layout(location = 16) uniform TerrainSubMaterial grass_material;

layout(binding = 0) uniform sampler2D heightmap;
layout(binding = 1) uniform sampler2D grass_texture;
layout(binding = 2) uniform sampler2D ground_texture;
layout(binding = 3) uniform sampler2D rock_texture;
layout(binding = 4) uniform sampler2D snow_texture;
layout(binding = 5) uniform sampler2D sand_texture;

in GS_OUT {
  vec2 uv;
  vec3 position;
  vec3 wireframe_weight;
} fs_in;

out vec4 color;

const float wireframe_width = 1.0;
float half_mix_area_width = mix_area_width * 0.5;
const vec3 light_color = vec3(1.0);

/**
 * @return the edge factor used for wireframe rendering
 */
float get_wireframe_edge_factor() {
  vec3 d = fwidth(fs_in.wireframe_weight);
  vec3 a3 = smoothstep(vec3(0.0), d * wireframe_width, fs_in.wireframe_weight);
  return min(min(a3.x, a3.y), a3.z);
}

/**
 * @param current_height of the terrain
 * @param reference_height of the material
 * @return the weight used by the mix function to blend two materials
 */
float get_mix_weight(float current_height, float reference_height) {
  // The mix area goes from (reference_height - half_mix_area_width) to (reference_height + half_mix_area_width).
  // So the starting point for our mix weight is (current_height - (reference_height - half_mix_area_width)).
  // We then devide by total width in order to match [0,1] range, relative to current_height.
  return (current_height - (reference_height - half_mix_area_width)) / (mix_area_width);
}


/**
 * @return the height color
 */
vec4 get_height_color() {
  float height = texture(heightmap, fs_in.uv).r;
  return vec4(height, height, height, 1.0);
}

/**
 * @return the normal color (from the texture)
 */
vec3 get_normal_texture_color() {
  vec3 normal = texture(heightmap, fs_in.uv).gba;
  // was  stored in [0, 1] range => remap to [-1, 1] range
  normal = (normal - 0.5) * 2.0;
  return normal;
}

/**
 * @retur the base color (material) of the terrain
 */
vec3 get_base_color() {
  float height = get_height_color().r;

  vec3 grass = texture(grass_texture, fs_in.uv * grass_material.primary_uv).rgb;
  vec3 ground = texture(ground_texture, fs_in.uv * ground_material.primary_uv).rgb;
  vec3 rock = texture(rock_texture, fs_in.uv * snow_material.secondary_uv).rgb;
  vec3 snow = texture(snow_texture, fs_in.uv * snow_material.primary_uv).rgb;
  vec3 sand = texture(sand_texture, fs_in.uv * grass_material.secondary_uv).rgb;

  vec3 vertical = vec3(0, 0, 1);
  vec3 normal = get_normal_texture_color();
  float angle = abs(dot(normalize(normal), vertical));
  // dot: 0->perp, 1->para

  float coef = 1.0 - smoothstep(snow_material.edge0, snow_material.edge1, angle);
  snow = mix(snow, rock, coef);

  //coef = 1.0 - smoothstep(edge0_rock_ground, edge1_rock_ground, angle);
  //ground = mix(ground, rock, coef);

  coef = 1.0 - smoothstep(grass_material.edge0, grass_material.edge1, angle);
  grass = mix(sand, grass, coef);

  vec3 snow_ground = mix(ground, snow, get_mix_weight(height, snow_material.height));
  vec3 ground_grass = mix(grass, ground, get_mix_weight(height, ground_material.height));

  if (height > snow_material.height + half_mix_area_width) return snow;
  else if (height > snow_material.height - half_mix_area_width) return snow_ground;
  else if (height > ground_material.height + half_mix_area_width) return ground;
  else if (height > ground_material.height - half_mix_area_width) return ground_grass;
  else return grass;
}


/**
 * @return the ambien ligth
 */
vec3 get_ambient_light() {
  float ambient_strength = 0.1;
  return ambient_strength * light_color;
}

/**
 * @return the diffuse light
 */
vec3 get_diffuse_light(vec3 normal, float height) {
  vec3 fragment_position = vec3(fs_in.uv, height);
  //vec3 fragment_position = vec3(fs_in.position.xy, height);
  vec3 light_direction = normalize(light_position - fragment_position);
  float coeff_diffuse = max(dot(normal, light_direction), 0.0);
  return coeff_diffuse * light_color;
}

void main() {
  vec3 base_color = get_base_color();

  if (display_type == 0) color = get_height_color();
  else if (display_type == 1) color = vec4(get_normal_texture_color(), 1.0);
  else {
    float height = get_height_color().x;
    vec3 normal;
    if (display_type == 2) normal = get_normal_texture_color();
    normal = normalize(normal);
    color = vec4((get_ambient_light() + get_diffuse_light(normal, height)) * base_color, 1.0);
    //color = vec4(get_diffuse_light(normal, height), 1.0);
    color = vec4(base_color, 1.0);
  }

  if (wireframe) color = vec4(mix(vec3(1.0), color.rgb, get_wireframe_edge_factor()), color.a);

}
