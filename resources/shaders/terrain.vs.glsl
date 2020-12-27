#version 460

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 uv;

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

out VS_OUT {
  vec2 uv;
  vec3 color;
} vs_out;

void main() {
  gl_Position = projection * view * model * vec4(position + gl_InstanceID, 0.0, 1.0);
  vs_out.uv = uv;
  vs_out.color = color;
}
