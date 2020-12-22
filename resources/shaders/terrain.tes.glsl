#version 460

layout(quads, equal_spacing, ccw) in;

in TC_OUT {
  vec2 uv;
  vec3 color;
} tes_in[];

out TE_OUT {
  vec2 uv;
  vec3 color;
} tes_out;

layout (location = 0) uniform float height_factor;
uniform sampler2D heightmap;

vec4 interpolate4(in vec4 v0, in vec4 v1, in vec4 v2, in vec4 v3) {
  vec4 a = mix(v0, v1, gl_TessCoord.x);
  vec4 b = mix(v3, v2, gl_TessCoord.x);
  return mix(a, b, gl_TessCoord.y);
}

vec3 interpolate3(in vec3 v0, in vec3 v1, in vec3 v2, in vec3 v3) {
  vec3 a = mix(v0, v1, gl_TessCoord.x);
  vec3 b = mix(v3, v2, gl_TessCoord.x);
  return mix(a, b, gl_TessCoord.y);
}

vec2 interpolate2(in vec2 v0, in vec2 v1, in vec2 v2, in vec2 v3) {
  vec2 a = mix(v0, v1, gl_TessCoord.x);
  vec2 b = mix(v3, v2, gl_TessCoord.x);
  return mix(a, b, gl_TessCoord.y);
}

void main() {
  gl_Position = interpolate4(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position, gl_in[3].gl_Position);
  tes_out.uv = interpolate2(tes_in[0].uv, tes_in[1].uv,tes_in[2].uv, tes_in[3].uv);
  tes_out.color = interpolate3(tes_in[0].color, tes_in[1].color,tes_in[2].color, tes_in[3].color).xyz;

  float heigth = texture(heightmap, tes_out.uv).x;
  gl_Position.y += heigth * height_factor;

}

