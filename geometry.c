#include <geometry/geometry.h>

// Forward declarations
int geometry_point_distance ( geometry *p_a, geometry *p_b, double *p_result );

// Function definitions
int geometry_init ( void )
{

    // Initialize the log library
    log_init();

    // Success
    return 1;
}

int geometry_area ( geometry *p_geometry, double *p_result )
{
    
    // Argument check
    if ( p_geometry == (void *) 0 ) goto no_geometry;
    if ( p_result   == (void *) 0 ) goto no_result;

    // Initialized data
    double ret = 0;

    // Switch on type
    switch (p_geometry->type)
    {
        case GEOMETRY_POINT:
        case GEOMETRY_POINT_LIST:
        case GEOMETRY_LINE:
        case GEOMETRY_LINE_LIST:

            // These types of geometry have no area
            ret = 0.0;
            
            // Done
            break;
            
        case GEOMETRY_POLYGON:

            // Store the area
            if ( geometry_polygon_area(&p_geometry->polygon, &ret) == 0 ) goto failed_to_calculate_polygon_area;
            
            // Done
            break;

        case GEOMETRY_POLYGON_LIST:
        {

            // Initialized data
            double temp = 0.0;

            // Iterate through each polygon
            for (size_t i = 0; i < p_geometry->polygon_list.quantity; i++)
            {

                // Compute the area
                geometry_polygon_area(&p_geometry->polygon_list.p_polygons[i], &temp);

                // Accumulate the area
                ret += temp;
            }

            // Done
            break;
        }

        case GEOMETRY_INVALID:
        default:

            // Error
            goto invalid_geometry_type;
    }

    // Store the return value
    *p_result = ret;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_geometry:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_geometry\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_result:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_result\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
                
        }

        // Geometry errors
        {
            failed_to_calculate_polygon_area:
                #ifndef NDEBUG
                    log_error("[geometry] Failed to calculate polygon area in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            invalid_geometry_type:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_geometry\" is of invalid type in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

double geometry_length ( geometry *p_geometry )
{
    
    // Argument check
    if ( p_geometry == (void *) 0 ) goto no_geometry;

    // Initialized data
    double ret = 0.0;

    // Strategy
    switch ( p_geometry->type )
    {
        case GEOMETRY_POINT:
        case GEOMETRY_POINT_LIST:

            // Done
            break;

        case GEOMETRY_LINE:

            // Store the length of the line
            ret = sqrt(pow((p_geometry->line.x1, p_geometry->line.x0), 2) + pow((p_geometry->line.y1, p_geometry->line.y0), 2));

            // Done
            break;

        case GEOMETRY_LINE_LIST:

            // TODO

            // Done
            break;

        case GEOMETRY_POLYGON:

            // TODO
            //

            /*
                result = 0.0, point O(0.0, 0.0) 

                for (i = 0; i < P.size()-1; ++i)

                result += cross(toVec(O,P[i]),toVec(O,P[i+1]))/2

                return fabs(result)
            */

            // Done
            break;

        default:

            // TODO: Error
            // Done
            break;
    }

    // Success
    return ret;

    // Error handling
    {

        // Argument errors
        {
            no_geometry:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_geometry\" in call to function \"%s\"\n", __FUNCTION__);
                #endif
                
                // Error
                return 0;
        }
    }
}

int geometry_distance ( geometry *p_a, geometry *p_b, double *p_result )
{
    
    // Argument check
    if ( p_a      == (void *) 0 ) goto no_a;
    if ( p_b      == (void *) 0 ) goto no_b;
    if ( p_result == (void *) 0 ) goto no_result;

    // Check the precedence of the input geometry
    if ( p_a->type > p_b->type )
    {

        // Initialized data
        geometry *p_temp = p_a;

        // Swap
        p_a = p_b;
        p_b = p_temp;
    }

    // Strategy
    switch (p_a->type)
    {

        // Point to geometry
        case GEOMETRY_POINT:

            // Compute the distance from point a to geometry b
            if ( geometry_point_distance(p_a, p_b, p_result) == 0 ) goto failed_to_compute_distance_from_point;
        
        case GEOMETRY_POINT_LIST:
        case GEOMETRY_LINE:
        case GEOMETRY_LINE_LIST:
        case GEOMETRY_POLYGON:
        default:
            break;
    }

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_a:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_a\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_b:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_b\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_result:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_result\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Geometry errors
        {
            failed_to_compute_distance_from_point:
                #ifndef NDEBUG
                    log_error("[geometry] Failed to compute distance to from point in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_point_distance ( geometry *p_a, geometry *p_b, double *p_result )
{

    // Argument check
    if ( p_a      == (void *) 0 ) goto no_a;
    if ( p_b      == (void *) 0 ) goto no_b;
    if ( p_result == (void *) 0 ) goto no_result;

    // Initialized data
    double ret = 0.0;
    geometry_point a = p_a->point;

    // Strategy
    switch (p_b->type)
    {
        case GEOMETRY_POINT:
        {
            
            // Initialized data
            geometry_point b = p_b->point;

            // Compute the distance from point a to point b
            ret = sqrt(
                pow((a.x - b.x), 2) + pow((a.y - b.y), 2)
            );
        }
        
        case GEOMETRY_LINE:
        {
            // Initialized data
            geometry_line b = p_b->line;
            double c  = a.x - b.x0,
                   d  = a.y - b.y0,
                   e  = b.x1 - b.x0,
                   f  = b.y1 - b.y0,
                   xx = 0,
                   yy = 0,
                   dx = 0,
                   dy = 0;
            double dot_product = c * e + d * f,
                   len_squared = e * e + f * f,
                   p = ( len_squared != 0 ) ? dot_product / len_squared : -1;

            // Line length is 0
            if ( p < 0 )
                xx = b.x0,
                yy = b.y0;
            
            // Line length is greater than 1
            else if ( p > 1 )
                xx = b.x1,
                yy = b.y1;

            // Line length is (0, 1)
            else
                xx = b.x0 + p * e,
                yy = b.y0 + p * f;

            // Store deltas
            dx = a.x - xx,
            dy = a.y - yy;

            // Compute the distance from point a to line b
            ret = sqrt(dx * dx + dy * dy);
        }

        default:
            
            // TODO: Error!
            break;
    }

    // Return a value to the caller
    *p_result = ret;
    
    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_a:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_a\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_b:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_b\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_result:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_result\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

bool geometry_point_in_polygon ( geometry *p_geometry )
{

    // TODO

    // Argument check
    //

    // Initialized data
    bool ret = false;
    
    /*
        for (i = 0; i < P.size()-1; ++i)

        if ccw(p, P[i], P[i+1])

            sum += angle(P[i], p, P[i+1])

        else sum -= angle(P[i], p, P[i+1])

        return fabs(sum) > PI ? 1 : -1; // 1/-1 = in/out   
    */

   // Success
   return ret;
}

int geometry_point_construct ( geometry *p_geometry, double x, double y )
{

    // Argument check
    if ( p_geometry == (void *) 0 ) goto no_geometry;

    // Store the point
    *p_geometry = (geometry)
    {
        .type = GEOMETRY_POINT,
        .point = 
        {
            .x = x,
            .y = y
        }
    };

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_geometry:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_geometry\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_point_load_as_json ( geometry *p_geometry, json_value *p_value )
{

    // Argument check
    if ( p_geometry == (void *) 0 ) goto no_geometry;
    if ( p_value    == (void *) 0 ) goto no_value;

    // Initialized data
    double x = 0.0,
           y = 0.0;
    json_value *p_x = 0,
               *p_y = 0;
    
    // Strategy
    switch (p_value->type)
    {
        case JSON_VALUE_ARRAY:
        {

            // Initialized data
            array *p_array = p_value->list;
                
            // Error check
            if ( array_size(p_array) == 0 ) goto empty_container;

            // Get x
            array_index(p_array, 0, &p_x);
            
            // Get y
            array_index(p_array, 0, &p_y);

            // Done
            break;
        }
    
        case JSON_VALUE_OBJECT:
        {

            // Initialized data
            dict *p_dict = p_value->object;
                
            // Error check
            if ( dict_keys(p_dict, 0) == 0 ) goto empty_container;

            // Get x
            p_x = dict_get(p_dict, "x");
            
            // Get y
            p_y = dict_get(p_dict, "y");

            // Done
            break;
        }
        
        default:

            // Wrong type
            goto wrong_type;
    }

    done:
    
    // Error check
    if ( p_x == 0 ) goto missing_x;
    if ( p_y == 0 ) goto missing_y;
    
    // Process x
    if ( p_x->type == JSON_VALUE_NUMBER )

        // Store x
        x = p_x->number;
    
    else if ( p_x->type == JSON_VALUE_INTEGER )

        // Store x
        x = p_x->integer;
        
    // Default
    else goto wrong_x_type;

    // Process y
    if ( p_y->type == JSON_VALUE_NUMBER )

        // Store y
        y = p_y->number;
    
    else if ( p_y->type == JSON_VALUE_INTEGER )

        // Store y
        y = p_y->integer;
        
    // Default
    else goto wrong_y_type;

    // Store the point
    *p_geometry = (geometry)
    {
        .type = GEOMETRY_POINT,
        .point = 
        {
            .x = x,
            .y = y
        }
    };

    // Success
    return 1;
    
    // Error handling
    {

        // Argument errors
        {
            no_geometry:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_geometry\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_value:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // JSON errors
        {
            wrong_type:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_value\" must be of type [ array | object ] in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
                
            missing_x:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_value\" must contain property \"x\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            missing_y:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_value\" must contain property \"y\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            wrong_x_type:
                #ifndef NDEBUG
                    log_error("[geometry] Property \"x\" of parameter \"p_value\" must be of type [ integer | number ] in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            wrong_y_type:
                #ifndef NDEBUG
                    log_error("[geometry] Property \"y\" of parameter \"p_value\" must be of type [ integer | number ] in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

        }

        // Geometry errors
        {
            empty_container:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_value\" must have at least one element in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_line_construct ( geometry *p_geometry, double x0, double y0, double x1, double y1 )
{

    // Argument check
    if ( p_geometry == (void *) 0 ) goto no_geometry;

    // Store the point
    *p_geometry = (geometry)
    {
        .type = GEOMETRY_LINE,
        .line = 
        {
            .x0 = x0,
            .y0 = y0,
            .x1 = x1,
            .y1 = y1
        }
    };

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_geometry:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_geometry\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_polygon_load_as_json ( geometry *p_geometry, json_value *p_value )
{

    // Argument check
    if ( p_geometry == (void *) 0 ) goto no_geometry;
    if ( p_value    == (void *) 0 ) goto no_value;

    // Type check
    if ( p_value->type != JSON_VALUE_ARRAY ) goto wrong_type;
    
    // Initialized data
    array  *p_array =  p_value->list;
    size_t  vertex_quantity = array_size(p_array);
    geometry_point *p_verticies = (void *) 0;

    // Error check
    if ( vertex_quantity < 3 ) goto not_a_polygon;
    
    // Allocate memory for verticies
    p_verticies = GEOMETRY_REALLOC(0, sizeof(geometry_point) * vertex_quantity);

    // Error check
    if ( p_verticies == (void *) 0 ) goto no_mem;

    // Iterate through the array
    for (size_t i = 0; i < vertex_quantity; i++)
    {
        
        // Initialized data
        json_value *i_value   = 0;
        geometry    _geometry = { 0 };

        // Store the json value at index i
        if ( array_index(p_array, i, &i_value) == 0 ) goto failed_to_index_array;

        // Construct a geometry from the json value
        if ( geometry_point_load_as_json(&_geometry, i_value) == 0 ) goto failed_to_load_point;

        // Store the point 
        p_verticies[i] = _geometry.point;
    }
    
    // Store the polygon
    *p_geometry = (geometry)
    {
        .type    = GEOMETRY_POLYGON,
        .polygon = 
        {
            .quantity    = vertex_quantity,
            .p_verticies = p_verticies
        }
    };

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_geometry:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_geometry\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            no_value:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_value\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Array errors
        {
            failed_to_index_array:
                #ifndef NDEBUG
                    log_error("[geometry] Call to function \"array_index\" returned an erroneous value in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // JSON errors
        {
            wrong_type:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_value\" must be of type [ array ] in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Geometry errors
        {
            empty_container:
                #ifndef NDEBUG
                    log_error("[geometry] Parameter \"p_value\" must have at least one element in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
                
            failed_to_load_point:
                #ifndef NDEBUG
                    log_error("[geometry] Failed to construct point in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            
            not_a_polygon:
                #ifndef NDEBUG
                    log_error("[geometry] Polygon must have at least 3 points in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }

        // Standard library errors
        {          
            no_mem:
                #ifndef NDEBUG
                    log_error("[Standard library] Failed to allocate memory in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;    
        }
    }
}

int geometry_polygon_area ( geometry_polygon *p_polygon, double *p_result )
{

    // Argument check
    if ( p_polygon == (void *) 0 ) goto no_polygon;
    if ( p_result  == (void *) 0 ) goto no_result;

    // Initialized data
    double result = 0.0,
           red    = 0.0,
           blue   = 0.0;
    geometry_point _first_point = p_polygon->p_verticies[0],
                   _last_point  = p_polygon->p_verticies[p_polygon->quantity - 1];

    // Iterate over each point in the polygon
    for ( size_t i = 0; i < p_polygon->quantity - 1; i++ )
    {

        // Initialized data
        geometry_point _current_point = p_polygon->p_verticies[i],
                       _next_point    = p_polygon->p_verticies[i + 1];

        // Accumulate
        blue += _current_point.x * _next_point.y;
        red  += _current_point.y * _next_point.x;
    }

    // Final accumulate
    blue += _first_point.y * _last_point.x;
    red  += _first_point.x * _last_point.y;

    // Store the absolute value of the result
    result = fabs(blue - red);
    
    // Return the result to the caller
    *p_result = result;

    // Success
    return 1;

    // Error handling
    {

        // Argument errors
        {
            no_polygon:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_polygon\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
            no_result:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_result\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_ccw ( geometry_point *p_a, geometry_point *p_b, geometry_point *p_c )
{

    // Argument check
    if ( p_a == (void *) 0 ) goto no_a;
    if ( p_b == (void *) 0 ) goto no_b;
    if ( p_c == (void *) 0 ) goto no_c;

    // Success
    return (p_b->x - p_a->x) * (p_c->y - p_a->y) - (p_c->x - p_a->x) * (p_b->y - p_a->y);
    
    // Error handling
    {
        
        // Argument errors
        {
            no_a:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_a\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_b:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_b\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;

            no_c:
                #ifndef NDEBUG
                    log_error("[geometry] Null pointer provided for parameter \"p_c\" in call to function \"%s\"\n", __FUNCTION__);
                #endif

                // Error
                return 0;
        }
    }
}

int geometry_quit ( void )
{

    // Success
    return 1;   
}
