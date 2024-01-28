
#include <gmshc.h>
/** @file gmsh.c
*  @author Chaitanya Joshi
*
*  @brief Implements the Gmsh class
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <morpho.h>
#include <common.h>
#include <morpho/list.h>
#include <morpho/mesh.h>
// #include <mesh.h>
#include <morpho/matrix.h>
#include <math.h>
#include "gmshapi.h"


bool morpho_is_double(value arg) {
    return (MORPHO_ISINTEGER(arg) || MORPHO_ISFLOAT(arg));
}

double morpho_get_double(value arg) {
    double out;
    if (MORPHO_ISFLOAT(arg)) {
        out = MORPHO_GETFLOATVALUE(arg);
    } else if (MORPHO_ISINTEGER(arg)) {
        out = (double)MORPHO_GETINTEGERVALUE(arg);
    }
    return out;
}

void morphoGetIntStarFromList(vm* v, objectlist* l, int * list) {
    int len = list_length(l);
    bool success = true;
    value elementI;
    for (int i = 0; i<len; i++) {
        success = (success && list_getelement(l, i, &elementI));
        if (!MORPHO_ISINTEGER(elementI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR);
        }
        list[i] = MORPHO_GETINTEGERVALUE(elementI);
    }
    if (!success) {
        morpho_runtimeerror(v, GMSH_ARGS_ERROR);
    }

}

void morphoGetSizeTStarFromList(vm* v, objectlist* l, size_t * list) {
    int len = list_length(l);
    bool success = true;
    value elementI;
    for (int i = 0; i<len; i++) {
        success = (success && list_getelement(l, i, &elementI));
        if (!MORPHO_ISINTEGER(elementI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR);
        }
        list[i] = MORPHO_GETINTEGERVALUE(elementI);
    }
    if (!success) {
        morpho_runtimeerror(v, GMSH_ARGS_ERROR);
    }

}

void morphoGetDoubleStarFromList(vm* v, objectlist* l, double * list) {
    int len = list_length(l);
    bool success = true;
    value elementI;
    for (int i = 0; i<len; i++) {
        success = (success && list_getelement(l, i, &elementI));
        if (!morpho_is_double(elementI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR);
        }
        list[i] = morpho_get_double(elementI);
    }
    if (!success) {
        morpho_runtimeerror(v, GMSH_ARGS_ERROR);
    }

}

void morphoGetCharStarStarFromList(vm* v, objectlist* l, char const ** list) {
    int len = list_length(l);
    bool success = true;
    value elementI;
    for (int i = 0; i<len; i++) {
        success = (success && list_getelement(l, i, &elementI));
        if (!MORPHO_ISSTRING(elementI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR);
        }
        list[i] = MORPHO_GETCSTRING(elementI);
    }
    if (!success) {
        morpho_runtimeerror(v, GMSH_ARGS_ERROR);
    }

}


value MorphoGmshInitialize(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int readConfigFiles = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int run = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshInitialize(0, NULL,
                   readConfigFiles,
                   run,
                   &ierr);
    return MORPHO_NIL;
}

value MorphoGmshIsInitialized(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    int outval = gmshIsInitialized(&ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshFinalize(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFinalize(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshOpen(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshOpen(fileName,
             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshMerge(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshMerge(fileName,
              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshWrite(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshWrite(fileName,
              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshClear(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshClear(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshOptionSetNumber(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double cvalue = morpho_get_double(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshOptionSetNumber(name,
                        cvalue,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOptionGetNumber(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    double cvalue;
    int ierr;
    gmshOptionGetNumber(name,
                        &cvalue,
                        &ierr);
    return MORPHO_FLOAT(cvalue);
}

value MorphoGmshOptionSetString(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * cvalue = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshOptionSetString(name,
                        cvalue,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOptionGetString(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    char * cvalue;
    int ierr;
    gmshOptionGetString(name,
                        &cvalue,
                        &ierr);
    value cvalue_value = object_stringfromcstring(cvalue, strlen(cvalue));
    objectstring* cvalue_str = MORPHO_GETSTRING(cvalue_value);
    value out;
    if (cvalue_str) {
        out = MORPHO_OBJECT(cvalue_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshOptionSetColor(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int r = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int g = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int b = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int a = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    gmshOptionSetColor(name,
                       r,
                       g,
                       b,
                       a,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOptionGetColor(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int r;
    int g;
    int b;
    int a;
    int ierr;
    gmshOptionGetColor(name,
                       &r,
                       &g,
                       &b,
                       &a,
                       &ierr);
    value outval[4];
    outval[0] = MORPHO_OBJECT(r);
    outval[1] = MORPHO_OBJECT(g);
    outval[2] = MORPHO_OBJECT(b);
    outval[3] = MORPHO_OBJECT(a);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelAdd(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelAdd(name,
                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelRemove(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelRemove(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelList(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    char ** names;
    size_t names_n;
    int ierr;
    gmshModelList(&names, &names_n,
                  &ierr);
    value names_values[(int) names_n];
    for (size_t j=0; j<names_n; j++) { 
        names_values[j] = object_stringfromcstring(names[j], strlen(names[j]));
    }
    objectlist* names_list = object_newlist((int) names_n, names_values);
    value out;
    if (names_list) {
        out = MORPHO_OBJECT(names_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetCurrent(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    char * name;
    int ierr;
    gmshModelGetCurrent(&name,
                        &ierr);
    value name_value = object_stringfromcstring(name, strlen(name));
    objectstring* name_str = MORPHO_GETSTRING(name_value);
    value out;
    if (name_str) {
        out = MORPHO_OBJECT(name_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelSetCurrent(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelSetCurrent(name,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetFileName(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    char * fileName;
    int ierr;
    gmshModelGetFileName(&fileName,
                         &ierr);
    value fileName_value = object_stringfromcstring(fileName, strlen(fileName));
    objectstring* fileName_str = MORPHO_GETSTRING(fileName_value);
    value out;
    if (fileName_str) {
        out = MORPHO_OBJECT(fileName_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelSetFileName(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelSetFileName(fileName,
                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetEntities(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelGetEntities(&dimTags, &dimTags_n,
                         dim,
                         &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelSetEntityName(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelSetEntityName(dim,
                           tag,
                           name,
                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetEntityName(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    char * name;
    int ierr;
    gmshModelGetEntityName(dim,
                           tag,
                           &name,
                           &ierr);
    value name_value = object_stringfromcstring(name, strlen(name));
    objectstring* name_str = MORPHO_GETSTRING(name_value);
    value out;
    if (name_str) {
        out = MORPHO_OBJECT(name_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelRemoveEntityName(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelRemoveEntityName(name,
                              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetPhysicalGroups(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelGetPhysicalGroups(&dimTags, &dimTags_n,
                               dim,
                               &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetEntitiesForPhysicalGroup(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* tags;
    size_t tags_n;
    int ierr;
    gmshModelGetEntitiesForPhysicalGroup(dim,
                                         tag,
                                         &tags, &tags_n,
                                         &ierr);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    value out;
    if (tags_list) {
        out = MORPHO_OBJECT(tags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetEntitiesForPhysicalName(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelGetEntitiesForPhysicalName(name,
                                        &dimTags, &dimTags_n,
                                        &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetPhysicalGroupsForEntity(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* physicalTags;
    size_t physicalTags_n;
    int ierr;
    gmshModelGetPhysicalGroupsForEntity(dim,
                                        tag,
                                        &physicalTags, &physicalTags_n,
                                        &ierr);
    value physicalTags_value[(int) physicalTags_n];
    for (size_t j=0; j<physicalTags_n; j++) { 
        physicalTags_value[j] = MORPHO_INTEGER(physicalTags[j]);
    }
    objectlist* physicalTags_list = object_newlist((int) physicalTags_n, physicalTags_value);
    value out;
    if (physicalTags_list) {
        out = MORPHO_OBJECT(physicalTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelAddPhysicalGroup(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int tags_len = list_length(tags_list); 
    int tags[tags_len]; 
    morphoGetIntStarFromList(v, tags_list, tags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 3)); 
    int ierr;
    int outval = gmshModelAddPhysicalGroup(dim,
                              tags, sizeof(tags)/sizeof(tags[0]),
                              tag,
                              name,
                              &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelRemovePhysicalGroups(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelRemovePhysicalGroups(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelSetPhysicalName(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelSetPhysicalName(dim,
                             tag,
                             name,
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetPhysicalName(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    char * name;
    int ierr;
    gmshModelGetPhysicalName(dim,
                             tag,
                             &name,
                             &ierr);
    value name_value = object_stringfromcstring(name, strlen(name));
    objectstring* name_str = MORPHO_GETSTRING(name_value);
    value out;
    if (name_str) {
        out = MORPHO_OBJECT(name_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelRemovePhysicalName(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelRemovePhysicalName(name,
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelSetTag(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int newTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelSetTag(dim,
                    tag,
                    newTag,
                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetBoundary(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int combined = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int oriented = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recursive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelGetBoundary(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                         &outDimTags, &outDimTags_n,
                         combined,
                         oriented,
                         recursive,
                         &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetAdjacencies(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* upward;
    size_t upward_n;
    int* downward;
    size_t downward_n;
    int ierr;
    gmshModelGetAdjacencies(dim,
                            tag,
                            &upward, &upward_n,
                            &downward, &downward_n,
                            &ierr);
    value upward_value[(int) upward_n];
    for (size_t j=0; j<upward_n; j++) { 
        upward_value[j] = MORPHO_INTEGER(upward[j]);
    }
    objectlist* upward_list = object_newlist((int) upward_n, upward_value);
    value downward_value[(int) downward_n];
    for (size_t j=0; j<downward_n; j++) { 
        downward_value[j] = MORPHO_INTEGER(downward[j]);
    }
    objectlist* downward_list = object_newlist((int) downward_n, downward_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(upward_list);
    outval[1] = MORPHO_OBJECT(downward_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetEntitiesInBoundingBox(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double xmin = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ymin = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double zmin = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double xmax = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ymax = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double zmax = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelGetEntitiesInBoundingBox(xmin,
                                      ymin,
                                      zmin,
                                      xmax,
                                      ymax,
                                      zmax,
                                      &dimTags, &dimTags_n,
                                      dim,
                                      &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetBoundingBox(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double xmin;
    double ymin;
    double zmin;
    double xmax;
    double ymax;
    double zmax;
    int ierr;
    gmshModelGetBoundingBox(dim,
                            tag,
                            &xmin,
                            &ymin,
                            &zmin,
                            &xmax,
                            &ymax,
                            &zmax,
                            &ierr);
    value outval[6];
    outval[0] = MORPHO_OBJECT(xmin);
    outval[1] = MORPHO_OBJECT(ymin);
    outval[2] = MORPHO_OBJECT(zmin);
    outval[3] = MORPHO_OBJECT(xmax);
    outval[4] = MORPHO_OBJECT(ymax);
    outval[5] = MORPHO_OBJECT(zmax);
    objectlist* outlist = object_newlist(6, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetDimension(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    int outval = gmshModelGetDimension(&ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelAddDiscreteEntity(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* boundary_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int boundary_len = list_length(boundary_list); 
    int boundary[boundary_len]; 
    morphoGetIntStarFromList(v, boundary_list, boundary); 
    int ierr;
    int outval = gmshModelAddDiscreteEntity(dim,
                               tag,
                               boundary, sizeof(boundary)/sizeof(boundary[0]),
                               &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelRemoveEntities(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recursive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelRemoveEntities(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                            recursive,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetType(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    char * entityType;
    int ierr;
    gmshModelGetType(dim,
                     tag,
                     &entityType,
                     &ierr);
    value entityType_value = object_stringfromcstring(entityType, strlen(entityType));
    objectstring* entityType_str = MORPHO_GETSTRING(entityType_value);
    value out;
    if (entityType_str) {
        out = MORPHO_OBJECT(entityType_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetParent(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int parentDim;
    int parentTag;
    int ierr;
    gmshModelGetParent(dim,
                       tag,
                       &parentDim,
                       &parentTag,
                       &ierr);
    value outval[2];
    outval[0] = MORPHO_OBJECT(parentDim);
    outval[1] = MORPHO_OBJECT(parentTag);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetNumberOfPartitions(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    int outval = gmshModelGetNumberOfPartitions(&ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGetPartitions(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* partitions;
    size_t partitions_n;
    int ierr;
    gmshModelGetPartitions(dim,
                           tag,
                           &partitions, &partitions_n,
                           &ierr);
    value partitions_value[(int) partitions_n];
    for (size_t j=0; j<partitions_n; j++) { 
        partitions_value[j] = MORPHO_INTEGER(partitions[j]);
    }
    objectlist* partitions_list = object_newlist((int) partitions_n, partitions_value);
    value out;
    if (partitions_list) {
        out = MORPHO_OBJECT(partitions_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetValue(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelGetValue(dim,
                      tag,
                      parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                      &coord, &coord_n,
                      &ierr);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value out;
    if (coord_list) {
        out = MORPHO_OBJECT(coord_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetDerivative(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    double* derivatives;
    size_t derivatives_n;
    int ierr;
    gmshModelGetDerivative(dim,
                           tag,
                           parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                           &derivatives, &derivatives_n,
                           &ierr);
    value derivatives_value[(int) derivatives_n];
    for (size_t j=0; j<derivatives_n; j++) { 
        derivatives_value[j] = MORPHO_FLOAT(derivatives[j]);
    }
    objectlist* derivatives_list = object_newlist((int) derivatives_n, derivatives_value);
    value out;
    if (derivatives_list) {
        out = MORPHO_OBJECT(derivatives_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetSecondDerivative(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    double* derivatives;
    size_t derivatives_n;
    int ierr;
    gmshModelGetSecondDerivative(dim,
                                 tag,
                                 parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                                 &derivatives, &derivatives_n,
                                 &ierr);
    value derivatives_value[(int) derivatives_n];
    for (size_t j=0; j<derivatives_n; j++) { 
        derivatives_value[j] = MORPHO_FLOAT(derivatives[j]);
    }
    objectlist* derivatives_list = object_newlist((int) derivatives_n, derivatives_value);
    value out;
    if (derivatives_list) {
        out = MORPHO_OBJECT(derivatives_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetCurvature(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    double* curvatures;
    size_t curvatures_n;
    int ierr;
    gmshModelGetCurvature(dim,
                          tag,
                          parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                          &curvatures, &curvatures_n,
                          &ierr);
    value curvatures_value[(int) curvatures_n];
    for (size_t j=0; j<curvatures_n; j++) { 
        curvatures_value[j] = MORPHO_FLOAT(curvatures[j]);
    }
    objectlist* curvatures_list = object_newlist((int) curvatures_n, curvatures_value);
    value out;
    if (curvatures_list) {
        out = MORPHO_OBJECT(curvatures_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetPrincipalCurvatures(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    double* curvatureMax;
    size_t curvatureMax_n;
    double* curvatureMin;
    size_t curvatureMin_n;
    double* directionMax;
    size_t directionMax_n;
    double* directionMin;
    size_t directionMin_n;
    int ierr;
    gmshModelGetPrincipalCurvatures(tag,
                                    parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                                    &curvatureMax, &curvatureMax_n,
                                    &curvatureMin, &curvatureMin_n,
                                    &directionMax, &directionMax_n,
                                    &directionMin, &directionMin_n,
                                    &ierr);
    value curvatureMax_value[(int) curvatureMax_n];
    for (size_t j=0; j<curvatureMax_n; j++) { 
        curvatureMax_value[j] = MORPHO_FLOAT(curvatureMax[j]);
    }
    objectlist* curvatureMax_list = object_newlist((int) curvatureMax_n, curvatureMax_value);
    value curvatureMin_value[(int) curvatureMin_n];
    for (size_t j=0; j<curvatureMin_n; j++) { 
        curvatureMin_value[j] = MORPHO_FLOAT(curvatureMin[j]);
    }
    objectlist* curvatureMin_list = object_newlist((int) curvatureMin_n, curvatureMin_value);
    value directionMax_value[(int) directionMax_n];
    for (size_t j=0; j<directionMax_n; j++) { 
        directionMax_value[j] = MORPHO_FLOAT(directionMax[j]);
    }
    objectlist* directionMax_list = object_newlist((int) directionMax_n, directionMax_value);
    value directionMin_value[(int) directionMin_n];
    for (size_t j=0; j<directionMin_n; j++) { 
        directionMin_value[j] = MORPHO_FLOAT(directionMin[j]);
    }
    objectlist* directionMin_list = object_newlist((int) directionMin_n, directionMin_value);
    value outval[4];
    outval[0] = MORPHO_OBJECT(curvatureMax_list);
    outval[1] = MORPHO_OBJECT(curvatureMin_list);
    outval[2] = MORPHO_OBJECT(directionMax_list);
    outval[3] = MORPHO_OBJECT(directionMin_list);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetNormal(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    double* normals;
    size_t normals_n;
    int ierr;
    gmshModelGetNormal(tag,
                       parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                       &normals, &normals_n,
                       &ierr);
    value normals_value[(int) normals_n];
    for (size_t j=0; j<normals_n; j++) { 
        normals_value[j] = MORPHO_FLOAT(normals[j]);
    }
    objectlist* normals_list = object_newlist((int) normals_n, normals_value);
    value out;
    if (normals_list) {
        out = MORPHO_OBJECT(normals_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetParametrization(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    double* parametricCoord;
    size_t parametricCoord_n;
    int ierr;
    gmshModelGetParametrization(dim,
                                tag,
                                coord, sizeof(coord)/sizeof(coord[0]),
                                &parametricCoord, &parametricCoord_n,
                                &ierr);
    value parametricCoord_value[(int) parametricCoord_n];
    for (size_t j=0; j<parametricCoord_n; j++) { 
        parametricCoord_value[j] = MORPHO_FLOAT(parametricCoord[j]);
    }
    objectlist* parametricCoord_list = object_newlist((int) parametricCoord_n, parametricCoord_value);
    value out;
    if (parametricCoord_list) {
        out = MORPHO_OBJECT(parametricCoord_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetParametrizationBounds(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double* min;
    size_t min_n;
    double* max;
    size_t max_n;
    int ierr;
    gmshModelGetParametrizationBounds(dim,
                                      tag,
                                      &min, &min_n,
                                      &max, &max_n,
                                      &ierr);
    value min_value[(int) min_n];
    for (size_t j=0; j<min_n; j++) { 
        min_value[j] = MORPHO_FLOAT(min[j]);
    }
    objectlist* min_list = object_newlist((int) min_n, min_value);
    value max_value[(int) max_n];
    for (size_t j=0; j<max_n; j++) { 
        max_value[j] = MORPHO_FLOAT(max[j]);
    }
    objectlist* max_list = object_newlist((int) max_n, max_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(min_list);
    outval[1] = MORPHO_OBJECT(max_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelIsInside(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int parametric = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int ierr;
    int outval = gmshModelIsInside(dim,
                      tag,
                      coord, sizeof(coord)/sizeof(coord[0]),
                      parametric,
                      &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGetClosestPoint(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    double* closestCoord;
    size_t closestCoord_n;
    double* parametricCoord;
    size_t parametricCoord_n;
    int ierr;
    gmshModelGetClosestPoint(dim,
                             tag,
                             coord, sizeof(coord)/sizeof(coord[0]),
                             &closestCoord, &closestCoord_n,
                             &parametricCoord, &parametricCoord_n,
                             &ierr);
    value closestCoord_value[(int) closestCoord_n];
    for (size_t j=0; j<closestCoord_n; j++) { 
        closestCoord_value[j] = MORPHO_FLOAT(closestCoord[j]);
    }
    objectlist* closestCoord_list = object_newlist((int) closestCoord_n, closestCoord_value);
    value parametricCoord_value[(int) parametricCoord_n];
    for (size_t j=0; j<parametricCoord_n; j++) { 
        parametricCoord_value[j] = MORPHO_FLOAT(parametricCoord[j]);
    }
    objectlist* parametricCoord_list = object_newlist((int) parametricCoord_n, parametricCoord_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(closestCoord_list);
    outval[1] = MORPHO_OBJECT(parametricCoord_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelReparametrizeOnSurface(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int surfaceTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int which = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    double* surfaceParametricCoord;
    size_t surfaceParametricCoord_n;
    int ierr;
    gmshModelReparametrizeOnSurface(dim,
                                    tag,
                                    parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                                    surfaceTag,
                                    &surfaceParametricCoord, &surfaceParametricCoord_n,
                                    which,
                                    &ierr);
    value surfaceParametricCoord_value[(int) surfaceParametricCoord_n];
    for (size_t j=0; j<surfaceParametricCoord_n; j++) { 
        surfaceParametricCoord_value[j] = MORPHO_FLOAT(surfaceParametricCoord[j]);
    }
    objectlist* surfaceParametricCoord_list = object_newlist((int) surfaceParametricCoord_n, surfaceParametricCoord_value);
    value out;
    if (surfaceParametricCoord_list) {
        out = MORPHO_OBJECT(surfaceParametricCoord_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelSetVisibility(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int cvalue = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recursive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelSetVisibility(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                           cvalue,
                           recursive,
                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetVisibility(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int cvalue;
    int ierr;
    gmshModelGetVisibility(dim,
                           tag,
                           &cvalue,
                           &ierr);
    return MORPHO_INTEGER(cvalue);
}

value MorphoGmshModelSetVisibilityPerWindow(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int cvalue = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int windowIndex = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelSetVisibilityPerWindow(cvalue,
                                    windowIndex,
                                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelSetColor(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int r = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int g = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int b = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int a = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recursive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    int ierr;
    gmshModelSetColor(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                      r,
                      g,
                      b,
                      a,
                      recursive,
                      &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetColor(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int r;
    int g;
    int b;
    int a;
    int ierr;
    gmshModelGetColor(dim,
                      tag,
                      &r,
                      &g,
                      &b,
                      &a,
                      &ierr);
    value outval[4];
    outval[0] = MORPHO_OBJECT(r);
    outval[1] = MORPHO_OBJECT(g);
    outval[2] = MORPHO_OBJECT(b);
    outval[3] = MORPHO_OBJECT(a);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelSetCoordinates(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshModelSetCoordinates(tag,
                            x,
                            y,
                            z,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelSetAttribute(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* values_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int values_len = list_length(values_list); 
    char const * values[values_len]; 
    morphoGetCharStarStarFromList(v, values_list, values); 
    int ierr;
    gmshModelSetAttribute(name,
                          values, values_len,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGetAttribute(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    char ** values;
    size_t values_n;
    int ierr;
    gmshModelGetAttribute(name,
                          &values, &values_n,
                          &ierr);
    value values_values[(int) values_n];
    for (size_t j=0; j<values_n; j++) { 
        values_values[j] = object_stringfromcstring(values[j], strlen(values[j]));
    }
    objectlist* values_list = object_newlist((int) values_n, values_values);
    value out;
    if (values_list) {
        out = MORPHO_OBJECT(values_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGetAttributeNames(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    char ** names;
    size_t names_n;
    int ierr;
    gmshModelGetAttributeNames(&names, &names_n,
                               &ierr);
    value names_values[(int) names_n];
    for (size_t j=0; j<names_n; j++) { 
        names_values[j] = object_stringfromcstring(names[j], strlen(names[j]));
    }
    objectlist* names_list = object_newlist((int) names_n, names_values);
    value out;
    if (names_list) {
        out = MORPHO_OBJECT(names_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelRemoveAttribute(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelRemoveAttribute(name,
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGenerate(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshGenerate(dim,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshPartition(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numPart = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* partitions_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int partitions_len = list_length(partitions_list); 
    int partitions[partitions_len]; 
    morphoGetIntStarFromList(v, partitions_list, partitions); 
    int ierr;
    gmshModelMeshPartition(numPart,
                           elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                           partitions, sizeof(partitions)/sizeof(partitions[0]),
                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshUnpartition(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshUnpartition(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshOptimize(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * method = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int force = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int niter = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshOptimize(method,
                          force,
                          niter,
                          dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRecombine(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshRecombine(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRefine(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshRefine(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetOrder(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int order = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshSetOrder(order,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetLastEntityError(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelMeshGetLastEntityError(&dimTags, &dimTags_n,
                                    &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetLastNodeError(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    size_t* nodeTags;
    size_t nodeTags_n;
    int ierr;
    gmshModelMeshGetLastNodeError(&nodeTags, &nodeTags_n,
                                  &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value out;
    if (nodeTags_list) {
        out = MORPHO_OBJECT(nodeTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshClear(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshClear(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshReverse(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshReverse(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshReverseElements(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    int ierr;
    gmshModelMeshReverseElements(elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshAffineTransform(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* affineTransform_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int affineTransform_len = list_length(affineTransform_list); 
    double affineTransform[affineTransform_len]; 
    morphoGetDoubleStarFromList(v, affineTransform_list, affineTransform); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshAffineTransform(affineTransform, sizeof(affineTransform)/sizeof(affineTransform[0]),
                                 dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetNodes(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int includeBoundary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int returnParametricCoord = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    size_t* nodeTags;
    size_t nodeTags_n;
    double* coord;
    size_t coord_n;
    double* parametricCoord;
    size_t parametricCoord_n;
    int ierr;
    gmshModelMeshGetNodes(&nodeTags, &nodeTags_n,
                          &coord, &coord_n,
                          &parametricCoord, &parametricCoord_n,
                          dim,
                          tag,
                          includeBoundary,
                          returnParametricCoord,
                          &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value parametricCoord_value[(int) parametricCoord_n];
    for (size_t j=0; j<parametricCoord_n; j++) { 
        parametricCoord_value[j] = MORPHO_FLOAT(parametricCoord[j]);
    }
    objectlist* parametricCoord_list = object_newlist((int) parametricCoord_n, parametricCoord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(nodeTags_list);
    outval[1] = MORPHO_OBJECT(coord_list);
    outval[2] = MORPHO_OBJECT(parametricCoord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetNodesByElementType(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int returnParametricCoord = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    size_t* nodeTags;
    size_t nodeTags_n;
    double* coord;
    size_t coord_n;
    double* parametricCoord;
    size_t parametricCoord_n;
    int ierr;
    gmshModelMeshGetNodesByElementType(elementType,
                                       &nodeTags, &nodeTags_n,
                                       &coord, &coord_n,
                                       &parametricCoord, &parametricCoord_n,
                                       tag,
                                       returnParametricCoord,
                                       &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value parametricCoord_value[(int) parametricCoord_n];
    for (size_t j=0; j<parametricCoord_n; j++) { 
        parametricCoord_value[j] = MORPHO_FLOAT(parametricCoord[j]);
    }
    objectlist* parametricCoord_list = object_newlist((int) parametricCoord_n, parametricCoord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(nodeTags_list);
    outval[1] = MORPHO_OBJECT(coord_list);
    outval[2] = MORPHO_OBJECT(parametricCoord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetNode(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t nodeTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    double* coord;
    size_t coord_n;
    double* parametricCoord;
    size_t parametricCoord_n;
    int dim;
    int tag;
    int ierr;
    gmshModelMeshGetNode(nodeTag,
                         &coord, &coord_n,
                         &parametricCoord, &parametricCoord_n,
                         &dim,
                         &tag,
                         &ierr);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value parametricCoord_value[(int) parametricCoord_n];
    for (size_t j=0; j<parametricCoord_n; j++) { 
        parametricCoord_value[j] = MORPHO_FLOAT(parametricCoord[j]);
    }
    objectlist* parametricCoord_list = object_newlist((int) parametricCoord_n, parametricCoord_value);
    value outval[4];
    outval[0] = MORPHO_OBJECT(coord_list);
    outval[1] = MORPHO_OBJECT(parametricCoord_list);
    outval[2] = MORPHO_OBJECT(dim);
    outval[3] = MORPHO_OBJECT(tag);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshSetNode(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t nodeTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    int ierr;
    gmshModelMeshSetNode(nodeTag,
                         coord, sizeof(coord)/sizeof(coord[0]),
                         parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRebuildNodeCache(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int onlyIfNecessary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshRebuildNodeCache(onlyIfNecessary,
                                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRebuildElementCache(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int onlyIfNecessary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshRebuildElementCache(onlyIfNecessary,
                                     &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetNodesForPhysicalGroup(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    size_t* nodeTags;
    size_t nodeTags_n;
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelMeshGetNodesForPhysicalGroup(dim,
                                          tag,
                                          &nodeTags, &nodeTags_n,
                                          &coord, &coord_n,
                                          &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(nodeTags_list);
    outval[1] = MORPHO_OBJECT(coord_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetMaxNodeTag(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    size_t maxTag;
    int ierr;
    gmshModelMeshGetMaxNodeTag(&maxTag,
                               &ierr);
    return MORPHO_INTEGER((int) maxTag);
}

value MorphoGmshModelMeshAddNodes(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* nodeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int nodeTags_len = list_length(nodeTags_list); 
    size_t nodeTags[nodeTags_len]; 
    morphoGetSizeTStarFromList(v, nodeTags_list, nodeTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    int ierr;
    gmshModelMeshAddNodes(dim,
                          tag,
                          nodeTags, sizeof(nodeTags)/sizeof(nodeTags[0]),
                          coord, sizeof(coord)/sizeof(coord[0]),
                          parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshReclassifyNodes(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshReclassifyNodes(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRelocateNodes(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelMeshRelocateNodes(dim,
                               tag,
                               &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetElements(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* elementTypes;
    size_t elementTypes_n;
    size_t ** elementTags;
    size_t * elementTags_n;
    size_t elementTags_nn;
    size_t ** nodeTags;
    size_t * nodeTags_n;
    size_t nodeTags_nn;
    int ierr;
    gmshModelMeshGetElements(&elementTypes, &elementTypes_n,
                             &elementTags, &elementTags_n, &elementTags_nn,
                             &nodeTags, &nodeTags_n, &nodeTags_nn,
                             dim,
                             tag,
                             &ierr);
    value elementTypes_value[(int) elementTypes_n];
    for (size_t j=0; j<elementTypes_n; j++) { 
        elementTypes_value[j] = MORPHO_INTEGER(elementTypes[j]);
    }
    objectlist* elementTypes_list = object_newlist((int) elementTypes_n, elementTypes_value);
    objectlist* elementTagslistoflist = object_newlist(0, NULL);
    value elementTags_value[(int) elementTags_nn];
    for (size_t i=0; i<elementTags_nn; i++) { 
        value elementTags_i_value[(int) elementTags_n[i]];
        for (size_t j=0; j<elementTags_n[i]; j++) { 
            elementTags_i_value[j] = MORPHO_INTEGER(elementTags[i][j]);
        }
        objectlist* elementTagslistoflist_i = object_newlist((int) elementTags_n[i], elementTags_i_value);
        list_append(elementTagslistoflist, MORPHO_OBJECT(elementTagslistoflist_i));    } 
    objectlist* nodeTagslistoflist = object_newlist(0, NULL);
    value nodeTags_value[(int) nodeTags_nn];
    for (size_t i=0; i<nodeTags_nn; i++) { 
        value nodeTags_i_value[(int) nodeTags_n[i]];
        for (size_t j=0; j<nodeTags_n[i]; j++) { 
            nodeTags_i_value[j] = MORPHO_INTEGER(nodeTags[i][j]);
        }
        objectlist* nodeTagslistoflist_i = object_newlist((int) nodeTags_n[i], nodeTags_i_value);
        list_append(nodeTagslistoflist, MORPHO_OBJECT(nodeTagslistoflist_i));    } 
    value outval[3];
    outval[0] = MORPHO_OBJECT(elementTypes_list);
    outval[1] = MORPHO_OBJECT(elementTagslistoflist);
    outval[2] = MORPHO_OBJECT(nodeTagslistoflist);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElement(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t elementTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int elementType;
    size_t* nodeTags;
    size_t nodeTags_n;
    int dim;
    int tag;
    int ierr;
    gmshModelMeshGetElement(elementTag,
                            &elementType,
                            &nodeTags, &nodeTags_n,
                            &dim,
                            &tag,
                            &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value outval[4];
    outval[0] = MORPHO_OBJECT(elementType);
    outval[1] = MORPHO_OBJECT(nodeTags_list);
    outval[2] = MORPHO_OBJECT(dim);
    outval[3] = MORPHO_OBJECT(tag);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementByCoordinates(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int strict = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    size_t elementTag;
    int elementType;
    size_t* nodeTags;
    size_t nodeTags_n;
    double u;
    double cv;
    double w;
    int ierr;
    gmshModelMeshGetElementByCoordinates(x,
                                         y,
                                         z,
                                         &elementTag,
                                         &elementType,
                                         &nodeTags, &nodeTags_n,
                                         &u,
                                         &cv,
                                         &w,
                                         dim,
                                         strict,
                                         &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value outval[6];
    outval[0] = MORPHO_OBJECT(elementTag);
    outval[1] = MORPHO_OBJECT(elementType);
    outval[2] = MORPHO_OBJECT(nodeTags_list);
    outval[3] = MORPHO_OBJECT(u);
    outval[4] = MORPHO_OBJECT(cv);
    outval[5] = MORPHO_OBJECT(w);
    objectlist* outlist = object_newlist(6, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementsByCoordinates(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int strict = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    size_t* elementTags;
    size_t elementTags_n;
    int ierr;
    gmshModelMeshGetElementsByCoordinates(x,
                                          y,
                                          z,
                                          &elementTags, &elementTags_n,
                                          dim,
                                          strict,
                                          &ierr);
    value elementTags_value[(int) elementTags_n];
    for (size_t j=0; j<elementTags_n; j++) { 
        elementTags_value[j] = MORPHO_INTEGER(elementTags[j]);
    }
    objectlist* elementTags_list = object_newlist((int) elementTags_n, elementTags_value);
    value out;
    if (elementTags_list) {
        out = MORPHO_OBJECT(elementTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetLocalCoordinatesInElement(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t elementTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    double u;
    double cv;
    double w;
    int ierr;
    gmshModelMeshGetLocalCoordinatesInElement(elementTag,
                                              x,
                                              y,
                                              z,
                                              &u,
                                              &cv,
                                              &w,
                                              &ierr);
    value outval[3];
    outval[0] = MORPHO_OBJECT(u);
    outval[1] = MORPHO_OBJECT(cv);
    outval[2] = MORPHO_OBJECT(w);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementTypes(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* elementTypes;
    size_t elementTypes_n;
    int ierr;
    gmshModelMeshGetElementTypes(&elementTypes, &elementTypes_n,
                                 dim,
                                 tag,
                                 &ierr);
    value elementTypes_value[(int) elementTypes_n];
    for (size_t j=0; j<elementTypes_n; j++) { 
        elementTypes_value[j] = MORPHO_INTEGER(elementTypes[j]);
    }
    objectlist* elementTypes_list = object_newlist((int) elementTypes_n, elementTypes_value);
    value out;
    if (elementTypes_list) {
        out = MORPHO_OBJECT(elementTypes_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementType(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * familyName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int order = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int serendip = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelMeshGetElementType(familyName,
                                order,
                                serendip,
                                &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelMeshGetElementProperties(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    char * elementName;
    int dim;
    int order;
    int numNodes;
    double* localNodeCoord;
    size_t localNodeCoord_n;
    int numPrimaryNodes;
    int ierr;
    gmshModelMeshGetElementProperties(elementType,
                                      &elementName,
                                      &dim,
                                      &order,
                                      &numNodes,
                                      &localNodeCoord, &localNodeCoord_n,
                                      &numPrimaryNodes,
                                      &ierr);
    value elementName_value = object_stringfromcstring(elementName, strlen(elementName));
    objectstring* elementName_str = MORPHO_GETSTRING(elementName_value);
    value localNodeCoord_value[(int) localNodeCoord_n];
    for (size_t j=0; j<localNodeCoord_n; j++) { 
        localNodeCoord_value[j] = MORPHO_FLOAT(localNodeCoord[j]);
    }
    objectlist* localNodeCoord_list = object_newlist((int) localNodeCoord_n, localNodeCoord_value);
    value outval[6];
    outval[0] = MORPHO_OBJECT(elementName_str);
    outval[1] = MORPHO_OBJECT(dim);
    outval[2] = MORPHO_OBJECT(order);
    outval[3] = MORPHO_OBJECT(numNodes);
    outval[4] = MORPHO_OBJECT(localNodeCoord_list);
    outval[5] = MORPHO_OBJECT(numPrimaryNodes);
    objectlist* outlist = object_newlist(6, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementsByType(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    size_t* elementTags;
    size_t elementTags_n;
    size_t* nodeTags;
    size_t nodeTags_n;
    int ierr;
    gmshModelMeshGetElementsByType(elementType,
                                   &elementTags, &elementTags_n,
                                   &nodeTags, &nodeTags_n,
                                   tag,
                                   task,
                                   numTasks,
                                   &ierr);
    value elementTags_value[(int) elementTags_n];
    for (size_t j=0; j<elementTags_n; j++) { 
        elementTags_value[j] = MORPHO_INTEGER(elementTags[j]);
    }
    objectlist* elementTags_list = object_newlist((int) elementTags_n, elementTags_value);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(elementTags_list);
    outval[1] = MORPHO_OBJECT(nodeTags_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetMaxElementTag(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    size_t maxTag;
    int ierr;
    gmshModelMeshGetMaxElementTag(&maxTag,
                                  &ierr);
    return MORPHO_INTEGER((int) maxTag);
}

value MorphoGmshModelMeshPreallocateElementsByType(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int nodeTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    size_t* elementTags;
    size_t elementTags_n;
    size_t* nodeTags;
    size_t nodeTags_n;
    int ierr;
    gmshModelMeshPreallocateElementsByType(elementType,
                                           elementTag,
                                           nodeTag,
                                           &elementTags, &elementTags_n,
                                           &nodeTags, &nodeTags_n,
                                           tag,
                                           &ierr);
    value elementTags_value[(int) elementTags_n];
    for (size_t j=0; j<elementTags_n; j++) { 
        elementTags_value[j] = MORPHO_INTEGER(elementTags[j]);
    }
    objectlist* elementTags_list = object_newlist((int) elementTags_n, elementTags_value);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(elementTags_list);
    outval[1] = MORPHO_OBJECT(nodeTags_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementQualities(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * qualityName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    double* elementsQuality;
    size_t elementsQuality_n;
    int ierr;
    gmshModelMeshGetElementQualities(elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                                     &elementsQuality, &elementsQuality_n,
                                     qualityName,
                                     task,
                                     numTasks,
                                     &ierr);
    value elementsQuality_value[(int) elementsQuality_n];
    for (size_t j=0; j<elementsQuality_n; j++) { 
        elementsQuality_value[j] = MORPHO_FLOAT(elementsQuality[j]);
    }
    objectlist* elementsQuality_list = object_newlist((int) elementsQuality_n, elementsQuality_value);
    value out;
    if (elementsQuality_list) {
        out = MORPHO_OBJECT(elementsQuality_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshAddElements(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTypes_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int elementTypes_len = list_length(elementTypes_list); 
    int elementTypes[elementTypes_len]; 
    morphoGetIntStarFromList(v, elementTypes_list, elementTypes); 

    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) { morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3));
    size_t elementTags_nn = (size_t) list_length(elementTags_list);
    size_t * elementTags_n;
    size_t ** elementTags;
    value elementTags_elI;
    objectlist * elementTags_li;
    bool elementTags_success;
    for (size_t i=0; i<elementTags_nn; i++) {
        elementTags_success = (elementTags_success && list_getelement(elementTags_list, i, &elementTags_elI));
        if (!MORPHO_ISLIST(elementTags_elI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR); 
            return MORPHO_NIL; 
        }
        elementTags_li = MORPHO_GETLIST(elementTags_elI);
        elementTags_n[i] = (size_t) list_length(elementTags_li);
        morphoGetSizeTStarFromList(v, elementTags_li, elementTags[i]);
    }
        
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) { morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* nodeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4));
    size_t nodeTags_nn = (size_t) list_length(nodeTags_list);
    size_t * nodeTags_n;
    size_t ** nodeTags;
    value nodeTags_elI;
    objectlist * nodeTags_li;
    bool nodeTags_success;
    for (size_t i=0; i<nodeTags_nn; i++) {
        nodeTags_success = (nodeTags_success && list_getelement(nodeTags_list, i, &nodeTags_elI));
        if (!MORPHO_ISLIST(nodeTags_elI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR); 
            return MORPHO_NIL; 
        }
        nodeTags_li = MORPHO_GETLIST(nodeTags_elI);
        nodeTags_n[i] = (size_t) list_length(nodeTags_li);
        morphoGetSizeTStarFromList(v, nodeTags_li, nodeTags[i]);
    }
            int ierr;
    gmshModelMeshAddElements(dim,
                             tag,
                             elementTypes, sizeof(elementTypes)/sizeof(elementTypes[0]),
                             elementTags, elementTags_n, elementTags_nn,
                             nodeTags, nodeTags_n, nodeTags_nn,
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshAddElementsByType(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* nodeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int nodeTags_len = list_length(nodeTags_list); 
    size_t nodeTags[nodeTags_len]; 
    morphoGetSizeTStarFromList(v, nodeTags_list, nodeTags); 
    int ierr;
    gmshModelMeshAddElementsByType(tag,
                                   elementType,
                                   elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                                   nodeTags, sizeof(nodeTags)/sizeof(nodeTags[0]),
                                   &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetIntegrationPoints(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * integrationType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    double* localCoord;
    size_t localCoord_n;
    double* weights;
    size_t weights_n;
    int ierr;
    gmshModelMeshGetIntegrationPoints(elementType,
                                      integrationType,
                                      &localCoord, &localCoord_n,
                                      &weights, &weights_n,
                                      &ierr);
    value localCoord_value[(int) localCoord_n];
    for (size_t j=0; j<localCoord_n; j++) { 
        localCoord_value[j] = MORPHO_FLOAT(localCoord[j]);
    }
    objectlist* localCoord_list = object_newlist((int) localCoord_n, localCoord_value);
    value weights_value[(int) weights_n];
    for (size_t j=0; j<weights_n; j++) { 
        weights_value[j] = MORPHO_FLOAT(weights[j]);
    }
    objectlist* weights_list = object_newlist((int) weights_n, weights_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(localCoord_list);
    outval[1] = MORPHO_OBJECT(weights_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetJacobians(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* localCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int localCoord_len = list_length(localCoord_list); 
    double localCoord[localCoord_len]; 
    morphoGetDoubleStarFromList(v, localCoord_list, localCoord); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    double* jacobians;
    size_t jacobians_n;
    double* determinants;
    size_t determinants_n;
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelMeshGetJacobians(elementType,
                              localCoord, sizeof(localCoord)/sizeof(localCoord[0]),
                              &jacobians, &jacobians_n,
                              &determinants, &determinants_n,
                              &coord, &coord_n,
                              tag,
                              task,
                              numTasks,
                              &ierr);
    value jacobians_value[(int) jacobians_n];
    for (size_t j=0; j<jacobians_n; j++) { 
        jacobians_value[j] = MORPHO_FLOAT(jacobians[j]);
    }
    objectlist* jacobians_list = object_newlist((int) jacobians_n, jacobians_value);
    value determinants_value[(int) determinants_n];
    for (size_t j=0; j<determinants_n; j++) { 
        determinants_value[j] = MORPHO_FLOAT(determinants[j]);
    }
    objectlist* determinants_list = object_newlist((int) determinants_n, determinants_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(jacobians_list);
    outval[1] = MORPHO_OBJECT(determinants_list);
    outval[2] = MORPHO_OBJECT(coord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshPreallocateJacobians(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numEvaluationPoints = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int allocateJacobians = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int allocateDeterminants = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int allocateCoord = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    double* jacobians;
    size_t jacobians_n;
    double* determinants;
    size_t determinants_n;
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelMeshPreallocateJacobians(elementType,
                                      numEvaluationPoints,
                                      allocateJacobians,
                                      allocateDeterminants,
                                      allocateCoord,
                                      &jacobians, &jacobians_n,
                                      &determinants, &determinants_n,
                                      &coord, &coord_n,
                                      tag,
                                      &ierr);
    value jacobians_value[(int) jacobians_n];
    for (size_t j=0; j<jacobians_n; j++) { 
        jacobians_value[j] = MORPHO_FLOAT(jacobians[j]);
    }
    objectlist* jacobians_list = object_newlist((int) jacobians_n, jacobians_value);
    value determinants_value[(int) determinants_n];
    for (size_t j=0; j<determinants_n; j++) { 
        determinants_value[j] = MORPHO_FLOAT(determinants[j]);
    }
    objectlist* determinants_list = object_newlist((int) determinants_n, determinants_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(jacobians_list);
    outval[1] = MORPHO_OBJECT(determinants_list);
    outval[2] = MORPHO_OBJECT(coord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetJacobian(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t elementTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* localCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int localCoord_len = list_length(localCoord_list); 
    double localCoord[localCoord_len]; 
    morphoGetDoubleStarFromList(v, localCoord_list, localCoord); 
    double* jacobians;
    size_t jacobians_n;
    double* determinants;
    size_t determinants_n;
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelMeshGetJacobian(elementTag,
                             localCoord, sizeof(localCoord)/sizeof(localCoord[0]),
                             &jacobians, &jacobians_n,
                             &determinants, &determinants_n,
                             &coord, &coord_n,
                             &ierr);
    value jacobians_value[(int) jacobians_n];
    for (size_t j=0; j<jacobians_n; j++) { 
        jacobians_value[j] = MORPHO_FLOAT(jacobians[j]);
    }
    objectlist* jacobians_list = object_newlist((int) jacobians_n, jacobians_value);
    value determinants_value[(int) determinants_n];
    for (size_t j=0; j<determinants_n; j++) { 
        determinants_value[j] = MORPHO_FLOAT(determinants[j]);
    }
    objectlist* determinants_list = object_newlist((int) determinants_n, determinants_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(jacobians_list);
    outval[1] = MORPHO_OBJECT(determinants_list);
    outval[2] = MORPHO_OBJECT(coord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetBasisFunctions(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* localCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int localCoord_len = list_length(localCoord_list); 
    double localCoord[localCoord_len]; 
    morphoGetDoubleStarFromList(v, localCoord_list, localCoord); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wantedOrientations_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int wantedOrientations_len = list_length(wantedOrientations_list); 
    int wantedOrientations[wantedOrientations_len]; 
    morphoGetIntStarFromList(v, wantedOrientations_list, wantedOrientations); 
    int numComponents;
    double* basisFunctions;
    size_t basisFunctions_n;
    int numOrientations;
    int ierr;
    gmshModelMeshGetBasisFunctions(elementType,
                                   localCoord, sizeof(localCoord)/sizeof(localCoord[0]),
                                   functionSpaceType,
                                   &numComponents,
                                   &basisFunctions, &basisFunctions_n,
                                   &numOrientations,
                                   wantedOrientations, sizeof(wantedOrientations)/sizeof(wantedOrientations[0]),
                                   &ierr);
    value basisFunctions_value[(int) basisFunctions_n];
    for (size_t j=0; j<basisFunctions_n; j++) { 
        basisFunctions_value[j] = MORPHO_FLOAT(basisFunctions[j]);
    }
    objectlist* basisFunctions_list = object_newlist((int) basisFunctions_n, basisFunctions_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(numComponents);
    outval[1] = MORPHO_OBJECT(basisFunctions_list);
    outval[2] = MORPHO_OBJECT(numOrientations);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetBasisFunctionsOrientation(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int* basisFunctionsOrientation;
    size_t basisFunctionsOrientation_n;
    int ierr;
    gmshModelMeshGetBasisFunctionsOrientation(elementType,
                                              functionSpaceType,
                                              &basisFunctionsOrientation, &basisFunctionsOrientation_n,
                                              tag,
                                              task,
                                              numTasks,
                                              &ierr);
    value basisFunctionsOrientation_value[(int) basisFunctionsOrientation_n];
    for (size_t j=0; j<basisFunctionsOrientation_n; j++) { 
        basisFunctionsOrientation_value[j] = MORPHO_INTEGER(basisFunctionsOrientation[j]);
    }
    objectlist* basisFunctionsOrientation_list = object_newlist((int) basisFunctionsOrientation_n, basisFunctionsOrientation_value);
    value out;
    if (basisFunctionsOrientation_list) {
        out = MORPHO_OBJECT(basisFunctionsOrientation_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetBasisFunctionsOrientationForElement(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t elementTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int basisFunctionsOrientation;
    int ierr;
    gmshModelMeshGetBasisFunctionsOrientationForElement(elementTag,
                                                        functionSpaceType,
                                                        &basisFunctionsOrientation,
                                                        &ierr);
    return MORPHO_INTEGER(basisFunctionsOrientation);
}

value MorphoGmshModelMeshGetNumberOfOrientations(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelMeshGetNumberOfOrientations(elementType,
                                         functionSpaceType,
                                         &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelMeshPreallocateBasisFunctionsOrientation(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* basisFunctionsOrientation;
    size_t basisFunctionsOrientation_n;
    int ierr;
    gmshModelMeshPreallocateBasisFunctionsOrientation(elementType,
                                                      &basisFunctionsOrientation, &basisFunctionsOrientation_n,
                                                      tag,
                                                      &ierr);
    value basisFunctionsOrientation_value[(int) basisFunctionsOrientation_n];
    for (size_t j=0; j<basisFunctionsOrientation_n; j++) { 
        basisFunctionsOrientation_value[j] = MORPHO_INTEGER(basisFunctionsOrientation[j]);
    }
    objectlist* basisFunctionsOrientation_list = object_newlist((int) basisFunctionsOrientation_n, basisFunctionsOrientation_value);
    value out;
    if (basisFunctionsOrientation_list) {
        out = MORPHO_OBJECT(basisFunctionsOrientation_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetEdges(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* nodeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int nodeTags_len = list_length(nodeTags_list); 
    size_t nodeTags[nodeTags_len]; 
    morphoGetSizeTStarFromList(v, nodeTags_list, nodeTags); 
    size_t* edgeTags;
    size_t edgeTags_n;
    int* edgeOrientations;
    size_t edgeOrientations_n;
    int ierr;
    gmshModelMeshGetEdges(nodeTags, sizeof(nodeTags)/sizeof(nodeTags[0]),
                          &edgeTags, &edgeTags_n,
                          &edgeOrientations, &edgeOrientations_n,
                          &ierr);
    value edgeTags_value[(int) edgeTags_n];
    for (size_t j=0; j<edgeTags_n; j++) { 
        edgeTags_value[j] = MORPHO_INTEGER(edgeTags[j]);
    }
    objectlist* edgeTags_list = object_newlist((int) edgeTags_n, edgeTags_value);
    value edgeOrientations_value[(int) edgeOrientations_n];
    for (size_t j=0; j<edgeOrientations_n; j++) { 
        edgeOrientations_value[j] = MORPHO_INTEGER(edgeOrientations[j]);
    }
    objectlist* edgeOrientations_list = object_newlist((int) edgeOrientations_n, edgeOrientations_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(edgeTags_list);
    outval[1] = MORPHO_OBJECT(edgeOrientations_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetFaces(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int faceType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* nodeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int nodeTags_len = list_length(nodeTags_list); 
    size_t nodeTags[nodeTags_len]; 
    morphoGetSizeTStarFromList(v, nodeTags_list, nodeTags); 
    size_t* faceTags;
    size_t faceTags_n;
    int* faceOrientations;
    size_t faceOrientations_n;
    int ierr;
    gmshModelMeshGetFaces(faceType,
                          nodeTags, sizeof(nodeTags)/sizeof(nodeTags[0]),
                          &faceTags, &faceTags_n,
                          &faceOrientations, &faceOrientations_n,
                          &ierr);
    value faceTags_value[(int) faceTags_n];
    for (size_t j=0; j<faceTags_n; j++) { 
        faceTags_value[j] = MORPHO_INTEGER(faceTags[j]);
    }
    objectlist* faceTags_list = object_newlist((int) faceTags_n, faceTags_value);
    value faceOrientations_value[(int) faceOrientations_n];
    for (size_t j=0; j<faceOrientations_n; j++) { 
        faceOrientations_value[j] = MORPHO_INTEGER(faceOrientations[j]);
    }
    objectlist* faceOrientations_list = object_newlist((int) faceOrientations_n, faceOrientations_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(faceTags_list);
    outval[1] = MORPHO_OBJECT(faceOrientations_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshCreateEdges(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshCreateEdges(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshCreateFaces(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshCreateFaces(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetAllEdges(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    size_t* edgeTags;
    size_t edgeTags_n;
    size_t* edgeNodes;
    size_t edgeNodes_n;
    int ierr;
    gmshModelMeshGetAllEdges(&edgeTags, &edgeTags_n,
                             &edgeNodes, &edgeNodes_n,
                             &ierr);
    value edgeTags_value[(int) edgeTags_n];
    for (size_t j=0; j<edgeTags_n; j++) { 
        edgeTags_value[j] = MORPHO_INTEGER(edgeTags[j]);
    }
    objectlist* edgeTags_list = object_newlist((int) edgeTags_n, edgeTags_value);
    value edgeNodes_value[(int) edgeNodes_n];
    for (size_t j=0; j<edgeNodes_n; j++) { 
        edgeNodes_value[j] = MORPHO_INTEGER(edgeNodes[j]);
    }
    objectlist* edgeNodes_list = object_newlist((int) edgeNodes_n, edgeNodes_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(edgeTags_list);
    outval[1] = MORPHO_OBJECT(edgeNodes_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetAllFaces(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int faceType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    size_t* faceTags;
    size_t faceTags_n;
    size_t* faceNodes;
    size_t faceNodes_n;
    int ierr;
    gmshModelMeshGetAllFaces(faceType,
                             &faceTags, &faceTags_n,
                             &faceNodes, &faceNodes_n,
                             &ierr);
    value faceTags_value[(int) faceTags_n];
    for (size_t j=0; j<faceTags_n; j++) { 
        faceTags_value[j] = MORPHO_INTEGER(faceTags[j]);
    }
    objectlist* faceTags_list = object_newlist((int) faceTags_n, faceTags_value);
    value faceNodes_value[(int) faceNodes_n];
    for (size_t j=0; j<faceNodes_n; j++) { 
        faceNodes_value[j] = MORPHO_INTEGER(faceNodes[j]);
    }
    objectlist* faceNodes_list = object_newlist((int) faceNodes_n, faceNodes_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(faceTags_list);
    outval[1] = MORPHO_OBJECT(faceNodes_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshAddEdges(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* edgeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int edgeTags_len = list_length(edgeTags_list); 
    size_t edgeTags[edgeTags_len]; 
    morphoGetSizeTStarFromList(v, edgeTags_list, edgeTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* edgeNodes_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int edgeNodes_len = list_length(edgeNodes_list); 
    size_t edgeNodes[edgeNodes_len]; 
    morphoGetSizeTStarFromList(v, edgeNodes_list, edgeNodes); 
    int ierr;
    gmshModelMeshAddEdges(edgeTags, sizeof(edgeTags)/sizeof(edgeTags[0]),
                          edgeNodes, sizeof(edgeNodes)/sizeof(edgeNodes[0]),
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshAddFaces(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int faceType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* faceTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int faceTags_len = list_length(faceTags_list); 
    size_t faceTags[faceTags_len]; 
    morphoGetSizeTStarFromList(v, faceTags_list, faceTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* faceNodes_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int faceNodes_len = list_length(faceNodes_list); 
    size_t faceNodes[faceNodes_len]; 
    morphoGetSizeTStarFromList(v, faceNodes_list, faceNodes); 
    int ierr;
    gmshModelMeshAddFaces(faceType,
                          faceTags, sizeof(faceTags)/sizeof(faceTags[0]),
                          faceNodes, sizeof(faceNodes)/sizeof(faceNodes[0]),
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetKeys(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int returnCoord = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int* typeKeys;
    size_t typeKeys_n;
    size_t* entityKeys;
    size_t entityKeys_n;
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelMeshGetKeys(elementType,
                         functionSpaceType,
                         &typeKeys, &typeKeys_n,
                         &entityKeys, &entityKeys_n,
                         &coord, &coord_n,
                         tag,
                         returnCoord,
                         &ierr);
    value typeKeys_value[(int) typeKeys_n];
    for (size_t j=0; j<typeKeys_n; j++) { 
        typeKeys_value[j] = MORPHO_INTEGER(typeKeys[j]);
    }
    objectlist* typeKeys_list = object_newlist((int) typeKeys_n, typeKeys_value);
    value entityKeys_value[(int) entityKeys_n];
    for (size_t j=0; j<entityKeys_n; j++) { 
        entityKeys_value[j] = MORPHO_INTEGER(entityKeys[j]);
    }
    objectlist* entityKeys_list = object_newlist((int) entityKeys_n, entityKeys_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(typeKeys_list);
    outval[1] = MORPHO_OBJECT(entityKeys_list);
    outval[2] = MORPHO_OBJECT(coord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetKeysForElement(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t elementTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int returnCoord = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int* typeKeys;
    size_t typeKeys_n;
    size_t* entityKeys;
    size_t entityKeys_n;
    double* coord;
    size_t coord_n;
    int ierr;
    gmshModelMeshGetKeysForElement(elementTag,
                                   functionSpaceType,
                                   &typeKeys, &typeKeys_n,
                                   &entityKeys, &entityKeys_n,
                                   &coord, &coord_n,
                                   returnCoord,
                                   &ierr);
    value typeKeys_value[(int) typeKeys_n];
    for (size_t j=0; j<typeKeys_n; j++) { 
        typeKeys_value[j] = MORPHO_INTEGER(typeKeys[j]);
    }
    objectlist* typeKeys_list = object_newlist((int) typeKeys_n, typeKeys_value);
    value entityKeys_value[(int) entityKeys_n];
    for (size_t j=0; j<entityKeys_n; j++) { 
        entityKeys_value[j] = MORPHO_INTEGER(entityKeys[j]);
    }
    objectlist* entityKeys_list = object_newlist((int) entityKeys_n, entityKeys_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value outval[3];
    outval[0] = MORPHO_OBJECT(typeKeys_list);
    outval[1] = MORPHO_OBJECT(entityKeys_list);
    outval[2] = MORPHO_OBJECT(coord_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetNumberOfKeys(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelMeshGetNumberOfKeys(elementType,
                                 functionSpaceType,
                                 &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelMeshGetKeysInformation(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* typeKeys_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int typeKeys_len = list_length(typeKeys_list); 
    int typeKeys[typeKeys_len]; 
    morphoGetIntStarFromList(v, typeKeys_list, typeKeys); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* entityKeys_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int entityKeys_len = list_length(entityKeys_list); 
    size_t entityKeys[entityKeys_len]; 
    morphoGetSizeTStarFromList(v, entityKeys_list, entityKeys); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 3)); 
    int* infoKeys;
    size_t infoKeys_n;
    int ierr;
    gmshModelMeshGetKeysInformation(typeKeys, sizeof(typeKeys)/sizeof(typeKeys[0]),
                                    entityKeys, sizeof(entityKeys)/sizeof(entityKeys[0]),
                                    elementType,
                                    functionSpaceType,
                                    &infoKeys, &infoKeys_n,
                                    &ierr);
    value infoKeys_value[(int) infoKeys_n];
    for (size_t j=0; j<infoKeys_n; j++) { 
        infoKeys_value[j] = MORPHO_INTEGER(infoKeys[j]);
    }
    objectlist* infoKeys_list = object_newlist((int) infoKeys_n, infoKeys_value);
    value out;
    if (infoKeys_list) {
        out = MORPHO_OBJECT(infoKeys_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetBarycenters(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int fast = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int primary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    double* barycenters;
    size_t barycenters_n;
    int ierr;
    gmshModelMeshGetBarycenters(elementType,
                                tag,
                                fast,
                                primary,
                                &barycenters, &barycenters_n,
                                task,
                                numTasks,
                                &ierr);
    value barycenters_value[(int) barycenters_n];
    for (size_t j=0; j<barycenters_n; j++) { 
        barycenters_value[j] = MORPHO_FLOAT(barycenters[j]);
    }
    objectlist* barycenters_list = object_newlist((int) barycenters_n, barycenters_value);
    value out;
    if (barycenters_list) {
        out = MORPHO_OBJECT(barycenters_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshPreallocateBarycenters(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double* barycenters;
    size_t barycenters_n;
    int ierr;
    gmshModelMeshPreallocateBarycenters(elementType,
                                        &barycenters, &barycenters_n,
                                        tag,
                                        &ierr);
    value barycenters_value[(int) barycenters_n];
    for (size_t j=0; j<barycenters_n; j++) { 
        barycenters_value[j] = MORPHO_FLOAT(barycenters[j]);
    }
    objectlist* barycenters_list = object_newlist((int) barycenters_n, barycenters_value);
    value out;
    if (barycenters_list) {
        out = MORPHO_OBJECT(barycenters_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementEdgeNodes(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int primary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    size_t* nodeTags;
    size_t nodeTags_n;
    int ierr;
    gmshModelMeshGetElementEdgeNodes(elementType,
                                     &nodeTags, &nodeTags_n,
                                     tag,
                                     primary,
                                     task,
                                     numTasks,
                                     &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value out;
    if (nodeTags_list) {
        out = MORPHO_OBJECT(nodeTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetElementFaceNodes(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int faceType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int primary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t task = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const size_t numTasks = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    size_t* nodeTags;
    size_t nodeTags_n;
    int ierr;
    gmshModelMeshGetElementFaceNodes(elementType,
                                     faceType,
                                     &nodeTags, &nodeTags_n,
                                     tag,
                                     primary,
                                     task,
                                     numTasks,
                                     &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value out;
    if (nodeTags_list) {
        out = MORPHO_OBJECT(nodeTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetGhostElements(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    size_t* elementTags;
    size_t elementTags_n;
    int* partitions;
    size_t partitions_n;
    int ierr;
    gmshModelMeshGetGhostElements(dim,
                                  tag,
                                  &elementTags, &elementTags_n,
                                  &partitions, &partitions_n,
                                  &ierr);
    value elementTags_value[(int) elementTags_n];
    for (size_t j=0; j<elementTags_n; j++) { 
        elementTags_value[j] = MORPHO_INTEGER(elementTags[j]);
    }
    objectlist* elementTags_list = object_newlist((int) elementTags_n, elementTags_value);
    value partitions_value[(int) partitions_n];
    for (size_t j=0; j<partitions_n; j++) { 
        partitions_value[j] = MORPHO_INTEGER(partitions[j]);
    }
    objectlist* partitions_list = object_newlist((int) partitions_n, partitions_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(elementTags_list);
    outval[1] = MORPHO_OBJECT(partitions_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshSetSize(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double size = morpho_get_double(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelMeshSetSize(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                         size,
                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetSizes(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    double* sizes;
    size_t sizes_n;
    int ierr;
    gmshModelMeshGetSizes(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                          &sizes, &sizes_n,
                          &ierr);
    value sizes_value[(int) sizes_n];
    for (size_t j=0; j<sizes_n; j++) { 
        sizes_value[j] = MORPHO_FLOAT(sizes[j]);
    }
    objectlist* sizes_list = object_newlist((int) sizes_n, sizes_value);
    value out;
    if (sizes_list) {
        out = MORPHO_OBJECT(sizes_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshSetSizeAtParametricPoints(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* parametricCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int parametricCoord_len = list_length(parametricCoord_list); 
    double parametricCoord[parametricCoord_len]; 
    morphoGetDoubleStarFromList(v, parametricCoord_list, parametricCoord); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* sizes_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int sizes_len = list_length(sizes_list); 
    double sizes[sizes_len]; 
    morphoGetDoubleStarFromList(v, sizes_list, sizes); 
    int ierr;
    gmshModelMeshSetSizeAtParametricPoints(dim,
                                           tag,
                                           parametricCoord, sizeof(parametricCoord)/sizeof(parametricCoord[0]),
                                           sizes, sizeof(sizes)/sizeof(sizes[0]),
                                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRemoveSizeCallback(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshRemoveSizeCallback(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetTransfiniteCurve(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numNodes = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * meshType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double coef = morpho_get_double(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshModelMeshSetTransfiniteCurve(tag,
                                     numNodes,
                                     meshType,
                                     coef,
                                     &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetTransfiniteSurface(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * arrangement = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cornerTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int cornerTags_len = list_length(cornerTags_list); 
    int cornerTags[cornerTags_len]; 
    morphoGetIntStarFromList(v, cornerTags_list, cornerTags); 
    int ierr;
    gmshModelMeshSetTransfiniteSurface(tag,
                                       arrangement,
                                       cornerTags, sizeof(cornerTags)/sizeof(cornerTags[0]),
                                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetTransfiniteVolume(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cornerTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int cornerTags_len = list_length(cornerTags_list); 
    int cornerTags[cornerTags_len]; 
    morphoGetIntStarFromList(v, cornerTags_list, cornerTags); 
    int ierr;
    gmshModelMeshSetTransfiniteVolume(tag,
                                      cornerTags, sizeof(cornerTags)/sizeof(cornerTags[0]),
                                      &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetTransfiniteAutomatic(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double cornerAngle = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshSetTransfiniteAutomatic(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                         cornerAngle,
                                         recombine,
                                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetRecombine(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshSetRecombine(dim,
                              tag,
                              angle,
                              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetSmoothing(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshSetSmoothing(dim,
                              tag,
                              val,
                              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetReverse(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshSetReverse(dim,
                            tag,
                            val,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetAlgorithm(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshSetAlgorithm(dim,
                              tag,
                              val,
                              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetSizeFromBoundary(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshSetSizeFromBoundary(dim,
                                     tag,
                                     val,
                                     &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetCompound(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int tags_len = list_length(tags_list); 
    int tags[tags_len]; 
    morphoGetIntStarFromList(v, tags_list, tags); 
    int ierr;
    gmshModelMeshSetCompound(dim,
                             tags, sizeof(tags)/sizeof(tags[0]),
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetOutwardOrientation(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshSetOutwardOrientation(tag,
                                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRemoveConstraints(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshRemoveConstraints(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                   &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshEmbed(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int tags_len = list_length(tags_list); 
    int tags[tags_len]; 
    morphoGetIntStarFromList(v, tags_list, tags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int inDim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int inTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshModelMeshEmbed(dim,
                       tags, sizeof(tags)/sizeof(tags[0]),
                       inDim,
                       inTag,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRemoveEmbedded(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelMeshRemoveEmbedded(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                dim,
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetEmbedded(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelMeshGetEmbedded(dim,
                             tag,
                             &dimTags, &dimTags_n,
                             &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshReorderElements(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* ordering_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int ordering_len = list_length(ordering_list); 
    size_t ordering[ordering_len]; 
    morphoGetSizeTStarFromList(v, ordering_list, ordering); 
    int ierr;
    gmshModelMeshReorderElements(elementType,
                                 tag,
                                 ordering, sizeof(ordering)/sizeof(ordering[0]),
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshComputeRenumbering(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * method = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    size_t* oldTags;
    size_t oldTags_n;
    size_t* newTags;
    size_t newTags_n;
    int ierr;
    gmshModelMeshComputeRenumbering(&oldTags, &oldTags_n,
                                    &newTags, &newTags_n,
                                    method,
                                    elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                                    &ierr);
    value oldTags_value[(int) oldTags_n];
    for (size_t j=0; j<oldTags_n; j++) { 
        oldTags_value[j] = MORPHO_INTEGER(oldTags[j]);
    }
    objectlist* oldTags_list = object_newlist((int) oldTags_n, oldTags_value);
    value newTags_value[(int) newTags_n];
    for (size_t j=0; j<newTags_n; j++) { 
        newTags_value[j] = MORPHO_INTEGER(newTags[j]);
    }
    objectlist* newTags_list = object_newlist((int) newTags_n, newTags_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(oldTags_list);
    outval[1] = MORPHO_OBJECT(newTags_list);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshRenumberNodes(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* oldTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int oldTags_len = list_length(oldTags_list); 
    size_t oldTags[oldTags_len]; 
    morphoGetSizeTStarFromList(v, oldTags_list, oldTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* newTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int newTags_len = list_length(newTags_list); 
    size_t newTags[newTags_len]; 
    morphoGetSizeTStarFromList(v, newTags_list, newTags); 
    int ierr;
    gmshModelMeshRenumberNodes(oldTags, sizeof(oldTags)/sizeof(oldTags[0]),
                               newTags, sizeof(newTags)/sizeof(newTags[0]),
                               &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRenumberElements(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* oldTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int oldTags_len = list_length(oldTags_list); 
    size_t oldTags[oldTags_len]; 
    morphoGetSizeTStarFromList(v, oldTags_list, oldTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* newTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int newTags_len = list_length(newTags_list); 
    size_t newTags[newTags_len]; 
    morphoGetSizeTStarFromList(v, newTags_list, newTags); 
    int ierr;
    gmshModelMeshRenumberElements(oldTags, sizeof(oldTags)/sizeof(oldTags[0]),
                                  newTags, sizeof(newTags)/sizeof(newTags[0]),
                                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetPeriodic(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int tags_len = list_length(tags_list); 
    int tags[tags_len]; 
    morphoGetIntStarFromList(v, tags_list, tags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tagsMaster_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int tagsMaster_len = list_length(tagsMaster_list); 
    int tagsMaster[tagsMaster_len]; 
    morphoGetIntStarFromList(v, tagsMaster_list, tagsMaster); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* affineTransform_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int affineTransform_len = list_length(affineTransform_list); 
    double affineTransform[affineTransform_len]; 
    morphoGetDoubleStarFromList(v, affineTransform_list, affineTransform); 
    int ierr;
    gmshModelMeshSetPeriodic(dim,
                             tags, sizeof(tags)/sizeof(tags[0]),
                             tagsMaster, sizeof(tagsMaster)/sizeof(tagsMaster[0]),
                             affineTransform, sizeof(affineTransform)/sizeof(affineTransform[0]),
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetPeriodic(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int tags_len = list_length(tags_list); 
    int tags[tags_len]; 
    morphoGetIntStarFromList(v, tags_list, tags); 
    int* tagMaster;
    size_t tagMaster_n;
    int ierr;
    gmshModelMeshGetPeriodic(dim,
                             tags, sizeof(tags)/sizeof(tags[0]),
                             &tagMaster, &tagMaster_n,
                             &ierr);
    value tagMaster_value[(int) tagMaster_n];
    for (size_t j=0; j<tagMaster_n; j++) { 
        tagMaster_value[j] = MORPHO_INTEGER(tagMaster[j]);
    }
    objectlist* tagMaster_list = object_newlist((int) tagMaster_n, tagMaster_value);
    value out;
    if (tagMaster_list) {
        out = MORPHO_OBJECT(tagMaster_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetPeriodicNodes(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int includeHighOrderNodes = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int tagMaster;
    size_t* nodeTags;
    size_t nodeTags_n;
    size_t* nodeTagsMaster;
    size_t nodeTagsMaster_n;
    double* affineTransform;
    size_t affineTransform_n;
    int ierr;
    gmshModelMeshGetPeriodicNodes(dim,
                                  tag,
                                  &tagMaster,
                                  &nodeTags, &nodeTags_n,
                                  &nodeTagsMaster, &nodeTagsMaster_n,
                                  &affineTransform, &affineTransform_n,
                                  includeHighOrderNodes,
                                  &ierr);
    value nodeTags_value[(int) nodeTags_n];
    for (size_t j=0; j<nodeTags_n; j++) { 
        nodeTags_value[j] = MORPHO_INTEGER(nodeTags[j]);
    }
    objectlist* nodeTags_list = object_newlist((int) nodeTags_n, nodeTags_value);
    value nodeTagsMaster_value[(int) nodeTagsMaster_n];
    for (size_t j=0; j<nodeTagsMaster_n; j++) { 
        nodeTagsMaster_value[j] = MORPHO_INTEGER(nodeTagsMaster[j]);
    }
    objectlist* nodeTagsMaster_list = object_newlist((int) nodeTagsMaster_n, nodeTagsMaster_value);
    value affineTransform_value[(int) affineTransform_n];
    for (size_t j=0; j<affineTransform_n; j++) { 
        affineTransform_value[j] = MORPHO_FLOAT(affineTransform[j]);
    }
    objectlist* affineTransform_list = object_newlist((int) affineTransform_n, affineTransform_value);
    value outval[4];
    outval[0] = MORPHO_OBJECT(tagMaster);
    outval[1] = MORPHO_OBJECT(nodeTags_list);
    outval[2] = MORPHO_OBJECT(nodeTagsMaster_list);
    outval[3] = MORPHO_OBJECT(affineTransform_list);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshGetPeriodicKeys(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int elementType = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * functionSpaceType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int returnCoord = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int tagMaster;
    int* typeKeys;
    size_t typeKeys_n;
    int* typeKeysMaster;
    size_t typeKeysMaster_n;
    size_t* entityKeys;
    size_t entityKeys_n;
    size_t* entityKeysMaster;
    size_t entityKeysMaster_n;
    double* coord;
    size_t coord_n;
    double* coordMaster;
    size_t coordMaster_n;
    int ierr;
    gmshModelMeshGetPeriodicKeys(elementType,
                                 functionSpaceType,
                                 tag,
                                 &tagMaster,
                                 &typeKeys, &typeKeys_n,
                                 &typeKeysMaster, &typeKeysMaster_n,
                                 &entityKeys, &entityKeys_n,
                                 &entityKeysMaster, &entityKeysMaster_n,
                                 &coord, &coord_n,
                                 &coordMaster, &coordMaster_n,
                                 returnCoord,
                                 &ierr);
    value typeKeys_value[(int) typeKeys_n];
    for (size_t j=0; j<typeKeys_n; j++) { 
        typeKeys_value[j] = MORPHO_INTEGER(typeKeys[j]);
    }
    objectlist* typeKeys_list = object_newlist((int) typeKeys_n, typeKeys_value);
    value typeKeysMaster_value[(int) typeKeysMaster_n];
    for (size_t j=0; j<typeKeysMaster_n; j++) { 
        typeKeysMaster_value[j] = MORPHO_INTEGER(typeKeysMaster[j]);
    }
    objectlist* typeKeysMaster_list = object_newlist((int) typeKeysMaster_n, typeKeysMaster_value);
    value entityKeys_value[(int) entityKeys_n];
    for (size_t j=0; j<entityKeys_n; j++) { 
        entityKeys_value[j] = MORPHO_INTEGER(entityKeys[j]);
    }
    objectlist* entityKeys_list = object_newlist((int) entityKeys_n, entityKeys_value);
    value entityKeysMaster_value[(int) entityKeysMaster_n];
    for (size_t j=0; j<entityKeysMaster_n; j++) { 
        entityKeysMaster_value[j] = MORPHO_INTEGER(entityKeysMaster[j]);
    }
    objectlist* entityKeysMaster_list = object_newlist((int) entityKeysMaster_n, entityKeysMaster_value);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value coordMaster_value[(int) coordMaster_n];
    for (size_t j=0; j<coordMaster_n; j++) { 
        coordMaster_value[j] = MORPHO_FLOAT(coordMaster[j]);
    }
    objectlist* coordMaster_list = object_newlist((int) coordMaster_n, coordMaster_value);
    value outval[7];
    outval[0] = MORPHO_OBJECT(tagMaster);
    outval[1] = MORPHO_OBJECT(typeKeys_list);
    outval[2] = MORPHO_OBJECT(typeKeysMaster_list);
    outval[3] = MORPHO_OBJECT(entityKeys_list);
    outval[4] = MORPHO_OBJECT(entityKeysMaster_list);
    outval[5] = MORPHO_OBJECT(coord_list);
    outval[6] = MORPHO_OBJECT(coordMaster_list);
    objectlist* outlist = object_newlist(7, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshImportStl(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshImportStl(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetDuplicateNodes(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    size_t* tags;
    size_t tags_n;
    int ierr;
    gmshModelMeshGetDuplicateNodes(&tags, &tags_n,
                                   dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                   &ierr);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    value out;
    if (tags_list) {
        out = MORPHO_OBJECT(tags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshRemoveDuplicateNodes(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshRemoveDuplicateNodes(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                      &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshRemoveDuplicateElements(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshRemoveDuplicateElements(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSplitQuadrangles(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double quality = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelMeshSplitQuadrangles(quality,
                                  tag,
                                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshSetVisibility(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int cvalue = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelMeshSetVisibility(elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                               cvalue,
                               &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshGetVisibility(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* elementTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int elementTags_len = list_length(elementTags_list); 
    size_t elementTags[elementTags_len]; 
    morphoGetSizeTStarFromList(v, elementTags_list, elementTags); 
    int* values;
    size_t values_n;
    int ierr;
    gmshModelMeshGetVisibility(elementTags, sizeof(elementTags)/sizeof(elementTags[0]),
                               &values, &values_n,
                               &ierr);
    value values_value[(int) values_n];
    for (size_t j=0; j<values_n; j++) { 
        values_value[j] = MORPHO_INTEGER(values[j]);
    }
    objectlist* values_list = object_newlist((int) values_n, values_value);
    value out;
    if (values_list) {
        out = MORPHO_OBJECT(values_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshClassifySurfaces(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int boundary = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int forReparametrization = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double curveAngle = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int exportDiscrete = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    gmshModelMeshClassifySurfaces(angle,
                                  boundary,
                                  forReparametrization,
                                  curveAngle,
                                  exportDiscrete,
                                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshCreateGeometry(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelMeshCreateGeometry(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshCreateTopology(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int makeSimplyConnected = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int exportDiscrete = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelMeshCreateTopology(makeSimplyConnected,
                                exportDiscrete,
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshAddHomologyRequest(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * type = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* domainTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int domainTags_len = list_length(domainTags_list); 
    int domainTags[domainTags_len]; 
    morphoGetIntStarFromList(v, domainTags_list, domainTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* subdomainTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int subdomainTags_len = list_length(subdomainTags_list); 
    int subdomainTags[subdomainTags_len]; 
    morphoGetIntStarFromList(v, subdomainTags_list, subdomainTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dims_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int dims_len = list_length(dims_list); 
    int dims[dims_len]; 
    morphoGetIntStarFromList(v, dims_list, dims); 
    int ierr;
    gmshModelMeshAddHomologyRequest(type,
                                    domainTags, sizeof(domainTags)/sizeof(domainTags[0]),
                                    subdomainTags, sizeof(subdomainTags)/sizeof(subdomainTags[0]),
                                    dims, sizeof(dims)/sizeof(dims[0]),
                                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshClearHomologyRequests(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelMeshClearHomologyRequests(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshComputeHomology(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelMeshComputeHomology(&dimTags, &dimTags_n,
                                 &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshComputeCrossField(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int* viewTags;
    size_t viewTags_n;
    int ierr;
    gmshModelMeshComputeCrossField(&viewTags, &viewTags_n,
                                   &ierr);
    value viewTags_value[(int) viewTags_n];
    for (size_t j=0; j<viewTags_n; j++) { 
        viewTags_value[j] = MORPHO_INTEGER(viewTags[j]);
    }
    objectlist* viewTags_list = object_newlist((int) viewTags_n, viewTags_value);
    value out;
    if (viewTags_list) {
        out = MORPHO_OBJECT(viewTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshTriangulate(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    size_t* tri;
    size_t tri_n;
    int ierr;
    gmshModelMeshTriangulate(coord, sizeof(coord)/sizeof(coord[0]),
                             &tri, &tri_n,
                             &ierr);
    value tri_value[(int) tri_n];
    for (size_t j=0; j<tri_n; j++) { 
        tri_value[j] = MORPHO_INTEGER(tri[j]);
    }
    objectlist* tri_list = object_newlist((int) tri_n, tri_value);
    value out;
    if (tri_list) {
        out = MORPHO_OBJECT(tri_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshTetrahedralize(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    size_t* tetra;
    size_t tetra_n;
    int ierr;
    gmshModelMeshTetrahedralize(coord, sizeof(coord)/sizeof(coord[0]),
                                &tetra, &tetra_n,
                                &ierr);
    value tetra_value[(int) tetra_n];
    for (size_t j=0; j<tetra_n; j++) { 
        tetra_value[j] = MORPHO_INTEGER(tetra[j]);
    }
    objectlist* tetra_list = object_newlist((int) tetra_n, tetra_value);
    value out;
    if (tetra_list) {
        out = MORPHO_OBJECT(tetra_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshFieldAdd(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fieldType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelMeshFieldAdd(fieldType,
                          tag,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelMeshFieldRemove(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshFieldRemove(tag,
                             &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshFieldList(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int* tags;
    size_t tags_n;
    int ierr;
    gmshModelMeshFieldList(&tags, &tags_n,
                           &ierr);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    value out;
    if (tags_list) {
        out = MORPHO_OBJECT(tags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshFieldGetType(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    char * fileType;
    int ierr;
    gmshModelMeshFieldGetType(tag,
                              &fileType,
                              &ierr);
    value fileType_value = object_stringfromcstring(fileType, strlen(fileType));
    objectstring* fileType_str = MORPHO_GETSTRING(fileType_value);
    value out;
    if (fileType_str) {
        out = MORPHO_OBJECT(fileType_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshFieldSetNumber(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double cvalue = morpho_get_double(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshFieldSetNumber(tag,
                                option,
                                cvalue,
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshFieldGetNumber(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    double cvalue;
    int ierr;
    gmshModelMeshFieldGetNumber(tag,
                                option,
                                &cvalue,
                                &ierr);
    return MORPHO_FLOAT(cvalue);
}

value MorphoGmshModelMeshFieldSetString(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * cvalue = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelMeshFieldSetString(tag,
                                option,
                                cvalue,
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshFieldGetString(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    char * cvalue;
    int ierr;
    gmshModelMeshFieldGetString(tag,
                                option,
                                &cvalue,
                                &ierr);
    value cvalue_value = object_stringfromcstring(cvalue, strlen(cvalue));
    objectstring* cvalue_str = MORPHO_GETSTRING(cvalue_value);
    value out;
    if (cvalue_str) {
        out = MORPHO_OBJECT(cvalue_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshFieldSetNumbers(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* values_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int values_len = list_length(values_list); 
    double values[values_len]; 
    morphoGetDoubleStarFromList(v, values_list, values); 
    int ierr;
    gmshModelMeshFieldSetNumbers(tag,
                                 option,
                                 values, sizeof(values)/sizeof(values[0]),
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshFieldGetNumbers(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    double* values;
    size_t values_n;
    int ierr;
    gmshModelMeshFieldGetNumbers(tag,
                                 option,
                                 &values, &values_n,
                                 &ierr);
    value values_value[(int) values_n];
    for (size_t j=0; j<values_n; j++) { 
        values_value[j] = MORPHO_FLOAT(values[j]);
    }
    objectlist* values_list = object_newlist((int) values_n, values_value);
    value out;
    if (values_list) {
        out = MORPHO_OBJECT(values_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelMeshFieldSetAsBackgroundMesh(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshFieldSetAsBackgroundMesh(tag,
                                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelMeshFieldSetAsBoundaryLayer(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshModelMeshFieldSetAsBoundaryLayer(tag,
                                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoAddPoint(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double meshSize = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    int outval = gmshModelGeoAddPoint(x,
                         y,
                         z,
                         meshSize,
                         tag,
                         &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddLine(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int startTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int endTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelGeoAddLine(startTag,
                        endTag,
                        tag,
                        &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddCircleArc(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int startTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int centerTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int endTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double nx = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ny = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double nz = morpho_get_double(MORPHO_GETARG(args, 6)); 
    int ierr;
    int outval = gmshModelGeoAddCircleArc(startTag,
                             centerTag,
                             endTag,
                             tag,
                             nx,
                             ny,
                             nz,
                             &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddEllipseArc(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int startTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int centerTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int majorTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int endTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double nx = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ny = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double nz = morpho_get_double(MORPHO_GETARG(args, 7)); 
    int ierr;
    int outval = gmshModelGeoAddEllipseArc(startTag,
                              centerTag,
                              majorTag,
                              endTag,
                              tag,
                              nx,
                              ny,
                              nz,
                              &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddSpline(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddSpline(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                          tag,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddBSpline(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddBSpline(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                           tag,
                           &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddBezier(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddBezier(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                          tag,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddPolyline(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddPolyline(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                            tag,
                            &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddCompoundSpline(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numIntervals = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelGeoAddCompoundSpline(curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                                  numIntervals,
                                  tag,
                                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddCompoundBSpline(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numIntervals = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelGeoAddCompoundBSpline(curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                                   numIntervals,
                                   tag,
                                   &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddCurveLoop(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int reorient = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelGeoAddCurveLoop(curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                             tag,
                             reorient,
                             &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddCurveLoops(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    int* tags;
    size_t tags_n;
    int ierr;
    gmshModelGeoAddCurveLoops(curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                              &tags, &tags_n,
                              &ierr);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    value out;
    if (tags_list) {
        out = MORPHO_OBJECT(tags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoAddPlaneSurface(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddPlaneSurface(wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                tag,
                                &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddSurfaceFilling(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int sphereCenterTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelGeoAddSurfaceFilling(wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                  tag,
                                  sphereCenterTag,
                                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddSurfaceLoop(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* surfaceTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int surfaceTags_len = list_length(surfaceTags_list); 
    int surfaceTags[surfaceTags_len]; 
    morphoGetIntStarFromList(v, surfaceTags_list, surfaceTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddSurfaceLoop(surfaceTags, sizeof(surfaceTags)/sizeof(surfaceTags[0]),
                               tag,
                               &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddVolume(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* shellTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int shellTags_len = list_length(shellTags_list); 
    int shellTags[shellTags_len]; 
    morphoGetIntStarFromList(v, shellTags_list, shellTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelGeoAddVolume(shellTags, sizeof(shellTags)/sizeof(shellTags[0]),
                          tag,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddGeometry(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * geometry = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numbers_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int numbers_len = list_length(numbers_list); 
    double numbers[numbers_len]; 
    morphoGetDoubleStarFromList(v, numbers_list, numbers); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* strings_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int strings_len = list_length(strings_list); 
    char const * strings[strings_len]; 
    morphoGetCharStarStarFromList(v, strings_list, strings); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int ierr;
    int outval = gmshModelGeoAddGeometry(geometry,
                            numbers, sizeof(numbers)/sizeof(numbers[0]),
                            strings, strings_len,
                            tag,
                            &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoAddPointOnGeometry(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int geometryTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double meshSize = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    int ierr;
    int outval = gmshModelGeoAddPointOnGeometry(geometryTag,
                                   x,
                                   y,
                                   z,
                                   meshSize,
                                   tag,
                                   &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoExtrude(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numElements_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int numElements_len = list_length(numElements_list); 
    int numElements[numElements_len]; 
    morphoGetIntStarFromList(v, numElements_list, numElements); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 5))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* heights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 5)); 
    int heights_len = list_length(heights_list); 
    double heights[heights_len]; 
    morphoGetDoubleStarFromList(v, heights_list, heights); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelGeoExtrude(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                        dx,
                        dy,
                        dz,
                        &outDimTags, &outDimTags_n,
                        numElements, sizeof(numElements)/sizeof(numElements[0]),
                        heights, sizeof(heights)/sizeof(heights[0]),
                        recombine,
                        &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoRevolve(vm* v, int nargs, value* args) {
    if (nargs != 11) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ax = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ay = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double az = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numElements_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int numElements_len = list_length(numElements_list); 
    int numElements[numElements_len]; 
    morphoGetIntStarFromList(v, numElements_list, numElements); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 9))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* heights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 9)); 
    int heights_len = list_length(heights_list); 
    double heights[heights_len]; 
    morphoGetDoubleStarFromList(v, heights_list, heights); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 10)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 10)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelGeoRevolve(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                        x,
                        y,
                        z,
                        ax,
                        ay,
                        az,
                        angle,
                        &outDimTags, &outDimTags_n,
                        numElements, sizeof(numElements)/sizeof(numElements[0]),
                        heights, sizeof(heights)/sizeof(heights[0]),
                        recombine,
                        &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoTwist(vm* v, int nargs, value* args) {
    if (nargs != 14) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ax = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 8)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ay = morpho_get_double(MORPHO_GETARG(args, 8)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 9)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double az = morpho_get_double(MORPHO_GETARG(args, 9)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 10)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 10)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 11))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numElements_list = MORPHO_GETLIST(MORPHO_GETARG(args, 11)); 
    int numElements_len = list_length(numElements_list); 
    int numElements[numElements_len]; 
    morphoGetIntStarFromList(v, numElements_list, numElements); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 12))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* heights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 12)); 
    int heights_len = list_length(heights_list); 
    double heights[heights_len]; 
    morphoGetDoubleStarFromList(v, heights_list, heights); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 13)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 13)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelGeoTwist(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                      x,
                      y,
                      z,
                      dx,
                      dy,
                      dz,
                      ax,
                      ay,
                      az,
                      angle,
                      &outDimTags, &outDimTags_n,
                      numElements, sizeof(numElements)/sizeof(numElements[0]),
                      heights, sizeof(heights)/sizeof(heights[0]),
                      recombine,
                      &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoExtrudeBoundaryLayer(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numElements_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int numElements_len = list_length(numElements_list); 
    int numElements[numElements_len]; 
    morphoGetIntStarFromList(v, numElements_list, numElements); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* heights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int heights_len = list_length(heights_list); 
    double heights[heights_len]; 
    morphoGetDoubleStarFromList(v, heights_list, heights); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int second = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int viewIndex = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelGeoExtrudeBoundaryLayer(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                     &outDimTags, &outDimTags_n,
                                     numElements, sizeof(numElements)/sizeof(numElements[0]),
                                     heights, sizeof(heights)/sizeof(heights[0]),
                                     recombine,
                                     second,
                                     viewIndex,
                                     &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoTranslate(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshModelGeoTranslate(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                          dx,
                          dy,
                          dz,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoRotate(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ax = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ay = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double az = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 7)); 
    int ierr;
    gmshModelGeoRotate(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       x,
                       y,
                       z,
                       ax,
                       ay,
                       az,
                       angle,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoDilate(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double a = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double b = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double c = morpho_get_double(MORPHO_GETARG(args, 6)); 
    int ierr;
    gmshModelGeoDilate(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       x,
                       y,
                       z,
                       a,
                       b,
                       c,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMirror(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double a = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double b = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double c = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double d = morpho_get_double(MORPHO_GETARG(args, 4)); 
    int ierr;
    gmshModelGeoMirror(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       a,
                       b,
                       c,
                       d,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoSymmetrize(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double a = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double b = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double c = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double d = morpho_get_double(MORPHO_GETARG(args, 4)); 
    int ierr;
    gmshModelGeoSymmetrize(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                           a,
                           b,
                           c,
                           d,
                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoCopy(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelGeoCopy(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                     &outDimTags, &outDimTags_n,
                     &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoRemove(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recursive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelGeoRemove(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       recursive,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoRemoveAllDuplicates(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelGeoRemoveAllDuplicates(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoSplitCurve(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    int* curveTags;
    size_t curveTags_n;
    int ierr;
    gmshModelGeoSplitCurve(tag,
                           pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                           &curveTags, &curveTags_n,
                           &ierr);
    value curveTags_value[(int) curveTags_n];
    for (size_t j=0; j<curveTags_n; j++) { 
        curveTags_value[j] = MORPHO_INTEGER(curveTags[j]);
    }
    objectlist* curveTags_list = object_newlist((int) curveTags_n, curveTags_value);
    value out;
    if (curveTags_list) {
        out = MORPHO_OBJECT(curveTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelGeoGetMaxTag(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    int outval = gmshModelGeoGetMaxTag(dim,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoSetMaxTag(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int maxTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelGeoSetMaxTag(dim,
                          maxTag,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoAddPhysicalGroup(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int tags_len = list_length(tags_list); 
    int tags[tags_len]; 
    morphoGetIntStarFromList(v, tags_list, tags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 3)); 
    int ierr;
    int outval = gmshModelGeoAddPhysicalGroup(dim,
                                 tags, sizeof(tags)/sizeof(tags[0]),
                                 tag,
                                 name,
                                 &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelGeoRemovePhysicalGroups(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelGeoRemovePhysicalGroups(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                     &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoSynchronize(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelGeoSynchronize(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetSize(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double size = morpho_get_double(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelGeoMeshSetSize(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                            size,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetTransfiniteCurve(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int nPoints = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * meshType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double coef = morpho_get_double(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshModelGeoMeshSetTransfiniteCurve(tag,
                                        nPoints,
                                        meshType,
                                        coef,
                                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetTransfiniteSurface(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * arrangement = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cornerTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int cornerTags_len = list_length(cornerTags_list); 
    int cornerTags[cornerTags_len]; 
    morphoGetIntStarFromList(v, cornerTags_list, cornerTags); 
    int ierr;
    gmshModelGeoMeshSetTransfiniteSurface(tag,
                                          arrangement,
                                          cornerTags, sizeof(cornerTags)/sizeof(cornerTags[0]),
                                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetTransfiniteVolume(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cornerTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int cornerTags_len = list_length(cornerTags_list); 
    int cornerTags[cornerTags_len]; 
    morphoGetIntStarFromList(v, cornerTags_list, cornerTags); 
    int ierr;
    gmshModelGeoMeshSetTransfiniteVolume(tag,
                                         cornerTags, sizeof(cornerTags)/sizeof(cornerTags[0]),
                                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetRecombine(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelGeoMeshSetRecombine(dim,
                                 tag,
                                 angle,
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetSmoothing(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelGeoMeshSetSmoothing(dim,
                                 tag,
                                 val,
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetReverse(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelGeoMeshSetReverse(dim,
                               tag,
                               val,
                               &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetAlgorithm(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelGeoMeshSetAlgorithm(dim,
                                 tag,
                                 val,
                                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelGeoMeshSetSizeFromBoundary(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int val = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshModelGeoMeshSetSizeFromBoundary(dim,
                                        tag,
                                        val,
                                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccAddPoint(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double meshSize = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    int outval = gmshModelOccAddPoint(x,
                         y,
                         z,
                         meshSize,
                         tag,
                         &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddLine(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int startTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int endTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelOccAddLine(startTag,
                        endTag,
                        tag,
                        &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddCircleArc(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int startTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int middleTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int endTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int center = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    int outval = gmshModelOccAddCircleArc(startTag,
                             middleTag,
                             endTag,
                             tag,
                             center,
                             &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddCircle(vm* v, int nargs, value* args) {
    if (nargs != 9) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle1 = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle2 = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 7))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* zAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 7)); 
    int zAxis_len = list_length(zAxis_list); 
    double zAxis[zAxis_len]; 
    morphoGetDoubleStarFromList(v, zAxis_list, zAxis); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* xAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int xAxis_len = list_length(xAxis_list); 
    double xAxis[xAxis_len]; 
    morphoGetDoubleStarFromList(v, xAxis_list, xAxis); 
    int ierr;
    int outval = gmshModelOccAddCircle(x,
                          y,
                          z,
                          r,
                          tag,
                          angle1,
                          angle2,
                          zAxis, sizeof(zAxis)/sizeof(zAxis[0]),
                          xAxis, sizeof(xAxis)/sizeof(xAxis[0]),
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddEllipseArc(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int startTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int centerTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int majorTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int endTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    int outval = gmshModelOccAddEllipseArc(startTag,
                              centerTag,
                              majorTag,
                              endTag,
                              tag,
                              &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddEllipse(vm* v, int nargs, value* args) {
    if (nargs != 10) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r1 = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r2 = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle1 = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle2 = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* zAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int zAxis_len = list_length(zAxis_list); 
    double zAxis[zAxis_len]; 
    morphoGetDoubleStarFromList(v, zAxis_list, zAxis); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 9))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* xAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 9)); 
    int xAxis_len = list_length(xAxis_list); 
    double xAxis[xAxis_len]; 
    morphoGetDoubleStarFromList(v, xAxis_list, xAxis); 
    int ierr;
    int outval = gmshModelOccAddEllipse(x,
                           y,
                           z,
                           r1,
                           r2,
                           tag,
                           angle1,
                           angle2,
                           zAxis, sizeof(zAxis)/sizeof(zAxis[0]),
                           xAxis, sizeof(xAxis)/sizeof(xAxis[0]),
                           &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddSpline(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tangents_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int tangents_len = list_length(tangents_list); 
    double tangents[tangents_len]; 
    morphoGetDoubleStarFromList(v, tangents_list, tangents); 
    int ierr;
    int outval = gmshModelOccAddSpline(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                          tag,
                          tangents, sizeof(tangents)/sizeof(tangents[0]),
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBSpline(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int degree = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* weights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int weights_len = list_length(weights_list); 
    double weights[weights_len]; 
    morphoGetDoubleStarFromList(v, weights_list, weights); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* knots_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int knots_len = list_length(knots_list); 
    double knots[knots_len]; 
    morphoGetDoubleStarFromList(v, knots_list, knots); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 5))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* multiplicities_list = MORPHO_GETLIST(MORPHO_GETARG(args, 5)); 
    int multiplicities_len = list_length(multiplicities_list); 
    int multiplicities[multiplicities_len]; 
    morphoGetIntStarFromList(v, multiplicities_list, multiplicities); 
    int ierr;
    int outval = gmshModelOccAddBSpline(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                           tag,
                           degree,
                           weights, sizeof(weights)/sizeof(weights[0]),
                           knots, sizeof(knots)/sizeof(knots[0]),
                           multiplicities, sizeof(multiplicities)/sizeof(multiplicities[0]),
                           &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBezier(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelOccAddBezier(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                          tag,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddWire(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int checkClosed = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelOccAddWire(curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                        tag,
                        checkClosed,
                        &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddCurveLoop(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelOccAddCurveLoop(curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                             tag,
                             &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddRectangle(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double roundedRadius = morpho_get_double(MORPHO_GETARG(args, 6)); 
    int ierr;
    int outval = gmshModelOccAddRectangle(x,
                             y,
                             z,
                             dx,
                             dy,
                             tag,
                             roundedRadius,
                             &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddDisk(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double xc = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double yc = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double zc = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double rx = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ry = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 6))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* zAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 6)); 
    int zAxis_len = list_length(zAxis_list); 
    double zAxis[zAxis_len]; 
    morphoGetDoubleStarFromList(v, zAxis_list, zAxis); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 7))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* xAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 7)); 
    int xAxis_len = list_length(xAxis_list); 
    double xAxis[xAxis_len]; 
    morphoGetDoubleStarFromList(v, xAxis_list, xAxis); 
    int ierr;
    int outval = gmshModelOccAddDisk(xc,
                        yc,
                        zc,
                        rx,
                        ry,
                        tag,
                        zAxis, sizeof(zAxis)/sizeof(zAxis[0]),
                        xAxis, sizeof(xAxis)/sizeof(xAxis[0]),
                        &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddPlaneSurface(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelOccAddPlaneSurface(wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                tag,
                                &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddSurfaceFilling(vm* v, int nargs, value* args) {
    if (nargs != 13) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wireTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int degree = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numPointsOnCurves = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numIter = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int anisotropic = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double tol2d = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 8)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double tol3d = morpho_get_double(MORPHO_GETARG(args, 8)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 9)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double tolAng = morpho_get_double(MORPHO_GETARG(args, 9)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 10)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double tolCurv = morpho_get_double(MORPHO_GETARG(args, 10)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 11)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int maxDegree = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 11)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 12)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int maxSegments = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 12)); 
    int ierr;
    int outval = gmshModelOccAddSurfaceFilling(wireTag,
                                  tag,
                                  pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                                  degree,
                                  numPointsOnCurves,
                                  numIter,
                                  anisotropic,
                                  tol2d,
                                  tol3d,
                                  tolAng,
                                  tolCurv,
                                  maxDegree,
                                  maxSegments,
                                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBSplineFilling(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wireTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * type = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelOccAddBSplineFilling(wireTag,
                                  tag,
                                  type,
                                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBezierFilling(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wireTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * type = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelOccAddBezierFilling(wireTag,
                                 tag,
                                 type,
                                 &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBSplineSurface(vm* v, int nargs, value* args) {
    if (nargs != 12) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numPointsU = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int degreeU = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int degreeV = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 5))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* weights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 5)); 
    int weights_len = list_length(weights_list); 
    double weights[weights_len]; 
    morphoGetDoubleStarFromList(v, weights_list, weights); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 6))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* knotsU_list = MORPHO_GETLIST(MORPHO_GETARG(args, 6)); 
    int knotsU_len = list_length(knotsU_list); 
    double knotsU[knotsU_len]; 
    morphoGetDoubleStarFromList(v, knotsU_list, knotsU); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 7))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* knotsV_list = MORPHO_GETLIST(MORPHO_GETARG(args, 7)); 
    int knotsV_len = list_length(knotsV_list); 
    double knotsV[knotsV_len]; 
    morphoGetDoubleStarFromList(v, knotsV_list, knotsV); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* multiplicitiesU_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int multiplicitiesU_len = list_length(multiplicitiesU_list); 
    int multiplicitiesU[multiplicitiesU_len]; 
    morphoGetIntStarFromList(v, multiplicitiesU_list, multiplicitiesU); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 9))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* multiplicitiesV_list = MORPHO_GETLIST(MORPHO_GETARG(args, 9)); 
    int multiplicitiesV_len = list_length(multiplicitiesV_list); 
    int multiplicitiesV[multiplicitiesV_len]; 
    morphoGetIntStarFromList(v, multiplicitiesV_list, multiplicitiesV); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 10))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 10)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 11)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wire3D = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 11)); 
    int ierr;
    int outval = gmshModelOccAddBSplineSurface(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                                  numPointsU,
                                  tag,
                                  degreeU,
                                  degreeV,
                                  weights, sizeof(weights)/sizeof(weights[0]),
                                  knotsU, sizeof(knotsU)/sizeof(knotsU[0]),
                                  knotsV, sizeof(knotsV)/sizeof(knotsV[0]),
                                  multiplicitiesU, sizeof(multiplicitiesU)/sizeof(multiplicitiesU[0]),
                                  multiplicitiesV, sizeof(multiplicitiesV)/sizeof(multiplicitiesV[0]),
                                  wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                  wire3D,
                                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBezierSurface(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* pointTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int pointTags_len = list_length(pointTags_list); 
    int pointTags[pointTags_len]; 
    morphoGetIntStarFromList(v, pointTags_list, pointTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numPointsU = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wire3D = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int ierr;
    int outval = gmshModelOccAddBezierSurface(pointTags, sizeof(pointTags)/sizeof(pointTags[0]),
                                 numPointsU,
                                 tag,
                                 wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                 wire3D,
                                 &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddTrimmedSurface(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int surfaceTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wire3D = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int ierr;
    int outval = gmshModelOccAddTrimmedSurface(surfaceTag,
                                  wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                  wire3D,
                                  tag,
                                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddSurfaceLoop(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* surfaceTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int surfaceTags_len = list_length(surfaceTags_list); 
    int surfaceTags[surfaceTags_len]; 
    morphoGetIntStarFromList(v, surfaceTags_list, surfaceTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int sewing = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshModelOccAddSurfaceLoop(surfaceTags, sizeof(surfaceTags)/sizeof(surfaceTags[0]),
                               tag,
                               sewing,
                               &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddVolume(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* shellTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int shellTags_len = list_length(shellTags_list); 
    int shellTags[shellTags_len]; 
    morphoGetIntStarFromList(v, shellTags_list, shellTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshModelOccAddVolume(shellTags, sizeof(shellTags)/sizeof(shellTags[0]),
                          tag,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddSphere(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double xc = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double yc = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double zc = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double radius = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle1 = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle2 = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle3 = morpho_get_double(MORPHO_GETARG(args, 7)); 
    int ierr;
    int outval = gmshModelOccAddSphere(xc,
                          yc,
                          zc,
                          radius,
                          tag,
                          angle1,
                          angle2,
                          angle3,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddBox(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    int ierr;
    int outval = gmshModelOccAddBox(x,
                       y,
                       z,
                       dx,
                       dy,
                       dz,
                       tag,
                       &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddCylinder(vm* v, int nargs, value* args) {
    if (nargs != 9) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 7)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 8)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 8)); 
    int ierr;
    int outval = gmshModelOccAddCylinder(x,
                            y,
                            z,
                            dx,
                            dy,
                            dz,
                            r,
                            tag,
                            angle,
                            &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddCone(vm* v, int nargs, value* args) {
    if (nargs != 10) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r1 = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r2 = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 8)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 8)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 9)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 9)); 
    int ierr;
    int outval = gmshModelOccAddCone(x,
                        y,
                        z,
                        dx,
                        dy,
                        dz,
                        r1,
                        r2,
                        tag,
                        angle,
                        &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddWedge(vm* v, int nargs, value* args) {
    if (nargs != 9) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ltx = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* zAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int zAxis_len = list_length(zAxis_list); 
    double zAxis[zAxis_len]; 
    morphoGetDoubleStarFromList(v, zAxis_list, zAxis); 
    int ierr;
    int outval = gmshModelOccAddWedge(x,
                         y,
                         z,
                         dx,
                         dy,
                         dz,
                         tag,
                         ltx,
                         zAxis, sizeof(zAxis)/sizeof(zAxis[0]),
                         &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddTorus(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r1 = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double r2 = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 7))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* zAxis_list = MORPHO_GETLIST(MORPHO_GETARG(args, 7)); 
    int zAxis_len = list_length(zAxis_list); 
    double zAxis[zAxis_len]; 
    morphoGetDoubleStarFromList(v, zAxis_list, zAxis); 
    int ierr;
    int outval = gmshModelOccAddTorus(x,
                         y,
                         z,
                         r1,
                         r2,
                         tag,
                         angle,
                         zAxis, sizeof(zAxis)/sizeof(zAxis[0]),
                         &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccAddThruSections(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* wireTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int wireTags_len = list_length(wireTags_list); 
    int wireTags[wireTags_len]; 
    morphoGetIntStarFromList(v, wireTags_list, wireTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int makeSolid = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int makeRuled = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int maxDegree = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * continuity = MORPHO_GETCSTRING(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * parametrization = MORPHO_GETCSTRING(MORPHO_GETARG(args, 6)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int smoothing = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 7)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccAddThruSections(wireTags, sizeof(wireTags)/sizeof(wireTags[0]),
                                &outDimTags, &outDimTags_n,
                                tag,
                                makeSolid,
                                makeRuled,
                                maxDegree,
                                continuity,
                                parametrization,
                                smoothing,
                                &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccAddThickSolid(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int volumeTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* excludeSurfaceTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int excludeSurfaceTags_len = list_length(excludeSurfaceTags_list); 
    int excludeSurfaceTags[excludeSurfaceTags_len]; 
    morphoGetIntStarFromList(v, excludeSurfaceTags_list, excludeSurfaceTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double offset = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccAddThickSolid(volumeTag,
                              excludeSurfaceTags, sizeof(excludeSurfaceTags)/sizeof(excludeSurfaceTags[0]),
                              offset,
                              &outDimTags, &outDimTags_n,
                              tag,
                              &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccExtrude(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numElements_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int numElements_len = list_length(numElements_list); 
    int numElements[numElements_len]; 
    morphoGetIntStarFromList(v, numElements_list, numElements); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 5))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* heights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 5)); 
    int heights_len = list_length(heights_list); 
    double heights[heights_len]; 
    morphoGetDoubleStarFromList(v, heights_list, heights); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccExtrude(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                        dx,
                        dy,
                        dz,
                        &outDimTags, &outDimTags_n,
                        numElements, sizeof(numElements)/sizeof(numElements[0]),
                        heights, sizeof(heights)/sizeof(heights[0]),
                        recombine,
                        &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccRevolve(vm* v, int nargs, value* args) {
    if (nargs != 11) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ax = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ay = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double az = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* numElements_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int numElements_len = list_length(numElements_list); 
    int numElements[numElements_len]; 
    morphoGetIntStarFromList(v, numElements_list, numElements); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 9))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* heights_list = MORPHO_GETLIST(MORPHO_GETARG(args, 9)); 
    int heights_len = list_length(heights_list); 
    double heights[heights_len]; 
    morphoGetDoubleStarFromList(v, heights_list, heights); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 10)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recombine = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 10)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccRevolve(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                        x,
                        y,
                        z,
                        ax,
                        ay,
                        az,
                        angle,
                        &outDimTags, &outDimTags_n,
                        numElements, sizeof(numElements)/sizeof(numElements[0]),
                        heights, sizeof(heights)/sizeof(heights[0]),
                        recombine,
                        &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccAddPipe(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int wireTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * trihedron = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccAddPipe(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                        wireTag,
                        &outDimTags, &outDimTags_n,
                        trihedron,
                        &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccFillet(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* volumeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int volumeTags_len = list_length(volumeTags_list); 
    int volumeTags[volumeTags_len]; 
    morphoGetIntStarFromList(v, volumeTags_list, volumeTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* radii_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int radii_len = list_length(radii_list); 
    double radii[radii_len]; 
    morphoGetDoubleStarFromList(v, radii_list, radii); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeVolume = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccFillet(volumeTags, sizeof(volumeTags)/sizeof(volumeTags[0]),
                       curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                       radii, sizeof(radii)/sizeof(radii[0]),
                       &outDimTags, &outDimTags_n,
                       removeVolume,
                       &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccChamfer(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* volumeTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int volumeTags_len = list_length(volumeTags_list); 
    int volumeTags[volumeTags_len]; 
    morphoGetIntStarFromList(v, volumeTags_list, volumeTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* curveTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int curveTags_len = list_length(curveTags_list); 
    int curveTags[curveTags_len]; 
    morphoGetIntStarFromList(v, curveTags_list, curveTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* surfaceTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int surfaceTags_len = list_length(surfaceTags_list); 
    int surfaceTags[surfaceTags_len]; 
    morphoGetIntStarFromList(v, surfaceTags_list, surfaceTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* distances_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int distances_len = list_length(distances_list); 
    double distances[distances_len]; 
    morphoGetDoubleStarFromList(v, distances_list, distances); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeVolume = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccChamfer(volumeTags, sizeof(volumeTags)/sizeof(volumeTags[0]),
                        curveTags, sizeof(curveTags)/sizeof(curveTags[0]),
                        surfaceTags, sizeof(surfaceTags)/sizeof(surfaceTags[0]),
                        distances, sizeof(distances)/sizeof(distances[0]),
                        &outDimTags, &outDimTags_n,
                        removeVolume,
                        &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccFuse(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* objectDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int objectDimTags_len = list_length(objectDimTags_list); 
    int objectDimTags[objectDimTags_len]; 
    morphoGetIntStarFromList(v, objectDimTags_list, objectDimTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* toolDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int toolDimTags_len = list_length(toolDimTags_list); 
    int toolDimTags[toolDimTags_len]; 
    morphoGetIntStarFromList(v, toolDimTags_list, toolDimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeObject = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeTool = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ** outDimTagsMap;
    size_t * outDimTagsMap_n;
    size_t outDimTagsMap_nn;
    int ierr;
    gmshModelOccFuse(objectDimTags, sizeof(objectDimTags)/sizeof(objectDimTags[0]),
                     toolDimTags, sizeof(toolDimTags)/sizeof(toolDimTags[0]),
                     &outDimTags, &outDimTags_n,
                     &outDimTagsMap, &outDimTagsMap_n, &outDimTagsMap_nn,
                     tag,
                     removeObject,
                     removeTool,
                     &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    objectlist* outDimTagsMaplistoflist = object_newlist(0, NULL);
    value outDimTagsMap_value[(int) outDimTagsMap_nn];
    for (size_t i=0; i<outDimTagsMap_nn; i++) { 
        value outDimTagsMap_i_value[(int) outDimTagsMap_n[i]];
        for (size_t j=0; j<outDimTagsMap_n[i]; j++) { 
            outDimTagsMap_i_value[j] = MORPHO_INTEGER(outDimTagsMap[i][j]);
        }
        objectlist* outDimTagsMaplistoflist_i = object_newlist((int) outDimTagsMap_n[i], outDimTagsMap_i_value);
        list_append(outDimTagsMaplistoflist, MORPHO_OBJECT(outDimTagsMaplistoflist_i));    } 
    value outval[2];
    outval[0] = MORPHO_OBJECT(outDimTags_list);
    outval[1] = MORPHO_OBJECT(outDimTagsMaplistoflist);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccIntersect(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* objectDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int objectDimTags_len = list_length(objectDimTags_list); 
    int objectDimTags[objectDimTags_len]; 
    morphoGetIntStarFromList(v, objectDimTags_list, objectDimTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* toolDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int toolDimTags_len = list_length(toolDimTags_list); 
    int toolDimTags[toolDimTags_len]; 
    morphoGetIntStarFromList(v, toolDimTags_list, toolDimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeObject = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeTool = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ** outDimTagsMap;
    size_t * outDimTagsMap_n;
    size_t outDimTagsMap_nn;
    int ierr;
    gmshModelOccIntersect(objectDimTags, sizeof(objectDimTags)/sizeof(objectDimTags[0]),
                          toolDimTags, sizeof(toolDimTags)/sizeof(toolDimTags[0]),
                          &outDimTags, &outDimTags_n,
                          &outDimTagsMap, &outDimTagsMap_n, &outDimTagsMap_nn,
                          tag,
                          removeObject,
                          removeTool,
                          &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    objectlist* outDimTagsMaplistoflist = object_newlist(0, NULL);
    value outDimTagsMap_value[(int) outDimTagsMap_nn];
    for (size_t i=0; i<outDimTagsMap_nn; i++) { 
        value outDimTagsMap_i_value[(int) outDimTagsMap_n[i]];
        for (size_t j=0; j<outDimTagsMap_n[i]; j++) { 
            outDimTagsMap_i_value[j] = MORPHO_INTEGER(outDimTagsMap[i][j]);
        }
        objectlist* outDimTagsMaplistoflist_i = object_newlist((int) outDimTagsMap_n[i], outDimTagsMap_i_value);
        list_append(outDimTagsMaplistoflist, MORPHO_OBJECT(outDimTagsMaplistoflist_i));    } 
    value outval[2];
    outval[0] = MORPHO_OBJECT(outDimTags_list);
    outval[1] = MORPHO_OBJECT(outDimTagsMaplistoflist);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccCut(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* objectDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int objectDimTags_len = list_length(objectDimTags_list); 
    int objectDimTags[objectDimTags_len]; 
    morphoGetIntStarFromList(v, objectDimTags_list, objectDimTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* toolDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int toolDimTags_len = list_length(toolDimTags_list); 
    int toolDimTags[toolDimTags_len]; 
    morphoGetIntStarFromList(v, toolDimTags_list, toolDimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeObject = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeTool = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ** outDimTagsMap;
    size_t * outDimTagsMap_n;
    size_t outDimTagsMap_nn;
    int ierr;
    gmshModelOccCut(objectDimTags, sizeof(objectDimTags)/sizeof(objectDimTags[0]),
                    toolDimTags, sizeof(toolDimTags)/sizeof(toolDimTags[0]),
                    &outDimTags, &outDimTags_n,
                    &outDimTagsMap, &outDimTagsMap_n, &outDimTagsMap_nn,
                    tag,
                    removeObject,
                    removeTool,
                    &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    objectlist* outDimTagsMaplistoflist = object_newlist(0, NULL);
    value outDimTagsMap_value[(int) outDimTagsMap_nn];
    for (size_t i=0; i<outDimTagsMap_nn; i++) { 
        value outDimTagsMap_i_value[(int) outDimTagsMap_n[i]];
        for (size_t j=0; j<outDimTagsMap_n[i]; j++) { 
            outDimTagsMap_i_value[j] = MORPHO_INTEGER(outDimTagsMap[i][j]);
        }
        objectlist* outDimTagsMaplistoflist_i = object_newlist((int) outDimTagsMap_n[i], outDimTagsMap_i_value);
        list_append(outDimTagsMaplistoflist, MORPHO_OBJECT(outDimTagsMaplistoflist_i));    } 
    value outval[2];
    outval[0] = MORPHO_OBJECT(outDimTags_list);
    outval[1] = MORPHO_OBJECT(outDimTagsMaplistoflist);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccFragment(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* objectDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int objectDimTags_len = list_length(objectDimTags_list); 
    int objectDimTags[objectDimTags_len]; 
    morphoGetIntStarFromList(v, objectDimTags_list, objectDimTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* toolDimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int toolDimTags_len = list_length(toolDimTags_list); 
    int toolDimTags[toolDimTags_len]; 
    morphoGetIntStarFromList(v, toolDimTags_list, toolDimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeObject = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int removeTool = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ** outDimTagsMap;
    size_t * outDimTagsMap_n;
    size_t outDimTagsMap_nn;
    int ierr;
    gmshModelOccFragment(objectDimTags, sizeof(objectDimTags)/sizeof(objectDimTags[0]),
                         toolDimTags, sizeof(toolDimTags)/sizeof(toolDimTags[0]),
                         &outDimTags, &outDimTags_n,
                         &outDimTagsMap, &outDimTagsMap_n, &outDimTagsMap_nn,
                         tag,
                         removeObject,
                         removeTool,
                         &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    objectlist* outDimTagsMaplistoflist = object_newlist(0, NULL);
    value outDimTagsMap_value[(int) outDimTagsMap_nn];
    for (size_t i=0; i<outDimTagsMap_nn; i++) { 
        value outDimTagsMap_i_value[(int) outDimTagsMap_n[i]];
        for (size_t j=0; j<outDimTagsMap_n[i]; j++) { 
            outDimTagsMap_i_value[j] = MORPHO_INTEGER(outDimTagsMap[i][j]);
        }
        objectlist* outDimTagsMaplistoflist_i = object_newlist((int) outDimTagsMap_n[i], outDimTagsMap_i_value);
        list_append(outDimTagsMaplistoflist, MORPHO_OBJECT(outDimTagsMaplistoflist_i));    } 
    value outval[2];
    outval[0] = MORPHO_OBJECT(outDimTags_list);
    outval[1] = MORPHO_OBJECT(outDimTagsMaplistoflist);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccTranslate(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dx = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dy = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double dz = morpho_get_double(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshModelOccTranslate(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                          dx,
                          dy,
                          dz,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccRotate(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ax = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ay = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double az = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double angle = morpho_get_double(MORPHO_GETARG(args, 7)); 
    int ierr;
    gmshModelOccRotate(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       x,
                       y,
                       z,
                       ax,
                       ay,
                       az,
                       angle,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccDilate(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double a = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double b = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double c = morpho_get_double(MORPHO_GETARG(args, 6)); 
    int ierr;
    gmshModelOccDilate(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       x,
                       y,
                       z,
                       a,
                       b,
                       c,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccMirror(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double a = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double b = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double c = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double d = morpho_get_double(MORPHO_GETARG(args, 4)); 
    int ierr;
    gmshModelOccMirror(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       a,
                       b,
                       c,
                       d,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccSymmetrize(vm* v, int nargs, value* args) {
    if (nargs != 5) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double a = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double b = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double c = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double d = morpho_get_double(MORPHO_GETARG(args, 4)); 
    int ierr;
    gmshModelOccSymmetrize(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                           a,
                           b,
                           c,
                           d,
                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccAffineTransform(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* affineTransform_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int affineTransform_len = list_length(affineTransform_list); 
    double affineTransform[affineTransform_len]; 
    morphoGetDoubleStarFromList(v, affineTransform_list, affineTransform); 
    int ierr;
    gmshModelOccAffineTransform(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                                affineTransform, sizeof(affineTransform)/sizeof(affineTransform[0]),
                                &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccCopy(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccCopy(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                     &outDimTags, &outDimTags_n,
                     &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccRemove(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int recursive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelOccRemove(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                       recursive,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccRemoveAllDuplicates(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelOccRemoveAllDuplicates(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccHealShapes(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double tolerance = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int fixDegenerated = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int fixSmallEdges = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int fixSmallFaces = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int sewFaces = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int makeSolids = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccHealShapes(&outDimTags, &outDimTags_n,
                           dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                           tolerance,
                           fixDegenerated,
                           fixSmallEdges,
                           fixSmallFaces,
                           sewFaces,
                           makeSolids,
                           &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccConvertToNURBS(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    int ierr;
    gmshModelOccConvertToNURBS(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                               &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccImportShapes(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int highestDimOnly = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * format = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int* outDimTags;
    size_t outDimTags_n;
    int ierr;
    gmshModelOccImportShapes(fileName,
                             &outDimTags, &outDimTags_n,
                             highestDimOnly,
                             format,
                             &ierr);
    value outDimTags_value[(int) outDimTags_n];
    for (size_t j=0; j<outDimTags_n; j++) { 
        outDimTags_value[j] = MORPHO_INTEGER(outDimTags[j]);
    }
    objectlist* outDimTags_list = object_newlist((int) outDimTags_n, outDimTags_value);
    value out;
    if (outDimTags_list) {
        out = MORPHO_OBJECT(outDimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetEntities(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelOccGetEntities(&dimTags, &dimTags_n,
                            dim,
                            &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetEntitiesInBoundingBox(vm* v, int nargs, value* args) {
    if (nargs != 7) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double xmin = morpho_get_double(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ymin = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double zmin = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double xmax = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double ymax = morpho_get_double(MORPHO_GETARG(args, 4)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double zmax = morpho_get_double(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    int* dimTags;
    size_t dimTags_n;
    int ierr;
    gmshModelOccGetEntitiesInBoundingBox(xmin,
                                         ymin,
                                         zmin,
                                         xmax,
                                         ymax,
                                         zmax,
                                         &dimTags, &dimTags_n,
                                         dim,
                                         &ierr);
    value dimTags_value[(int) dimTags_n];
    for (size_t j=0; j<dimTags_n; j++) { 
        dimTags_value[j] = MORPHO_INTEGER(dimTags[j]);
    }
    objectlist* dimTags_list = object_newlist((int) dimTags_n, dimTags_value);
    value out;
    if (dimTags_list) {
        out = MORPHO_OBJECT(dimTags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetBoundingBox(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double xmin;
    double ymin;
    double zmin;
    double xmax;
    double ymax;
    double zmax;
    int ierr;
    gmshModelOccGetBoundingBox(dim,
                               tag,
                               &xmin,
                               &ymin,
                               &zmin,
                               &xmax,
                               &ymax,
                               &zmax,
                               &ierr);
    value outval[6];
    outval[0] = MORPHO_OBJECT(xmin);
    outval[1] = MORPHO_OBJECT(ymin);
    outval[2] = MORPHO_OBJECT(zmin);
    outval[3] = MORPHO_OBJECT(xmax);
    outval[4] = MORPHO_OBJECT(ymax);
    outval[5] = MORPHO_OBJECT(zmax);
    objectlist* outlist = object_newlist(6, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetCurveLoops(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int surfaceTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int* curveLoopTags;
    size_t curveLoopTags_n;
    int ** curveTags;
    size_t * curveTags_n;
    size_t curveTags_nn;
    int ierr;
    gmshModelOccGetCurveLoops(surfaceTag,
                              &curveLoopTags, &curveLoopTags_n,
                              &curveTags, &curveTags_n, &curveTags_nn,
                              &ierr);
    value curveLoopTags_value[(int) curveLoopTags_n];
    for (size_t j=0; j<curveLoopTags_n; j++) { 
        curveLoopTags_value[j] = MORPHO_INTEGER(curveLoopTags[j]);
    }
    objectlist* curveLoopTags_list = object_newlist((int) curveLoopTags_n, curveLoopTags_value);
    objectlist* curveTagslistoflist = object_newlist(0, NULL);
    value curveTags_value[(int) curveTags_nn];
    for (size_t i=0; i<curveTags_nn; i++) { 
        value curveTags_i_value[(int) curveTags_n[i]];
        for (size_t j=0; j<curveTags_n[i]; j++) { 
            curveTags_i_value[j] = MORPHO_INTEGER(curveTags[i][j]);
        }
        objectlist* curveTagslistoflist_i = object_newlist((int) curveTags_n[i], curveTags_i_value);
        list_append(curveTagslistoflist, MORPHO_OBJECT(curveTagslistoflist_i));    } 
    value outval[2];
    outval[0] = MORPHO_OBJECT(curveLoopTags_list);
    outval[1] = MORPHO_OBJECT(curveTagslistoflist);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetSurfaceLoops(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int volumeTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int* surfaceLoopTags;
    size_t surfaceLoopTags_n;
    int ** surfaceTags;
    size_t * surfaceTags_n;
    size_t surfaceTags_nn;
    int ierr;
    gmshModelOccGetSurfaceLoops(volumeTag,
                                &surfaceLoopTags, &surfaceLoopTags_n,
                                &surfaceTags, &surfaceTags_n, &surfaceTags_nn,
                                &ierr);
    value surfaceLoopTags_value[(int) surfaceLoopTags_n];
    for (size_t j=0; j<surfaceLoopTags_n; j++) { 
        surfaceLoopTags_value[j] = MORPHO_INTEGER(surfaceLoopTags[j]);
    }
    objectlist* surfaceLoopTags_list = object_newlist((int) surfaceLoopTags_n, surfaceLoopTags_value);
    objectlist* surfaceTagslistoflist = object_newlist(0, NULL);
    value surfaceTags_value[(int) surfaceTags_nn];
    for (size_t i=0; i<surfaceTags_nn; i++) { 
        value surfaceTags_i_value[(int) surfaceTags_n[i]];
        for (size_t j=0; j<surfaceTags_n[i]; j++) { 
            surfaceTags_i_value[j] = MORPHO_INTEGER(surfaceTags[i][j]);
        }
        objectlist* surfaceTagslistoflist_i = object_newlist((int) surfaceTags_n[i], surfaceTags_i_value);
        list_append(surfaceTagslistoflist, MORPHO_OBJECT(surfaceTagslistoflist_i));    } 
    value outval[2];
    outval[0] = MORPHO_OBJECT(surfaceLoopTags_list);
    outval[1] = MORPHO_OBJECT(surfaceTagslistoflist);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetMass(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double mass;
    int ierr;
    gmshModelOccGetMass(dim,
                        tag,
                        &mass,
                        &ierr);
    return MORPHO_FLOAT(mass);
}

value MorphoGmshModelOccGetCenterOfMass(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double x;
    double y;
    double z;
    int ierr;
    gmshModelOccGetCenterOfMass(dim,
                                tag,
                                &x,
                                &y,
                                &z,
                                &ierr);
    value outval[3];
    outval[0] = MORPHO_OBJECT(x);
    outval[1] = MORPHO_OBJECT(y);
    outval[2] = MORPHO_OBJECT(z);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetMatrixOfInertia(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double* mat;
    size_t mat_n;
    int ierr;
    gmshModelOccGetMatrixOfInertia(dim,
                                   tag,
                                   &mat, &mat_n,
                                   &ierr);
    value mat_value[(int) mat_n];
    for (size_t j=0; j<mat_n; j++) { 
        mat_value[j] = MORPHO_FLOAT(mat[j]);
    }
    objectlist* mat_list = object_newlist((int) mat_n, mat_value);
    value out;
    if (mat_list) {
        out = MORPHO_OBJECT(mat_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshModelOccGetMaxTag(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    int outval = gmshModelOccGetMaxTag(dim,
                          &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshModelOccSetMaxTag(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int maxTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelOccSetMaxTag(dim,
                          maxTag,
                          &ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccSynchronize(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshModelOccSynchronize(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshModelOccMeshSetSize(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 0))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* dimTags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 0)); 
    int dimTags_len = list_length(dimTags_list); 
    int dimTags[dimTags_len]; 
    morphoGetIntStarFromList(v, dimTags_list, dimTags); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double size = morpho_get_double(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshModelOccMeshSetSize(dimTags, sizeof(dimTags)/sizeof(dimTags[0]),
                            size,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewAdd(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    int outval = gmshViewAdd(name,
                tag,
                &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshViewRemove(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshViewRemove(tag,
                   &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewGetIndex(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    int ierr;
    int outval = gmshViewGetIndex(tag,
                     &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshViewGetTags(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int* tags;
    size_t tags_n;
    int ierr;
    gmshViewGetTags(&tags, &tags_n,
                    &ierr);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    value out;
    if (tags_list) {
        out = MORPHO_OBJECT(tags_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewAddModelData(vm* v, int nargs, value* args) {
    if (nargs != 9) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int step = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * modelName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * dataType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int tags_len = list_length(tags_list); 
    size_t tags[tags_len]; 
    morphoGetSizeTStarFromList(v, tags_list, tags); 

    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 5))) { morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* data_list = MORPHO_GETLIST(MORPHO_GETARG(args, 5));
    double data_nn = (size_t) list_length(data_list);
    double * data_n;
    double ** data;
    value data_elI;
    objectlist * data_li;
    bool data_success;
    for (size_t i=0; i<data_nn; i++) {
        data_success = (data_success && list_getelement(data_list, i, &data_elI));
        if (!MORPHO_ISLIST(data_elI)) {
            morpho_runtimeerror(v, GMSH_ARGS_ERROR); 
            return MORPHO_NIL; 
        }
        data_li = MORPHO_GETLIST(data_elI);
        data_n[i] = (size_t) list_length(data_li);
        morphoGetDoubleStarFromList(v, data_li, data[i]);
    }
            if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double time = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numComponents = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 8)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int partition = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 8)); 
    int ierr;
    gmshViewAddModelData(tag,
                         step,
                         modelName,
                         dataType,
                         tags, sizeof(tags)/sizeof(tags[0]),
                         data, data_n, data_nn,
                         time,
                         numComponents,
                         partition,
                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewAddHomogeneousModelData(vm* v, int nargs, value* args) {
    if (nargs != 9) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int step = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * modelName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * dataType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* tags_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int tags_len = list_length(tags_list); 
    size_t tags[tags_len]; 
    morphoGetSizeTStarFromList(v, tags_list, tags); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 5))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* data_list = MORPHO_GETLIST(MORPHO_GETARG(args, 5)); 
    int data_len = list_length(data_list); 
    double data[data_len]; 
    morphoGetDoubleStarFromList(v, data_list, data); 
    if (!morpho_is_double(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double time = morpho_get_double(MORPHO_GETARG(args, 6)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numComponents = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 8)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int partition = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 8)); 
    int ierr;
    gmshViewAddHomogeneousModelData(tag,
                                    step,
                                    modelName,
                                    dataType,
                                    tags, sizeof(tags)/sizeof(tags[0]),
                                    data, sizeof(data)/sizeof(data[0]),
                                    time,
                                    numComponents,
                                    partition,
                                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewGetModelData(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int step = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    char * dataType;
    size_t* tags;
    size_t tags_n;
    double ** data;
    size_t * data_n;
    size_t data_nn;
    double time;
    int numComponents;
    int ierr;
    gmshViewGetModelData(tag,
                         step,
                         &dataType,
                         &tags, &tags_n,
                         &data, &data_n, &data_nn,
                         &time,
                         &numComponents,
                         &ierr);
    value dataType_value = object_stringfromcstring(dataType, strlen(dataType));
    objectstring* dataType_str = MORPHO_GETSTRING(dataType_value);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    objectlist* datalistoflist = object_newlist(0, NULL);
    value data_value[(int) data_nn];
    for (size_t i=0; i<data_nn; i++) { 
        value data_i_value[(int) data_n[i]];
        for (size_t j=0; j<data_n[i]; j++) { 
            data_i_value[j] = MORPHO_FLOAT(data[i][j]);
        }
        objectlist* datalistoflist_i = object_newlist((int) data_n[i], data_i_value);
        list_append(datalistoflist, MORPHO_OBJECT(datalistoflist_i));    } 
    value outval[5];
    outval[0] = MORPHO_OBJECT(dataType_str);
    outval[1] = MORPHO_OBJECT(tags_list);
    outval[2] = MORPHO_OBJECT(datalistoflist);
    outval[3] = MORPHO_OBJECT(time);
    outval[4] = MORPHO_OBJECT(numComponents);
    objectlist* outlist = object_newlist(5, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewGetHomogeneousModelData(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int step = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    char * dataType;
    size_t* tags;
    size_t tags_n;
    double* data;
    size_t data_n;
    double time;
    int numComponents;
    int ierr;
    gmshViewGetHomogeneousModelData(tag,
                                    step,
                                    &dataType,
                                    &tags, &tags_n,
                                    &data, &data_n,
                                    &time,
                                    &numComponents,
                                    &ierr);
    value dataType_value = object_stringfromcstring(dataType, strlen(dataType));
    objectstring* dataType_str = MORPHO_GETSTRING(dataType_value);
    value tags_value[(int) tags_n];
    for (size_t j=0; j<tags_n; j++) { 
        tags_value[j] = MORPHO_INTEGER(tags[j]);
    }
    objectlist* tags_list = object_newlist((int) tags_n, tags_value);
    value data_value[(int) data_n];
    for (size_t j=0; j<data_n; j++) { 
        data_value[j] = MORPHO_FLOAT(data[j]);
    }
    objectlist* data_list = object_newlist((int) data_n, data_value);
    value outval[5];
    outval[0] = MORPHO_OBJECT(dataType_str);
    outval[1] = MORPHO_OBJECT(tags_list);
    outval[2] = MORPHO_OBJECT(data_list);
    outval[3] = MORPHO_OBJECT(time);
    outval[4] = MORPHO_OBJECT(numComponents);
    objectlist* outlist = object_newlist(5, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewAddListData(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * dataType = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numEle = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* data_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int data_len = list_length(data_list); 
    double data[data_len]; 
    morphoGetDoubleStarFromList(v, data_list, data); 
    int ierr;
    gmshViewAddListData(tag,
                        dataType,
                        numEle,
                        data, sizeof(data)/sizeof(data[0]),
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewGetListData(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int returnAdaptive = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    char ** dataType;
    size_t dataType_n;
    int* numElements;
    size_t numElements_n;
    double ** data;
    size_t * data_n;
    size_t data_nn;
    int ierr;
    gmshViewGetListData(tag,
                        &dataType, &dataType_n,
                        &numElements, &numElements_n,
                        &data, &data_n, &data_nn,
                        returnAdaptive,
                        &ierr);
    value dataType_values[(int) dataType_n];
    for (size_t j=0; j<dataType_n; j++) { 
        dataType_values[j] = object_stringfromcstring(dataType[j], strlen(dataType[j]));
    }
    objectlist* dataType_list = object_newlist((int) dataType_n, dataType_values);
    value numElements_value[(int) numElements_n];
    for (size_t j=0; j<numElements_n; j++) { 
        numElements_value[j] = MORPHO_INTEGER(numElements[j]);
    }
    objectlist* numElements_list = object_newlist((int) numElements_n, numElements_value);
    objectlist* datalistoflist = object_newlist(0, NULL);
    value data_value[(int) data_nn];
    for (size_t i=0; i<data_nn; i++) { 
        value data_i_value[(int) data_n[i]];
        for (size_t j=0; j<data_n[i]; j++) { 
            data_i_value[j] = MORPHO_FLOAT(data[i][j]);
        }
        objectlist* datalistoflist_i = object_newlist((int) data_n[i], data_i_value);
        list_append(datalistoflist, MORPHO_OBJECT(datalistoflist_i));    } 
    value outval[3];
    outval[0] = MORPHO_OBJECT(dataType_list);
    outval[1] = MORPHO_OBJECT(numElements_list);
    outval[2] = MORPHO_OBJECT(datalistoflist);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewAddListDataString(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int coord_len = list_length(coord_list); 
    double coord[coord_len]; 
    morphoGetDoubleStarFromList(v, coord_list, coord); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 2))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* data_list = MORPHO_GETLIST(MORPHO_GETARG(args, 2)); 
    int data_len = list_length(data_list); 
    char const * data[data_len]; 
    morphoGetCharStarStarFromList(v, data_list, data); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* style_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int style_len = list_length(style_list); 
    char const * style[style_len]; 
    morphoGetCharStarStarFromList(v, style_list, style); 
    int ierr;
    gmshViewAddListDataString(tag,
                              coord, sizeof(coord)/sizeof(coord[0]),
                              data, data_len,
                              style, style_len,
                              &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewGetListDataStrings(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    double* coord;
    size_t coord_n;
    char ** data;
    size_t data_n;
    char ** style;
    size_t style_n;
    int ierr;
    gmshViewGetListDataStrings(tag,
                               dim,
                               &coord, &coord_n,
                               &data, &data_n,
                               &style, &style_n,
                               &ierr);
    value coord_value[(int) coord_n];
    for (size_t j=0; j<coord_n; j++) { 
        coord_value[j] = MORPHO_FLOAT(coord[j]);
    }
    objectlist* coord_list = object_newlist((int) coord_n, coord_value);
    value data_values[(int) data_n];
    for (size_t j=0; j<data_n; j++) { 
        data_values[j] = object_stringfromcstring(data[j], strlen(data[j]));
    }
    objectlist* data_list = object_newlist((int) data_n, data_values);
    value style_values[(int) style_n];
    for (size_t j=0; j<style_n; j++) { 
        style_values[j] = object_stringfromcstring(style[j], strlen(style[j]));
    }
    objectlist* style_list = object_newlist((int) style_n, style_values);
    value outval[3];
    outval[0] = MORPHO_OBJECT(coord_list);
    outval[1] = MORPHO_OBJECT(data_list);
    outval[2] = MORPHO_OBJECT(style_list);
    objectlist* outlist = object_newlist(3, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewSetInterpolationMatrices(vm* v, int nargs, value* args) {
    if (nargs != 8) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * type = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int d = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 3))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coef_list = MORPHO_GETLIST(MORPHO_GETARG(args, 3)); 
    int coef_len = list_length(coef_list); 
    double coef[coef_len]; 
    morphoGetDoubleStarFromList(v, coef_list, coef); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 4))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* exp_list = MORPHO_GETLIST(MORPHO_GETARG(args, 4)); 
    int exp_len = list_length(exp_list); 
    double exp[exp_len]; 
    morphoGetDoubleStarFromList(v, exp_list, exp); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dGeo = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 6))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* coefGeo_list = MORPHO_GETLIST(MORPHO_GETARG(args, 6)); 
    int coefGeo_len = list_length(coefGeo_list); 
    double coefGeo[coefGeo_len]; 
    morphoGetDoubleStarFromList(v, coefGeo_list, coefGeo); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 7))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* expGeo_list = MORPHO_GETLIST(MORPHO_GETARG(args, 7)); 
    int expGeo_len = list_length(expGeo_list); 
    double expGeo[expGeo_len]; 
    morphoGetDoubleStarFromList(v, expGeo_list, expGeo); 
    int ierr;
    gmshViewSetInterpolationMatrices(tag,
                                     type,
                                     d,
                                     coef, sizeof(coef)/sizeof(coef[0]),
                                     exp, sizeof(exp)/sizeof(exp[0]),
                                     dGeo,
                                     coefGeo, sizeof(coefGeo)/sizeof(coefGeo[0]),
                                     expGeo, sizeof(expGeo)/sizeof(expGeo[0]),
                                     &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewAddAlias(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int refTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int copyOptions = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    int outval = gmshViewAddAlias(refTag,
                     copyOptions,
                     tag,
                     &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshViewCombine(vm* v, int nargs, value* args) {
    if (nargs != 4) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * what = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * how = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int remove = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int copyOptions = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    int ierr;
    gmshViewCombine(what,
                    how,
                    remove,
                    copyOptions,
                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewProbe(vm* v, int nargs, value* args) {
    if (nargs != 12) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double x = morpho_get_double(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double y = morpho_get_double(MORPHO_GETARG(args, 2)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double z = morpho_get_double(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int step = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int numComp = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 6)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int gradient = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 6)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 7)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double distanceMax = morpho_get_double(MORPHO_GETARG(args, 7)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 8))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* xElemCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 8)); 
    int xElemCoord_len = list_length(xElemCoord_list); 
    double xElemCoord[xElemCoord_len]; 
    morphoGetDoubleStarFromList(v, xElemCoord_list, xElemCoord); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 9))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* yElemCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 9)); 
    int yElemCoord_len = list_length(yElemCoord_list); 
    double yElemCoord[yElemCoord_len]; 
    morphoGetDoubleStarFromList(v, yElemCoord_list, yElemCoord); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 10))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* zElemCoord_list = MORPHO_GETLIST(MORPHO_GETARG(args, 10)); 
    int zElemCoord_len = list_length(zElemCoord_list); 
    double zElemCoord[zElemCoord_len]; 
    morphoGetDoubleStarFromList(v, zElemCoord_list, zElemCoord); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 11)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int dim = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 11)); 
    double* values;
    size_t values_n;
    double distance;
    int ierr;
    gmshViewProbe(tag,
                  x,
                  y,
                  z,
                  &values, &values_n,
                  &distance,
                  step,
                  numComp,
                  gradient,
                  distanceMax,
                  xElemCoord, sizeof(xElemCoord)/sizeof(xElemCoord[0]),
                  yElemCoord, sizeof(yElemCoord)/sizeof(yElemCoord[0]),
                  zElemCoord, sizeof(zElemCoord)/sizeof(zElemCoord[0]),
                  dim,
                  &ierr);
    value values_value[(int) values_n];
    for (size_t j=0; j<values_n; j++) { 
        values_value[j] = MORPHO_FLOAT(values[j]);
    }
    objectlist* values_list = object_newlist((int) values_n, values_value);
    value outval[2];
    outval[0] = MORPHO_OBJECT(values_list);
    outval[1] = MORPHO_OBJECT(distance);
    objectlist* outlist = object_newlist(2, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewWrite(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int append = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshViewWrite(tag,
                  fileName,
                  append,
                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewSetVisibilityPerWindow(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int cvalue = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int windowIndex = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshViewSetVisibilityPerWindow(tag,
                                   cvalue,
                                   windowIndex,
                                   &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewOptionSetNumber(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double cvalue = morpho_get_double(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshViewOptionSetNumber(tag,
                            name,
                            cvalue,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewOptionGetNumber(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    double cvalue;
    int ierr;
    gmshViewOptionGetNumber(tag,
                            name,
                            &cvalue,
                            &ierr);
    return MORPHO_FLOAT(cvalue);
}

value MorphoGmshViewOptionSetString(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * cvalue = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshViewOptionSetString(tag,
                            name,
                            cvalue,
                            &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewOptionGetString(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    char * cvalue;
    int ierr;
    gmshViewOptionGetString(tag,
                            name,
                            &cvalue,
                            &ierr);
    value cvalue_value = object_stringfromcstring(cvalue, strlen(cvalue));
    objectstring* cvalue_str = MORPHO_GETSTRING(cvalue_value);
    value out;
    if (cvalue_str) {
        out = MORPHO_OBJECT(cvalue_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewOptionSetColor(vm* v, int nargs, value* args) {
    if (nargs != 6) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int r = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 2)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 3)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int g = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 3)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 4)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int b = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 4)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 5)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int a = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 5)); 
    int ierr;
    gmshViewOptionSetColor(tag,
                           name,
                           r,
                           g,
                           b,
                           a,
                           &ierr);
    return MORPHO_NIL;
}

value MorphoGmshViewOptionGetColor(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int r;
    int g;
    int b;
    int a;
    int ierr;
    gmshViewOptionGetColor(tag,
                           name,
                           &r,
                           &g,
                           &b,
                           &a,
                           &ierr);
    value outval[4];
    outval[0] = MORPHO_OBJECT(r);
    outval[1] = MORPHO_OBJECT(g);
    outval[2] = MORPHO_OBJECT(b);
    outval[3] = MORPHO_OBJECT(a);
    objectlist* outlist = object_newlist(4, outval);
    value out;
    if (outlist) {
        out = MORPHO_OBJECT(outlist);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshViewOptionCopy(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int refTag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int tag = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshViewOptionCopy(refTag,
                       tag,
                       &ierr);
    return MORPHO_NIL;
}

value MorphoGmshPluginSetNumber(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!morpho_is_double(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double cvalue = morpho_get_double(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshPluginSetNumber(name,
                        option,
                        cvalue,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshPluginSetString(vm* v, int nargs, value* args) {
    if (nargs != 3) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * option = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 2)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * cvalue = MORPHO_GETCSTRING(MORPHO_GETARG(args, 2)); 
    int ierr;
    gmshPluginSetString(name,
                        option,
                        cvalue,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshPluginRun(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    int outval = gmshPluginRun(name,
                  &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshGraphicsDraw(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshGraphicsDraw(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkInitialize(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFltkInitialize(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkFinalize(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFltkFinalize(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkWait(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!morpho_is_double(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const double time = morpho_get_double(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshFltkWait(time,
                 &ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkUpdate(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFltkUpdate(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkAwake(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * action = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshFltkAwake(action,
                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkLock(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFltkLock(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkUnlock(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFltkUnlock(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkRun(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshFltkRun(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshFltkIsAvailable(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    int outval = gmshFltkIsAvailable(&ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshParserGetNames(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * search = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    char ** names;
    size_t names_n;
    int ierr;
    gmshParserGetNames(&names, &names_n,
                       search,
                       &ierr);
    value names_values[(int) names_n];
    for (size_t j=0; j<names_n; j++) { 
        names_values[j] = object_stringfromcstring(names[j], strlen(names[j]));
    }
    objectlist* names_list = object_newlist((int) names_n, names_values);
    value out;
    if (names_list) {
        out = MORPHO_OBJECT(names_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshParserSetNumber(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cvalue_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int cvalue_len = list_length(cvalue_list); 
    double cvalue[cvalue_len]; 
    morphoGetDoubleStarFromList(v, cvalue_list, cvalue); 
    int ierr;
    gmshParserSetNumber(name,
                        cvalue, sizeof(cvalue)/sizeof(cvalue[0]),
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshParserSetString(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cvalue_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int cvalue_len = list_length(cvalue_list); 
    char const * cvalue[cvalue_len]; 
    morphoGetCharStarStarFromList(v, cvalue_list, cvalue); 
    int ierr;
    gmshParserSetString(name,
                        cvalue, cvalue_len,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshParserGetNumber(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    double* cvalue;
    size_t cvalue_n;
    int ierr;
    gmshParserGetNumber(name,
                        &cvalue, &cvalue_n,
                        &ierr);
    value cvalue_value[(int) cvalue_n];
    for (size_t j=0; j<cvalue_n; j++) { 
        cvalue_value[j] = MORPHO_FLOAT(cvalue[j]);
    }
    objectlist* cvalue_list = object_newlist((int) cvalue_n, cvalue_value);
    value out;
    if (cvalue_list) {
        out = MORPHO_OBJECT(cvalue_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshParserGetString(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    char ** cvalue;
    size_t cvalue_n;
    int ierr;
    gmshParserGetString(name,
                        &cvalue, &cvalue_n,
                        &ierr);
    value cvalue_values[(int) cvalue_n];
    for (size_t j=0; j<cvalue_n; j++) { 
        cvalue_values[j] = object_stringfromcstring(cvalue[j], strlen(cvalue[j]));
    }
    objectlist* cvalue_list = object_newlist((int) cvalue_n, cvalue_values);
    value out;
    if (cvalue_list) {
        out = MORPHO_OBJECT(cvalue_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshParserClear(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshParserClear(name,
                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshParserParse(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * fileName = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshParserParse(fileName,
                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOnelabSet(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * data = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * format = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshOnelabSet(data,
                  format,
                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOnelabGet(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * format = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    char * data;
    int ierr;
    gmshOnelabGet(&data,
                  name,
                  format,
                  &ierr);
    value data_value = object_stringfromcstring(data, strlen(data));
    objectstring* data_str = MORPHO_GETSTRING(data_value);
    value out;
    if (data_str) {
        out = MORPHO_OBJECT(data_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshOnelabGetNames(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * search = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    char ** names;
    size_t names_n;
    int ierr;
    gmshOnelabGetNames(&names, &names_n,
                       search,
                       &ierr);
    value names_values[(int) names_n];
    for (size_t j=0; j<names_n; j++) { 
        names_values[j] = object_stringfromcstring(names[j], strlen(names[j]));
    }
    objectlist* names_list = object_newlist((int) names_n, names_values);
    value out;
    if (names_list) {
        out = MORPHO_OBJECT(names_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshOnelabSetNumber(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cvalue_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int cvalue_len = list_length(cvalue_list); 
    double cvalue[cvalue_len]; 
    morphoGetDoubleStarFromList(v, cvalue_list, cvalue); 
    int ierr;
    gmshOnelabSetNumber(name,
                        cvalue, sizeof(cvalue)/sizeof(cvalue[0]),
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOnelabSetString(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, 1))) {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    objectlist* cvalue_list = MORPHO_GETLIST(MORPHO_GETARG(args, 1)); 
    int cvalue_len = list_length(cvalue_list); 
    char const * cvalue[cvalue_len]; 
    morphoGetCharStarStarFromList(v, cvalue_list, cvalue); 
    int ierr;
    gmshOnelabSetString(name,
                        cvalue, cvalue_len,
                        &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOnelabGetNumber(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    double* cvalue;
    size_t cvalue_n;
    int ierr;
    gmshOnelabGetNumber(name,
                        &cvalue, &cvalue_n,
                        &ierr);
    value cvalue_value[(int) cvalue_n];
    for (size_t j=0; j<cvalue_n; j++) { 
        cvalue_value[j] = MORPHO_FLOAT(cvalue[j]);
    }
    objectlist* cvalue_list = object_newlist((int) cvalue_n, cvalue_value);
    value out;
    if (cvalue_list) {
        out = MORPHO_OBJECT(cvalue_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshOnelabGetString(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    char ** cvalue;
    size_t cvalue_n;
    int ierr;
    gmshOnelabGetString(name,
                        &cvalue, &cvalue_n,
                        &ierr);
    value cvalue_values[(int) cvalue_n];
    for (size_t j=0; j<cvalue_n; j++) { 
        cvalue_values[j] = object_stringfromcstring(cvalue[j], strlen(cvalue[j]));
    }
    objectlist* cvalue_list = object_newlist((int) cvalue_n, cvalue_values);
    value out;
    if (cvalue_list) {
        out = MORPHO_OBJECT(cvalue_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshOnelabGetChanged(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    int outval = gmshOnelabGetChanged(name,
                         &ierr);
    return MORPHO_INTEGER(outval);
}

value MorphoGmshOnelabSetChanged(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISINTEGER(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const int cvalue = MORPHO_GETINTEGERVALUE(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshOnelabSetChanged(name,
                         cvalue,
                         &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOnelabClear(vm* v, int nargs, value* args) {
    if (nargs != 1) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    int ierr;
    gmshOnelabClear(name,
                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshOnelabRun(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * name = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * command = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshOnelabRun(name,
                  command,
                  &ierr);
    return MORPHO_NIL;
}

value MorphoGmshLoggerWrite(vm* v, int nargs, value* args) {
    if (nargs != 2) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 0)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * message = MORPHO_GETCSTRING(MORPHO_GETARG(args, 0)); 
    if (!MORPHO_ISSTRING(MORPHO_GETARG(args, 1)))  {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }
    const char * level = MORPHO_GETCSTRING(MORPHO_GETARG(args, 1)); 
    int ierr;
    gmshLoggerWrite(message,
                    level,
                    &ierr);
    return MORPHO_NIL;
}

value MorphoGmshLoggerStart(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshLoggerStart(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshLoggerGet(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    char ** log;
    size_t log_n;
    int ierr;
    gmshLoggerGet(&log, &log_n,
                  &ierr);
    value log_values[(int) log_n];
    for (size_t j=0; j<log_n; j++) { 
        log_values[j] = object_stringfromcstring(log[j], strlen(log[j]));
    }
    objectlist* log_list = object_newlist((int) log_n, log_values);
    value out;
    if (log_list) {
        out = MORPHO_OBJECT(log_list);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}

value MorphoGmshLoggerStop(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    gmshLoggerStop(&ierr);
    return MORPHO_NIL;
}

value MorphoGmshLoggerGetWallTime(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    double outval = gmshLoggerGetWallTime(&ierr);
    return MORPHO_FLOAT(outval);
}

value MorphoGmshLoggerGetCpuTime(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    int ierr;
    double outval = gmshLoggerGetCpuTime(&ierr);
    return MORPHO_FLOAT(outval);
}

value MorphoGmshLoggerGetLastError(vm* v, int nargs, value* args) {
    if (nargs != 0) {
        morpho_runtimeerror(v, GMSH_NARGS_ERROR);
        return MORPHO_NIL;
    } 
    char * error;
    int ierr;
    gmshLoggerGetLastError(&error,
                           &ierr);
    value error_value = object_stringfromcstring(error, strlen(error));
    objectstring* error_str = MORPHO_GETSTRING(error_value);
    value out;
    if (error_str) {
        out = MORPHO_OBJECT(error_str);
        morpho_bindobjects(v, 1, &out);
    }
    return out;
}
void gmshapi_initialize(void) {
    builtin_addfunction(MORPHOGMSHINITIALIZE_FUNCTION, MorphoGmshInitialize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHISINITIALIZED_FUNCTION, MorphoGmshIsInitialized, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFINALIZE_FUNCTION, MorphoGmshFinalize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPEN_FUNCTION, MorphoGmshOpen, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMERGE_FUNCTION, MorphoGmshMerge, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHWRITE_FUNCTION, MorphoGmshWrite, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHCLEAR_FUNCTION, MorphoGmshClear, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPTIONSETNUMBER_FUNCTION, MorphoGmshOptionSetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPTIONGETNUMBER_FUNCTION, MorphoGmshOptionGetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPTIONSETSTRING_FUNCTION, MorphoGmshOptionSetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPTIONGETSTRING_FUNCTION, MorphoGmshOptionGetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPTIONSETCOLOR_FUNCTION, MorphoGmshOptionSetColor, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHOPTIONGETCOLOR_FUNCTION, MorphoGmshOptionGetColor, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELADD_FUNCTION, MorphoGmshModelAdd, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREMOVE_FUNCTION, MorphoGmshModelRemove, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELLIST_FUNCTION, MorphoGmshModelList, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETCURRENT_FUNCTION, MorphoGmshModelGetCurrent, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETCURRENT_FUNCTION, MorphoGmshModelSetCurrent, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETFILENAME_FUNCTION, MorphoGmshModelGetFileName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETFILENAME_FUNCTION, MorphoGmshModelSetFileName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETENTITIES_FUNCTION, MorphoGmshModelGetEntities, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETENTITYNAME_FUNCTION, MorphoGmshModelSetEntityName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETENTITYNAME_FUNCTION, MorphoGmshModelGetEntityName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREMOVEENTITYNAME_FUNCTION, MorphoGmshModelRemoveEntityName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPHYSICALGROUPS_FUNCTION, MorphoGmshModelGetPhysicalGroups, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETENTITIESFORPHYSICALGROUP_FUNCTION, MorphoGmshModelGetEntitiesForPhysicalGroup, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETENTITIESFORPHYSICALNAME_FUNCTION, MorphoGmshModelGetEntitiesForPhysicalName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPHYSICALGROUPSFORENTITY_FUNCTION, MorphoGmshModelGetPhysicalGroupsForEntity, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELADDPHYSICALGROUP_FUNCTION, MorphoGmshModelAddPhysicalGroup, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREMOVEPHYSICALGROUPS_FUNCTION, MorphoGmshModelRemovePhysicalGroups, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETPHYSICALNAME_FUNCTION, MorphoGmshModelSetPhysicalName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPHYSICALNAME_FUNCTION, MorphoGmshModelGetPhysicalName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREMOVEPHYSICALNAME_FUNCTION, MorphoGmshModelRemovePhysicalName, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETTAG_FUNCTION, MorphoGmshModelSetTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETBOUNDARY_FUNCTION, MorphoGmshModelGetBoundary, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETADJACENCIES_FUNCTION, MorphoGmshModelGetAdjacencies, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETENTITIESINBOUNDINGBOX_FUNCTION, MorphoGmshModelGetEntitiesInBoundingBox, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETBOUNDINGBOX_FUNCTION, MorphoGmshModelGetBoundingBox, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETDIMENSION_FUNCTION, MorphoGmshModelGetDimension, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELADDDISCRETEENTITY_FUNCTION, MorphoGmshModelAddDiscreteEntity, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREMOVEENTITIES_FUNCTION, MorphoGmshModelRemoveEntities, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETTYPE_FUNCTION, MorphoGmshModelGetType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPARENT_FUNCTION, MorphoGmshModelGetParent, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETNUMBEROFPARTITIONS_FUNCTION, MorphoGmshModelGetNumberOfPartitions, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPARTITIONS_FUNCTION, MorphoGmshModelGetPartitions, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETVALUE_FUNCTION, MorphoGmshModelGetValue, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETDERIVATIVE_FUNCTION, MorphoGmshModelGetDerivative, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETSECONDDERIVATIVE_FUNCTION, MorphoGmshModelGetSecondDerivative, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETCURVATURE_FUNCTION, MorphoGmshModelGetCurvature, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPRINCIPALCURVATURES_FUNCTION, MorphoGmshModelGetPrincipalCurvatures, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETNORMAL_FUNCTION, MorphoGmshModelGetNormal, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPARAMETRIZATION_FUNCTION, MorphoGmshModelGetParametrization, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETPARAMETRIZATIONBOUNDS_FUNCTION, MorphoGmshModelGetParametrizationBounds, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELISINSIDE_FUNCTION, MorphoGmshModelIsInside, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETCLOSESTPOINT_FUNCTION, MorphoGmshModelGetClosestPoint, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREPARAMETRIZEONSURFACE_FUNCTION, MorphoGmshModelReparametrizeOnSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETVISIBILITY_FUNCTION, MorphoGmshModelSetVisibility, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETVISIBILITY_FUNCTION, MorphoGmshModelGetVisibility, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETVISIBILITYPERWINDOW_FUNCTION, MorphoGmshModelSetVisibilityPerWindow, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETCOLOR_FUNCTION, MorphoGmshModelSetColor, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETCOLOR_FUNCTION, MorphoGmshModelGetColor, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETCOORDINATES_FUNCTION, MorphoGmshModelSetCoordinates, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELSETATTRIBUTE_FUNCTION, MorphoGmshModelSetAttribute, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETATTRIBUTE_FUNCTION, MorphoGmshModelGetAttribute, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGETATTRIBUTENAMES_FUNCTION, MorphoGmshModelGetAttributeNames, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELREMOVEATTRIBUTE_FUNCTION, MorphoGmshModelRemoveAttribute, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGENERATE_FUNCTION, MorphoGmshModelMeshGenerate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHPARTITION_FUNCTION, MorphoGmshModelMeshPartition, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHUNPARTITION_FUNCTION, MorphoGmshModelMeshUnpartition, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHOPTIMIZE_FUNCTION, MorphoGmshModelMeshOptimize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHRECOMBINE_FUNCTION, MorphoGmshModelMeshRecombine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREFINE_FUNCTION, MorphoGmshModelMeshRefine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETORDER_FUNCTION, MorphoGmshModelMeshSetOrder, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETLASTENTITYERROR_FUNCTION, MorphoGmshModelMeshGetLastEntityError, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETLASTNODEERROR_FUNCTION, MorphoGmshModelMeshGetLastNodeError, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCLEAR_FUNCTION, MorphoGmshModelMeshClear, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREVERSE_FUNCTION, MorphoGmshModelMeshReverse, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREVERSEELEMENTS_FUNCTION, MorphoGmshModelMeshReverseElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHAFFINETRANSFORM_FUNCTION, MorphoGmshModelMeshAffineTransform, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETNODES_FUNCTION, MorphoGmshModelMeshGetNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETNODESBYELEMENTTYPE_FUNCTION, MorphoGmshModelMeshGetNodesByElementType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETNODE_FUNCTION, MorphoGmshModelMeshGetNode, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETNODE_FUNCTION, MorphoGmshModelMeshSetNode, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREBUILDNODECACHE_FUNCTION, MorphoGmshModelMeshRebuildNodeCache, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREBUILDELEMENTCACHE_FUNCTION, MorphoGmshModelMeshRebuildElementCache, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETNODESFORPHYSICALGROUP_FUNCTION, MorphoGmshModelMeshGetNodesForPhysicalGroup, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETMAXNODETAG_FUNCTION, MorphoGmshModelMeshGetMaxNodeTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHADDNODES_FUNCTION, MorphoGmshModelMeshAddNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHRECLASSIFYNODES_FUNCTION, MorphoGmshModelMeshReclassifyNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHRELOCATENODES_FUNCTION, MorphoGmshModelMeshRelocateNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTS_FUNCTION, MorphoGmshModelMeshGetElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENT_FUNCTION, MorphoGmshModelMeshGetElement, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTBYCOORDINATES_FUNCTION, MorphoGmshModelMeshGetElementByCoordinates, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTSBYCOORDINATES_FUNCTION, MorphoGmshModelMeshGetElementsByCoordinates, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETLOCALCOORDINATESINELEMENT_FUNCTION, MorphoGmshModelMeshGetLocalCoordinatesInElement, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTTYPES_FUNCTION, MorphoGmshModelMeshGetElementTypes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTTYPE_FUNCTION, MorphoGmshModelMeshGetElementType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTPROPERTIES_FUNCTION, MorphoGmshModelMeshGetElementProperties, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTSBYTYPE_FUNCTION, MorphoGmshModelMeshGetElementsByType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETMAXELEMENTTAG_FUNCTION, MorphoGmshModelMeshGetMaxElementTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHPREALLOCATEELEMENTSBYTYPE_FUNCTION, MorphoGmshModelMeshPreallocateElementsByType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTQUALITIES_FUNCTION, MorphoGmshModelMeshGetElementQualities, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHADDELEMENTS_FUNCTION, MorphoGmshModelMeshAddElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHADDELEMENTSBYTYPE_FUNCTION, MorphoGmshModelMeshAddElementsByType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETINTEGRATIONPOINTS_FUNCTION, MorphoGmshModelMeshGetIntegrationPoints, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETJACOBIANS_FUNCTION, MorphoGmshModelMeshGetJacobians, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHPREALLOCATEJACOBIANS_FUNCTION, MorphoGmshModelMeshPreallocateJacobians, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETJACOBIAN_FUNCTION, MorphoGmshModelMeshGetJacobian, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETBASISFUNCTIONS_FUNCTION, MorphoGmshModelMeshGetBasisFunctions, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETBASISFUNCTIONSORIENTATION_FUNCTION, MorphoGmshModelMeshGetBasisFunctionsOrientation, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETBASISFUNCTIONSORIENTATIONFORELEMENT_FUNCTION, MorphoGmshModelMeshGetBasisFunctionsOrientationForElement, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETNUMBEROFORIENTATIONS_FUNCTION, MorphoGmshModelMeshGetNumberOfOrientations, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHPREALLOCATEBASISFUNCTIONSORIENTATION_FUNCTION, MorphoGmshModelMeshPreallocateBasisFunctionsOrientation, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETEDGES_FUNCTION, MorphoGmshModelMeshGetEdges, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETFACES_FUNCTION, MorphoGmshModelMeshGetFaces, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCREATEEDGES_FUNCTION, MorphoGmshModelMeshCreateEdges, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCREATEFACES_FUNCTION, MorphoGmshModelMeshCreateFaces, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETALLEDGES_FUNCTION, MorphoGmshModelMeshGetAllEdges, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETALLFACES_FUNCTION, MorphoGmshModelMeshGetAllFaces, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHADDEDGES_FUNCTION, MorphoGmshModelMeshAddEdges, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHADDFACES_FUNCTION, MorphoGmshModelMeshAddFaces, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETKEYS_FUNCTION, MorphoGmshModelMeshGetKeys, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETKEYSFORELEMENT_FUNCTION, MorphoGmshModelMeshGetKeysForElement, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETNUMBEROFKEYS_FUNCTION, MorphoGmshModelMeshGetNumberOfKeys, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETKEYSINFORMATION_FUNCTION, MorphoGmshModelMeshGetKeysInformation, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETBARYCENTERS_FUNCTION, MorphoGmshModelMeshGetBarycenters, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHPREALLOCATEBARYCENTERS_FUNCTION, MorphoGmshModelMeshPreallocateBarycenters, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTEDGENODES_FUNCTION, MorphoGmshModelMeshGetElementEdgeNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETELEMENTFACENODES_FUNCTION, MorphoGmshModelMeshGetElementFaceNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETGHOSTELEMENTS_FUNCTION, MorphoGmshModelMeshGetGhostElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETSIZE_FUNCTION, MorphoGmshModelMeshSetSize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETSIZES_FUNCTION, MorphoGmshModelMeshGetSizes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETSIZEATPARAMETRICPOINTS_FUNCTION, MorphoGmshModelMeshSetSizeAtParametricPoints, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREMOVESIZECALLBACK_FUNCTION, MorphoGmshModelMeshRemoveSizeCallback, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETTRANSFINITECURVE_FUNCTION, MorphoGmshModelMeshSetTransfiniteCurve, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETTRANSFINITESURFACE_FUNCTION, MorphoGmshModelMeshSetTransfiniteSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETTRANSFINITEVOLUME_FUNCTION, MorphoGmshModelMeshSetTransfiniteVolume, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETTRANSFINITEAUTOMATIC_FUNCTION, MorphoGmshModelMeshSetTransfiniteAutomatic, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETRECOMBINE_FUNCTION, MorphoGmshModelMeshSetRecombine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETSMOOTHING_FUNCTION, MorphoGmshModelMeshSetSmoothing, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETREVERSE_FUNCTION, MorphoGmshModelMeshSetReverse, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETALGORITHM_FUNCTION, MorphoGmshModelMeshSetAlgorithm, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETSIZEFROMBOUNDARY_FUNCTION, MorphoGmshModelMeshSetSizeFromBoundary, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETCOMPOUND_FUNCTION, MorphoGmshModelMeshSetCompound, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETOUTWARDORIENTATION_FUNCTION, MorphoGmshModelMeshSetOutwardOrientation, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREMOVECONSTRAINTS_FUNCTION, MorphoGmshModelMeshRemoveConstraints, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHEMBED_FUNCTION, MorphoGmshModelMeshEmbed, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREMOVEEMBEDDED_FUNCTION, MorphoGmshModelMeshRemoveEmbedded, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETEMBEDDED_FUNCTION, MorphoGmshModelMeshGetEmbedded, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREORDERELEMENTS_FUNCTION, MorphoGmshModelMeshReorderElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCOMPUTERENUMBERING_FUNCTION, MorphoGmshModelMeshComputeRenumbering, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHRENUMBERNODES_FUNCTION, MorphoGmshModelMeshRenumberNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHRENUMBERELEMENTS_FUNCTION, MorphoGmshModelMeshRenumberElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETPERIODIC_FUNCTION, MorphoGmshModelMeshSetPeriodic, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETPERIODIC_FUNCTION, MorphoGmshModelMeshGetPeriodic, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETPERIODICNODES_FUNCTION, MorphoGmshModelMeshGetPeriodicNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETPERIODICKEYS_FUNCTION, MorphoGmshModelMeshGetPeriodicKeys, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHIMPORTSTL_FUNCTION, MorphoGmshModelMeshImportStl, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETDUPLICATENODES_FUNCTION, MorphoGmshModelMeshGetDuplicateNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREMOVEDUPLICATENODES_FUNCTION, MorphoGmshModelMeshRemoveDuplicateNodes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHREMOVEDUPLICATEELEMENTS_FUNCTION, MorphoGmshModelMeshRemoveDuplicateElements, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSPLITQUADRANGLES_FUNCTION, MorphoGmshModelMeshSplitQuadrangles, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHSETVISIBILITY_FUNCTION, MorphoGmshModelMeshSetVisibility, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHGETVISIBILITY_FUNCTION, MorphoGmshModelMeshGetVisibility, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCLASSIFYSURFACES_FUNCTION, MorphoGmshModelMeshClassifySurfaces, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCREATEGEOMETRY_FUNCTION, MorphoGmshModelMeshCreateGeometry, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCREATETOPOLOGY_FUNCTION, MorphoGmshModelMeshCreateTopology, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHADDHOMOLOGYREQUEST_FUNCTION, MorphoGmshModelMeshAddHomologyRequest, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCLEARHOMOLOGYREQUESTS_FUNCTION, MorphoGmshModelMeshClearHomologyRequests, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCOMPUTEHOMOLOGY_FUNCTION, MorphoGmshModelMeshComputeHomology, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHCOMPUTECROSSFIELD_FUNCTION, MorphoGmshModelMeshComputeCrossField, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHTRIANGULATE_FUNCTION, MorphoGmshModelMeshTriangulate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHTETRAHEDRALIZE_FUNCTION, MorphoGmshModelMeshTetrahedralize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDADD_FUNCTION, MorphoGmshModelMeshFieldAdd, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDREMOVE_FUNCTION, MorphoGmshModelMeshFieldRemove, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDLIST_FUNCTION, MorphoGmshModelMeshFieldList, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDGETTYPE_FUNCTION, MorphoGmshModelMeshFieldGetType, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDSETNUMBER_FUNCTION, MorphoGmshModelMeshFieldSetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDGETNUMBER_FUNCTION, MorphoGmshModelMeshFieldGetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDSETSTRING_FUNCTION, MorphoGmshModelMeshFieldSetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDGETSTRING_FUNCTION, MorphoGmshModelMeshFieldGetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDSETNUMBERS_FUNCTION, MorphoGmshModelMeshFieldSetNumbers, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDGETNUMBERS_FUNCTION, MorphoGmshModelMeshFieldGetNumbers, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDSETASBACKGROUNDMESH_FUNCTION, MorphoGmshModelMeshFieldSetAsBackgroundMesh, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELMESHFIELDSETASBOUNDARYLAYER_FUNCTION, MorphoGmshModelMeshFieldSetAsBoundaryLayer, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDPOINT_FUNCTION, MorphoGmshModelGeoAddPoint, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDLINE_FUNCTION, MorphoGmshModelGeoAddLine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDCIRCLEARC_FUNCTION, MorphoGmshModelGeoAddCircleArc, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDELLIPSEARC_FUNCTION, MorphoGmshModelGeoAddEllipseArc, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDSPLINE_FUNCTION, MorphoGmshModelGeoAddSpline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDBSPLINE_FUNCTION, MorphoGmshModelGeoAddBSpline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDBEZIER_FUNCTION, MorphoGmshModelGeoAddBezier, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDPOLYLINE_FUNCTION, MorphoGmshModelGeoAddPolyline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDCOMPOUNDSPLINE_FUNCTION, MorphoGmshModelGeoAddCompoundSpline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDCOMPOUNDBSPLINE_FUNCTION, MorphoGmshModelGeoAddCompoundBSpline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDCURVELOOP_FUNCTION, MorphoGmshModelGeoAddCurveLoop, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDCURVELOOPS_FUNCTION, MorphoGmshModelGeoAddCurveLoops, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDPLANESURFACE_FUNCTION, MorphoGmshModelGeoAddPlaneSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDSURFACEFILLING_FUNCTION, MorphoGmshModelGeoAddSurfaceFilling, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDSURFACELOOP_FUNCTION, MorphoGmshModelGeoAddSurfaceLoop, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDVOLUME_FUNCTION, MorphoGmshModelGeoAddVolume, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDGEOMETRY_FUNCTION, MorphoGmshModelGeoAddGeometry, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDPOINTONGEOMETRY_FUNCTION, MorphoGmshModelGeoAddPointOnGeometry, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOEXTRUDE_FUNCTION, MorphoGmshModelGeoExtrude, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOREVOLVE_FUNCTION, MorphoGmshModelGeoRevolve, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOTWIST_FUNCTION, MorphoGmshModelGeoTwist, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOEXTRUDEBOUNDARYLAYER_FUNCTION, MorphoGmshModelGeoExtrudeBoundaryLayer, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOTRANSLATE_FUNCTION, MorphoGmshModelGeoTranslate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOROTATE_FUNCTION, MorphoGmshModelGeoRotate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEODILATE_FUNCTION, MorphoGmshModelGeoDilate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMIRROR_FUNCTION, MorphoGmshModelGeoMirror, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOSYMMETRIZE_FUNCTION, MorphoGmshModelGeoSymmetrize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOCOPY_FUNCTION, MorphoGmshModelGeoCopy, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOREMOVE_FUNCTION, MorphoGmshModelGeoRemove, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOREMOVEALLDUPLICATES_FUNCTION, MorphoGmshModelGeoRemoveAllDuplicates, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOSPLITCURVE_FUNCTION, MorphoGmshModelGeoSplitCurve, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOGETMAXTAG_FUNCTION, MorphoGmshModelGeoGetMaxTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOSETMAXTAG_FUNCTION, MorphoGmshModelGeoSetMaxTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOADDPHYSICALGROUP_FUNCTION, MorphoGmshModelGeoAddPhysicalGroup, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOREMOVEPHYSICALGROUPS_FUNCTION, MorphoGmshModelGeoRemovePhysicalGroups, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOSYNCHRONIZE_FUNCTION, MorphoGmshModelGeoSynchronize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETSIZE_FUNCTION, MorphoGmshModelGeoMeshSetSize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETTRANSFINITECURVE_FUNCTION, MorphoGmshModelGeoMeshSetTransfiniteCurve, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETTRANSFINITESURFACE_FUNCTION, MorphoGmshModelGeoMeshSetTransfiniteSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETTRANSFINITEVOLUME_FUNCTION, MorphoGmshModelGeoMeshSetTransfiniteVolume, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETRECOMBINE_FUNCTION, MorphoGmshModelGeoMeshSetRecombine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETSMOOTHING_FUNCTION, MorphoGmshModelGeoMeshSetSmoothing, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETREVERSE_FUNCTION, MorphoGmshModelGeoMeshSetReverse, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETALGORITHM_FUNCTION, MorphoGmshModelGeoMeshSetAlgorithm, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELGEOMESHSETSIZEFROMBOUNDARY_FUNCTION, MorphoGmshModelGeoMeshSetSizeFromBoundary, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDPOINT_FUNCTION, MorphoGmshModelOccAddPoint, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDLINE_FUNCTION, MorphoGmshModelOccAddLine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDCIRCLEARC_FUNCTION, MorphoGmshModelOccAddCircleArc, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDCIRCLE_FUNCTION, MorphoGmshModelOccAddCircle, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDELLIPSEARC_FUNCTION, MorphoGmshModelOccAddEllipseArc, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDELLIPSE_FUNCTION, MorphoGmshModelOccAddEllipse, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDSPLINE_FUNCTION, MorphoGmshModelOccAddSpline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBSPLINE_FUNCTION, MorphoGmshModelOccAddBSpline, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBEZIER_FUNCTION, MorphoGmshModelOccAddBezier, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDWIRE_FUNCTION, MorphoGmshModelOccAddWire, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDCURVELOOP_FUNCTION, MorphoGmshModelOccAddCurveLoop, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDRECTANGLE_FUNCTION, MorphoGmshModelOccAddRectangle, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDDISK_FUNCTION, MorphoGmshModelOccAddDisk, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDPLANESURFACE_FUNCTION, MorphoGmshModelOccAddPlaneSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDSURFACEFILLING_FUNCTION, MorphoGmshModelOccAddSurfaceFilling, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBSPLINEFILLING_FUNCTION, MorphoGmshModelOccAddBSplineFilling, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBEZIERFILLING_FUNCTION, MorphoGmshModelOccAddBezierFilling, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBSPLINESURFACE_FUNCTION, MorphoGmshModelOccAddBSplineSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBEZIERSURFACE_FUNCTION, MorphoGmshModelOccAddBezierSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDTRIMMEDSURFACE_FUNCTION, MorphoGmshModelOccAddTrimmedSurface, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDSURFACELOOP_FUNCTION, MorphoGmshModelOccAddSurfaceLoop, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDVOLUME_FUNCTION, MorphoGmshModelOccAddVolume, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDSPHERE_FUNCTION, MorphoGmshModelOccAddSphere, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDBOX_FUNCTION, MorphoGmshModelOccAddBox, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDCYLINDER_FUNCTION, MorphoGmshModelOccAddCylinder, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDCONE_FUNCTION, MorphoGmshModelOccAddCone, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDWEDGE_FUNCTION, MorphoGmshModelOccAddWedge, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDTORUS_FUNCTION, MorphoGmshModelOccAddTorus, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDTHRUSECTIONS_FUNCTION, MorphoGmshModelOccAddThruSections, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDTHICKSOLID_FUNCTION, MorphoGmshModelOccAddThickSolid, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCEXTRUDE_FUNCTION, MorphoGmshModelOccExtrude, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCREVOLVE_FUNCTION, MorphoGmshModelOccRevolve, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCADDPIPE_FUNCTION, MorphoGmshModelOccAddPipe, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCFILLET_FUNCTION, MorphoGmshModelOccFillet, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCCHAMFER_FUNCTION, MorphoGmshModelOccChamfer, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCFUSE_FUNCTION, MorphoGmshModelOccFuse, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCINTERSECT_FUNCTION, MorphoGmshModelOccIntersect, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCCUT_FUNCTION, MorphoGmshModelOccCut, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCFRAGMENT_FUNCTION, MorphoGmshModelOccFragment, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCTRANSLATE_FUNCTION, MorphoGmshModelOccTranslate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCROTATE_FUNCTION, MorphoGmshModelOccRotate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCDILATE_FUNCTION, MorphoGmshModelOccDilate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCMIRROR_FUNCTION, MorphoGmshModelOccMirror, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCSYMMETRIZE_FUNCTION, MorphoGmshModelOccSymmetrize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCAFFINETRANSFORM_FUNCTION, MorphoGmshModelOccAffineTransform, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCCOPY_FUNCTION, MorphoGmshModelOccCopy, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCREMOVE_FUNCTION, MorphoGmshModelOccRemove, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCREMOVEALLDUPLICATES_FUNCTION, MorphoGmshModelOccRemoveAllDuplicates, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCHEALSHAPES_FUNCTION, MorphoGmshModelOccHealShapes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCCONVERTTONURBS_FUNCTION, MorphoGmshModelOccConvertToNURBS, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCIMPORTSHAPES_FUNCTION, MorphoGmshModelOccImportShapes, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETENTITIES_FUNCTION, MorphoGmshModelOccGetEntities, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETENTITIESINBOUNDINGBOX_FUNCTION, MorphoGmshModelOccGetEntitiesInBoundingBox, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETBOUNDINGBOX_FUNCTION, MorphoGmshModelOccGetBoundingBox, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETCURVELOOPS_FUNCTION, MorphoGmshModelOccGetCurveLoops, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETSURFACELOOPS_FUNCTION, MorphoGmshModelOccGetSurfaceLoops, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETMASS_FUNCTION, MorphoGmshModelOccGetMass, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETCENTEROFMASS_FUNCTION, MorphoGmshModelOccGetCenterOfMass, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETMATRIXOFINERTIA_FUNCTION, MorphoGmshModelOccGetMatrixOfInertia, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCGETMAXTAG_FUNCTION, MorphoGmshModelOccGetMaxTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCSETMAXTAG_FUNCTION, MorphoGmshModelOccSetMaxTag, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCSYNCHRONIZE_FUNCTION, MorphoGmshModelOccSynchronize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHMODELOCCMESHSETSIZE_FUNCTION, MorphoGmshModelOccMeshSetSize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWADD_FUNCTION, MorphoGmshViewAdd, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWREMOVE_FUNCTION, MorphoGmshViewRemove, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWGETINDEX_FUNCTION, MorphoGmshViewGetIndex, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWGETTAGS_FUNCTION, MorphoGmshViewGetTags, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWADDMODELDATA_FUNCTION, MorphoGmshViewAddModelData, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWADDHOMOGENEOUSMODELDATA_FUNCTION, MorphoGmshViewAddHomogeneousModelData, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWGETMODELDATA_FUNCTION, MorphoGmshViewGetModelData, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWGETHOMOGENEOUSMODELDATA_FUNCTION, MorphoGmshViewGetHomogeneousModelData, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWADDLISTDATA_FUNCTION, MorphoGmshViewAddListData, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWGETLISTDATA_FUNCTION, MorphoGmshViewGetListData, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWADDLISTDATASTRING_FUNCTION, MorphoGmshViewAddListDataString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWGETLISTDATASTRINGS_FUNCTION, MorphoGmshViewGetListDataStrings, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWSETINTERPOLATIONMATRICES_FUNCTION, MorphoGmshViewSetInterpolationMatrices, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWADDALIAS_FUNCTION, MorphoGmshViewAddAlias, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWCOMBINE_FUNCTION, MorphoGmshViewCombine, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWPROBE_FUNCTION, MorphoGmshViewProbe, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWWRITE_FUNCTION, MorphoGmshViewWrite, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWSETVISIBILITYPERWINDOW_FUNCTION, MorphoGmshViewSetVisibilityPerWindow, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONSETNUMBER_FUNCTION, MorphoGmshViewOptionSetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONGETNUMBER_FUNCTION, MorphoGmshViewOptionGetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONSETSTRING_FUNCTION, MorphoGmshViewOptionSetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONGETSTRING_FUNCTION, MorphoGmshViewOptionGetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONSETCOLOR_FUNCTION, MorphoGmshViewOptionSetColor, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONGETCOLOR_FUNCTION, MorphoGmshViewOptionGetColor, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHVIEWOPTIONCOPY_FUNCTION, MorphoGmshViewOptionCopy, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPLUGINSETNUMBER_FUNCTION, MorphoGmshPluginSetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPLUGINSETSTRING_FUNCTION, MorphoGmshPluginSetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPLUGINRUN_FUNCTION, MorphoGmshPluginRun, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHGRAPHICSDRAW_FUNCTION, MorphoGmshGraphicsDraw, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKINITIALIZE_FUNCTION, MorphoGmshFltkInitialize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKFINALIZE_FUNCTION, MorphoGmshFltkFinalize, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKWAIT_FUNCTION, MorphoGmshFltkWait, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKUPDATE_FUNCTION, MorphoGmshFltkUpdate, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKAWAKE_FUNCTION, MorphoGmshFltkAwake, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKLOCK_FUNCTION, MorphoGmshFltkLock, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKUNLOCK_FUNCTION, MorphoGmshFltkUnlock, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKRUN_FUNCTION, MorphoGmshFltkRun, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHFLTKISAVAILABLE_FUNCTION, MorphoGmshFltkIsAvailable, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERGETNAMES_FUNCTION, MorphoGmshParserGetNames, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERSETNUMBER_FUNCTION, MorphoGmshParserSetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERSETSTRING_FUNCTION, MorphoGmshParserSetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERGETNUMBER_FUNCTION, MorphoGmshParserGetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERGETSTRING_FUNCTION, MorphoGmshParserGetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERCLEAR_FUNCTION, MorphoGmshParserClear, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHPARSERPARSE_FUNCTION, MorphoGmshParserParse, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABSET_FUNCTION, MorphoGmshOnelabSet, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABGET_FUNCTION, MorphoGmshOnelabGet, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABGETNAMES_FUNCTION, MorphoGmshOnelabGetNames, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABSETNUMBER_FUNCTION, MorphoGmshOnelabSetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABSETSTRING_FUNCTION, MorphoGmshOnelabSetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABGETNUMBER_FUNCTION, MorphoGmshOnelabGetNumber, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABGETSTRING_FUNCTION, MorphoGmshOnelabGetString, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABGETCHANGED_FUNCTION, MorphoGmshOnelabGetChanged, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABSETCHANGED_FUNCTION, MorphoGmshOnelabSetChanged, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABCLEAR_FUNCTION, MorphoGmshOnelabClear, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHONELABRUN_FUNCTION, MorphoGmshOnelabRun, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERWRITE_FUNCTION, MorphoGmshLoggerWrite, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERSTART_FUNCTION, MorphoGmshLoggerStart, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERGET_FUNCTION, MorphoGmshLoggerGet, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERSTOP_FUNCTION, MorphoGmshLoggerStop, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERGETWALLTIME_FUNCTION, MorphoGmshLoggerGetWallTime, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERGETCPUTIME_FUNCTION, MorphoGmshLoggerGetCpuTime, BUILTIN_FLAGSEMPTY);
    builtin_addfunction(MORPHOGMSHLOGGERGETLASTERROR_FUNCTION, MorphoGmshLoggerGetLastError, BUILTIN_FLAGSEMPTY);

    morpho_defineerror(GMSH_NARGS_ERROR, ERROR_HALT, GMSH_NARGS_ERROR_MSG);
    morpho_defineerror(GMSH_ARGS_ERROR, ERROR_HALT, GMSH_ARGS_ERROR_MSG);

}

void gmshapi_finalize(void) { 
    int ierr;
    int outval = gmshIsInitialized(&ierr);
    if (outval != 0) {
        gmshFinalize(&ierr);
    }
}
