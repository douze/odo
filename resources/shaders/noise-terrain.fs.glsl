#version 460

#import webgl-noise/noise2D.glsl
#import utils/debug.glsl

in VS_OUT {
  vec3 position;
  vec2 uv;
} fs_in;

layout (location = 0) uniform int fbm_octaves;
layout (location = 1) uniform vec2 fbm_amplitude_persistence;
layout (location = 2) uniform vec2 fbm_frequency_lacunarity;

layout (location = 3) uniform int billow_octaves;
layout (location = 4) uniform vec2 billow_amplitude_persistence;
layout (location = 5) uniform vec2 billow_frequency_lacunarity;

layout (location = 6) uniform int rmf_octaves;
layout (location = 7) uniform vec2 rmf_amplitude_persistence;
layout (location = 8) uniform vec2 rmf_frequency_lacunarity;
layout (location = 9) uniform vec2 rmf_h_offset;

layout (location = 11) uniform bool use_demo_value;
layout (location = 12) uniform int noise_function;

layout (location = 13) uniform int normal_type;

out vec4 color;

/**
 * @brief Fractal Brownian Motion noise.
 */
float fbm (vec2 xy, int octaves, float amplitude, float persistence, float frequency, float lacunarity) {
    float value = 0.0;
    for (int i = 0; i < octaves; i++) {
        value += amplitude * snoise(xy * frequency);
        amplitude *= persistence;
        frequency *= lacunarity;
    }
    return value;
}

/**
 * @brief Billowy noise.
 */
float billow (vec2 xy, int octaves, float amplitude, float persistence, float frequency, float lacunarity) {
    float value = 0.0;
    for (int i = 0; i < octaves; i++) {
        value += amplitude * (2.0 * abs(snoise(xy * frequency)) - 1.0);
        amplitude *= persistence;
        frequency *= lacunarity;
    }
    return value + 0.5;
}

/**
 * @brief Ridged Multi Fractal noise.
 */
float rmf (vec2 xy, int octaves, float amplitude, float persistence, float frequency, float lacunarity,
           float h, float offset) {
    float value = 0.0;

    float weights[8]; // max octaves
    float local_frequency = frequency;
    for (int i = 0 ; i< octaves ;i++) {
      weights[i] = pow(local_frequency, -h);
      local_frequency *= lacunarity;
    }

    float weight  = 1.0;
    for (int i = 0; i < octaves; i++) {
        float n = snoise(xy*frequency);
        n = offset - abs(n);
        n = n * n * weight;
        weight = n * persistence;
        weight = clamp(weight, 0.0, 1.0);
        frequency *= lacunarity;
        value += n * weights[i];
    }
    return (value * 1.25) - 1.0;
}

/**
 * @brief Compute the height of the xy position.
 * @note Result depends on noise_function selection.
 */
float compute_height(vec2 xy) {
  if (noise_function == 0) {
    //return circle(xy, 0.9);
    //return box(xy, vec2(0.4,0.3)) + box(xy, vec2(0.3,0.4));
    //return smoothstep(0.1,0.9,xy.x);
    return (cubicPulse(0.5,0.2,xy.x));
    return (cubicPulse(0.5,0.2,xy.x) + cubicPulse(0.5,0.2,xy.y))*0.5;
  }
  if (noise_function == 1){
    return fbm(xy, fbm_octaves, fbm_amplitude_persistence[0], fbm_amplitude_persistence[1],
        fbm_frequency_lacunarity[0], fbm_frequency_lacunarity[1]);
  }
  if (noise_function == 2){
    return billow(xy, billow_octaves, billow_amplitude_persistence[0], billow_amplitude_persistence[1],
        billow_frequency_lacunarity[0], billow_frequency_lacunarity[1]);
  }
  if (noise_function == 3) {
    return rmf(xy, rmf_octaves, rmf_amplitude_persistence[0], rmf_amplitude_persistence[1],
        rmf_frequency_lacunarity[0], rmf_frequency_lacunarity[1], rmf_h_offset[0], rmf_h_offset[1]);
  }
  if (noise_function == 4) {
    if (use_demo_value) {
      float mountain_terrain = rmf(xy, 6, 1.0, 0.5, 1.0, 2.0, 1.0, 1.0);
      float base_flat_terrain = billow(xy, 6, 1.0, 0.5, 2.0, 2.0);
      float flat_terrain = base_flat_terrain  * 0.125 - 0.75;
      float terrain_type = fbm(xy, 6, 1.0, 0.25, 0.5, 2.0);
      float final_terrain = mix(flat_terrain, mountain_terrain, smoothstep(0.0, 1.0, terrain_type));
      return final_terrain;
    } else {
      float mountain_terrain = rmf(xy, rmf_octaves, rmf_amplitude_persistence[0], rmf_amplitude_persistence[1],
          rmf_frequency_lacunarity[0], rmf_frequency_lacunarity[1], rmf_h_offset[0], rmf_h_offset[1]);
      float base_flat_terrain = billow(xy, billow_octaves, billow_amplitude_persistence[0], billow_amplitude_persistence[1],
          billow_frequency_lacunarity[0], billow_frequency_lacunarity[1]);
      float flat_terrain = base_flat_terrain  * 0.125 - 0.75;
      float terrain_type = fbm(xy, fbm_octaves, fbm_amplitude_persistence[0], fbm_amplitude_persistence[1],
          fbm_frequency_lacunarity[0], fbm_frequency_lacunarity[1]);
      float final_terrain = mix(flat_terrain, mountain_terrain, smoothstep(0.0, 1.0, terrain_type));
      return final_terrain;
    }
  }
}

// https://www.shadertoy.com/view/MsScRt
vec3 bump_from_depth(vec2 uv, vec2 resolution, float scale) {
  vec2 step = 1. / resolution;
  float height = compute_height(uv);
  vec2 dxy = height - vec2(
      compute_height(uv + vec2(step.x, 0.)),
      compute_height(uv + vec2(0., step.y))
  );
  return normalize(vec3(dxy * scale / step, 1.));
}


/**
 * @brief Compute the analytic normals of the xy position.
 */
vec3 compute_normal(vec2 uv) {
  vec3 offset = vec3(-1.0/1024.0, 0, 1.0/1024.0);

  float curr = compute_height(uv);
  float left = compute_height(uv.xy + offset.xy);
  float right = compute_height(uv.xy + offset.zy);
  float below = compute_height(uv.xy + offset.yx);
  float above = compute_height(uv.xy + offset.yz);

  if (normal_type == 0) {
    vec3 va = normalize( vec3(offset.z, 0.0, right - curr) );
    vec3 vb = normalize( vec3(0.0, offset.z, above - curr) );
    return normalize( cross(va, vb) );
  } else if (normal_type == 1) {
    vec3 va = normalize( vec3(offset.z, 0.0, right - left) );
    vec3 vb = normalize( vec3(0.0, offset.z, above - below) );
    return normalize( cross(va, vb) );
  } else if (normal_type == 2) {
    return bump_from_depth(uv, vec2(1024), .1).rgb;
  }
}

void main() {
  float height = compute_height(fs_in.uv);
  height = height*0.5 + 0.5;

  vec3 normal = compute_normal(fs_in.uv);
  // normal [-1, 1] => map to [0, 1]
  normal = normal * 0.5 + 0.5;

  color = vec4(height, normal);
};
