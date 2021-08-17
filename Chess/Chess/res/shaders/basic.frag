#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
	vec4 position;
    vec2 uv;
    float texture_slot;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    vec4 frag_color = fs_in.color;
    if (fs_in.texture_slot > 0.0)
    {
        int texture_slot = int(fs_in.texture_slot - 0.5); // -0.5 instead of -1 to prevent floating point errors
        frag_color = texture(textures[texture_slot], fs_in.uv);
        if (isnan(fs_in.texture_slot) || isinf(fs_in.texture_slot))
        {
            frag_color = vec4(0, 0, 0, 1);    
        }
    }
	color = frag_color * intensity;
}
