#version 460

layout(quads, equal_spacing, ccw) in;

layout(location = 0) uniform float height_factor;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;
layout(binding = 0) uniform sampler2D heightmap;

in TCS_OUT {
  vec2 uv;
} tes_in[];

out TES_OUT {
  vec2 uv;
} tes_out;

vec2 interpolate2(vec2 v0, vec2 v1, vec2 v2, vec2 v3) {
  vec2 a = mix(v0, v1, gl_TessCoord.x);
  vec2 b = mix(v3, v2, gl_TessCoord.x);
  return mix(a, b, gl_TessCoord.y);
}

vec4 interpolate4(vec4 v0, vec4 v1, vec4 v2, vec4 v3) {
  vec4 a = mix(v0, v1, gl_TessCoord.x);
  vec4 b = mix(v3, v2, gl_TessCoord.x);
  return mix(a, b, gl_TessCoord.y);
}

void main() {
  gl_Position = interpolate4(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
  gl_Position = projection * view * gl_Position;

  tes_out.uv = interpolate2(tes_in[0].uv, tes_in[1].uv,tes_in[2].uv, tes_in[3].uv);

  float heigth = texture(heightmap, tes_out.uv).x;
  gl_Position.y += heigth * height_factor;
}
