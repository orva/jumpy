#version 130

in vec4 position;
uniform vec2 offset;

void main()
{
	gl_Position = position;
}
