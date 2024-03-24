// Include
#include <stdio.h>
#include <stdlib.h>

// geometry
#include <geometry/geometry.h>

int main ( int argc, const char *argv[] )
{

    // Supress compiler warnings
    (void) argc;
    (void) argv;

    // Initialized data
    geometry _geometry_a = { 0 },
             _geometry_b = { 0 };

    geometry_area(&_geometry_a);

    // Success
    return EXIT_SUCCESS;
}
