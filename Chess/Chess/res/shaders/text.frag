#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
	vec4 position;
    vec2 uv;
    flat int texture_layer;
	vec4 color;
} fs_in;

uniform sampler2DArray textures;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	color = vec4(fs_in.color.rgb, texture(textures, vec3(fs_in.uv, fs_in.texture_layer)).r);
}
