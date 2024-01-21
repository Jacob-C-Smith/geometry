/** !
 * Geometry header
 * 
 * @author Jacob Smith
 * @file geometry/geometry.h
 */

// Include
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Enumeration definitions
enum geometry_type_e
{
    GEOMETRY_INVALID      = 0,
    GEOMETRY_POINT        = 1,
    GEOMETRY_LINE_LIST    = 2,
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

// Structure definitions
struct geometry_point_s 
{
    double x, y;
};

struct geometry_point_list_s
{
    size_t quantity;
    geometry_point *points;
};

struct geometry_line_s
{
    double x0, y0;
    double x1, y1;
};

struct geometry_line_list_s
{
    size_t quantity;
    geometry_line *lines;
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