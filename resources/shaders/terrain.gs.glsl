#version 460

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in TES_OUT {
  vec2 uv;
} gs_in[];

out GS_OUT {
  vec2 uv;
  vec3 wireframe_weight;
} gs_out;

void main(void) {
  for(int i = 0; i < gl_in.length(); i++) {
    gl_Position = gl_in[i].gl_Position;

    gs_out.uv = gs_in[i].uv;
    gs_out.wireframe_weight = vec3(0.0);
    gs_out.wireframe_weight[i] = 1.0;

    EmitVertex();
  }
  EndPrimitive();
}
