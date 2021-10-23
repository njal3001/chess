#include "chess/graphics/resourcemanager.h"

namespace Game
{
    ResourceManager::ResourceManager()
        :  m_sprite_shader(nullptr), m_text_shader(nullptr), m_sprite_array(nullptr),
            m_text_array(nullptr), m_game_layer(nullptr), m_text_layer(nullptr)
    {}

    ResourceManager::~ResourceManager()
    {
        delete m_game_layer;
        delete m_text_layer;
        delete m_sprite_array;
        delete m_text_array;
        delete m_sprite_shader;
        delete m_text_shader;
        delete m_font_atlas;
    }

    bool ResourceManager::init()
    {
        m_font_atlas = new FontAtlas("res/fonts/upheavtt.ttf", 20, Vec2(256, 128));
        if (!m_font_atlas->init())
        {
            std::cout << "Could not initialize font atlas!" << std::endl;
            return false;
        }

        m_sprite_shader = new Shader("res/shaders/sprite.vert",
                "res/shaders/sprite.frag");

        m_text_shader = new Shader("res/shaders/text.vert",
            "res/shaders/text.frag");

        
        m_sprite_array = new TextureArray(10, Vec2(64, 64), GL_RGBA, GL_BGRA, 4);
        m_game_layer = new Layer(m_sprite_array->get_id(), m_sprite_shader, 
                Mat4x4::create_orthographic(0.0f, 64.0f, 0.0f, 64.0f, -1.0f, 1.0f));

        Vec2 atlas_size = m_font_atlas->get_size();
        unsigned char* atlas_pixels = m_font_atlas->get_pixels();
        m_text_array = new TextureArray(2, atlas_size, GL_RED, GL_RED, 1);
        m_font_texture = m_text_array->add(atlas_pixels, (int)atlas_size.x, (int)atlas_size.y);

        m_text_layer = new Layer(m_text_array->get_id(), m_text_shader, 
                Mat4x4::create_orthographic(0.0f, 64.0f, 0.0f,  64.0f, -1.0f, 1.0f));
    }

    Shader* ResourceManager::get_sprite_shader() const
    {
        return m_sprite_shader;
    }

    Shader* ResourceManager::get_text_shader() const
    {
        return m_text_shader;
    }

    TextureArray* ResourceManager::get_sprite_array() const
    {
        return m_sprite_array;
    }

    TextureArray* ResourceManager::get_text_array() const
    {
        return m_text_array;
    }

    Layer* ResourceManager::get_game_layer() const
    {
        return m_game_layer;
    }

    Layer* ResourceManager::get_text_layer() const
    {
        return m_text_layer;
    }

    FontAtlas* ResourceManager::get_font_atlas() const
    {
        return m_font_atlas;
    }

    TextureArray::Element ResourceManager::get_font_texture() const
    {
        return m_font_texture;
    }
}