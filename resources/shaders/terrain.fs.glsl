#version 460

in GS_OUT {
  vec2 uv;
  vec3 color;
  vec3 wireframeDist;
} fs_in;

uniform sampler2D ourTexture;

out vec4 color;

void main() {
  vec3 d = fwidth(fs_in.wireframeDist);

  vec3 a3 = smoothstep(vec3(0.0), d * 1.0, fs_in.wireframeDist);
  float edgeFactor = min(min(a3.x, a3.y), a3.z);

//   color = vec4(fs_in.color, 1.0);
  color = texture(ourTexture, fs_in.uv);

  bool wireframe = true;
  if (wireframe) color = vec4(mix(vec3(1.0), color.rgb, edgeFactor), color.a);
}
