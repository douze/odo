#version 460

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in TE_OUT {
  vec3 color;
} gs_in[];

out GS_OUT {
  vec3 color;
  noperspective vec3 wireframeDist;
} gs_out;

void main(void) {
  for(int i = 0; i < gl_in.length(); ++i) {
    gs_out.color = gs_in[i].color;
    gs_out.wireframeDist = vec3(0.0);
    gs_out.wireframeDist[i] = 1.0;
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();
}
