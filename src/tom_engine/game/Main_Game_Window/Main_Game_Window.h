#pragma once
#include <random>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "../../../map/Map.h"
#include "../../game_night_backend/Game_Night_Backend.h"
#include "../../components/sprites/Left_Door.h"
#include "../../components/sprites/Right_Door.h"
#include  "../../components/sprites/Open_Cam_Button.h"
#include "../../components/sprites/Camera_System.h"
class Main_Game_Window {
    std::mt19937 rng;
    sf::Image icon;

    Game_Night_Backend night;
    int night_number;

    Bonnie bonnie;
    Foxy foxy;
    Chica chica;
    Freddy freddy;

    int move_count;
    int bonnie_jumpscare_counter;
    int foxy_jumpscare_counter;
    int number_of_foxy_hits;
    int chica_jumpscare_counter;
    int freddy_jumpscare_counter;

    int battery_power;
    std::string battery_display_value;
    int passive_battery_drain_interval;
    std::vector<bool> battery_power_usage_array;
    int battery_power_usage_value;
    sf::Font battery_caption_font;
    sf::Text battery_caption;

    sf::Font usage_caption_font;
    sf::Text usage_caption;
    sf::RenderTexture usage_bar_texture;
    sf::Sprite usage_bar_sprite;

    sf::Texture Office_Background_texture;
    sf::Sprite Office_Background_sprite;

    sf::Texture map_layout_texture;
    sf::Sprite map_layout_sprite;

    std::string active_cam;
    Camera_System camera_system;

    sf::Font clock_font;
    sf::Text clock_text;

    bool entered_office;
    bool player_alive;
    bool bonnie_jumpscare;
    bool foxy_jumpscare;
    bool foxy_running;
    bool chica_jumpscare;
    bool freddy_jumpscare;
    int game_time;
    int frame_counter_60;

    bool night_win;
    bool night_lose;

    bool leftdoorClosed;
    bool leftlightsOn;
    bool left_door_open_close_clicked_on;
    bool left_door_light_clicked_on;
    Left_Door left_door;

    bool rightdoorClosed;
    bool rightlightsOn;
    bool right_door_open_close_clicked_on;
    bool right_door_light_clicked_on;
    Right_Door right_door;

    bool open_cam_button_clicked_on;
    bool cam_mode;
    Open_Cam_Button open_cam_button;

    sf::RectangleShape top_line;
    sf::RectangleShape bottom_line;
    sf::RenderWindow game_window {};
    sf::Vector2f translated_mouse_pos;

    sf::RenderTexture freddy_nose;
    sf::Sprite freddy_noseSprite;
    sf::SoundBuffer freddy_sound_buffer;
    sf::SoundBuffer jumpscare_sound_buffer;
    sf::Sound sound_effect;

    sf::SoundBuffer open_door_sound_buffer;
    sf::SoundBuffer close_door_sound_buffer;
    sf::Sound open_door_sound;
    sf::Sound close_door_sound;

    sf::SoundBuffer open_cam_sound_buffer;
    sf::SoundBuffer close_cam_sound_buffer;
    sf::Sound open_cam_sound;
    sf::Sound close_cam_sound;

    sf::SoundBuffer change_cam_sound_buffer;
    sf::Sound change_cam_sound;

    sf::SoundBuffer lights_on_sound_buffer;
    sf::SoundBuffer lights_off_sound_buffer;
    sf::Sound lights_on_sound;
    sf::Sound lights_off_sound;
    bool lights_on_sound_playing;
    bool lights_off_sound_playing;

    sf::SoundBuffer bonnie_at_door_sound_buffer;
    sf::Sound bonnie_at_door_sound;
    bool bonnie_sound_playing;

    sf::SoundBuffer chica_at_door_sound_buffer;
    sf::Sound chica_at_door_sound;
    bool chica_sound_playing;

    sf::SoundBuffer power_zero_buffer;
    sf::Sound power_zero_sound;
    bool power_zero_playing;
    int power_zero_timer;

    sf::SoundBuffer win_6_am_buffer;
    sf::Sound win_6_am_sound;
    bool win_6_am_playing;
    int game_win_timer;

    sf::SoundBuffer leaving_door_sound_buffer;
    sf::Sound leaving_door_sound;

    sf::SoundBuffer foxy_bgm_sound_buffer;
    sf::Sound foxy_bgm_sound;
    bool foxy_bgm_sound_playing;

    sf::SoundBuffer foxy_running_sound_buffer;
    sf::Sound foxy_running_sound;
    bool foxy_running_sound_playing;

    sf::SoundBuffer toreador_sound_buffer;
    sf::Sound toreador_sound;
    bool toreador_sound_playing;

    sf::SoundBuffer freddy_moving_sound_buffer;
    sf::Sound freddy_moving_sound;

    void Update();
    void Draw();
public:
    Main_Game_Window(std::mt19937& rng, int night_number, int bonnie_level, int foxy_level, int chica_level, int freddy_level);
    ~Main_Game_Window();
    const bool getleftdoorClosed();
    void setleftdoorClosed(bool newBool);
    const bool getleftLightsOn();
    void setleftLightsOn(bool newBool);
    const bool getrightdoorClosed();
    void setrightdoorClosed(bool newBool);
    const bool getrightLightsOn();
    void setrightLightsOn(bool newBool);
    void nightWinStopSounds();
    bool Run();
};
