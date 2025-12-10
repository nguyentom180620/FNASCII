cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(main 
        src/main.cpp 
        src/graphics/icon/resources.rc
        src/map/Map.h
        src/map/Map.cpp
        src/animatronics/Base_Animatronic/Base_Animatronic.h
        src/animatronics/Base_Animatronic/Base_Animatronic.cpp
        src/tom_engine/game_night_backend/Game_Night_Backend.h
        src/tom_engine/game_night_backend/Game_Night_Backend.cpp
        src/animatronics/Bonnie/Bonnie.h
        src/animatronics/Bonnie/Bonnie.cpp
        src/animatronics/Base_Animatronic/Adjacency_List.h
        src/animatronics/Base_Animatronic/Adjacency_List.cpp
        src/graphics/Left_Door_Graphic.h
        src/tom_engine/game/Main_Game_Window/Main_Game_Window.h
        src/tom_engine/components/sprites/Left_Door.h
        src/tom_engine/components/sprites/Left_Door.cpp
        src/tom_engine/game/Main_Game_Window/Main_Game_Window.cpp
        src/graphics/Bonnie_Graphic.h
        src/tom_engine/components/sprites/Open_Cam_Button.h
        src/tom_engine/components/sprites/Open_Cam_Button.cpp
        src/tom_engine/components/sprites/Camera.cpp
        src/tom_engine/components/sprites/Camera.h
        src/tom_engine/components/sprites/Camera_System.cpp
        src/tom_engine/components/sprites/Camera_System.h
        src/animatronics/Foxy/Foxy.cpp
        src/animatronics/Foxy/Foxy.h
        src/graphics/Right_Door_Graphic.h
        src/tom_engine/components/sprites/Right_Door.cpp
        src/tom_engine/components/sprites/Right_Door.h
        src/animatronics/Chica/Chica.cpp
        src/animatronics/Chica/Chica.h
        src/graphics/Chica_Graphic.h
        src/animatronics/Freddy/Freddy.cpp
        src/animatronics/Freddy/Freddy.h
        src/tom_engine/game/Home_Screen_Window/Home_Screen_Window.cpp
        src/tom_engine/game/Home_Screen_Window/Home_Screen_Window.h
        src/tom_engine/game/Custom_Night_Settings_Window/Custom_Night_Settings_Window.cpp
        src/tom_engine/game/Custom_Night_Settings_Window/Custom_Night_Settings_Window.h
)
target_link_libraries(main PRIVATE sfml-graphics sfml-audio)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    target_sources(main PRIVATE src/graphics/icon/resources.rc)

    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
