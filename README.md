# FNASCII

![FNASCII Freddy Face](src/graphics/Freddy_Face.png)

FNASCII is a Five Nights at Freddy's (FNAF) demake that uses ASCII-based art.  
It was built from the ground-up, being great as an exercise for reverse-engineering how FNAF works.

To play the game from downloading a zip file, the project is avaliabled on my itch.io page:  
  
[FNASCII](https://folixangel.itch.io/fnascii)

## Installation

### Building on Ubuntu/Debian Linux

To compile the project after cloning the repo, you must install dependencies for graphics, audio, and windows that let SFML run.

Run the following in terminal:

    sudo apt update
    sudo apt install libxrandr-dev libxcursor-dev libxext-dev libfreetype-dev libopenal-dev libflac-dev libvorbis-dev libjpeg-dev libudev-dev libgl1-mesa-dev

Now, we want to build the project using CMakeLists.  
Change directories till you are at the root of the project, for example:  

> ~/Personal/c++/FNASCII$

Then run the following commands:

    cmake -S . -B build
    cmake --build build --target main -j 8

Now, you can run the game.  
Make sure you are in the root directory, then run the program:

    ./build/bin/main

To make it easier to access, I recommend making a symbolic link.
To do so, run the following from the root directory:

    ln -s build/bin/main FNASCII.exe

Then, you can run the game from the root directory by the following command:

    ./FNASCII.exe

### Building on Windows using CLion

Make sure you have git. Then, you should be able to use the CMakeSFMLProject configuration to make an initial cmake-build-debug directory.  

After that, you need to make a new CMake Application configuration. In CLion, this means clicking on the configurations which are to the left of the 'build hammer'.

Edit configurations, and click on the plus sign to add a new "CMake Application". Lastly, change the working directory so that the root of the project is the working directory.  

This may look like:

> C:/Users/{YOUR_NAME}/CLionProjects/FNASCII

After that, you can click the hammer to build the project. Finally, you can run the project by pressing the green arrow with your CMake Application configuration set.

## Usage

The game is point and click. In the office, the left and right doors work identically. You can left click the buttons to toggle doors and lights. 
Optionally, you can also left click the door directly to toggle it, and you can right click the door to turn the lights on and off quickly.
The camera console can be pulled up by left clicking the bar at the bottom of the screen. Then, cameras can be selected on the right side.
UI for the battery, battery usage, and time are always at the top of the screen.

For the title screen, new game will reset the game to night 1. Continue game will continue from whichever night the player has made it to from nights 1 to 5.
Beating Night 5 will unlock night 6 and earn a star on the title screen.
Beating Night 6 will unlock Custom Night and earn another star.
Beating Custom Night will earn the final star, and the game is considered 100%.

The player data is saved in *src/savefiles/fnascii_player_data.txt*, where the first number is the number of nights from 1 to 5 the player has beat and the second is the number of stars earned.
The default values should therefore be:

> 1
> 0

As be default the player starts on Night 1, with 0 stars earned.

## Contributing

Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement". Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (git checkout -b feature/AmazingFeature)
3. Commit your Changes (git commit -m 'Add some AmazingFeature')
4. Push to the Branch (git push origin feature/AmazingFeature)
5. Open a Pull Request

## License
This project uses SFML and so I will credit them here:

[SFML](https://github.com/SFML/SFML)
