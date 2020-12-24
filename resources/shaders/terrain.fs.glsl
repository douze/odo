#version 460

in GS_OUT {
  vec2 uv;
  vec3 wireframeDist;
} fs_in;

layout (location = 0) uniform bool wireframe;
uniform sampler2D ourTexture;

out vec4 color;

void main() {
  vec3 d = fwidth(fs_in.wireframeDist);

  vec3 a3 = smoothstep(vec3(0.0), d * 1.0, fs_in.wireframeDist);
  float edgeFactor = min(min(a3.x, a3.y), a3.z);

  color = texture(ourTexture, fs_in.uv);

  if (wireframe) color = vec4(mix(vec3(1.0), color.rgb, edgeFactor), color.a);
}
