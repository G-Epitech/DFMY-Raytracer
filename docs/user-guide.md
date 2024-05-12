![Baby gnu](https://upload.wikimedia.org/wikipedia/commons/4/42/Baby.gnu-800x800.png "Baby gnu")

# DFMY Raytracer User Guide

This guide serves as a comprehensive resource for users of the DFMY Raytracer, providing instructions on how to install the raytracer, customize its settings using command-line options, and utilize its features effectively.

1. [Installation](#installation)
    - [Prerequisites](#prerequisites)
    - [Installation Steps](#installation-steps)
2. [Usage](#usage)
    - [Command-Line Options](#command-line-options)
    - [Examples](#examples)
3. [Authors](#authors)

## Installation

### Prerequisites

Before installing the DFMY Raytracer, ensure you have the following dependencies installed:

- CMake
- Make
- Git

### Installation Steps

1. Clone the repository from GitHub:

```bash
git clone git@github.com:G-Epitech/DFMY-Raytracer.git
```

2. Navigate to the cloned directory:

```bash
cd DFMY-Raytracer
```

3. Build the raytracer using the following command:

```bash
make
```

## Usage

### Command-Line Options

The DFMY Raytracer provides several command-line options for customization:

```plaintext
USAGE: ./raytracer [options] <scene file>
DESCRIPTION:
  Raytracer is a program that generates images using ray tracing.
  It takes a scene file as input and generates an image based on the scene description.
  The generated image is saved as a PPM file.
ARGUMENTS:
  <scene file>                          Path to the scene file
OPTIONS:
  -g, --gui                             Launch the graphical user interface
  -h, --help                            Display this help message
  -p, --plugin-path <path = ./plugins>  Specify the path to the plugins directory
  -f, --format <format = ppm>           Specify the output image format. Supported formats: PPM, PNG, JPEG, BMP
  -t, --threads <count = 20>            Specify the number of threads to use.
  -r, --rays-per-pixel <count = 15>     Specify the number of rays per pixel.
  -b, --bounce <count = 30>             Specify the number of ray bounces.
  -F, --additional-frames <count = 15>  Specify the number of additional frames to render.
```

| Option                      | Description                                                                                                                                                   |
|-----------------------------|---------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `-g, --gui`                 | Launches the graphical user interface, allowing for a visual representation of the scene and its settings.                                                  |
| `-h, --help`                | Displays the help message, providing information on how to use the program and its command-line options.                                                    |
| `-p, --plugin-path <path>`  | Specifies the path to the plugins directory. Plugins can provide additional functionality or effects to the raytracer.                                      |
| `-f, --format <format>`     | Specifies the output image format. Supported formats include PPM (Portable Pixmap), PNG (Portable Network Graphics), JPEG (Joint Photographic Experts Group), and BMP (Bitmap). |
| `-t, --threads <count>`     | Specifies the number of threads to use for rendering. Increasing the number of threads can speed up rendering, especially on multi-core processors.            |
| `-r, --rays-per-pixel <count>` | Specifies the number of rays cast per pixel during rendering. Increasing this value can improve image quality, especially for complex scenes or when using effects like anti-aliasing. |
| `-b, --bounce <count>`      | Specifies the maximum number of ray bounces allowed per pixel. Increasing this value can improve the accuracy of reflections and refractions but may also increase rendering time. |
| `-F, --additional-frames <count>` | Specifies the number of additional frames to render. This option is useful for effects like motion blur or depth of field, where multiple frames are rendered and combined to create the final image. |


### Examples

- To render a scene using default settings:

```bash
./raytracer scene_file.cfg
```

- To render a scene and save the image in PNG format:

```bash
./raytracer -f png scene_file.cfg
```

- To launch the graphical user interface:

```bash
./raytracer -g scene_file.cfg
```

## Authors

DFMY Raytracer was developed by Dragos Suceveanu, Flavien Chenu, Matheo Coquet & Yann Masson.
