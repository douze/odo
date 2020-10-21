#version 460

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

out VS_OUT { 
  vec3 position;
  vec2 uv;
} vs_out;

void main() {
  vs_out.position = vec3(position, 0.0);
  vs_out.uv = uv;
  gl_Position = vec4(vs_out.position, 1.0);
}
