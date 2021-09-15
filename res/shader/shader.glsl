@shader vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 MVP;

out vec2 texcoords;

void main() {
  gl_Position = MVP*vec4(aPos, 1.0);
  texcoords = aTexCoord;
}


@shader fragment
#version 330 core
out vec4 color;
in vec2 texcoords;

void main() {
  color = vec4(texcoords, 0.7, 1.0);
}
