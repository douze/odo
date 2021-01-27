#version 460

layout(location = 0) uniform bool wireframe;
layout(location = 1) uniform float snow_height;
layout(location = 2) uniform float grass_height;
layout(location = 3) uniform float mix_area_width;
layout(binding = 0) uniform sampler2D heightmap;
layout(binding = 1) uniform sampler2D grass_texture;
layout(binding = 2) uniform sampler2D ground_texture;
layout(binding = 3) uniform sampler2D rock_texture;
layout(binding = 4) uniform sampler2D snow_texture;

in GS_OUT {
  vec2 uv;
  vec3 wireframe_weight;
} fs_in;

out vec4 color;

const float wireframe_width = 1.0;
float half_mix_area_width = mix_area_width * 0.5;

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
 * @retur the base color (material) of the terrain
 */
vec3 get_base_color() {
  float height = texture(heightmap, fs_in.uv).r;

  vec3 grass = texture(grass_texture, fs_in.uv * 50).rgb;
  vec3 ground = texture(ground_texture, fs_in.uv * 20).rgb;
  vec3 rock = texture(rock_texture, fs_in.uv * 10).rgb;
  vec3 snow = texture(snow_texture, fs_in.uv * 100).rgb;

  vec3 snow_grass = mix(grass, snow, get_mix_weight(height, snow_height));
  vec3 grass_ground = mix(ground, grass, get_mix_weight(height, grass_height));

  if (height > snow_height + half_mix_area_width) return snow;
  else if (height > snow_height - half_mix_area_width) return snow_grass;
  else if (height > grass_height + half_mix_area_width) return grass;
  else if (height > grass_height - half_mix_area_width) return grass_ground;
  else return ground;

}

void main() {
  vec3 base_color = get_base_color();
  color = vec4(base_color, 1.0);
  if (wireframe) color = vec4(mix(vec3(1.0), color.rgb, get_wireframe_edge_factor()), color.a);
}
