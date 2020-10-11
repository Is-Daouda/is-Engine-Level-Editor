# is::Engine Level Editor
Level editor of the **[Game Engine Demo](https://github.com/Is-Daouda/is-Engine-Demo)**. It was created with the **[is::Engine](https://github.com/Is-Daouda/is-Engine)**. This tool allows you to create your own levels and to be able to integrate it into the game engine demo. You can also adapt it to use it for your own game.

**Please consult the [user guide](./doc/) to learn how to use the Level editor.**

![Image](./images/demo_screen.png)

## Prerequisites
- [SFML Library (2.4 +)](https://www.sfml-dev.org/download.php)
- GCC Compiler (7.3 +)

---

## How to use is::Engine with the different development tools:
## ![cmake](https://i48.servimg.com/u/f48/20/16/75/27/icon_c11.png) CMake
**1. Prerequisites**
- CMake (3.1 +)

**2. Installation**
#### Windows
1. Compile SFML with CMake to have **static libraries** and put on **C:/ (C:/SFML)**.
2. Move the **is-Engine-Level-Editor** project to your **C:/ (C:/is-Engine-Level-Editor)**.
3. Execute this command :
```bash
cmake -S "C:/is-Engine-Level-Editor" -B "C:/build"
cd build
make
```

#### Linux
1. Install SFML 2.5.1 on your machine.
2. Move the **is-Engine-Level-Editor** project to **/home/user/ (/home/user/is-Engine-Level-Editor)**.
3. Execute this command :
```bash
sudo cmake -S "is-Engine-Level-Editor" -B "build"
cd build
sudo make
```

**3. After installation**
- You will have a **bin** folder in which the engine demo is located.

**5. Adding Source Files**
- In order for CMake to detect your source files (.cpp) you must include them in the **[app_src.cmake](./app/src/main/cmake/app_src.cmake) or [isengine.cmake](./app/src/main/cmake/isengine.cmake)** file which is located in the **[is-Engine-Level-Editor/app/src/main/cmake](./app/src/main/cmake/)** location.

---

## ![vs](https://i48.servimg.com/u/f48/20/16/75/27/icon_v10.png) Visual Studio Code
This project uses the template of **andrew-r-king**. For more information on this template [click here](https://github.com/andrew-r-king/sfml-vscode-boilerplate).

**1. Prerequisites**
#### Windows
- [SFML 2.5.1 - GCC 7.3.0 MinGW (DW2) 32-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip)
- [GCC 7.3.0 MinGW (DW2) 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download)
- [Git Bash](https://git-scm.com/downloads)

#### Linux
- Get SFML 2.5.1 from your distro if it has it, or compile from source.

**2. Installation**
#### Windows
1. Download & Extract SFML 2.5.1 to **C:/SFML/** where the bin/lib/include folders are contained within.
2. Download & Extract MinGW to **C:/mingw32/** where the bin/lib/include folders are contained within.

#### Linux
1. Ensure the GCC Toolchain is installed (**sudo apt install build-essential**).
2. Run **sudo apt install libsfml-dev**. The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.

**3. Opening the project with the IDE:**
#### Windows
1. Run the file **open_vscode.bat** in the main directory.

#### Linux
2. Execute this command in the main directory:
```bash
code -n "./app/src/main"
```

#### All
3. Or open the **[is-Engine-Level-Editor/app/src/main](./app/src/main/)** folder with **Solution Explorer**.

**4. Executable location**
- The compiler files can be found in **is-Engine-Level-Editor/app/src/main/bin-vscode**.

---

## ![cb](https://i48.servimg.com/u/f48/20/16/75/27/icon_c10.png) Code::Blocks
**1. Prerequisites**

#### Windows
- [Code::Blocks 20.03 MinGW](https://sourceforge.net/projects/codeblocks/files/Binaries/20.03/Windows/codeblocks-20.03mingw-setup.exe/download)

#### Linux
- Code::Blocks 20.03

**2. Installation**
#### Windows
1. Compile SFML and put on **C:/ (C:/SFML_MinGW)**. The folder must have an **include** subfolder and a **lib** subfolder which contains the **static** (.a) and **Dynamic Link Library** (.dll) files.

#### Linux
1. Ensure the GCC Toolchain is installed (**sudo apt install build-essential**).
2. Run **sudo apt install libsfml-dev**. The SFML version you got will vary depending on the distro. 2.5.1 is included in [Ubuntu 19.04 Disco Dingo](http://cdimage.ubuntu.com/daily-live/current/HEADER.html) for example.

**3. Opening the project with the IDE:**

#### Windows
1. Run the file **open_codeblocks.bat** in the main directory.
2. Or open the file **is-Engine-windows.cbp** in the location **[is-Engine-Level-Editor/app/src/main](./app/src/main/)**

#### Linux
1. Execute this command in the main directory:
```bash
codeblocks "./app/src/main/is-Engine-linux.cbp"
```
2. Or open the file **is-Engine-linux.cbp** in the location **[is-Engine-Level-Editor/app/src/main](./app/src/main/)**.

**3. Executable location**
- The compiler files can be found in **is-Engine-Level-Editor/app/src/main/bin-codeblocks**.

---

## ![icon](https://i48.servimg.com/u/f48/20/16/75/27/icon10.png) Change application icon:
#### Windows
- To change the icon of the application you must go to the location **[is-Engine-Level-Editor/app/src/main/env/windows](./app/src/main/env/windows)** replace all the images **(Attention CMake uses the same resources).**

#### Linux
- To change the icon of the application you must go to the location **[is-Engine-Level-Editor/app/src/main/env/linux](./app/src/main/env/linux)**.

---

## Description of the project structure:
![header](./images/is_Engine_structure.png)
----------------------------
- The source files of the project can be found in the **[is-Engine-Level-Editor/app/src/main/cpp](./app/src/main/cpp/)** location.

#### 1. [main.cpp](./app/src/main/cpp/main.cpp) file
Contains the entry point of the program, inside there are two instructions :
- `game.play()`: Launches the engine rendering loop which allows to manage the introduction screen, main menu, level and game over.
- `game.basicSFMLmain()` (disabled by default): Launches the display of a classic SFML window. The implementation is in the **[basicSFMLmain.cpp](./app/src/main/cpp/basicSFMLmain.cpp)** file. *Very useful if you already have a project under development and you want to associate it with the engine. You can also use it to implement your own components to the engine.*

----------------------------
#### 2. [app_src](./app/src/main/cpp/app_src/) folder
Contains the source code of the game.
Description of these sub-directories:
- **[activity](./app/src/main/cpp/app_src/activity/)** : Contains the **[Activity](./app/src/main/cpp/app_src/activity/GameActivity.h)** class which allows the interaction of the different scenes of the game.
- **[config](./app/src/main/cpp/app_src/config/)** : Contains the **[GameConfig.h](./app/src/main/cpp/app_src/config/GameConfig.h)** file which allows to define the general parameters of the game.
- **[gamesystem_ext](./app/src/main/cpp/app_src/gamesystem_ext/)** : Contains **[GameSystemExtended](./app/src/main/cpp/app_src/gamesystem_ext/GameSystemExtended.h)** a class derived from **[GameSystem](./app/src/main/cpp/isEngine/system/function/GameSystem.h)** which allows to manipulate game data (save, load, ...).
- **[language](./app/src/main/cpp/app_src/language/)** : Contains the **[GameLanguage.h](./app/src/main/cpp/app_src/language/GameLanguage.h)** file which allows to manage everything related to game languages.
- **[levels](./app/src/main/cpp/app_src/levels/)** : Contains game levels and the **[Level.h](./app/src/main/cpp/app_src/levels/Level.h)** file which allows to integrate them into the game.
- **[objects](./app/src/main/cpp/app_src/objects/)** : Contains the objects that will be used in the different scenes.
- **[scenes](./app/src/main/cpp/app_src/scenes/)** : Contains the different scenes of the game (Introduction, Main menu, ...).

----------------------------
#### 3. [assets](./app/src/main/assets/) folder
Contains game resource files (music, sound sfx, image, ...)

----------------------------
#### 4. [isEngine](./app/src/main/cpp/isEngine/) folder
Contains the source code of the game engine

---

## How to contribute?
Here are some examples of how to contribute:
- have You developed a module and want it to be part of the engine? You are welcome!
- have You thought of a feature and you want it to be integrated into the engine? Do not hesitate to submit it to us with your **name** of course!
- You want to participate in the development of the engine? Well! welcome to the team!
- You have developed a game or application with the engine? We gladly accept it to publish it!
- You noticed a bug? Well done! Let us know Mr. Hacker!

## Contacts
  * For any help please contact me on my [email address](mailto:isdaouda.n@gmail.com)
  * You can follow me on Twitter for more informations on my activities [@Is Daouda Games](https://twitter.com/IsDaouda_Games)