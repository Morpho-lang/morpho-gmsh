# This is a version of the Gmsh API generation file 
# https://gitlab.onelab.info/gmsh/gmsh/blob/master/api/GenApi.py
# adpoted for the purpose of generating (partial) bindings for the Morpho language
# https://github.com/Morpho-lang/morpho from the 
# Gmsh API definitions file:
# https://gitlab.onelab.info/gmsh/gmsh/blob/master/api/gen.py

# Credit to
# Gmsh - Copyright (C) 1997-2019 C. Geuzaine, J.-F. Remacle
# Contributor(s):
#   Jonathan Lambrechts
#
# Modifications for Morpho by Chaitanya Joshi (chaitanyajoshi.usa@gmail.com)

# Morpho is written in C, so it's easiest to use Gmsh's C-API. 
# This API generator will essentially wrap the C function calls as Morpho function calls with appropriate modifications to the inputs and outputs.

# Currently skips the following functions:
# 1. gmshModelMeshSetSizeCallback (Handling of the isizefun class is not implemented yet)
# 2. gmshModelOccImportShapesNativePointer (Handling of the ivectorstar class is not implemented yet)
# 3. gmshFltkSelectEntities (and other future C functions that have both a non-void return type and return something via assigning to pointers, as this case is not handled yet.)
  
# The design of this Morpho-specific binding was improved by 
# inspirations from a Haskell Binding to the Gmsh API 
# by Antero Marjamäki : https://github.com/Ehtycs/haskell-gmsh/

# Gmsh API generator for Morpho-lang. By Chaitanya Joshi
import textwrap
import string
import os
import re

INDENTL1 = "    "
INDENTL2 = "        "
INDENTL3 = "            "
EXTENSION_NAME = "gmshapi"
# Removing all the Python, Julia and Fortran related attributes, but
# keeping the function call signatures the same in order to use gen.py 
# without editing.
class arg:
    """ Basic datatype of an argument. Every datatype inherits this constructor
    and also default behaviour from here.
    
    Compared to the original, this object only stores the C-related information (to actually call the C-API functions) and Morpho-specific information. 

    Subclasses of this constructor will have methods for processing inputs/outputs, etc.

    """
    def __init__(self, name, value, python_value, julia_value, cpp_type,
                 c_type, out):
        self.c_type = c_type
        self.name = name
        if (name == "value"): # value is a builtin type in Morpho, so change it slightly
            self.name = "cvalue"
            name = "cvalue"
        if (name == "v"): # Similarly, v is used for the virtual machine (vm) in Morpho
            self.name = "cv"
            name = "cv"
        self.value = value
        self.out = out
        self.c = c_type + " " + name
        self.texi_type = ""
        self.texi = name + ""
        # self.morpho will be used in place of self.c while calling the C-API functions, since the inputs will be slightly different while calling from the Morpho wrappers.
        self.morpho = name 
        # self.morpho_object specifies how to name the Morpho Objects corresponding to the args. For instance, a string would have morpho_object as name + "_str", so that it is declared as `objectstring * name_str = ...` 
        self.morpho_object = name

class inputArg(arg):
    """
    Basic datatype for an input argument, inherited from `arg`. Provides some extra attributes and methods to process the input.
    """
    def __init__(self, name, value, python_value, julia_value, cpp_type, c_type, out):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)

        # C-code to generate specific runtime error if the arguments are not correct. To-do: Currently, all inputs return the same error. Change this so that the error is function-specific or more helpful in general.
        self.runTimeErr = " {morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }\n"
        # morphoTypeChecker is the builtin (or otherwise) Morpho function to check whether the input value is of the correct type.
        self.morphoTypeCheker = "MORPHO_ISINTEGER" # For default, using the integer case
        # morphoToCConverter is the builtin (or otherwise) Morpho function to grab the correct C-type from the input Morpho value.
        self.morphoToCConverter = "MORPHO_GETINTEGERVALUE"


    def capture_input(self, i):
        """
        capture_input(i)

        Generates C-code to check the (i+1)th input argument to the Morpho function and convert it to an appropriate C-type.
        """
        
        # Here, we check for a single object as defualt, which can be reused for anything that's not a list: `iint`, `idouble, `istring`, etc.
        chk = INDENTL1 + f"if (!{self.morphoTypeCheker}(MORPHO_GETARG(args, {i}))) " + self.runTimeErr
        inp = INDENTL1 + f"{self.c_type} {self.name} = {self.morphoToCConverter}(MORPHO_GETARG(args, {i})); \n"
        return chk + inp

# input types
    
# iint, isize and ibool, all need the same morphoTypeChecker and morphoToCConverter.
class iint(inputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const int", c_type="const int", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.texi_type = "integer"
    

class isize(inputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None, 
                 cpp_type="const std::size_t", c_type="const size_t", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.texi_type = "size"
        
    
class ibool(inputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None, 
                 cpp_type="const bool", c_type="const int", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.texi_type = "boolean"


class idouble(inputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const double", c_type="const double", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.texi_type = "double"
        # Need different type functions for double.
        self.morphoTypeCheker = "morpho_is_double" # For default, using the integer case
        self.morphoToCConverter = "morpho_get_double"

class istring(inputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const std::string &", c_type="const char *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.texi_type = "string"
        self.morphoTypeCheker = "MORPHO_ISSTRING"
        self.morphoToCConverter = "MORPHO_GETCSTRING"

# Haven't implemented this one yet, but it isn't required for the modules currently implemented.
# To-do: Figure out how to handle this one. 
def ivoidstar(name, value=None, python_value=None, julia_value=None):
    a = arg(name, value, python_value, julia_value, "const void *",
            "const void *", False)
    a.texi_type = "pointer"
    return a

# Now we begin the vector inputs, that will require different `capture_input` methods.
# We will first define the ivectorint type and will inherit from it for the rest of the input vectors
class ivectorint(inputArg):
    
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const std::vector<int> &", c_type="const int *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c = "const int * " + self.name + ", const size_t " + self.name + "_n"
        self.morpho = self.name + f", sizeof({self.name})/sizeof({self.name}[0])"
        self.texi_type = "vector of integers"
        # Since the vector inputs are all going to be Morpho Lists, we don't need to specify `morphoTypeChecker` and `morphoToCConverter`. Instead, we need the C-types for the arrays of inputs and functions to get them from Morpho Lists, as seen below.
        self.inputListType = "int" # will initialize an `int name[length]; // list`
        self.toListFunction = "morphoGetIntStarFromList" # Function to get an int * from a Morpho List (defined in this file).
        
    def capture_input(self, i):
        """
        capture_input(i)

        Generates C-code to check the (i+1)th input argument to the Morpho function and convert it to an appropriate C-type. 

        Since this is a list, we first check whether the input is a Morpho List, then create an C array and call a function to pull the Morpho List elements into this array.
        """
        chk =  INDENTL1 + f"if (!MORPHO_ISLIST(MORPHO_GETARG(args, {i})))" + self.runTimeErr
        inp =  INDENTL1 + f"objectlist* {self.name}_list = MORPHO_GETLIST(MORPHO_GETARG(args, {i})); \n"
        inp += INDENTL1 + f"int {self.name}_len = list_length({self.name}_list); \n" \
             + INDENTL1 + f"{self.inputListType} {self.name}[{self.name}_len]; \n"
        inp += INDENTL1 + f"{self.toListFunction}(v, {self.name}_list, {self.name}); \n"
        return chk + inp

class ivectorpair(ivectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const gmsh::vectorpair &", c_type="const int *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.texi_type = "vector of pairs of integers"
    
class ivectorsize(ivectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const std::vector<std::size_t> &", c_type="const size_t *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c = "const size_t * " + self.name + ", const size_t " + self.name + "_n"
        self.morpho = self.name + f", sizeof({self.name})/sizeof({self.name}[0])"
        self.texi_type = "vector of sizes"
        self.inputListType = "size_t"
        self.toListFunction = "morphoGetSizeTStarFromList"

class ivectordouble(ivectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const std::vector<double> &", c_type="const double * const *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c = "const double * " + self.name + ", const size_t " + self.name + "_n"
        self.morpho = self.name + f", sizeof({self.name})/sizeof({self.name}[0])"
        self.texi_type = "vector of doubles"
        self.inputListType = "double"
        self.toListFunction = "morphoGetDoubleStarFromList"

class ivectorstring(ivectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None, cpp_type="const std::vector<std::string> &", c_type="const char * const *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c = "const char * const * " + self.name + ", const size_t " + self.name + "_n"
        self.morpho = self.name + f", {self.name}_len"
        self.texi_type = "vector of strings"
        self.inputListType = "char const *"
        self.toListFunction = "morphoGetCharStarStarFromList"

# Now we begin the vector of vector inputs, that will require yet another `capture_input` methods.
# We will first define the ivectorvectorint as a prototype
class ivectorvectorint(ivectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None,
                 cpp_type="const std::vector<std::vector<int> > &", 
                 c_type="const int * const *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
    
        self.c = ("const int * const * " + self.name + ", const size_t * " + self.name + "_n, " +
            "const size_t " + self.name + "_nn")
        self.texi_type = "vector of vectors of integers"
        self.elementType = "int"

    def capture_input(self, i):
        """
        capture_input(i)

        Generates C-code to check the (i+1)th input argument to the Morpho function and convert it to an appropriate C-type. 

        Similar to the one for lists, but modified to capture list of lists.
        """

        out = """
    if (!MORPHO_ISLIST(MORPHO_GETARG(args, {3}))) {{ morpho_runtimeerror(v, GMSH_ARGS_ERROR); return MORPHO_NIL; }}
    objectlist* {2}_list = MORPHO_GETLIST(MORPHO_GETARG(args, {3}));
    {0} {2}_nn = (size_t) list_length({2}_list);
    {0} * {2}_n;
    {0} ** {2};
    value {2}_elI;
    objectlist * {2}_li;
    bool {2}_success;
    for (size_t i=0; i<{2}_nn; i++) {{
        {2}_success = ({2}_success && list_getelement({2}_list, i, &{2}_elI));
        if (!MORPHO_ISLIST({2}_elI)) {{
            morpho_runtimeerror(v, GMSH_ARGS_ERROR); 
            return MORPHO_NIL; 
        }}
        {2}_li = MORPHO_GETLIST({2}_elI);
        {2}_n[i] = (size_t) list_length({2}_li);
        {1}(v, {2}_li, {2}[i]);
    }}
        """.format(self.elementType, self.toListFunction, self.name, i)
        return out

class ivectorvectorsize(ivectorvectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None,
                 cpp_type="const std::vector<std::vector<std::size_t> > &", c_type="const size_t * const *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c = ("const size_t * const * " + self.name + ", const size_t * " + self.name + "_n, " +
           "const size_t " + self.name + "_nn")
        self.morpho = self.name + ", " + self.name + "_n, " + self.name + "_nn"
        self.texi_type = "vector of vectors of integers (size)"
        self.toListFunction = "morphoGetSizeTStarFromList"
        self.elementType = "size_t"

class ivectorvectordouble(ivectorvectorint):
    def __init__(self, name, value=None, python_value=None, julia_value=None,
                 cpp_type="const std::vector<std::vector<double> > &", c_type="const double * const *", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c = ("const double * const * " + self.name + ", const size_t * " + self.name + "_n, " +
           "const size_t " + self.name + "_nn")
        self.morpho = self.name + ", " + self.name + "_n, " + self.name + "_nn"
        self.texi_type = "vector of vectors of doubles"
        self.toListFunction = "morphoGetDoubleStarFromList"
        self.elementType = "double"

# output types

class outputArg(arg):
    """
    Basic datatype for an output argument, inherited from `arg`. 
    Defines some extra methods to process the output. This makes sure that
    the methods below exist even for simple outputs that don't require some of them.
    """
    def capture_output(self):
        return "" 


class oint(outputArg):
    rc_type = "int"
    texi_type = "integer"
    cToMorphoConverter = "MORPHO_INTEGER"
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value, "int &",
                     "int *", True)
        self.texi_type = "integer"
        self.morpho = "&" + self.name
        self.elementType = "int"
        self.cToMorphoConverter = "MORPHO_INTEGER"
    
    def init_output(self):
        
        return INDENTL1 + f"{self.elementType} {self.name};\n" 
    
    def return_output(self):
        
        return INDENTL1 + f"return {self.cToMorphoConverter}({self.name});\n"

class osize(oint):
    rc_type = "size_t"
    texi_type = "size"

    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value,
                     "std::size_t &", "size_t *", True)
        self.texi_type = "size"
        self.morpho = "&" + self.name
        self.elementType = "size_t"
        self.cToMorphoConverter = "MORPHO_INTEGER"
    
    def return_output(self):
        
        return INDENTL1 + f"return {self.cToMorphoConverter}((int) {self.name});\n"


class odouble(oint):
    rc_type = "double"
    texi_type = "double"
    cToMorphoConverter = "MORPHO_FLOAT"

    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value, "double &",
                     "double *", True)
        self.texi_type = "double"
        self.morpho = "&" + self.name
        self.elementType = "double"
        self.cToMorphoConverter = "MORPHO_FLOAT"

class ostring(oint):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value, "std::string &", "char **",
            True)
        self.morpho = "&" + self.name
        self.texi_type = "string"
        self.morpho_object = self.name + "_str"
        self.elementType = "char *"
        self.cToMorphoConverter = "MORPHO_GETSTRING"

    def capture_output(self):
        return INDENTL1 + f"value {self.name}_value = object_stringfromcstring({self.name}, strlen({self.name}));\n" \
             + INDENTL1 + f"objectstring* {self.morpho_object} = MORPHO_GETSTRING({self.name}_value);\n" 

    def return_output(self):
        return INDENTL1 + "value out;\n" \
             + INDENTL1 + f"if ({self.morpho_object}) " + "{\n" \
             + INDENTL2 + f"out = MORPHO_OBJECT({self.morpho_object});\n" \
             + INDENTL2 + f"morpho_bindobjects(v, 1, &out);\n" \
             + INDENTL1 + "}\n" \
             + INDENTL1 + "return out;\n" 
    
class ovectorint(oint):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value, "std::vector<int> &",
                "int **", True)
        self.c = "int ** " + self.name + ", size_t * " + self.name + "_n"
        self.morpho = "&" + self.name + ", &" + self.name + "_n"
        self.texi_type = "vector of integers"
        self.morpho_object = self.name + "_list"
        self.elementType = "int"
        self.cToMorphoConverter = "MORPHO_INTEGER"
    
    def init_output(self):
        return INDENTL1 \
                + f"{self.elementType}* {self.name};\n" \
                + INDENTL1 \
                + f"size_t {self.name}_n;\n"

    def capture_output(self):
        return INDENTL1 + f"value {self.name}_value[(int) {self.name}_n];\n" \
             + INDENTL1 + f"for (size_t j=0; j<{self.name}_n; j++) " +"{ \n" \
             + INDENTL2 + f"{self.name}_value[j] = {self.cToMorphoConverter}({self.name}[j]);\n" \
             + INDENTL1 + "}\n" \
             + INDENTL1 + f"objectlist* {self.morpho_object} = object_newlist((int) {self.name}_n, {self.name}_value);\n" 

    def return_output(self):
        return INDENTL1 + "value out;\n" \
             + INDENTL1 + f"if ({self.name}_list) " + "{\n" \
             + INDENTL2 + f"out = MORPHO_OBJECT({self.name}_list);\n" \
             + INDENTL2 + f"morpho_bindobjects(v, 1, &out);\n" \
             + INDENTL1 + "}\n" \
             + INDENTL1 + "return out;\n" 
    
# ovectorpair has the same init_output as ovectorint
class ovectorpair(ovectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self,name, value, python_value, julia_value,  "gmsh::vectorpair &",
                "int **", True)
        self.c = "int ** " + self.name + ", size_t * " + self.name + "_n"
        self.morpho = "&" + self.name + ", &" + self.name + "_n"
        self.texi_type = "vector of pairs of integers"
        self.morpho_object = self.name + "_list"
        self.elementType = "int"
        self.cToMorphoConverter = "MORPHO_INTEGER"

class ovectorsize(ovectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self,name, value, python_value, julia_value,
                "std::vector<std::size_t> &", "size_t **", True)
        self.c = "size_t ** " + self.name + ", size_t * " + self.name + "_n"
        self.morpho = "&" + self.name + ", &" + self.name + "_n"
        self.texi_type = "vector of sizes"
        self.morpho_object = self.name + "_list"
        self.elementType = "size_t"
        self.cToMorphoConverter = "MORPHO_INTEGER"

class ovectordouble(ovectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self,name, value, python_value, julia_value, "std::vector<double> &", "double *", True)
        self.c = "double ** " + self.name + ", size_t * " + self.name + "_n"
        self.morpho = "&" + self.name + ", &" + self.name + "_n"
        self.texi_type = "vector of doubles"
        self.morpho_object = self.name + "_list"
        self.elementType = "double"
        self.cToMorphoConverter = "MORPHO_FLOAT"

class ovectorstring(ovectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value,
                "std::vector<std::string> &", "char **", True)
        self.c = "char *** " + self.name + ", size_t * " + self.name + "_n"
        self.morpho = "&" + self.name + ", &" + self.name + "_n"
        self.texi_type = "vector of strings"
        self.morpho_object = self.name + "_list"
        self.elementType = "char *"
        self.cToMorphoConverter = "MORPHO_STRING"
    
    def capture_output(self):
        return INDENTL1 + f"value {self.name}_values[(int) {self.name}_n];\n" \
             + INDENTL1 + f"for (size_t j=0; j<{self.name}_n; j++) " +"{ \n" \
             + INDENTL2 + f"{self.name}_values[j] = object_stringfromcstring({self.name}[j], strlen({self.name}[j]));\n" \
             + INDENTL1 + "}\n" \
             + INDENTL1 + f"objectlist* {self.morpho_object} = object_newlist((int) {self.name}_n, {self.name}_values);\n" 


class ovectorvectorint(ovectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value,
                "std::vector<std::vector<int> > &", "int **", True)
        self.c = "int *** " + self.name + ", size_t ** " + self.name + "_n, size_t *" + self.name + "_nn"
        self.morpho = "&" + self.name + ", &" + self.name + "_n" + ", &" + self.name + "_nn"
        self.texi_type = "vector of vectors of integers"
        self.morpho_object = self.name + "listoflist"
        self.elementType = "int"
        self.cToMorphoConverter = "MORPHO_INTEGER"


    def init_output(self):
        return INDENTL1 \
                + f"{self.elementType} ** {self.name};\n" \
                + INDENTL1 \
                + f"size_t * {self.name}_n;\n" \
                + INDENTL1 \
                + f"size_t {self.name}_nn;\n"

    def capture_output(self): 
        return INDENTL1 + f"objectlist* {self.morpho_object} = object_newlist(0, NULL);\n" \
             + INDENTL1 + f"value {self.name}_value[(int) {self.name}_nn];\n" \
             + INDENTL1 + f"for (size_t i=0; i<{self.name}_nn; i++) " +"{ \n" \
             + INDENTL2 + f"value {self.name}_i_value[(int) {self.name}_n[i]];\n" \
             + INDENTL2 + f"for (size_t j=0; j<{self.name}_n[i]; j++) " +"{ \n" \
             + INDENTL3 + f"{self.name}_i_value[j] = {self.cToMorphoConverter}({self.name}[i][j]);\n" \
             + INDENTL2 + "}\n" \
             + INDENTL2 + f"objectlist* {self.morpho_object}_i = object_newlist((int) {self.name}_n[i], {self.name}_i_value);\n" \
             + INDENTL2 + f"list_append({self.morpho_object}, MORPHO_OBJECT({self.morpho_object}_i));" \
             + INDENTL1 + "} \n"

class ovectorvectorpair(ovectorvectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self,name, value, python_value, julia_value,
                "std::vector<gmsh::vectorpair> &", "int **", True)
        self.c = "int *** " + self.name + ", size_t ** " + self.name + "_n, size_t *" + self.name + "_nn"
        self.morpho = "&" + self.name + ", &" + self.name + "_n" + ", &" + self.name + "_nn"
        self.texi_type = "vector of vectors of pairs of integers"
        self.morpho_object = self.name + "listoflist"
        self.elementType = "int"
        self.cToMorphoConverter = "MORPHO_INTEGER"

class ovectorvectorsize(ovectorvectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value,
                "std::vector<std::vector<std::size_t> > &", "size_t **", True)
        self.c = "size_t *** " + self.name + ", size_t ** " + self.name + "_n, size_t *" + self.name + "_nn"
        self.morpho = "&" + self.name + ", &" + self.name + "_n" + ", &" + self.name + "_nn"
        self.texi_type = "vector of vectors of sizes"
        self.morpho_object = self.name + "listoflist"
        self.elementType = "size_t"
        self.cToMorphoConverter = "MORPHO_INTEGER"


class ovectorvectordouble(ovectorvectorint, outputArg):
    def __init__(self, name, value=None, python_value=None, julia_value=None):
        arg.__init__(self, name, value, python_value, julia_value,
                "std::vector<std::vector<double> > &", "double **", True)
        self.c = "double *** " + self.name + ", size_t ** " + self.name + "_n, size_t *" + self.name + "_nn"
        self.morpho = "&" + self.name + ", &" + self.name + "_n" + ", &" + self.name + "_nn"
        self.texi_type = "vector of vectors of doubles"
        self.morpho_object = self.name + "listoflist"
        self.elementType = "double"
        self.cToMorphoConverter = "MORPHO_FLOAT"


# special types

# Unclear as to how the argv is handles in the C-API. Tried subclassing from ivectorstring and treating the first input to gmshInitialize as the argvs, bit didn't work. (compiled and ran, but didn't do anything)
class iargcargv(arg):
    def __init__(self, name="", value=None, python_value=None, julia_value=None, cpp_type="", c_type="", out=False):
        super().__init__(name, value, python_value, julia_value, cpp_type, c_type, out)
        self.c_type = "char *"
        self.c = "int argc, char ** argv"
        self.name = "argv"
        self.texi = "(argc = 0)}, @code{argv = []"
        self.texi_type = "command line arguments"
        self.morpho = "0, NULL"
    
    def capture_input(self, i):
        return ""

def isizefun(name):
    a = arg(name, None, None, None, "", "", False)
    a.c = ("double (*" + name + ")" +
           "(int dim, int tag, double x, double y, double z, double lc, void * data), " +
           "void * " + name + "_data")
    return a


class Module:
    def __init__(self, name, doc):
        self.name = name
        self.doc = doc
        self.fs = []
        self.submodules = []

    def add(self, name, doc, rtype, *args):
        self.fs.append((rtype, name, args, doc, []))

    def add_special(self, name, doc, special, rtype, *args):
        self.fs.append((rtype, name, args, doc, special))

    def add_module(self, name, doc):
        module = Module(name, doc)
        self.submodules.append(module)
        return module

# The footer for the C file which contains the finalization function..
# Here, we check if Gmsh is initialized and then finalize it.
cmorpho_footer = """
void {0}_finalize(void) {{ 
    int ierr;
    int outval = gmshIsInitialized(&ierr);
    if (outval != 0) {{
        gmshFinalize(&ierr);
    }}
}}
""".format(EXTENSION_NAME)

# To-do: The checkers for double are obsolete since Morpho already has those, so we need to remove this code, but we can keep them for now.
cmorpho_helpers = """
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
"""

def func_convert_list_to_pointer_array(func_name, pointer_type, element_checker, element_getter): 

    return """
void {0}(vm* v, objectlist* l, {1} list) {{
    int len = list_length(l);
    bool success = true;
    value elementI;
    for (int i = 0; i<len; i++) {{
        success = (success && list_getelement(l, i, &elementI));
        if (!{2}(elementI)) {{
            morpho_runtimeerror(v, GMSH_ARGS_ERROR);
        }}
        list[i] = {3}(elementI);
    }}
    if (!success) {{
        morpho_runtimeerror(v, GMSH_ARGS_ERROR);
    }}

}}
""".format(func_name, pointer_type, element_checker, element_getter)
    
cmorpho_helpers += func_convert_list_to_pointer_array("morphoGetIntStarFromList",
                                                      "int *", 
                                                      "MORPHO_ISINTEGER", 
                                                      "MORPHO_GETINTEGERVALUE")

cmorpho_helpers += func_convert_list_to_pointer_array("morphoGetSizeTStarFromList",
                                                      "size_t *", 
                                                      "MORPHO_ISINTEGER", 
                                                      "MORPHO_GETINTEGERVALUE")


cmorpho_helpers += func_convert_list_to_pointer_array("morphoGetDoubleStarFromList",
                                                      "double *", 
                                                      "morpho_is_double", 
                                                      "morpho_get_double")

cmorpho_helpers += func_convert_list_to_pointer_array("morphoGetCharStarStarFromList",
                                                      "char const **", 
                                                      "MORPHO_ISSTRING", 
                                                      "MORPHO_GETCSTRING")

cmorpho_header = """
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
#include "{0}.h"

""".format(EXTENSION_NAME)

# Common beginning of the Header file. Here, we declare two errors that will be raised when either the number of arguments or the type of arguments is incorrect.
hmorpho_header = """
#include <stdio.h>
#include <morpho/morpho.h>
#include <morpho/builtin.h>

#define GMSH_NARGS_ERROR "GmshNargsErr"
#define GMSH_NARGS_ERROR_MSG "Incorrect Number of arguments for Gmsh function. Check the help for this function."

#define GMSH_ARGS_ERROR "GmshArgsErr"
#define GMSH_ARGS_ERROR_MSG "Incorrect type of argument for Gmsh function. Check the help for this function."
"""

cmorpho_error_def = """
    morpho_defineerror(GMSH_NARGS_ERROR, ERROR_HALT, GMSH_NARGS_ERROR_MSG);
    morpho_defineerror(GMSH_ARGS_ERROR, ERROR_HALT, GMSH_ARGS_ERROR_MSG);
"""

morpho_help_header = """
[comment]: # ({0} help)
[version]: # (0.6)

# {0}
[tag{0}]: # ({0})
""".format(EXTENSION_NAME[0].upper() + EXTENSION_NAME[1:]) 

def processForMD(string):
    '''
    Method to process a the Python docstring for Markdown. 
    So far, it just replaces "'" with "`".
    '''
    return string.replace("'", "`")

def capi(s):
    return s[:1].upper() + s[1:]


class API:
    def __init__(
        self,
        version_major,
        version_minor,
        version_patch,
        namespace = "gmsh",
        code = "Gmsh",
        copyright = "Gmsh - Copyright (C) 1997-2023 C. Geuzaine, J.-F. Remacle",
        issues = "https://gitlab.onelab.info/gmsh/gmsh/issues.",
        description = "Gmsh is an automatic three-dimensional finite element mesh generator with a built-in CAD engine and post-processor. Its design goal is to provide a fast, light and user-friendly meshing tool with parametric input and flexible visualization capabilities.\nGmsh is built around four modules (geometry, mesh, solver and post-processing), which can be controlled with the graphical user interface, from the command line, using text files written in Gmsh's own scripting language (.geo files), or through the C++, C, Python, Julia and Fortran application programming interface (API)."):
        self.version_major = version_major
        self.version_minor = version_minor
        self.version_patch = version_patch
        global ns
        ns = namespace
        self.code = code
        self.copyright = copyright
        self.issues = issues
        self.description = description
        self.modules = []
        self.api_lineno = {'cpp': {}, 'c': {}, 'py': {}, 'jl': {}, 'f': {}}

    def add_module(self, name, doc):
        module = Module(name, doc)
        self.modules.append(module)
        return module

    def fwrite(self, f, s):
        self.current_lineno += s.count('\n')
        f.write(s)

    def flog(self, lang, fname):
        self.api_lineno[lang][fname] = self.current_lineno

    def write_julia(self):
        pass

    def write_texi(self):
        pass

    def write_cpp(self):
        pass

    def write_c(self):
        pass

    def write_fortran(self):
        pass

    def write_python(self):
        """
        This method is actually `write_morpho`, but is named `write_python` so that 
        we can run `gen.py` directly without modification.
        """

        method_names = []

        def collect_list_of_outputs(oargs):
            l = INDENTL1 + f"value outval[{len(oargs)}];\n" 
            for j, oarg in enumerate(oargs):
                l += INDENTL1 + f"outval[{j}] = MORPHO_OBJECT({oarg.morpho_object});\n" 
            l += INDENTL1 + f"objectlist* outlist = object_newlist({len(oargs)}, outval);\n" 
            self.fwrite(f, l)
            return
        
        def return_list_of_outputs():
            l = INDENTL1 + "value out;\n" \
              + INDENTL1 + f"if (outlist) " + "{\n" \
              + INDENTL2 + f"out = MORPHO_OBJECT(outlist);\n" \
              + INDENTL2 + f"morpho_bindobjects(v, 1, &out);\n" \
              + INDENTL1 + "}\n" \
              + INDENTL1 + "return out;\n" 
            self.fwrite(f, l)

        def write_module(module, c_namespace):
            '''
            write_module(module, c_namespace)

            This function writes a given module to the C file `../../src/gmshapi.c` as well as the Morpho inline help file `../../share/help/gmshapi.md`
            It will write all the methods in the given module, and then call itself recursively for all the submodules of the given module.
            '''
            if c_namespace:
                c_namespace += module.name[0].upper() + module.name[1:]
            else:
                c_namespace = module.name
            
            # Write all the methods in this module
            for rtype, name, args, doc, special in module.fs:
                # *c.h
                if name=="importShapesNativePointer":
                    # To-do: Handle ivoidstar to be able to use this function
                    # Skipping for now...
                    continue
                if name=="setSizeCallback":
                    # To-do: Handle isizefun to be able to use this function.
                    # Skipping for now...
                    continue

                # Get the input and output arguments
                iargs = list(a for a in args if not a.out)
                oargs = list(a for a in args if a.out)
                if len(oargs)>0 and rtype:
                    # To-do: Handle this case where both rtype and oargs present.
                    # Skipping for now...
                    return
                
                # Get the name of the method
                fname = c_namespace + name[0].upper() + name[1:] # This is how the method is called in C
                fnameapi = fname + "(" # Add the opening bracket for the call signature
                fnamemorpho = "Morpho" + fname[0].upper() + fname[1:] # This is how the veneer function will be called in C. Note that we will ultimately call the function with the original C name (`fname`) from Morpho. This is just a veneer function and its name doesn't matter.

                method_names.append(fnamemorpho) # Add the veneer function to the list of method names, to be used later to define their calling names in the Header file as well as initializing in the C file.
                
                ### Write help for this function to the hlp file ###
                self.fwrite(hlp, f"## {fname}\n")
                self.fwrite(hlp, f"[tag{fname}]: # ({fname})\n\n")
                # Add call signature
                self.fwrite(hlp, f"Call signature:\n")
                morpho_call_signature = fnameapi + (", ").join(
                    list((a.name for a in iargs ))) + ")\n"
                self.fwrite(hlp, morpho_call_signature + "\n")
                # Add arguments
                if (len(iargs)>0):
                    self.fwrite(hlp, "Arguments:\n")
                    for iarg in iargs:
                        morpho_type = iarg.texi_type.replace("vector", "List")
                        self.fwrite(hlp, f"{iarg.name} ({morpho_type})\n")
                    # Add new line
                    self.fwrite(hlp, "\n")
                # Add returns
                self.fwrite(hlp, "Returns:\n")
                if len(oargs)==0 and not rtype:
                    self.fwrite(hlp, f"nil\n")
                elif len(oargs)==0 and rtype:
                    morpho_type = rtype.texi_type.replace("vector", "List")
                    self.fwrite(hlp, f"{morpho_type}\n")
                for oarg in oargs:
                    morpho_type = oarg.texi_type.replace("vector", "List")
                    self.fwrite(hlp, f"{oarg.name} ({morpho_type})\n")
                # Add new line 
                self.fwrite(hlp, "\n")
                # Add description
                self.fwrite(hlp, "\n".join(textwrap.wrap(processForMD(doc), 75)) + "\n\n")
                
                ##############################

                ### Write the veneer function to the C file ###
                self.fwrite(f, "\n\n")

                # Initialize the veneer function
                fnamemorphoapi = "value " + fnamemorpho \
                           + "(vm* v, int nargs, value* args) {\n"
                self.fwrite(f, fnamemorphoapi)
                # Add in code to check the number of arguments
                nargsCheck = INDENTL1 + f"if (nargs != {len(iargs)})"+ " {\n" \
                           + INDENTL2 + "morpho_runtimeerror(v, GMSH_NARGS_ERROR);\n" \
                           + INDENTL2 + "return MORPHO_NIL;\n" \
                           + INDENTL1 + "} \n"
                self.fwrite(f, nargsCheck)

                # Capture all the inputs
                for i,iarg in enumerate(iargs):
                    self.fwrite(f, iarg.capture_input(i))
                    
                # Initialize the outputs 
                for i,oarg in enumerate(oargs):
                    self.fwrite(f, oarg.init_output())

                # Create the C function call
                self.fwrite(f, INDENTL1 + "int ierr;\n")
                fn_call = fnameapi + (",\n" + ' ' * len(fnameapi + INDENTL1)).join(
                        list((a.morpho for a in args + (oint("ierr"), )))) + ");\n"
                
                # If the function returns something, modify the function call to capture it
                if rtype:
                    fn_call = f"{rtype.rc_type} outval = " + fn_call
                
                # Write the function call
                self.fwrite(f, INDENTL1 + fn_call)
                
                # Write the return statement (Note that we have already skipped the case where both rtype and oargs are present, so we don't need to account for that here.)
                if len(oargs)==0 and not rtype: ## If there's nothing to return, return MORPHO_NIL
                    self.fwrite(f, INDENTL1 + "return MORPHO_NIL;\n")
                elif len(oargs)==0 and rtype: ## If there are no outputs, but the function returns something, return the value
                    self.fwrite(f, INDENTL1 + f"return {rtype.cToMorphoConverter}(outval);\n")
                for oarg in oargs: ## If there are outputs, we need to first capture them as Morpho values.
                    self.fwrite(f, oarg.capture_output())
                if (len(oargs)==1): ## If there's only one output, return it
                    self.fwrite(f, oargs[0].return_output())
                elif (len(oargs)>1): ## If there are multiple outputs, collect them in a Morpho List and return it
                    collect_list_of_outputs(oargs)
                    return_list_of_outputs()
                
                self.fwrite(f, "}")
            
            # Recursively write all the submodules
            for m in module.submodules:
                write_module(m, c_namespace)

        self.current_lineno = 1
        # Simultanously open the C file and the help file as we need to add the methods one by one
        with open("../src/" + f"{EXTENSION_NAME}.c", "w") as f, \
             open("../share/help/" + f"{EXTENSION_NAME}.md", "w") as hlp:
            # Write the header for the Help file
            self.fwrite(hlp, morpho_help_header)
            self.fwrite(hlp, "\n")
            # Write the description of Gmsh to the Help file
            self.fwrite(hlp, "\n".join(textwrap.wrap(self.description, 80)) + "\n \n")
            # Code to indicate the inline help to display the subtopics when the user types `help gmshapi` in the Morpho REPL
            # To-do: Currently, *all* the methods fall under `gmshapi`'s subtopics, whereas it would be nice if the help is also organized by the submodules. We need to add this functionality.
            self.fwrite(hlp, "[showsubtopics]: # (subtopics)\n\n")

            # Write the header for the C file
            self.fwrite(f, cmorpho_header)
            # Write the helper functions 
            self.fwrite(f, cmorpho_helpers)
            # Write all the modules. The `write_module` function will write to both the C and the Help file.
            for module in self.modules:
                write_module(module, "")
            
            # Write the footer for the C file
            # Write the initialize method
            self.fwrite(f, "\nvoid " + f"{EXTENSION_NAME}_initialize(void) " + "{\n")
            # Add all the functions
            for method in method_names:
                # The constant `{method.upper()}_FUNCTION` will be defined in the header file below
                self.fwrite(f, INDENTL1 + f"builtin_addfunction({method.upper()}_FUNCTION, {method}, BUILTIN_FLAGSEMPTY);\n")
            # Add the error definitions.
            # To-do: Currently, there are only two errors: One for incorrect number of arguments and one for incorrect type of arguments. We need to add more specific and helpful error messages for each function.
            self.fwrite(f, cmorpho_error_def)
            self.fwrite(f, "\n}\n")
            # Write the finalize method
            self.fwrite(f, cmorpho_footer)
        
        # Now, write the header file
        with open("../src/" + f"{EXTENSION_NAME}.h", "w") as fh:
            self.fwrite(fh, hmorpho_header)
            self.fwrite(fh, "\n")
            for method in method_names:
                self.fwrite(fh, f"#define {method.upper()}_FUNCTION \"{method[6].lower()+method[7:]}\"\n") # Don't want Morpho in the name of the front facing functions. This will convert, say, `MorphoGmshInitialize` to `gmshInitialize`, so that the user can call `gmshInitialize` from the Morpho REPL.
        
        # And that's it! We have written the C file and the header file. The help file is also written.
                
