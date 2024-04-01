/** !
 * Example geometry program
 * 
 * @file main.c
 * 
 * @author Jacob Smith
 */

// Standard library
#include <stdio.h>
#include <stdlib.h>

// log
#include <log/log.h>

// geometry
#include <geometry/geometry.h>
#include <geometry/linear.h>

// Enumeration definitions
enum geometry_examples_e
{
    GEOMETRY_POINT_EXAMPLE        = 0,
    GEOMETRY_POINT_LIST_EXAMPLE   = 1,
    GEOMETRY_CIRCLE_LIST_EXAMPLE  = 2,
    GEOMETRY_LINE_EXAMPLE         = 3,
    GEOMETRY_LINE_LIST_EXAMPLE    = 4,
    GEOMETRY_TRIANGLE_EXAMPLE     = 5,
    GEOMETRY_RECTANGLE_EXAMPLE    = 6,
    GEOMETRY_POLYGON_EXAMPLE      = 7,
    GEOMETRY_POLYGON_LIST_EXAMPLE = 8,
    GEOMETRY_EXAMPLES_QUANTITY    = 9
};

// Forward declarations
/** !
 * Print a usage message to standard out
 * 
 * @param argv0 the name of the program
 * 
 * @return void
 */
void print_usage ( const char *argv0 );

/** !
 * Parse command line arguments
 * 
 * @param argc            the argc parameter of the entry point
 * @param argv            the argv parameter of the entry point
 * @param examples_to_run return
 * 
 * @return void on success, program abort on failure
 */
void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run );

/** !
 * Point example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int geometry_point_example ( int argc, const char *argv[] );

/** !
 * Line example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int geometry_line_example ( int argc, const char *argv[] );

/** !
 * Polygon example program
 * 
 * @param argc the argc parameter of the entry point
 * @param argv the argv parameter of the entry point
 * 
 * @return 1 on success, 0 on error
 */
int geometry_polygon_example ( int argc, const char *argv[] );

// Entry point
int main ( int argc, const char *argv[] )
{
    
    // Initialized data
    bool examples_to_run[GEOMETRY_EXAMPLES_QUANTITY] = { 0 };

    // Parse command line arguments
    parse_command_line_arguments(argc, argv, examples_to_run);

    // Initialize geometry
    //if ( geometry_init() == 0 ) goto failed_to_initialize_geometry;

    // Formatting
    printf(
        "╭──────────────────╮\n"\
        "│ geometry example │\n"\
        "╰──────────────────╯\n"\
        "The geometry library provides abstractions for geometry.\n"\
        "Geometry provides %d abstractions. The point, point list,\n"\
        "line, line list, triangle, rectangle, polygon, and polygon list.\n\n"\
        "A point is a vector\n"\
        "A point list is a list of vectors\n"\
        "A line is 2 element tuple of vectors\n"\
        "A line list list of lines\n"\
        "TODO: Finish all descriptions\n",
        GEOMETRY_EXAMPLES_QUANTITY
    );

    //////////////////////
    // Run the examples //
    //////////////////////

    // Run the point example program
    if ( examples_to_run[GEOMETRY_POINT_EXAMPLE] )

        // Error check
        if ( geometry_point_example(argc, argv) == 0 ) goto failed_to_run_point_example;

    // Run the line example program
    if ( examples_to_run[GEOMETRY_LINE_EXAMPLE] )

        // Error check
        if ( geometry_line_example(argc, argv) == 0 ) goto failed_to_run_line_example;

    // Run the polygon example program
    if ( examples_to_run[GEOMETRY_POLYGON_EXAMPLE] )

        // Error check
        if ( geometry_polygon_example(argc, argv) == 0 ) goto failed_to_run_polygon_example;

    // TODO: Add more examples

    // Clean up geometry
    //geometry_quit();

    // Success
    return EXIT_SUCCESS;

    // Error handling
    {
        
        failed_to_initialize_geometry:

            // Write an error message to standard out
            printf("Failed to initialize geometry!\n");

            // Error
            return EXIT_FAILURE;

        failed_to_run_point_example:

            // Print an error message
            printf("Failed to run point example!\n");

            // Error
            return EXIT_FAILURE; 
        
        failed_to_run_line_example:

            // Print an error message
            printf("Failed to run line example!\n");

            // Error
            return EXIT_FAILURE; 

        failed_to_run_polygon_example:

            // Print an error message
            printf("Failed to run polygon example!\n");

            // Error
            return EXIT_FAILURE;         
    }
}

void print_usage ( const char *argv0 )
{

    // Argument check
    if ( argv0 == (void *) 0 ) exit(EXIT_FAILURE);

    // Print a usage message to standard out
    printf("Usage: %s [point] [point-list] [line] [line-list] [polygon] [polygon-list]\n", argv0);

    // Done
    return;
}

void parse_command_line_arguments ( int argc, const char *argv[], bool *examples_to_run )
{

    // If no command line arguments are supplied, run all the examples
    if ( argc == 1 ) goto all_examples;

    // Error check
    if ( argc > GEOMETRY_EXAMPLES_QUANTITY + 1 ) goto invalid_arguments;

    // Iterate through each command line argument
    for (size_t i = 1; i < argc; i++)
    {
        
        // Point example?
        if ( strcmp(argv[i], "point") == 0 )

            // Set the point example flag
            examples_to_run[GEOMETRY_POINT_EXAMPLE] = true;

        // Point list example?
        else if ( strcmp(argv[i], "point-list") == 0 )
            
            // Set the point list example flag
            examples_to_run[GEOMETRY_POINT_LIST_EXAMPLE] = true;
        
        // Line example?
        if ( strcmp(argv[i], "line") == 0 )

            // Set the line example flag
            examples_to_run[GEOMETRY_LINE_EXAMPLE] = true;

        // Point list example?
        else if ( strcmp(argv[i], "line-list") == 0 )
            
            // Set the line list example flag
            examples_to_run[GEOMETRY_LINE_LIST_EXAMPLE] = true;

        // Default
        else goto invalid_arguments;
    }
    
    // Success
    return;

    // Set each example flag
    all_examples:
    {

        // For each example ...
        for (size_t i = 0; i < GEOMETRY_EXAMPLES_QUANTITY; i++)
        
            // ... set the example flag
            examples_to_run[i] = true;
        
        // Success
        return;
    }

    // Error handling
    {

        // Argument errors
        {
            invalid_arguments:
                
                // Print a usage message to standard out
                print_usage(argv[0]);

                // Abort
                exit(EXIT_FAILURE);
        }
    }
}

int geometry_point_example ( int argc, const char *argv[] )
{
    
    // Supress warnings
    (void) argc;
    (void) argv;

    // Formatting
    printf(
        "╭───────────────╮\n"\
        "│ point example │\n"\
        "╰───────────────╯\n"\
        "TODO: Describe\n\n"
    );

    // Initialized data
    geometry _a = { 0 };
    geometry _b = { 0 };
    geometry _c = { 0 };
    char _point_json[] = "{\"x\" : 4, \"y\" : 9}";
    json_value *p_value = (void *) 0;
    double distanceAB = 0.0,
           distanceBC = 0.0,
           distanceAC = 0.0;
    
    // Construct a point 
    if ( geometry_point_construct(&_a, 3, 2) == 0 ) goto failed_to_construct_point;

    // Construct another point 
    if ( geometry_point_construct(&_b, 5, 6) == 0 ) goto failed_to_construct_point;

    // Parse the point JSON
    if ( parse_json_value(&_point_json, 0, &p_value) == 0 ) goto failed_to_parse_json_value;

    // Construct a point from a json value
    if ( geometry_point_load_as_json(&_c, p_value) == 0 ) goto failed_to_construct_point;

    // Compute the distance from point a to point b
    if ( geometry_distance(&_a, &_b, &distanceAB) == 0 ) goto failed_to_compute_distance;
    
    // Compute the distance from point b to point c
    if ( geometry_distance(&_b, &_c, &distanceBC) == 0 ) goto failed_to_compute_distance;
    
    // Compute the distance from point a to point c
    if ( geometry_distance(&_a, &_c, &distanceAC) == 0 ) goto failed_to_compute_distance;
    
    // Print the location of point a
    printf("Point A: <%lg, %lg>\n", _a.point.x, _a.point.y);

    // Print the location of point b
    printf("Point B: <%lg, %lg>\n", _b.point.x, _b.point.y);

    // Print the location of point c
    printf("Point C: <%lg, %lg>\n", _c.point.x, _c.point.y);

    // Example formatting
    putchar('\n');

    // Print the distance from point a to point b
    printf("Distance from A to B: %lg\n", distanceAB);

    // Print the distance from point b to point c
    printf("Distance from B to C: %lg\n", distanceBC);

    // Print the distance from point a to point c
    printf("Distance from A to C: %lg\n", distanceAC);

    // Example formatting
    putchar('\n');

    // Cleanup
    free_json_value(p_value);

    // Success
    return 1;

    // TODO
    failed_to_parse_json_value:

        // Error
        return 0;

    // Error handling
    {

        // Geometry errors
        {
            failed_to_construct_point:
                #ifndef NDEBUG
                    // TODO:
                #endif

                // Error
                return 0;
            
            failed_to_compute_distance:
                #ifndef NDEBUG
                    // TODO:
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_line_example ( int argc, const char *argv[] )
{
    
    // Supress warnings
    (void) argc;
    (void) argv;

    // Formatting
    printf(
        "╭──────────────╮\n"\
        "│ line example │\n"\
        "╰──────────────╯\n"\
        "TODO: Describe\n\n"
    );

    // Initialized data
    geometry _a = { 0 };
    geometry _b = { 0 };
    geometry _c = { 0 };
    char _line_json[] = "{\"x0\" : 0, \"y0\" : 0, \"x1\" : 5, \"y1\" : 5}";
    json_value *p_value = (void *) 0;
    double distanceAB = 0.0;
    
    // Construct a line 
    if ( geometry_line_construct(&_a, 0, 0, 10, 0) == 0 ) goto failed_to_construct_line;

    // Construct a point 
    if ( geometry_point_construct(&_b, 5, 5) == 0 ) goto failed_to_construct_line;

    // Parse the line JSON
    if ( parse_json_value(&_line_json, 0, &p_value) == 0 ) goto failed_to_parse_json_value;

    // TODO: Construct a point from a json value
    //if ( geometry_line_load_as_json(&_c, p_value) == 0 ) goto failed_to_construct_line;

    // Compute the distance from line a to point b
    if ( geometry_distance(&_a, &_b, &distanceAB) == 0 ) goto failed_to_compute_distance;

    // Print a description of line A
    printf("Line A: <%lg, %lg>, <%lg, %lg>\n", _a.line.x0, _a.line.y0, _a.line.x1, _a.line.y1);

    // Print the location of point b
    printf("Point B: <%lg, %lg>\n", _b.point.x, _b.point.y);

    // Example formatting
    putchar('\n');

    // Print the distance from line a to point b
    printf("Distance from A to B: %lg\n", distanceAB);

    // Example formatting
    putchar('\n');

    // Cleanup
    free_json_value(p_value);

    // Success
    return 1;

    // TODO
    failed_to_parse_json_value:

        // Error
        return 0;

    // Error handling
    {

        // Geometry errors
        {
            failed_to_construct_line:
                #ifndef NDEBUG
                    // TODO:
                #endif

                // Error
                return 0;
            
            failed_to_compute_distance:
                #ifndef NDEBUG
                    // TODO:
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_polygon_example ( int argc, const char *argv[] )
{
    
    // Supress warnings
    (void) argc;
    (void) argv;

    // Formatting
    printf(
        "╭─────────────────╮\n"\
        "│ polygon example │\n"\
        "╰─────────────────╯\n"\
        "TODO: Describe\n\n"
    );

    // NOTE: These polygons are from visualgo's computational geometry page
    //       https://visualgo.net/en/polygon

    // Initialized data
    char _simple_json[]     = "[{\"x\":1,\"y\":6},{\"x\":3,\"y\":1},{\"x\":7,\"y\":2},{\"x\":4,\"y\":4},{\"x\":8,\"y\":5}]";
    char _convex_json[]     = "[{\"x\":150,\"y\":330},{\"x\":550,\"y\":330},{\"x\":700,\"y\":200},{\"x\":550,\"y\":50},{\"x\":150,\"y\":50}]";
    char _concave_json[]    = "[{\"x\":150,\"y\":330},{\"x\":250,\"y\":250},{\"x\":550,\"y\":330},{\"x\":700,\"y\":200},{\"x\":550,\"y\":50},{\"x\":150,\"y\":50}]";
    char _mountain_json[]   = "[{\"x\":150,\"y\":330},{\"x\":750,\"y\":330},{\"x\":650,\"y\":50},{\"x\":550,\"y\":300},{\"x\":450,\"y\":50},{\"x\":350,\"y\":300},{\"x\":250,\"y\":50}]";
    char _maze_json[]       = "[{\"x\":120,\"y\":320},{\"x\":400,\"y\":320},{\"x\":400,\"y\":40},{\"x\":120,\"y\":40},{\"x\":120,\"y\":240},{\"x\":320,\"y\":240},{\"x\":320,\"y\":120},{\"x\":200,\"y\":120},{\"x\":200,\"y\":160},{\"x\":280,\"y\":160},{\"x\":280,\"y\":200},{\"x\":160,\"y\":200},{\"x\":160,\"y\":80},{\"x\":360,\"y\":80},{\"x\":360,\"y\":280},{\"x\":120,\"y\":280}]";
    char _star_json[]       = "[{\"x\":80,\"y\":280},{\"x\":180,\"y\":200},{\"x\":320,\"y\":320},{\"x\":220,\"y\":180},{\"x\":400,\"y\":200},{\"x\":200,\"y\":140},{\"x\":240,\"y\":40},{\"x\":160,\"y\":120},{\"x\":80,\"y\":40},{\"x\":140,\"y\":180}]";
    char _goalkeeper_json[] = "[{\"x\":80,\"y\":280},{\"x\":400,\"y\":320},{\"x\":700,\"y\":340},{\"x\":860,\"y\":320},{\"x\":820,\"y\":280},{\"x\":680,\"y\":300},{\"x\":680,\"y\":180},{\"x\":840,\"y\":140},{\"x\":820,\"y\":60},{\"x\":780,\"y\":80},{\"x\":800,\"y\":120},{\"x\":640,\"y\":140},{\"x\":580,\"y\":180},{\"x\":520,\"y\":180},{\"x\":480,\"y\":60},{\"x\":400,\"y\":20},{\"x\":240,\"y\":40},{\"x\":260,\"y\":80},{\"x\":420,\"y\":60},{\"x\":380,\"y\":200},{\"x\":300,\"y\":100},{\"x\":220,\"y\":120},{\"x\":240,\"y\":180},{\"x\":320,\"y\":220},{\"x\":280,\"y\":260},{\"x\":220,\"y\":260},{\"x\":100,\"y\":240}]";
    char _fish_json[]       = "[{\"x\":180,\"y\":180},{\"x\":240,\"y\":220},{\"x\":320,\"y\":220},{\"x\":380,\"y\":200},{\"x\":440,\"y\":160},{\"x\":480,\"y\":180},{\"x\":520,\"y\":240},{\"x\":520,\"y\":20},{\"x\":480,\"y\":80},{\"x\":440,\"y\":100},{\"x\":400,\"y\":40},{\"x\":340,\"y\":20},{\"x\":300,\"y\":20},{\"x\":260,\"y\":40},{\"x\":200,\"y\":60},{\"x\":180,\"y\":80},{\"x\":140,\"y\":140}]";
    json_value *p_goalkeeper = 0;
    geometry _goalkeeper = { 0 };
    double goalkeeper_area = 0.0;

    // Parse the goalkeeper json text into a value
    if ( parse_json_value(&_goalkeeper_json, 0, &p_goalkeeper) == 0 ) goto failed_to_parse_json;

    // Construct the goalkeeper geometry
    if ( geometry_polygon_load_as_json(&_goalkeeper, p_goalkeeper ) == 0 ) goto failed_to_construct_polygon;

    // Compute the area of the goalkeeper geometry
    if ( geometry_polygon_area(&_goalkeeper, &goalkeeper_area) == 0 ) goto failed_to_compute_area;

    // Print the area of the goalkeeper geometry
    printf("Area of goalkeeper: %lg distance units squared\n", goalkeeper_area);

    // Success
    return 1;

    // TODO
    failed_to_parse_json:
    failed_to_construct_polygon:
    failed_to_compute_area:

        // Error
        return 0;

    // Error handling
    {

        // Geometry errors
        {
            
        }
    }
}
