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
    vec4 frag_color = fs_in.color;
    if (fs_in.texture_layer >= 0)
    {
        ivec3 texture_size = textureSize(textures, 0);
        frag_color *= texture(textures, vec3(fs_in.uv, fs_in.texture_layer));
    }
    color = frag_color;
}
