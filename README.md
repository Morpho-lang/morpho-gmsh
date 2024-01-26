# morpho-gmsh
Morpho bindings for the Gmsh API


## Installation instructions

1. This extension requires `gmsh` to be installed as a dynamic library. Download the source code of the latest stable release of gmsh from https://gitlab.onelab.info/gmsh/gmsh/-/releases.

2. Build gmsh from source with the dynamic build flag turned on:
    
    cd build
    cmake -DENABLE_BUILD_DYNAMIC=1 ..
    make
    make install

3. In [apigenerator/generate.py](./apigenerator/generate.py), set the correct version of gmsh that you have downloaded, and run the file.

4. Navigate to morpho-gmsh

5. Build the extension by running the following:

    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make install

6. Try out the test example

    cd ../examples
    morpho6 testgmshapi.morpho

