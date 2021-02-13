#version 460

layout(vertices = 4) out;

layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform vec3 camera_position;
layout(binding = 0) uniform sampler2D heightmap;

in VS_OUT {
  vec2 uv;
} tcs_in[];

out TCS_OUT {
  vec2 uv;
} tcs_out[];

float min_depth = 1.0;
float max_depth = 10.0;

/*
 * @param value to map & clamp
 * @param min_range of the new range
 * @param max_range of the new range
 * @return value mapped & clamped to the new range
 */
float map_range_clamped(float value, float min_range, float max_range) {
  return clamp((value - min_range) / (max_range - min_range), 0.0, 1.0);
}

/*
 * @param vertex0 of the edge
 * @param vertex1 of the edge
 * @return the tessellation level of the edge, using distance to the camera
 */
float get_tess_level(vec4 vertex0, vec2 uv0, vec4 vertex1, vec2 uv1) {
  vec4 vertex0_camera_space = view * vertex0;
  vertex0_camera_space.y = texture(heightmap, uv0).x;
  vec4 vertex1_camera_space = view * vertex1;
  vertex1_camera_space.y = texture(heightmap, uv1).x;

  float edge_distance = (length(vertex0_camera_space) + length(vertex1_camera_space)) * 0.5;
  float constrained_edge_distance = map_range_clamped(edge_distance, min_depth, max_depth);

  return mix(64, 2, constrained_edge_distance);
}

void main(void) {
  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

  gl_TessLevelOuter[0] = get_tess_level(gl_in[3].gl_Position, tcs_in[3].uv, gl_in[0].gl_Position, tcs_in[0].uv);
  gl_TessLevelOuter[1] = get_tess_level(gl_in[0].gl_Position, tcs_in[0].uv, gl_in[1].gl_Position, tcs_in[1].uv);
  gl_TessLevelOuter[2] = get_tess_level(gl_in[1].gl_Position, tcs_in[1].uv, gl_in[2].gl_Position, tcs_in[2].uv);
  gl_TessLevelOuter[3] = get_tess_level(gl_in[2].gl_Position, tcs_in[2].uv, gl_in[3].gl_Position, tcs_in[3].uv);

  gl_TessLevelInner[0] = (gl_TessLevelOuter[0] + gl_TessLevelOuter[3]) * 0.5;
  gl_TessLevelInner[1] = (gl_TessLevelOuter[1] + gl_TessLevelOuter[2]) * 0.5;

  tcs_out[gl_InvocationID].uv = tcs_in[gl_InvocationID].uv;

  // fixed tesselation level for debug
  for (int i = 0 ; i < 4 ; i++) gl_TessLevelOuter[i] = 64.0;
  for (int i = 0 ; i < 2 ; i++) gl_TessLevelInner[i] = 64.0;
}

