#version 430

in layout(location=0) vec2 position;

out vec4 theColor;

uniform vec3 drawingColor;
uniform mat4 projectionMatrix;

void main() { 
	gl_Position = projectionMatrix * vec4(position, 0.0, 1.0);
	theColor = vec4(drawingColor, 1.0);
}