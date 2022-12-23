![Space Warrior](https://github.com/Adrian-2105/SpaceWarrior/blob/main/assets/logo.png)

Space Warrior is a small *shoot 'em up* videogame that I presented as a project for a subject of my 1st year of university at Computer Engineering (so the code presented is quite improvable). This game takes as inspiration the games *1943* and *Gemini Wing* (taking from the latter some of its assets).

The game consists on controlling a spaceship that will have to survive for as long as possible while destroying enemies, dodging shots and collecting different *power UP's* (you have to discover the purpose of each one ;) ). The final goal of the game is to get the highest scores and be crowned in the highscore table.

# How to compile and play it

For the moment, this repository **only provides support for running on Linux, specifically Ubuntu**. It can also be compiled and executed on Windows and other Linux distributions by adapting the installation of the libraries and dependencies to each of them.

### Prerequisites

Before you can install it, you need to install the SDL library and some additional packages. A script is provided for self-installation by running the following command:

```bash
sudo bash install_dependencies.sh
```

**Note:** for other Linux distributions, modify this script accordingly to be able to install the same packages from the corresponding package manager.

### Compilation and execution

After having installed all prerequisites with the script, the compilation should be done correctly with the following command:

```bash
make
```

Finally, the executable will be generated and the game can be started by executing it with the following command:

```bash
./SpaceWarrior
```

# Controls

- **Menus**
  - `UP / DOWN`: scroll
  - `ENTER`: accept
  - `ESC`: Back
- **PARTING** **PARTING
  - `UP / DOWN / LEFT / RIGHT`: ship movement
  - `X`: fire bullets (unlimited)
  - `C`: fire bomb (limited)
  - `ESC`: pause menu
  
# Configuration

- This game is originally designed to be played at a resolution of 600x800. However, this can be changed by modifying the `hPantalla` macro of `main.c` to specify the height of the screen. The same can be done for the width, `wPantalla`, although this is not recommended. Modifying these parameters may affect the final game experience, resulting in sizes for which the game was not specifically designed.

- Any other parameters of the `main.c` macros can be changed if you want to play around with the project. Remember to always recompile after making any new changes.

# Screenshots

![Main Menu](https://github.com/Adrian-2105/SpaceWarrior/blob/main/docs/screenshots/menu.png)

![Game](https://github.com/Adrian-2105/SpaceWarrior/blob/main/docs/screenshots/partida.png)
