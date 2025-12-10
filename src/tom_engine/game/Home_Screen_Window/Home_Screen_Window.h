#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Home_Screen_Window {
    sf::RenderWindow home_screen {};
    sf::Vector2f translated_mouse_pos;
    sf::Image icon;

    sf::Texture freddy_texture;
    sf::Sprite freddy_sprite;

    sf::Font text_font;

    sf::Text title_text;
    sf::RenderTexture title_render_texture;
    sf::Sprite title_sprite;

    sf::Text version_text;
    sf::RenderTexture version_render_texture;
    sf::Sprite version_sprite;

    sf::Texture stars_texture;
    sf::Sprite stars_sprite;
    int stars;

    sf::Text select_game_text;
    sf::RenderTexture select_game_render_texture;
    sf::Sprite select_game_sprite;

    sf::Text start_game_text;
    sf::RenderTexture start_game_render_texture;
    sf::Sprite start_game_sprite;

    sf::Text continue_game_text;
    sf::RenderTexture continue_game_render_texture;
    sf::Sprite continue_game_sprite;

    sf::Text continue_night_number_text;
    sf::RenderTexture continue_night_number_render_texture;
    sf::Sprite continue_night_number_sprite;
    int night_number;

    sf::Text sixth_night_game_text;
    sf::RenderTexture sixth_night_render_texture;
    sf::Sprite sixth_night_game_sprite;

    sf::Text custom_night_game_text;
    sf::RenderTexture custom_night_render_texture;
    sf::Sprite custom_night_game_sprite;

    sf::SoundBuffer select_sound_buffer;
    sf::Sound select_sound;
    bool select_sound_playing;

    sf::Music home_screen_music;

    std::string selected_night;
public:
    Home_Screen_Window(int night_number, int stars);
    void Update();
    void Draw();
    std::string Run();
};
