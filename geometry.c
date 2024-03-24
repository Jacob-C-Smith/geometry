#include <geometry/geometry.h>

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

double geometry_distance ( geometry *p_geometry )
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

double geometric_point_in_polygon ( geometry *p_geometry )
{
    /*
    
    for (i = 0; i < P.size()-1; ++i)

  if ccw(p, P[i], P[i+1])

    sum += angle(P[i], p, P[i+1])

  else sum -= angle(P[i], p, P[i+1])

return fabs(sum) > PI ? 1 : -1; // 1/-1 = in/out
    
    */
}