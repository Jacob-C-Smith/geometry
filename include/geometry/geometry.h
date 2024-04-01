/** !
 * Geometry header
 * 
 * @file geometry/geometry.h
 * 
 * @author Jacob Smith
 */

// Include guard
#pragma once

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// log
#include <log/log.h>

// array
#include <array/array.h>

// dict
#include <dict/dict.h>

// json
#include <json/json.h>

// Platform dependent macros
#ifdef _WIN64
    #define DLLEXPORT extern __declspec(dllexport)
#else
    #define DLLEXPORT
#endif

// Enumeration definitions
enum geometry_type_e
{
    GEOMETRY_INVALID      = 0,
    GEOMETRY_POINT        = 1,
    GEOMETRY_POINT_LIST   = 2,
    GEOMETRY_LINE         = 3,
    GEOMETRY_LINE_LIST    = 4,
    GEOMETRY_TRIANGLE     = 5,
    GEOMETRY_RECTANGLE    = 6,
    GEOMETRY_POLYGON      = 7,
    GEOMETRY_POLYGON_LIST = 8,
};

// Structure declarations
struct geometry_point_s;
struct geometry_point_list_s;
struct geometry_line_s;
struct geometry_line_list_s;
struct geometry_s;

// Type definitions
typedef struct geometry_point_s      geometry_point;
typedef struct geometry_point_list_s geometry_point_list;
typedef struct geometry_line_s       geometry_line;
typedef struct geometry_line_list_s  geometry_line_list;
typedef struct geometry_s            geometry;

typedef int (*fn_geometry_distance)     (geometry *p_a, geometry *p_b, double *p_return);
typedef int (*fn_geometry_equals)       (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_disjoint)     (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_intersects)   (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_touches)      (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_crosses)      (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_overlaps)     (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_contains)     (geometry *p_a, geometry *p_b, bool   *p_return);
typedef int (*fn_geometry_length)       (geometry *p_a, double   *p_return);
typedef int (*fn_geometry_area)         (geometry *p_a, double   *p_return);
typedef int (*fn_geometry_centroid)     (geometry *p_a, geometry *p_return);
typedef int (*fn_geometry_intersection) (geometry *p_a, geometry *p_b, geometry *p_return);
typedef int (*fn_geometry_serialize)    (geometry *p_a, void     *p_return);

// Structure definitions
struct geometry_point_s 
{
    double x, y;
};

struct geometry_point_list_s
{
    size_t quantity;
    geometry_point *p_points;
};

struct geometry_line_s
{
    double x0, y0,
           x1, y1;
};

struct geometry_line_list_s
{
    size_t quantity;
    geometry_line *p_lines;
};

struct geometry_s
{
    enum geometry_type_e type;

    union
    {
        geometry_point      point;
        geometry_point_list point_list;
        geometry_line       line;
        geometry_line_list  line_list;
    };
};

// Function declarations
/** !
 * Construct a point from X and Y values
 * 
 * @param p_geometry return
 * @param x          the x value 
 * @param y          the y value
 * 
 * @return 1 on success, 0 on error
 */
int geometry_point_construct ( geometry *p_geometry, double x, double y );

/** !
 * Construct a point from a json value
 * 
 * @param p_geometry return
 * @param p_value    the json value 
 * 
 * @return 1 on success, 0 on error
 */
int geometry_point_load_as_json ( geometry *p_geometry, json_value *p_value );

/** !
 * Construct a line from two points 
 * 
 * @param p_geometry return
 * @param x0         the x value of the first point
 * @param y0         the x value of the first point
 * @param x1         the x value of the second point
 * @param y1         the x value of the second point
 * 
 * @return 1 on success, 0 on error
 */
int geometry_line_construct ( geometry *p_geometry, double x0, double y0, double x1, double y1 );

/** !
 * Compute the distance between two geometries
 * 
 * @param p_a      the first geometry
 * @param p_b      the second geometry
 * @param p_result return
 * 
 * @return 1 on success, 0 on error
*/
int geometry_distance ( geometry *p_a, geometry *p_b, double *p_result );
