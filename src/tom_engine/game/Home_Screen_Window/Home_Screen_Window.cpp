#include "Home_Screen_Window.h"

Home_Screen_Window::Home_Screen_Window(int night_number, int stars) {
    home_screen.close();
    home_screen.create(sf::VideoMode(1000, 900), "FNASCII", sf::Style::Close);
    home_screen.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(home_screen);
    translated_mouse_pos = home_screen.mapPixelToCoords(mouse_pos);

    icon.loadFromFile("src/graphics/Freddy_Face.png");
    home_screen.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    freddy_texture.loadFromFile("src/graphics/Freddy_On_Cam.png");
    freddy_sprite.setTexture(freddy_texture);
    freddy_sprite.setPosition(sf::Vector2f(550, 100));
    freddy_sprite.setScale(sf::Vector2f(1.5, 1.5));

    text_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");

    title_text.setFont(text_font);
    title_text.setString("FNASCII");
    title_text.setCharacterSize(125);
    title_text.setFillColor(sf::Color::White);
    title_render_texture.create(title_text.getLocalBounds().width, title_text.getLocalBounds().height+75);
    title_render_texture.clear(sf::Color::Transparent);
    title_render_texture.draw(title_text);
    title_render_texture.display();
    title_sprite.setTexture(title_render_texture.getTexture());
    title_sprite.setPosition(40, 40);

    version_text.setFont(text_font);
    version_text.setString("Version 1.0");
    version_text.setCharacterSize(20);
    version_text.setFillColor(sf::Color::White);
    version_render_texture.create(version_text.getLocalBounds().width, version_text.getLocalBounds().height+75);
    version_render_texture.clear(sf::Color::Transparent);
    version_render_texture.draw(version_text);
    version_render_texture.display();
    version_sprite.setTexture(version_render_texture.getTexture());
    version_sprite.setPosition(20, 870);

    stars_texture.loadFromFile("src/graphics/white_star.png");
    stars_sprite.setTexture(stars_texture);
    stars_sprite.setScale(sf::Vector2f(0.5, 0.5));
    this->stars = stars;

    select_game_text.setFont(text_font);
    select_game_text.setString(">");
    select_game_text.setCharacterSize(35);
    select_game_text.setFillColor(sf::Color::White);
    select_game_render_texture.create(select_game_text.getLocalBounds().width, select_game_text.getLocalBounds().height+10);
    select_game_render_texture.clear(sf::Color::Transparent);
    select_game_render_texture.draw(select_game_text);
    select_game_render_texture.display();
    select_game_sprite.setTexture(select_game_render_texture.getTexture());
    select_game_sprite.setPosition(80, 500);

    start_game_text.setFont(text_font);
    start_game_text.setString("Start Game");
    start_game_text.setCharacterSize(35);
    start_game_text.setFillColor(sf::Color::White);
    start_game_render_texture.create(start_game_text.getLocalBounds().width, start_game_text.getLocalBounds().height+10);
    start_game_render_texture.clear(sf::Color::Transparent);
    start_game_render_texture.draw(start_game_text);
    start_game_render_texture.display();
    start_game_sprite.setTexture(start_game_render_texture.getTexture());
    start_game_sprite.setPosition(100, 500);

    continue_game_text.setFont(text_font);
    continue_game_text.setString("Continue Game");
    continue_game_text.setCharacterSize(35);
    continue_game_text.setFillColor(sf::Color::White);
    continue_game_render_texture.create(continue_game_text.getLocalBounds().width, continue_game_text.getLocalBounds().height+10);
    continue_game_render_texture.clear(sf::Color::Transparent);
    continue_game_render_texture.draw(continue_game_text);
    continue_game_render_texture.display();
    continue_game_sprite.setTexture(continue_game_render_texture.getTexture());
    continue_game_sprite.setPosition(100, 600);

    this->night_number = night_number;
    continue_night_number_text.setFont(text_font);
    std::string continue_night_number = "Night " + std::to_string(night_number);
    continue_night_number_text.setString(continue_night_number);
    continue_night_number_text.setCharacterSize(30);
    continue_night_number_text.setFillColor(sf::Color::White);
    continue_night_number_render_texture.create(continue_night_number_text.getLocalBounds().width, continue_night_number_text.getLocalBounds().height+10);
    continue_night_number_render_texture.clear(sf::Color::Transparent);
    continue_night_number_render_texture.draw(continue_night_number_text);
    continue_night_number_render_texture.display();
    continue_night_number_sprite.setTexture(continue_night_number_render_texture.getTexture());
    continue_night_number_sprite.setPosition(continue_game_text.getLocalBounds().width + 125, 606);

    sixth_night_game_text.setFont(text_font);
    sixth_night_game_text.setString("6th Night");
    sixth_night_game_text.setCharacterSize(35);
    sixth_night_game_text.setFillColor(sf::Color::White);
    sixth_night_render_texture.create(sixth_night_game_text.getLocalBounds().width, sixth_night_game_text.getLocalBounds().height+10);
    sixth_night_render_texture.clear(sf::Color::Transparent);
    sixth_night_render_texture.draw(sixth_night_game_text);
    sixth_night_render_texture.display();
    sixth_night_game_sprite.setTexture(sixth_night_render_texture.getTexture());
    sixth_night_game_sprite.setPosition(100, 700);

    custom_night_game_text.setFont(text_font);
    custom_night_game_text.setString("Custom Night");
    custom_night_game_text.setCharacterSize(35);
    custom_night_game_text.setFillColor(sf::Color::White);
    custom_night_render_texture.create(custom_night_game_text.getLocalBounds().width, custom_night_game_text.getLocalBounds().height + 10);
    custom_night_render_texture.clear(sf::Color::Transparent);
    custom_night_render_texture.draw(custom_night_game_text);
    custom_night_render_texture.display();
    custom_night_game_sprite.setTexture(custom_night_render_texture.getTexture());
    custom_night_game_sprite.setPosition(100, 800);

    select_sound_buffer.loadFromFile("src/sound/Light_On.wav");
    select_sound.setBuffer(select_sound_buffer);
    select_sound_playing = false;
    select_sound.setVolume(50);

    // Music changes based on progress!
    if (stars < 1) {
        home_screen_music.openFromFile("src/sound/Fnascii_home_screen.wav");
    }
    else {
        home_screen_music.openFromFile("src/sound/Ode_To_Joy.wav");
    }
    home_screen_music.setLoop(true);
    home_screen_music.setVolume(100);
    home_screen_music.play();

    selected_night = "Start Game";
}

void Home_Screen_Window::Update() {
    select_sound_playing = false;
}

void Home_Screen_Window::Draw() {
    home_screen.clear();
    home_screen.draw(freddy_sprite);
    home_screen.draw(title_sprite);
    home_screen.draw(version_sprite);
    for (int i = 0; i < stars; i++) {
        stars_sprite.setPosition(40 + i*130, 200);
        home_screen.draw(stars_sprite);
    }
    home_screen.draw(select_game_sprite);
    home_screen.draw(start_game_sprite);
    home_screen.draw(continue_game_sprite);
    home_screen.draw(continue_night_number_sprite);
    if (stars >= 1) {
        home_screen.draw(sixth_night_game_sprite);
    }
    if (stars >= 2) {
        home_screen.draw(custom_night_game_sprite);
    }
    home_screen.display();
}

std::string Home_Screen_Window::Run() {
    while (home_screen.isOpen()) {
        auto mouse_pos = sf::Mouse::getPosition(home_screen);
        translated_mouse_pos = home_screen.mapPixelToCoords(mouse_pos);

        sf::Event event;
        while (home_screen.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                home_screen.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    home_screen.close();
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (start_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                    if (selected_night != "Start Game") {
                        if (select_sound_playing == false) {
                            select_sound_playing = true;
                            select_sound.play();
                        }
                        selected_night = "Start Game";
                        select_game_sprite.setPosition(80, 500);
                    }
                }
                if (continue_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                    if (selected_night != "Continue Game") {
                        if (select_sound_playing == false) {
                            select_sound_playing = true;
                            select_sound.play();
                        }
                        selected_night = "Continue Game";
                        select_game_sprite.setPosition(80, 600);
                    }
                }
                if (stars >= 1) {
                    if (sixth_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        if (selected_night != "6th Night") {
                            if (select_sound_playing == false) {
                                select_sound_playing = true;
                                select_sound.play();
                            }
                            selected_night = "6th Night";
                            select_game_sprite.setPosition(80, 700);
                        }
                    }
                    if (stars >= 2) {
                        if (custom_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                            if (selected_night != "Custom Night") {
                                if (select_sound_playing == false) {
                                    select_sound_playing = true;
                                    select_sound.play();
                                }
                                selected_night = "Custom Night";
                                select_game_sprite.setPosition(80, 800);
                            }
                        }
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (start_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        home_screen_music.stop();
                        home_screen.close();
                        return selected_night;
                    }
                    if (continue_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                        home_screen_music.stop();
                        home_screen.close();
                        return selected_night;
                    }
                    if (stars >= 1) {
                        if (sixth_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                            home_screen_music.stop();
                            home_screen.close();
                            return selected_night;
                        }
                        if (stars >= 2) {
                            if (custom_night_game_sprite.getGlobalBounds().contains(translated_mouse_pos)) {
                                home_screen_music.stop();
                                home_screen.close();
                                return selected_night;
                            }
                        }
                    }
                }
            }
        }
        Update();
        Draw();
    }
    home_screen_music.stop();
    return "None";
}
