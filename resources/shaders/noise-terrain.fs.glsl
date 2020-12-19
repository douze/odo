#version 460

#import webgl-noise/noise2D.glsl

in VS_OUT {
  vec3 position;
  vec2 uv;
} fs_in;

layout (location = 0) uniform int fbm_octaves;
layout (location = 1) uniform float fbm_amplitude;
layout (location = 2) uniform float fbm_frequency;

out vec4 color;

float fbm (in vec2 st) {
    float value = 0.0;
    int octaves = fbm_octaves;
    float amplitude = fbm_amplitude;
    float frequency = fbm_frequency;
    for (int i = 0; i < octaves; i++) {
        value += amplitude * snoise(st * frequency);
        amplitude *= .5;
        frequency *= 2.;
    }
    return value;
}


void main() {
  float v = fbm(fs_in.uv);
  v = v*0.5+0.5;
  color = vec4(v,v,v,1.0);
};
