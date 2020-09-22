#version 460

out gl_PerVertex { 
  vec4 gl_Position; 
};

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vCol;

layout (location = 0) uniform mat4 transformation;

out V_OUT { 
  vec3 color;
} v_out;

void main()
{
  gl_Position = transformation * vec4(vPos, 1.0);
  v_out.color = vCol;
 };
