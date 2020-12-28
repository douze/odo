#version 460

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

layout (location = 3) uniform int grid_size;
layout (location = 4) uniform float scale_xy;

out VS_OUT {
  vec2 uv;
  vec3 color;
  vec2 position;
} vs_out;

vec2 get_grid_xy_coordinates() {
  int x = gl_InstanceID % grid_size;
  int y = gl_InstanceID / grid_size;
  return vec2(x, y);
}

void main() {
  vec2 grid_xy_coordinates = get_grid_xy_coordinates();
  vec2 grid_xy = position + grid_xy_coordinates;
  vec2 grid_xy_scaled = grid_xy * scale_xy;

  gl_Position = projection * view * model * vec4(grid_xy_scaled, 0.0, 1.0);
  vs_out.uv = grid_xy / grid_size;
  vs_out.color = color;
  vs_out.position = position;
}
