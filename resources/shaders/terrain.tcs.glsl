#version 460

layout(vertices = 4) out;

in V_OUT {
  vec2 uv;
  vec3 color;
} tcs_in[];

out TC_OUT {
  vec2 uv;
  vec3 color;
} tcs_out[];

void main(void) {
  gl_TessLevelOuter[0] = 2.0;
  gl_TessLevelOuter[1] = 4.0;
  gl_TessLevelOuter[2] = 6.0;
  gl_TessLevelOuter[3] = 8.0;
  
//   gl_TessLevelOuter[0] = gl_TessLevelOuter[1] = gl_TessLevelOuter[2] = gl_TessLevelOuter[3] = 1.0;

  gl_TessLevelInner[0] = 8.0;
  gl_TessLevelInner[1] = 8.0;
  
//   gl_TessLevelInner[0] = gl_TessLevelInner[1] = 1.0;

  gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
  
  tcs_out[gl_InvocationID].uv = tcs_in[gl_InvocationID].uv;
  tcs_out[gl_InvocationID].color = tcs_in[gl_InvocationID].color;
}