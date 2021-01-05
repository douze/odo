#version 460

layout(location = 0) in vec2 position;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

layout(location = 3) uniform int grid_size;
layout(location = 4) uniform float patch_scale;
layout(location = 5) uniform float patch_size;

out VS_OUT {
  vec2 uv;
} vs_out;

/**
 * @return the offset of the current patch, in order to represent a grid
 * @note first offset is (0, 0), last offset is (grid_size - 1, grid_size - 1)
 */
vec2 get_patch_offset() {
  int x = gl_InstanceID % grid_size;
  int y = gl_InstanceID / grid_size;
  return vec2(x, y);
}

void main() {
  vec2 patch_offset = position + (get_patch_offset() * patch_size);
  vec2 patch_position = patch_offset * patch_scale;

  gl_Position = model * vec4(patch_position, 0.0, 1.0);
  vs_out.uv = patch_offset / (grid_size * patch_size);
}
