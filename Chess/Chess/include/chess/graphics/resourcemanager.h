#pragma once
#include "fontatlas.h"
#include "shader.h"
#include "texturearray.h"
#include "layer.h"

namespace Chess
{
    namespace Graphics
    {
        class ResourceManager
        {
        private:
            FontAtlas* m_font_atlas;
            Shader* m_sprite_shader;
            Shader* m_text_shader;
            TextureArray* m_sprite_array;
            TextureArray* m_text_array;
            Layer* m_game_layer;
            Layer* m_text_layer;

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
        };
    }
}