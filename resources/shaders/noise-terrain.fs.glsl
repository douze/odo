#version 460

in VS_OUT {
  vec3 position;
  vec2 uv;
} fs_in;

out vec4 color;

vec2 tile(vec2 _st, float _zoom){
  _st *= _zoom;
  return fract(_st);
}

float box(vec2 _st, vec2 _size){
  _size = vec2(0.5)-_size*0.5;
  vec2 uv = smoothstep(_size,_size+vec2(0.0001),_st);
  uv *= smoothstep(_size,_size+vec2(0.0001),vec2(1.0)-_st);
  return uv.x*uv.y;
}
void main() {
  color = vec4(fs_in.uv, 0.0, 1.0);
  
vec2 st = fs_in.uv;
  st = tile(st,10.0);
  
  vec3 c = vec3(box(st,vec2(0.9)));

  color = vec4(c,1.0);    
};