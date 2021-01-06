#version 460

layout(location = 0) uniform bool wireframe;
layout(binding = 0) uniform sampler2D heightmap;

in GS_OUT {
  vec2 uv;
  vec3 wireframe_weight;
} fs_in;

out vec4 color;

const float wireframe_width = 1.0;

float get_edge_factor() {
  vec3 d = fwidth(fs_in.wireframe_weight);
  vec3 a3 = smoothstep(vec3(0.0), d * wireframe_width, fs_in.wireframe_weight);
  return min(min(a3.x, a3.y), a3.z);
}

void main() {
  color = texture(heightmap, fs_in.uv);
  if (wireframe) color = vec4(mix(vec3(1.0), color.rgb, get_edge_factor()), color.a);
}
