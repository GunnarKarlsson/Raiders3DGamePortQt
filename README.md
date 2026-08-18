# Raiders3DQt

Port to Qt of the **Raiders3D** game in the book *"Tricks of the 3D Game Programming Gurus"* by André LaMothe.

![Screen shots](https://github.com/GunnarKarlsson/Raiders3DQt/raw/master/screen_shot.png)

## How to Run

This is a qmake project. You need **Qt 5** with the Widgets and Multimedia modules (`QSound` is not available in Qt 6).

### Qt Creator

1. Open `Raiders3DPort.pro` in Qt Creator.
2. Choose a kit that uses Qt 5.
3. Build and run (Ctrl+R on Windows/Linux, Cmd+R on macOS).

### Command line

```sh
qmake Raiders3DPort.pro
make
./Raiders3DPort
```

On macOS the binary is an app bundle, so after `make` you can also run:

```sh
open Raiders3DPort.app
```

## How to Play

Shoot incoming TIE fighters before 100 of them escape. The game ends when 100 fighters have gotten away.

| Key | Action |
| --- | --- |
| **Left / Right / Up / Down** | Move the crosshairs |
| **Space** | Fire lasers |
| **W** | Increase flight speed |
| **S** | Decrease flight speed |

## License

The Qt port and other original work in this repository are licensed under the [MIT License](LICENSE).

That license does **not** cover the original Raiders3D source code (or its assets) from *Tricks of the 3D Game Programming Gurus*. Those remain under André LaMothe's and the publisher's copyright and license terms; see the book and its CD-ROM.
