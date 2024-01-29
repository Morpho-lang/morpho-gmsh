
[comment]: # (Gmsh help)
[version]: # (0.6)

# Gmsh
[tagGmsh]: # (Gmsh)

The Gmsh module provides a Morpho interface to use the Gmsh API. 

[showsubtopics]: # (subtopics)

## GmshLoader
[tagGmshLoader]: # (GmshLoader)

The GmshLoader object initializes `gmsh` if it's not already and opens the file `filename` in the `gmsh` API.

    var gm = GmshLoader("gmshmesh.msh")

This doesn't launch the `gmsh` GUI, just loads the file.

[showsubtopics]: # (subtopics)

### launch

The `launch` method launches the `gmsh` GUI. Any modifications done to the mesh in the GUI will be stored even after closing the GUI.

### buildMorphoMesh

The `buildMorphoMesh` method creates a Morpho mesh from `gmsh`'s mesh and returns it. (Note: this will behave in an unexpected way if the `gmsh` mesh has any elements that are not simplicial (eg. quadrangles, pyramids, etc).)

### exportToMorpho

The `exportToMorpho` method takes an input `filename`, builds the Morpho mesh and exports it in the `.mesh` format.

    gm.exportToMorpho("morphomesh.mesh")

