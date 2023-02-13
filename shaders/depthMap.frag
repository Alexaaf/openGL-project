#version 410 core

out vec4 fColor;
uniform sampler2D diffuseTexture;
in vec2 fTexCoords;
void main()
{
	if(texture(diffuseTexture, fTexCoords).a < 0.1f){
		discard;
	}
	fColor = vec4(1.0f);
}
