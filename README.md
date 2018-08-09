# RogueTerm
Minimal toolkit for creating text-based roguelike games
<p align="center">
<img src="./img/screenshot.png" width="580px"></img>
</p>

## Compiling
Currently RogueTerm isn't properly implemented as a library and so running `make` will just create an executable from the existing `src/main.cpp` file.

To compile you'll need the SDL2 and SDL2_image development libraries. This can be installed on a debian based distro by typing: 
```bash
sudo apt-get install libsdl2-dev libsdl2-image-dev
```

Finally, run the following inside the root directory of the project to compile demo
```bash
make
```
