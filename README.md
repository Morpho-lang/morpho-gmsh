# morpho-gmsh
Morpho bindings for the Gmsh API


## Installation instructions

1\. This extension requires `gmsh` to be installed as a dynamic library. Download the source code of the latest stable release of gmsh from https://gitlab.onelab.info/gmsh/gmsh/-/releases. Then, in a terminal, move to this directory.

    cd Downloads/gmsh

(assuming that is the name and location of the direcory.)

2\. Install dependencies of Gmsh. The two main dependencies are `fltk` for the Gmsh GUI and `opencascade` for mesh-generation using the OpenCasCade kernel. On MacOS, these can be installed using homebrew:

    brew install fltk
    brew install opencascade

On other operating systems, please refer to the dependencies section of [this wiki](https://gitlab.onelab.info/gmsh/gmsh/-/wikis/Gmsh-compilation) provided by Gmsh.

2\. Build gmsh from source with the dynamic build flag turned on:
    
    mkdir build
    cd build
    cmake -DENABLE_BUILD_DYNAMIC=1 ..
    make
    make install

The `make` command might need to be prefixed by `sudo`. Note that this step takes some time.

3\. Currently, this repository provides the API for the Gmsh version 4.13.0. If you wish to use an updated one, run this step, otherwise skip to the next step.

In [apigenerator/generate.py](./apigenerator/generate.py), set the new version of gmsh that you have downloaded, and run the file.

This downloads `apigenerator/CMakeLists.txt` (the Gmsh CMakeLists file) and `apigenerator/api/gen.py`. In addition, it should overwrite 3 files:

* `src/gmshapi.c` 

* `src/gmshapi.h`

* `share/help/gmshapi.md`

4\. Navigate to `morpho-gmsh`

5\. Build the extension by running the following:

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make install

Note that Morpho extension installs do not need `sudo` access. 

6\. Add the `morpho-gmsh` directory to `~/.morphopackages`

    cd ../
    pwd >> ~/.morphopackages

7\. Try out the test example

    cd examples
    morpho6 testgmshapi.morpho

For help with the high-level `gmsh` module, see [the gmsh help](./share/help/gmsh.md), or, in the Morpho CLI, type

    >?gmsh

or 

    >help gmsh

To access the API reference from within the Morpho CLI, type

    >?gmshapi

or 

    >help gmshapi

or see the newly generated `gmshapi` help under [share/help](./share/help/).

## Design

The design of this extension is documented [here](https://joshichaitanya3.github.io/gmsh-design-docs/).
