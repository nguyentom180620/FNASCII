#include "Main_Game_Window.h"
#include <iostream>
#define FONT_SIZE 35

Main_Game_Window::Main_Game_Window(std::mt19937& rng, int night_number, int bonnie_level, int foxy_level, int chica_level, int freddy_level): night(rng),
bonnie(bonnie_level), foxy(foxy_level), chica(chica_level), freddy(freddy_level) {
    this->rng = rng;
    this->night_number = night_number;

    night.addAnimatronic(bonnie);
    night.addFoxy(foxy);
    night.addAnimatronic(chica);
    night.addAnimatronic(freddy);
    move_count = 0;
    bonnie_jumpscare_counter = 0;
    foxy_jumpscare_counter = 0;
    number_of_foxy_hits = 0;
    foxy_running = false;
    chica_jumpscare_counter = 0;
    freddy_jumpscare_counter = 0;
    battery_power = 1000;
    passive_battery_drain_interval = 1000;
    battery_display_value = battery_power / 10;
    battery_power_usage_array = {true, false, false, false, false, false};
    battery_power_usage_value = std::count(battery_power_usage_array.begin(),
        battery_power_usage_array.end(), true);
    entered_office = false;
    player_alive = true;
    bonnie_jumpscare = false;
    foxy_jumpscare = false;
    chica_jumpscare = false;
    freddy_jumpscare = false;
    game_time = 0;
    game_win_timer = 60 * 10;
    power_zero_timer = 60 * 22;
    frame_counter_60 = 0;

    night_win = false;
    night_lose = false;

    leftdoorClosed = false;
    leftlightsOn = false;
    left_door_open_close_clicked_on = false;
    left_door_light_clicked_on = false;

    rightdoorClosed = false;
    rightlightsOn = false;
    right_door_open_close_clicked_on = false;
    right_door_light_clicked_on = false;

    open_cam_button_clicked_on = false;
    cam_mode = false;

    battery_caption_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    battery_caption.setFont(battery_caption_font);
    battery_display_value = std::to_string(battery_power / 10);
    battery_caption.setString("Battery: " + battery_display_value + '%');
    battery_caption.setCharacterSize(FONT_SIZE);
    battery_caption.setFillColor(sf::Color::White);
    battery_caption.setPosition(sf::Vector2f(20, 25));

    usage_caption_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    usage_caption.setFont(usage_caption_font);
    usage_caption.setString("Usage:");
    usage_caption.setCharacterSize(FONT_SIZE);
    usage_caption.setFillColor(sf::Color::White);
    usage_caption.setPosition(sf::Vector2f(350, 25));

    usage_bar_texture.create(25, 55);
    usage_bar_texture.clear(sf::Color::White);
    usage_bar_texture.display();
    usage_bar_sprite.setTexture(usage_bar_texture.getTexture());
    usage_bar_sprite.setPosition(sf::Vector2f(485, 21));

    Office_Background_texture.loadFromFile("src/graphics/Fnaf_background_image.png", sf::IntRect({50, 0}, {753, 526}));
    Office_Background_sprite.setTexture(Office_Background_texture);
    Office_Background_sprite.setPosition(sf::Vector2f(200,150));
    Office_Background_sprite.setScale(0.94, 0.94);

    map_layout_texture.loadFromFile("src/graphics/fnascii_map.png");
    map_layout_sprite.setTexture(map_layout_texture);
    map_layout_sprite.setPosition(sf::Vector2f(500, 200));

    active_cam = "Cam 1A";

    clock_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
    clock_text.setFont(clock_font);
    clock_text.setString("12 AM, Night " + std::to_string(night_number));
    clock_text.setCharacterSize(FONT_SIZE);
    clock_text.setFillColor(sf::Color::White);
    clock_text.setPosition(sf::Vector2f(700, 25));

    top_line.setFillColor(sf::Color::Transparent);
    top_line.setOutlineColor(sf::Color::White);
    top_line.setSize(sf::Vector2f(1000,0));
    top_line.setPosition(sf::Vector2f(0, 100));
    top_line.setOutlineThickness(1.0f);
    bottom_line.setFillColor(sf::Color::Transparent);
    bottom_line.setOutlineColor(sf::Color::White);
    bottom_line.setSize(sf::Vector2f(1000,0));
    bottom_line.setPosition(sf::Vector2f(0, 800));
    bottom_line.setOutlineThickness(1.0f);

    freddy_nose.create(22, 20);
    freddy_nose.clear(sf::Color::Transparent);
    freddy_nose.display();
    freddy_noseSprite.setTexture(freddy_nose.getTexture());
    freddy_noseSprite.setPosition(sf::Vector2f(475, 300));

    freddy_sound_buffer.loadFromFile("src/sound/fnaf_nose_honk.wav");
    jumpscare_sound_buffer.loadFromFile("src/sound/jumpscare.wav");
    open_door_sound_buffer.loadFromFile("src/sound/Open_Door.wav");
    close_door_sound_buffer.loadFromFile("src/sound/Close_Door.wav");
    open_cam_sound_buffer.loadFromFile("src/sound/Open_Cam.wav");
    close_cam_sound_buffer.loadFromFile("src/sound/Close_Cam.wav");
    change_cam_sound_buffer.loadFromFile("src/sound/Change_Cam.wav");
    lights_on_sound_buffer.loadFromFile("src/sound/Light_On.wav");
    lights_off_sound_buffer.loadFromFile("src/sound/Light_Off.wav");
    lights_on_sound_playing = false;
    lights_off_sound_playing = false;
    bonnie_at_door_sound_buffer.loadFromFile("src/sound/Ani_At_door.wav");
    bonnie_sound_playing = false;
    chica_at_door_sound_buffer.loadFromFile("src/sound/Ani_At_door.wav");
    chica_sound_playing = false;
    power_zero_buffer.loadFromFile("src/sound/power_zero.wav");
    power_zero_playing = false;
    win_6_am_buffer.loadFromFile("src/sound/Win_6_AM.wav");
    win_6_am_playing = false;
    leaving_door_sound_buffer.loadFromFile("src/sound/Leaving_Door.wav");
    foxy_bgm_sound_buffer.loadFromFile("src/sound/foxy_bgm.wav");
    foxy_bgm_sound.setBuffer(foxy_bgm_sound_buffer);
    foxy_bgm_sound.setLoop(true);
    foxy_bgm_sound.setVolume(75.f);
    foxy_bgm_sound_playing = false;
    foxy_running_sound_buffer.loadFromFile("src/sound/Foxy_Running.wav");
    foxy_running_sound.setBuffer(foxy_running_sound_buffer);
    foxy_running_sound_playing = false;
    toreador_sound_buffer.loadFromFile("src/sound/Toreadors_March.wav");
    toreador_sound.setBuffer(toreador_sound_buffer);
    toreador_sound_playing = false;

    game_window.close();
    game_window.create(sf::VideoMode(1000, 900), "FNASCII", sf::Style::Close);
    game_window.setFramerateLimit(60);
    auto mouse_pos = sf::Mouse::getPosition(game_window);
    translated_mouse_pos = game_window.mapPixelToCoords(mouse_pos);
    icon.loadFromFile("src/graphics/Freddy_Face.png");
    game_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

Main_Game_Window::~Main_Game_Window() {}

void Main_Game_Window::Update() {
    // These only work if power is above 0!
    if (battery_power > 0) {
        // Check the new cam button
        if (open_cam_button_clicked_on) {
            // Toggle cam mode
            cam_mode = !cam_mode;
            // Play sound corresponding to new state
            if (cam_mode == false) {
                close_cam_sound.setBuffer(close_cam_sound_buffer);
                close_cam_sound.play();
            }
            else {
                open_cam_sound.setBuffer(open_cam_sound_buffer);
                open_cam_sound.play();
            }
            open_cam_button_clicked_on = false;
        }

        // Update Left Door open close toggle
        if (left_door_open_close_clicked_on) {
            setleftdoorClosed(!getleftdoorClosed());
            if (leftdoorClosed == true) {
                close_door_sound.setBuffer(close_door_sound_buffer);
                close_door_sound.play();
            }
            else {
                open_door_sound.setBuffer(open_door_sound_buffer);
                open_door_sound.play();
            }
            left_door.openCloseDoor(getleftdoorClosed(), getleftLightsOn());
            left_door_open_close_clicked_on = false;
            // Reset Animatronic Sprite
            bonnie.resetSprite();
        }

        // Update Right Door open close toggle
        if (right_door_open_close_clicked_on) {
            rightdoorClosed = !rightdoorClosed;
            if (rightdoorClosed == true) {
                close_door_sound.setBuffer(close_door_sound_buffer);
                close_door_sound.play();
            }
            else {
                open_door_sound.setBuffer(open_door_sound_buffer);
                open_door_sound.play();
            }
            right_door.openCloseDoor(getrightdoorClosed(), getrightLightsOn());
            right_door_open_close_clicked_on = false;
            // Reset Animatronic Sprite
            chica.resetSprite();
        }

        // Update Left Door Light
        if (left_door_light_clicked_on) {
            setleftLightsOn(true);
            left_door_light_clicked_on = false;
        }

        // Update Right Door Light
        if (right_door_light_clicked_on) {
            setrightLightsOn(true);
            right_door_light_clicked_on = false;
        }
    }

    else {
        battery_power = 0;
        leftdoorClosed = false;
        leftlightsOn = false;
        rightdoorClosed = false;
        rightlightsOn = false;
        cam_mode = false;
        battery_power_usage_array = {false, false, false, false, false, false};
        left_door.doorLightOff();
        left_door.lightButtonOff();
        left_door.openCloseDoor(leftdoorClosed, leftlightsOn);
        right_door.doorLightOff();
        right_door.lightButtonOff();
        right_door.openCloseDoor(rightdoorClosed, rightlightsOn);

        lights_on_sound.stop();
        lights_off_sound.stop();

        if (power_zero_playing == false) {
            power_zero_playing = true;
            power_zero_sound.setBuffer(power_zero_buffer);
            power_zero_sound.play();
        }

        if (power_zero_timer < (60 * 18)) {
            // Draw freddy going in and out (In draw function)
            // Play Toreador's March
            if (toreador_sound_playing == false) {
                toreador_sound_playing = true;
                toreador_sound.play();
            }
        }
        if (power_zero_timer <= 0) {
            player_alive = false;
            night_lose = true;
            freddy_jumpscare = true;
        }
        power_zero_timer -= 1;
    }

    // Have Left Door update while lightsOn is true
    if (leftlightsOn) {
        left_door.lightButtonOn();
        if (leftdoorClosed == false) {
            // // If Bonnie is at the door, play his sound and draw him at door
            if (night.animatronicAtDoorCheck(bonnie, "Left Door")) {
                if (cam_mode == false && bonnie_sound_playing == false) {
                    bonnie_sound_playing = true;
                    bonnie_at_door_sound.setBuffer(bonnie_at_door_sound_buffer);
                    bonnie_at_door_sound.play();
                }
                bonnie.loadAtLeftDoorSprite();
                left_door.doorLightOff();
            }
            else {
                // Reset Animatronic Sprites
                bonnie_sound_playing = false;
                bonnie.resetSprite();
                left_door.doorLightOn();
            }
        }
    }
    else {
        if (leftdoorClosed == false) {
            left_door.doorLightOff();
        }
        left_door.lightButtonOff();
        bonnie.resetSprite();
    }

    // Have Right Door update while lightsOn is true
    if (rightlightsOn) {
        right_door.lightButtonOn();
        if (rightdoorClosed == false) {
            // If Chica is at the door, use bonnie left door behavior as model
            if (night.animatronicAtDoorCheck(chica, "Right Door")) {
                if (cam_mode == false && chica_sound_playing == false) {
                    chica_sound_playing = true;
                    chica_at_door_sound.setBuffer(chica_at_door_sound_buffer);
                    chica_at_door_sound.play();
                }
                chica.loadAtRightDoorSprite();
                right_door.doorLightOff();
            }
            else {
                // Reset Animatronic Sprites
                chica_sound_playing = false;
                chica.resetSprite();
                right_door.doorLightOn();
            }
        }
    }
    else {
        if (rightdoorClosed == false) {
            right_door.doorLightOff();
        }
        right_door.lightButtonOff();
        chica.resetSprite();
    }

    // Update array every frame to get faster feedback on usage bar
    if (leftdoorClosed) {
        battery_power_usage_array[1] = true;
    }
    else {
        battery_power_usage_array[1] = false;
    }
    if (leftlightsOn) {
        battery_power_usage_array[2] = true;
    }
    else {
        battery_power_usage_array[2] = false;
    }
    if (cam_mode) {
        battery_power_usage_array[3] = true;
    }
    else {
        battery_power_usage_array[3] = false;
    }
    if (rightdoorClosed) {
        battery_power_usage_array[4] = true;
    }
    else {
        battery_power_usage_array[4] = false;
    }
    if (rightlightsOn) {
        battery_power_usage_array[5] = true;
    }
    else {
        battery_power_usage_array[5] = false;
    }
    battery_power_usage_value = std::count(battery_power_usage_array.begin(),
        battery_power_usage_array.end(), true);

    // Music Management for Foxy
    if (cam_mode == true && active_cam == "Cam 1C") {
        if (foxy_bgm_sound_playing == false) {
            foxy_bgm_sound.play();
            foxy_bgm_sound_playing = true;
        }
    }
    else {
        foxy_bgm_sound.pause();
        foxy_bgm_sound_playing = false;
    }
    if (cam_mode == true && active_cam == "Cam 2A") {
        if (foxy_running) {
            if (foxy_running_sound_playing == false) {
                foxy_running_sound.play();
                foxy_running_sound_playing = true;
            }
        }
    }
    else {
        if (!foxy_running) {
            foxy_running_sound.stop();
        }
        foxy_running_sound_playing = false;
    }

    // Timer engine
    // Manages Bonnie, Foxy, Chica, and Battery
    ++frame_counter_60;
    if (frame_counter_60 >= 60) {
        if (game_time >= GAME_LENGTH) {
            night_win = true;
        }
        switch (game_time) {
            case 0:
            break;
            case 90:
                clock_text.setString("1 AM, Night " + std::to_string(night_number));
            break;
            case 179:
                clock_text.setString("2 AM, Night " + std::to_string(night_number));
            break;
            case 268:
                clock_text.setString("3 AM, Night " + std::to_string(night_number));
            break;
            case 357:
                clock_text.setString("4 AM, Night " + std::to_string(night_number));
            break;
            case 446:
                clock_text.setString("5 AM, Night " + std::to_string(night_number));
            break;
            case GAME_LENGTH:
                clock_text.setString("6 AM, Night " + std::to_string(night_number));
            break;
            default: break;
        }
        if (night.animatronicInOffice() && battery_power > 0) {
            if (night.animatronicInOfficeName() == "Bonnie") {
                if (bonnie_jumpscare_counter >= 3) {
                    player_alive = false;
                    night_lose = true;
                    bonnie_jumpscare = true;
                }
                bonnie_jumpscare_counter++;
            }
            if (night.animatronicInOfficeName() == "Chica") {
                if (chica_jumpscare_counter >= 3) {
                    player_alive = false;
                    night_lose = true;
                    chica_jumpscare = true;
                }
                chica_jumpscare_counter++;
            }
            if (night.animatronicInOfficeName() == "Freddy") {
                if (freddy_jumpscare_counter >= 3) {
                    player_alive = false;
                    night_lose = true;
                    freddy_jumpscare = true;
                }
                freddy_jumpscare_counter++;
            }
        }
        if (night.findAnimatronicCamName(foxy) == "Cam 1C") {
            if (foxy.getStage() == 4) {
                night.moveAnimatronic(foxy);
            }
        }
        if (night.findAnimatronicCamName(foxy) == "Cam 2A") {
            if (active_cam == "Cam 2A") {
                foxy_running = true;
            }
            if (foxy_running) {
                if (foxy_jumpscare_counter <= 20) {
                    foxy.setFrame(1);
                }
                else {
                    foxy.setFrame(2);
                }
                foxy_jumpscare_counter += 20;
            }
            if (foxy_jumpscare_counter >= 60) {
                if (getleftdoorClosed() == false) {
                    night.enterOffice(foxy);
                    entered_office = true;
                    player_alive = false;
                    night_lose = true;
                    foxy_jumpscare = true;
                }
                else {
                    // Reduce power by number of foxy hits
                    battery_power -= 10 + number_of_foxy_hits * 50;
                    number_of_foxy_hits += 1;
                    leaving_door_sound.setBuffer(leaving_door_sound_buffer);
                    leaving_door_sound.play();
                    bonnie_sound_playing = false;
                    night.moveAnimatronic(foxy);
                    foxy_jumpscare_counter = 0;
                    foxy.resetStage();
                    foxy.resetFrame();
                    foxy_running = false;
                }
            }
            foxy_jumpscare_counter++;
        }
        if (move_count == 5) {
            std::uniform_int_distribution<int> uid(1,20);
            if (night.animatronicAtDoorCheck(bonnie, "Left Door")) {
                int random_move_value_bonnie = uid(rng);
                if (bonnie.getLevel() >= random_move_value_bonnie) {
                    if (getleftdoorClosed() == false) {
                        night.enterOffice(bonnie);
                        entered_office = true;
                    }
                    else {
                        night.moveAnimatronic(bonnie);
                        leaving_door_sound.setBuffer(leaving_door_sound_buffer);
                        leaving_door_sound.play();
                        bonnie_sound_playing = false;
                    }
                }
            }
            if (night.animatronicAtDoorCheck(chica, "Right Door")) {
                int random_move_value_chica = uid(rng);
                if (chica.getLevel() >= random_move_value_chica) {
                    if (getrightdoorClosed() == false) {
                        night.enterOffice(chica);
                        entered_office = true;
                    }
                    else {
                        night.moveAnimatronic(chica);
                        leaving_door_sound.setBuffer(leaving_door_sound_buffer);
                        leaving_door_sound.play();
                        chica_sound_playing = false;
                    }
                }
            }
            if (night.findAnimatronicCamName(freddy) == "Cam 4B") {
                int random_move_value_freddy = uid(rng);
                if (freddy.getLevel() >= random_move_value_freddy) {
                    // Freddy only enters the office IF cams are up and the active cam is not on him
                    // This creates balance: Freddy forces need cams down, Foxy forces need for cams up
                    if (cam_mode == true && active_cam != "Cam 4B") {
                        if (getrightdoorClosed() == false) {
                            night.enterOffice(freddy);
                            entered_office = true;
                        }
                    }
                }
            }
            if (entered_office == false && battery_power > 0) {
                // Bonnie
                if (!(night.animatronicAtDoorCheck(bonnie, "Left Door"))) {
                    int random_move_value_bonnie = uid(rng);
                    if (bonnie.getLevel() >= random_move_value_bonnie) {
                        night.moveAnimatronic(bonnie);
                    }
                }

                // Foxy
                int random_move_value_foxy = uid(rng);
                if (foxy.getLevel() >= random_move_value_foxy) {
                    if (night.findAnimatronicCamName(foxy) == "Cam 1C") {
                        if (foxy.getStage() < 4) {
                            if (cam_mode == false) {
                                foxy.incrementStage();
                            }
                        }
                    }
                }

                // Chica
                if (!(night.animatronicAtDoorCheck(chica, "Right Door"))) {
                    int random_move_value_chica = uid(rng);
                    if (chica.getLevel() >= random_move_value_chica) {
                        night.moveAnimatronic(chica);
                    }
                }

                // Freddy
                if (!(cam_mode == true && night.findAnimatronicCamName(freddy) == active_cam)) {
                    int random_move_value_freddy = uid(rng);
                    if (freddy.getLevel() >= random_move_value_freddy) {
                        if (freddy.getMovingSongNumber() == 1) {
                            freddy_moving_sound_buffer.loadFromFile("src/sound/Freddy_Moving_1.wav");
                            freddy_moving_sound.setBuffer(freddy_moving_sound_buffer);
                            freddy_moving_sound.play();
                            freddy.setMovingSongNumber(2);
                        }
                        else if (freddy.getMovingSongNumber() == 2) {
                            freddy_moving_sound_buffer.loadFromFile("src/sound/Freddy_Moving_2.wav");
                            freddy_moving_sound.setBuffer(freddy_moving_sound_buffer);
                            freddy_moving_sound.play();
                            freddy.setMovingSongNumber(1);
                        }
                        night.moveAnimatronic(freddy);
                    }
                }
            }
            move_count = 0;
        }
        // Passive Battery Drain and Usage Drain
        if (game_time % passive_battery_drain_interval == 0) {
            battery_power = battery_power - 1;
        }
        if (battery_power > 0) {
            battery_power = battery_power - battery_power_usage_value;
            if (battery_power < 0) {
                battery_power = 0;
            }
        }
        battery_display_value = battery_power / 10;
        battery_display_value = std::to_string(battery_power / 10);
        battery_caption.setString("Battery: " + battery_display_value + '%');
        ++move_count;
        ++game_time;
        frame_counter_60 = 0;
    }
}

void Main_Game_Window::Draw() {
    game_window.clear();
    // Depends on Scene
    if (cam_mode == true) {
        // For drawing cam map and current cam scene
        game_window.draw(map_layout_sprite);
        auto cameras = camera_system.getCameras();
        for (auto &cam : cameras) {
            game_window.draw(cam.getCameraSprite());
        }

        // Vertical Dividing Line
        sf::RectangleShape vertical_line;
        vertical_line.setFillColor(sf::Color::White);
        vertical_line.setOutlineColor(sf::Color::White);
        vertical_line.setSize(sf::Vector2f(0,700));
        vertical_line.setPosition(sf::Vector2f(500, 100));
        vertical_line.setOutlineThickness(1.f);
        game_window.draw(vertical_line);

        // Get current cam scene

        //For foxy stages
        if (active_cam == "Cam 1C") {
            sf::Texture cam1C_texture;
            sf::Sprite cam1C_sprite;
            std::string cam1CDisplay_file_location = "src/graphics/Cam_1C_Stage" + std::to_string(foxy.getStage()) + ".png";
            cam1C_texture.loadFromFile(cam1CDisplay_file_location);
            cam1C_sprite.setTexture(cam1C_texture);
            cam1C_sprite.setPosition(sf::Vector2f(0, 100));
            cam1C_sprite.setScale(sf::Vector2f(1, 1));
            game_window.draw(cam1C_sprite);
        }
        // Every other cam
        else {
            sf::Texture cam_texture;
            sf::Sprite cam_sprite;
            std::string name_for_file = active_cam.substr(0,3) + "_" + active_cam.substr(4);
            std::string camDisplay_file_location = "src/graphics/" + name_for_file + ".png";
            cam_texture.loadFromFile(camDisplay_file_location);
            cam_sprite.setTexture(cam_texture);
            cam_sprite.setPosition(sf::Vector2f(0, 100));
            cam_sprite.setScale(sf::Vector2f(1, 1));
            game_window.draw(cam_sprite);
        }

        // Drawing foxy on Cam 2A
        if (active_cam == "Cam 2A" && foxy_running && night.findAnimatronicCamName(foxy) == "Cam 2A") {
            sf::Texture foxy_texture;
            sf::Sprite foxy_sprite;
            foxy_texture.loadFromFile("src/graphics/foxy.png");
            foxy_sprite.setTexture(foxy_texture);
            if (foxy.getFrame() == 1) {
                foxy_sprite.setPosition(sf::Vector2f(200, 200));
                foxy_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else {
                foxy_sprite.setPosition(sf::Vector2f(50, 225));
                foxy_sprite.setScale(sf::Vector2f(1, 1));
            }
            game_window.draw(foxy_sprite);
        }

        // Cam Name bottom left
        sf::Font cam_name_font;
        sf::Text cam_name_text;
        cam_name_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
        cam_name_text.setFont(cam_name_font);
        cam_name_text.setString(active_cam);
        cam_name_text.setCharacterSize(FONT_SIZE);
        cam_name_text.setFillColor(sf::Color::White);
        cam_name_text.setPosition(sf::Vector2f(10, 750));
        game_window.draw(cam_name_text);

        // This part draws the animatronics onto the scene
        const std::string current_cam_name = active_cam;
        Map::Cam current_camera = night.getMap().accessCam(current_cam_name);
        std::vector<std::string> animatronic_names = current_camera.getAnimatronicNames();

        // Draw Bonnie on screen if Bonnie is on current cam
        if (std::find(animatronic_names.begin(), animatronic_names.end(), "Bonnie")
            != animatronic_names.end()) {
            sf::Texture bonnie_texture;
            sf::Sprite bonnie_sprite;
            bonnie_texture.loadFromFile("src/graphics/Bonnie_On_Cam.png");
            bonnie_sprite.setTexture(bonnie_texture);
            if (current_cam_name == "Cam 1A") {
                bonnie_sprite.setPosition(sf::Vector2f(0, 200));
                bonnie_sprite.setScale(sf::Vector2f(1, 1));
            }
            else if (current_cam_name == "Cam 1B") {
                bonnie_sprite.setPosition(sf::Vector2f(100, 400));
                bonnie_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 2A") {
                bonnie_sprite.setPosition(sf::Vector2f(200, 200));
                bonnie_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 2B") {
                bonnie_sprite.setPosition(sf::Vector2f(150, 400));
                bonnie_sprite.setScale(sf::Vector2f(0.7, 0.7));
            }
            else if (current_cam_name == "Cam 3") {
                bonnie_sprite.setPosition(sf::Vector2f(115, 225));
                bonnie_sprite.setScale(sf::Vector2f(1, 1));
            }
            else if (current_cam_name == "Cam 5") {
                bonnie_sprite.setPosition(sf::Vector2f(150, 400));
                bonnie_sprite.setScale(sf::Vector2f(0.7, 0.7));
            }
            if (!(foxy_running && active_cam == "Cam 2A")) {
                game_window.draw(bonnie_sprite);
            }
        }

        // Draw Chica on screen if Chica is on current cam
        if (std::find(animatronic_names.begin(), animatronic_names.end(), "Chica")
            != animatronic_names.end()) {
            sf::Texture chica_texture;
            sf::Sprite chica_sprite;
            chica_texture.loadFromFile("src/graphics/Chica_On_Cam.png");
            chica_sprite.setTexture(chica_texture);
            if (current_cam_name == "Cam 1A") {
                chica_sprite.setPosition(sf::Vector2f(250, 300));
                chica_sprite.setScale(sf::Vector2f(1, 1));
            }
            else if (current_cam_name == "Cam 1B") {
                chica_sprite.setPosition(sf::Vector2f(300, 375));
                chica_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 4A") {
                chica_sprite.setPosition(sf::Vector2f(100, 225));
                chica_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 4B") {
                chica_sprite.setPosition(sf::Vector2f(125, 300));
                chica_sprite.setScale(sf::Vector2f(0.9, 0.9));
            }
            else if (current_cam_name == "Cam 6") {
                chica_sprite.setPosition(sf::Vector2f(200, 400));
                chica_sprite.setScale(sf::Vector2f(0.7, 0.7));
            }
            else if (current_cam_name == "Cam 7") {
                chica_sprite.setPosition(sf::Vector2f(150, 500));
                chica_sprite.setScale(sf::Vector2f(0.7, 0.7));
            }
            game_window.draw(chica_sprite);
        }

        // Draw Freddy on screen if Freddy is on current cam
        if (std::find(animatronic_names.begin(), animatronic_names.end(), "Freddy")
            != animatronic_names.end()) {
            sf::Texture freddy_texture;
            sf::Sprite freddy_sprite;
            freddy_texture.loadFromFile("src/graphics/Freddy_On_Cam.png");
            freddy_sprite.setTexture(freddy_texture);
            if (current_cam_name == "Cam 1A") {
                freddy_sprite.setPosition(sf::Vector2f(150, 325));
                freddy_sprite.setScale(sf::Vector2f(0.6, 0.6));
            }
            else if (current_cam_name == "Cam 1B") {
                freddy_sprite.setPosition(sf::Vector2f(250, 130));
                freddy_sprite.setScale(sf::Vector2f(0.25, 0.25));
            }
            else if (current_cam_name == "Cam 4A") {
                freddy_sprite.setPosition(sf::Vector2f(100, 225));
                freddy_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 4B") {
                freddy_sprite.setPosition(sf::Vector2f(125, 300));
                freddy_sprite.setScale(sf::Vector2f(1, 1));
            }
            else if (current_cam_name == "Cam 6") {
                freddy_sprite.setPosition(sf::Vector2f(25, 100));
                freddy_sprite.setScale(sf::Vector2f(0.5, 0.5));
            }
            else if (current_cam_name == "Cam 7") {
                freddy_sprite.setPosition(sf::Vector2f(40, 205));
                freddy_sprite.setScale(sf::Vector2f(0.30, 0.30));
            }
            game_window.draw(freddy_sprite);
        }

    }
    if (cam_mode == false) {
        game_window.draw(left_door.getSprite());
        game_window.draw(left_door.getDoorButtonSprite());
        game_window.draw(left_door.getLightButtonSprite());
        game_window.draw(left_door.getDoorButtonCaption());
        game_window.draw(left_door.getLightButtonCaption());
        game_window.draw(right_door.getSprite());
        game_window.draw(right_door.getDoorButtonSprite());
        game_window.draw(right_door.getLightButtonSprite());
        game_window.draw(right_door.getDoorButtonCaption());
        game_window.draw(right_door.getLightButtonCaption());
        game_window.draw(Office_Background_sprite);
        game_window.draw(bonnie.getSprite());
        game_window.draw(chica.getSprite());
        game_window.draw(freddy_noseSprite);
    }

    if (battery_power <= 0) {
        sf::RenderTexture dark_overlay_texture;
        sf::Sprite dark_overlay_sprite;
        dark_overlay_texture.create(1000, 700);
        dark_overlay_texture.clear(sf::Color::White);
        dark_overlay_texture.display();
        dark_overlay_sprite.setTexture(dark_overlay_texture.getTexture());
        dark_overlay_sprite.setPosition(sf::Vector2f(0, 100));
        dark_overlay_sprite.setColor(sf::Color(0,0,0,128));
        game_window.draw(dark_overlay_sprite);

        // Freddy for Toreador's March
        if (power_zero_timer < (60 * 18) && power_zero_timer > (60 * 2)) {
            sf::Texture freddy_face_texture;
            sf::Sprite freddy_face_sprite;
            freddy_face_texture.loadFromFile("src/graphics/Freddy_Face.png");
            freddy_face_sprite.setTexture(freddy_face_texture);
            freddy_face_sprite.setScale(sf::Vector2f(0.7, 0.7));
            freddy_face_sprite.setPosition(sf::Vector2f(97.f, 275.f));
            if ((power_zero_timer / 30) % 2 == 1) {
                game_window.draw(freddy_face_sprite);
            }
        }
    }

    // Always on Screen
    game_window.draw(battery_caption);
    game_window.draw(usage_caption);
    for (int i = 0; i < battery_power_usage_value; i++) {
        usage_bar_sprite.setPosition(sf::Vector2f(485 + (35*i), 21));
        game_window.draw(usage_bar_sprite);
    }
    game_window.draw(clock_text);
    game_window.draw(top_line);
    game_window.draw(bottom_line);
    game_window.draw(open_cam_button.getSprite());
    game_window.display();
}

const bool Main_Game_Window::getleftdoorClosed() {
    return leftdoorClosed;
}

void Main_Game_Window::setleftdoorClosed(bool newBool) {
    leftdoorClosed = newBool;
}

const bool Main_Game_Window::getleftLightsOn() {
    return leftlightsOn;
}

void Main_Game_Window::setleftLightsOn(bool newBool) {
    leftlightsOn = newBool;
    if (leftlightsOn == true && lights_on_sound_playing == false) {
        lights_on_sound_playing = true;
        lights_off_sound_playing = false;
        lights_on_sound.setBuffer(lights_on_sound_buffer);
        lights_on_sound.play();
    }
    if (leftlightsOn == false && lights_off_sound_playing == false) {
        lights_off_sound_playing = true;
        lights_on_sound_playing = false;
        lights_off_sound.setBuffer(lights_off_sound_buffer);
        lights_off_sound.play();
    }
}

const bool Main_Game_Window::getrightdoorClosed() {
    return rightdoorClosed;
}

void Main_Game_Window::setrightdoorClosed(bool newBool) {
    rightdoorClosed = newBool;
}

const bool Main_Game_Window::getrightLightsOn() {
    return rightlightsOn;
}

void Main_Game_Window::setrightLightsOn(bool newBool) {
    rightlightsOn = newBool;
    if (rightlightsOn == true && lights_on_sound_playing == false) {
        lights_on_sound_playing = true;
        lights_off_sound_playing = false;
        lights_on_sound.setBuffer(lights_on_sound_buffer);
        lights_on_sound.play();
    }
    if (rightlightsOn == false && lights_off_sound_playing == false) {
        lights_off_sound_playing = true;
        lights_on_sound_playing = false;
        lights_off_sound.setBuffer(lights_off_sound_buffer);
        lights_off_sound.play();
    }
}

void Main_Game_Window::nightWinStopSounds() {
    sound_effect.stop();
    open_door_sound.stop();
    close_door_sound.stop();
    open_cam_sound.stop();
    close_cam_sound.stop();
    change_cam_sound.stop();
    lights_on_sound.stop();
    lights_off_sound.stop();
    bonnie_at_door_sound.stop();
    chica_at_door_sound.stop();
    power_zero_sound.stop();
    leaving_door_sound.stop();
    foxy_bgm_sound.stop();
    foxy_running_sound.stop();
    toreador_sound.stop();
}

bool Main_Game_Window::Run() {
    while (game_window.isOpen()) {
        if (night_win == true) {
            nightWinStopSounds();
            if (win_6_am_playing == false) {
                win_6_am_playing = true;
                win_6_am_sound.setBuffer(win_6_am_buffer);
                win_6_am_sound.play();
            }
            sf::Font win_6_am_font;
            sf::Text win_6_am_text;
            win_6_am_font.loadFromFile("src/graphics/font/PixeloidSans.ttf");
            if (game_win_timer > 235) {
                game_window.clear();
                win_6_am_text.setFont(win_6_am_font);
                win_6_am_text.setString("6 AM!");
                win_6_am_text.setCharacterSize(FONT_SIZE * 4);
                win_6_am_text.setFillColor(sf::Color::White);
                win_6_am_text.setPosition(sf::Vector2f(300, 350));
                game_window.draw(win_6_am_text);
                game_window.display();
            }
            else {
                game_window.clear();
                win_6_am_text.setFont(win_6_am_font);
                win_6_am_text.setString("You won\nthe night!");
                win_6_am_text.setCharacterSize(FONT_SIZE * 3);
                win_6_am_text.setPosition(sf::Vector2f(250, 300));
                game_window.draw(win_6_am_text);
                game_window.display();
            }
            if (game_win_timer <= 0) {
                game_window.close();
            }
            game_win_timer -= 1;
        }
        if (night_lose == true) {
            foxy_bgm_sound.stop();
            if (bonnie_jumpscare) {
                sf::Texture bonnie_jumpscare_texture;
                sf::Sprite bonnie_jumpscare_sprite;
                bonnie_jumpscare_sprite.setPosition(125, 75);

                sound_effect.setBuffer(jumpscare_sound_buffer);
                sound_effect.play();

                // Loop frames
                for (int i = 0; i < 5; i++) {
                    game_window.clear();
                    bonnie_jumpscare_texture.loadFromFile("src/graphics/Bonnie_Jumpscare_Frame1.png");
                    bonnie_jumpscare_sprite.setTexture(bonnie_jumpscare_texture);
                    game_window.draw(bonnie_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                    game_window.clear();
                    bonnie_jumpscare_texture.loadFromFile("src/graphics/Bonnie_Jumpscare_Frame2.png");
                    bonnie_jumpscare_sprite.setTexture(bonnie_jumpscare_texture);
                    game_window.draw(bonnie_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                }
            }
            if (foxy_jumpscare) {
                sf::Texture foxy_jumpscare_texture;
                sf::Sprite foxy_jumpscare_sprite;
                foxy_jumpscare_sprite.setPosition(205, 75);

                sound_effect.setBuffer(jumpscare_sound_buffer);
                sound_effect.play();

                // Loop frames
                for (int i = 0; i < 5; i++) {
                    game_window.clear();
                    foxy_jumpscare_texture.loadFromFile("src/graphics/Foxy_Jumpscare_Frame_1.png");
                    foxy_jumpscare_sprite.setTexture(foxy_jumpscare_texture);
                    game_window.draw(foxy_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                    game_window.clear();
                    foxy_jumpscare_texture.loadFromFile("src/graphics/Foxy_Jumpscare_Frame_2.png");
                    foxy_jumpscare_sprite.setTexture(foxy_jumpscare_texture);
                    game_window.draw(foxy_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                }
            }
            if (chica_jumpscare) {
                sf::Texture chica_jumpscare_texture;
                sf::Sprite chica_jumpscare_sprite;
                chica_jumpscare_texture.loadFromFile("src/graphics/Chica_Jumpscare_Frame_2.png");
                chica_jumpscare_sprite.setTexture(chica_jumpscare_texture);
                chica_jumpscare_sprite.setPosition(125, 75);

                sound_effect.setBuffer(jumpscare_sound_buffer);
                sound_effect.play();

                // Loop frames
                for (int i = 0; i < 5; i++) {
                    game_window.clear();
                    chica_jumpscare_texture.loadFromFile("src/graphics/Chica_Jumpscare_Frame_1.png");
                    chica_jumpscare_sprite.setTexture(chica_jumpscare_texture);
                    game_window.draw(chica_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                    game_window.clear();
                    chica_jumpscare_texture.loadFromFile("src/graphics/Chica_Jumpscare_Frame_2.png");
                    chica_jumpscare_sprite.setTexture(chica_jumpscare_texture);
                    chica_jumpscare_sprite.setPosition(100, 75);
                    game_window.draw(chica_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                }
            }
            if (freddy_jumpscare) {
                sf::Texture freddy_jumpscare_texture;
                sf::Sprite freddy_jumpscare_sprite;
                freddy_jumpscare_texture.loadFromFile("src/graphics/Freddy_Jumpscare_Frame_2.png");
                freddy_jumpscare_sprite.setTexture(freddy_jumpscare_texture);
                freddy_jumpscare_sprite.setPosition(50, 75);

                sound_effect.setBuffer(jumpscare_sound_buffer);
                sound_effect.play();

                // Loop frames
                for (int i = 0; i < 5; i++) {
                    game_window.clear();
                    freddy_jumpscare_texture.loadFromFile("src/graphics/Freddy_Jumpscare_Frame_1.png");
                    freddy_jumpscare_sprite.setTexture(freddy_jumpscare_texture);
                    game_window.draw(freddy_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                    game_window.clear();
                    freddy_jumpscare_texture.loadFromFile("src/graphics/Freddy_Jumpscare_Frame_2.png");
                    freddy_jumpscare_sprite.setTexture(freddy_jumpscare_texture);
                    game_window.draw(freddy_jumpscare_sprite);
                    game_window.display();
                    sf::sleep(sf::seconds(0.25f));
                }
            }
            game_window.close();
        }
        //     // Mouse pos collection
        auto mouse_pos = sf::Mouse::getPosition(game_window);
        translated_mouse_pos = game_window.mapPixelToCoords(mouse_pos);

        sf::Event event{};
        while (game_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                player_alive = false;
                game_window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    player_alive = false;
                    game_window.close();
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // In camera
                    if (cam_mode == true) {
                        if (open_cam_button.clickedOn(translated_mouse_pos)) {
                            open_cam_button_clicked_on = true;
                        }
                        // Change camera here
                        std::vector<Camera>& cams = camera_system.getCameras();
                        for (auto& cam : cams) {
                            if (cam.clickedOn(translated_mouse_pos)) {
                                change_cam_sound.setBuffer(change_cam_sound_buffer);
                                change_cam_sound.play();
                                active_cam = cam.getCameraName().getString();
                            }
                        }
                    }
                    // In office
                    if (cam_mode == false) {
                        if (left_door.clickedOn(translated_mouse_pos)) {
                            left_door_open_close_clicked_on = true;
                        }
                        if (right_door.clickedOn(translated_mouse_pos)) {
                            right_door_open_close_clicked_on = true;
                        }
                        if (open_cam_button.clickedOn(translated_mouse_pos)) {
                            open_cam_button_clicked_on = true;
                        }
                        // Quick Light Button Toggle instead of hold
                        if (left_door.getLightButtonSprite().getGlobalBounds().contains(translated_mouse_pos)) {
                            leftlightsOn = !leftlightsOn;
                            if (leftlightsOn == true) {
                                lights_on_sound.setBuffer(lights_on_sound_buffer);
                                lights_on_sound.play();
                            }
                            else {
                                lights_off_sound.setBuffer(lights_off_sound_buffer);
                                lights_off_sound.play();
                            }
                        }
                        if (right_door.getLightButtonSprite().getGlobalBounds().contains(translated_mouse_pos)) {
                            rightlightsOn = !rightlightsOn;
                            if (rightlightsOn == true) {
                                lights_on_sound.setBuffer(lights_on_sound_buffer);
                                lights_on_sound.play();
                            }
                            else {
                                lights_off_sound.setBuffer(lights_off_sound_buffer);
                                lights_off_sound.play();
                            }
                        }
                        // If Freddy Picture Nose Booped
                        if (freddy_noseSprite.getGlobalBounds().contains(translated_mouse_pos)) {
                            // Play sound
                            sound_effect.setBuffer(freddy_sound_buffer);
                            sound_effect.play();
                        }
                    }
                }
            }
            // Right click hold on door for light mechanic
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                // In camera
                if (cam_mode == true) {
                    // For right-clicking stuff in cam mode
                }
                if (cam_mode == false) {
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        left_door_light_clicked_on = true;
                    }
                    if (right_door.clickedOn(translated_mouse_pos)) {
                        right_door_light_clicked_on = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                // In camera
                if (cam_mode == true) {
                    // future use
                }
                if (cam_mode == false) {
                    // Reference for this idea: https://en.sfml-dev.org/forums/index.php?topic=13412.0
                    // If right-click released for door lights, stop!
                    if (left_door.clickedOn(translated_mouse_pos)) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            setleftLightsOn(false);
                            if (leftdoorClosed == false) {
                                left_door.doorLightOff();
                            }
                            // Reset Animatronic Sprites
                            bonnie.resetSprite();
                        }
                    }
                    if (right_door.clickedOn(translated_mouse_pos)) {
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            setrightLightsOn(false);
                            if (rightdoorClosed == false) {
                                right_door.doorLightOff();
                            }
                            // Reset Animatronic Sprites
                            chica.resetSprite();
                        }
                    }
                }
            }
        }
        if (!(night_win || night_lose)) {
            Update();
            Draw();
        }
    }
    return player_alive;
}
