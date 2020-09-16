#version 460
   
in V_OUT {
  vec3 color;
} v_out;
 
out vec4 color;

void main()
{
  color = vec4(v_out.color, 1.0);
};
