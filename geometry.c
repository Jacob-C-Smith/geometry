#include <geometry/geometry.h>

// Forward declarations
int geometry_point_distance ( geometry *p_a, geometry *p_b, double *p_result );

// Function definitions
double geometry_area ( geometry *p_geometry )
{
    
    // Argument check
    //

    // Initialized data
    //

    // Switch on type
    switch (p_geometry->type)
    {
    case GEOMETRY_POINT:
    case GEOMETRY_POINT_LIST:
    case GEOMETRY_LINE:
    case GEOMETRY_LINE_LIST:

        return 0.0;

    case GEOMETRY_POLYGON:
    /*
    result = 0.0, point O(0.0, 0.0) 

    for (i = 0; i < P.size()-1; ++i)

    result += cross(toVec(O,P[i]),toVec(O,P[i+1]))/2

    return fabs(result)
    */
    default:
        break;
    }
}

double geometry_length ( geometry *p_geometry )
{

    
    // Argument check
    //

    // Initialized data
    //

    // Switch on type
    switch (p_geometry->type)
    {
    case GEOMETRY_POINT:
    case GEOMETRY_POINT_LIST:
        return 0.0;

    case GEOMETRY_LINE:
        return sqrt(pow((p_geometry->line.x1, p_geometry->line.x0),2) + pow((p_geometry->line.y1, p_geometry->line.y0),2));
    case GEOMETRY_LINE_LIST:



    case GEOMETRY_POLYGON:
    /*
    result = 0.0, point O(0.0, 0.0) 

    for (i = 0; i < P.size()-1; ++i)

    result += cross(toVec(O,P[i]),toVec(O,P[i+1]))/2

    return fabs(result)
    */
    default:
        break;
    }
}

int geometry_distance ( geometry *p_a, geometry *p_b, double *p_result )
{
    
    // Argument check
    //

    // Check the precedence of types of geometry
    if ( p_a->type == p_b->type )
    
        // Do nothing
        ;

    // Swap A and B
    else if ( p_a->type > p_b->type )
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
        {

            // Compute the distance from point a to geometry b
            if ( geometry_point_distance(p_a, p_b, p_result) == 0 ) goto failed_to_compute_distance;
        }

        case GEOMETRY_POINT_LIST:
        case GEOMETRY_LINE:
        case GEOMETRY_LINE_LIST:
        case GEOMETRY_POLYGON:
        default:
            break;
    }

    // Success
    return 1;

    // TODO
    failed_to_compute_distance:

        // Error
        return 0;
}

int geometry_point_distance ( geometry *p_a, geometry *p_b, double *p_result )
{
    // Argument check
    //

    // Initialized data
    geometry_point a = p_a->point;
    double ret = 0.0;

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
            break;
    }

    // Return a value to the caller
    *p_result = ret;
    
    // Success
    return 1;
}

double geometry_point_in_polygon ( geometry *p_geometry )
{
    /*
    
    for (i = 0; i < P.size()-1; ++i)

  if ccw(p, P[i], P[i+1])

    sum += angle(P[i], p, P[i+1])

  else sum -= angle(P[i], p, P[i+1])

return fabs(sum) > PI ? 1 : -1; // 1/-1 = in/out
    
    */
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

    // TODO: 
    missing_x:
    missing_y:
    wrong_x_type:
    wrong_y_type:
        // Error
        return 0;
    
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
