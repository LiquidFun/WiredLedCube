# ArduinoLightCube

A small library for an Arduino Uno for a 3x3x3 LED light cube which has been wired to the GPIO pins.
It uses the [PlatformIO](https://platformio.org) framework, so it should be fairly portable. 

Below is a demonstration of a matrix-pattern (LEDs light up from top to bottom).

![](media/matrix-demo.gif)

## Installation

Install PlatformIO:

```
pip3 install platformio
```

Then connect your Arduino Uno. 
You might need to give permissions to be able to write to it: `sudo chmod 666 /dev/ttyACM0`.
You can find its name by running `pio device list`.

Clone this repository and `cd` to it.
Then upload the code to the Arduino:

```
pio run --target upload
```

Now to get into interactive mode you can run this:

```
pio device monitor
```

See below for key-bindings in interactive mode.

## Modes

### General key bindings:

| key | effect                 |
| --- | ---------------------- |
|   0 | switch to `FreezeMode` |
|   1 | switch to `MatrixMode` |
|   2 | switch to `PlayerMode` |

### `PlayerMode` key bindings:

|   key | effect                |
| ----- | --------------------- |
|     e | move forward  (y - 1) |
|     s | move left     (x - 1) |
|     d | move backward (y + 1) |
|     f | move right    (x + 1) |
| space | move up       (z + 1) |
|     t | toggle LED at current position (will take effect after moving)  |

### `MatrixMode` key bindings:

| key | effect              |
| --- | ------------------- |
|   - | decrease speed      |
|   + | increase speed      |
|   = | increase speed      |
|   < | decrease occupation |
|   > | increase occupation |

## GPIO Pins

Currently GPIO pins 0 to 8 are used for addressing the 9 columns and pins 10 to 12 are used to address the 3 layers. 
Pins 9 and 13 are not used.
As the 12 pins in use are not enough to create all 2^27 patterns, a 'cube-plexer' is implemented which quickly flashes each layer for 1 ms. Using this, every pattern can be created. This is hidden behind this library, so you can just write `cube.on(0, 0, 0)`, which would turn on one of the LEDs.
