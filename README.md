# morpho-gmsh
Morpho bindings for the Gmsh API


## Installation instructions

1\. This extension requires `gmsh` to be installed as a dynamic library. Download the source code of the latest stable release of gmsh from https://gitlab.onelab.info/gmsh/gmsh/-/releases.

2\. Build gmsh from source with the dynamic build flag turned on:
    
    cd build
    cmake -DENABLE_BUILD_DYNAMIC=1 ..
    make
    make install

3\. In [apigenerator/generate.py](./apigenerator/generate.py), set the correct version of gmsh that you have downloaded, and run the file.

This downloads `apigenerator/CMakeLists.txt` (the Gmsh CMakeLists file) and `apigenerator/api/gen.py`. In addition, it should generate 3 files:

* `src/gmshapi.c` (already shipped with this repo)

* `src/gmshapi.h` (already shipped with this repo)

* `share/help/gmshapi.md`

4\. Navigate to `morpho-gmsh`

5\. Build the extension by running the following:

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make install

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
