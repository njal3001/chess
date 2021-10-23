#pragma once
#include "fontatlas.h"
#include "shader.h"
#include "texturearray.h"
#include "layer.h"

namespace Game
{
    class ResourceManager
    {
    private:
        Shader* m_sprite_shader;
        Shader* m_text_shader;
        TextureArray* m_sprite_array;
        TextureArray* m_text_array;
        Layer* m_game_layer;
        Layer* m_text_layer;
        FontAtlas* m_font_atlas;
        TextureArray::Element m_font_texture;

    public:
        ResourceManager();
        ~ResourceManager();

        bool init();

        Shader* get_sprite_shader() const;
        Shader* get_text_shader() const;

        TextureArray* get_sprite_array() const;
        TextureArray* get_text_array() const;

        Layer* get_game_layer() const;
        Layer* get_text_layer() const;

        FontAtlas* get_font_atlas() const;
        TextureArray::Element get_font_texture() const;
    };
}