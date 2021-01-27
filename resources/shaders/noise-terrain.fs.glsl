#version 460

#import webgl-noise/noise2D.glsl

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
    return fbm(xy, fbm_octaves, fbm_amplitude_persistence[0], fbm_amplitude_persistence[1],
        fbm_frequency_lacunarity[0], fbm_frequency_lacunarity[1]);
  }
  if (noise_function == 1){
    return billow(xy, billow_octaves, billow_amplitude_persistence[0], billow_amplitude_persistence[1],
        billow_frequency_lacunarity[0], billow_frequency_lacunarity[1]);
  }
  if (noise_function == 2) {
    return rmf(xy, rmf_octaves, rmf_amplitude_persistence[0], rmf_amplitude_persistence[1],
        rmf_frequency_lacunarity[0], rmf_frequency_lacunarity[1], rmf_h_offset[0], rmf_h_offset[1]);
  }
  if (noise_function == 3) {
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

/**
 * @brief Compute the analytic normals of the xy position.
 */
vec3 compute_normal(vec2 uv) {
  vec3 offset = vec3(1.0/1280.0, 1.0/800.0, 0.0); // TODO uniforms
  float height_left = compute_height(fs_in.uv - offset.xz);
  float height_right = compute_height(fs_in.uv + offset.xz);
  float height_down = compute_height(fs_in.uv - offset.zy);
  float height_up = compute_height(fs_in.uv + offset.zy);
  return normalize(vec3(height_left - height_right, height_down - height_up, 0));
}

void main() {
  float height = compute_height(fs_in.uv);
  height = height*0.5 + 0.5;
  vec3 normal = compute_normal(fs_in.uv);
  color = vec4(height, normal);
};
