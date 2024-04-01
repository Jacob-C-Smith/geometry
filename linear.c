/** !
 * Linear algebra 
 * 
 * @author Jacob Smith
 * 
 * @file linear.c
 */

// Header
#include <geometry/linear.h>

// Function definitions
void vec2_add_vec2 ( vec2 *p_result, vec2 a, vec2 b )
{

    // Store the sum
    *p_result = (vec2)
    {
        .x = a.x + b.x,
        .y = a.y + b.y
    };

    // Done
    return;
}

void vec2_sub_vec2 ( vec2 *p_result, vec2 a, vec2 b )
{
    
    // Store the difference
    *p_result = (vec2)
    {
        .x = a.x - b.x,
        .y = a.y - b.y
    };

    // Done
    return;
}

void vec2_mul_vec2 ( vec2 *p_result, vec2 a, vec2 b )
{

    // Store the product
    *p_result = (vec2)
    {
        .x = a.x * b.x,
        .y = a.y * b.y
    };

    // Done
    return;
}

void vec2_div_vec2 ( vec2 *p_result, vec2 a, vec2 b )
{

    // Store the quotient
    *p_result = (vec2)
    {
        .x = a.x / b.x,
        .y = a.y / b.y
    };

    // Done
    return;
}

void vec2_mul_scalar ( vec2 *p_result, vec2 v, float s )
{

    // Store the scaled vector
    *p_result = (vec2)
    {
        .x = v.x * s,
        .y = v.y * s
    };

    // Done
    return;
}

void vec2_length ( float *p_result, vec2 v )
{

    // Store the length of the vector
    *p_result = sqrtf(
        v.x * v.x +
        v.y * v.y
    );

    // Done
    return;
}

void mat2_mul_vec2 ( vec2 *p_result, mat2 m, vec2 v )
{

    // Store the product
    *p_result = (vec2)
    {
        m.a * v.x + m.b * v.y,
        m.c * v.x + m.d * v.y
    };

    // Done
    return;
}

void mat2_mul_mat2 ( mat2 *p_result, mat2 m, mat2 n )
{

    // Store the product
    *p_result = (mat2)
    {
        .a = m.a * n.a + m.b * n.c, .b = m.a * n.b + m.b * n.d,
        .c = m.c * n.a + m.d * n.c, .d = m.c * n.b + m.d * n.d
    };

    // Done
    return;
}

void mat2_transpose ( mat2 *p_result, mat2 m )
{
    
    // Store the transpose
    *p_result = (mat2)
    {
        .a = m.a, .b = m.c,
        .c = m.b, .d = m.d
    };

    // Done
    return;
}

void mat2_identity ( mat2 *p_result )
{

    // Store the identity matrix
    *p_result = (mat2)
    {
        .a = 1.f, .b = 0.f,
        .c = 0.f, .d = 1.f
    };

    // Done
    return;
}

/*
void mat4_translation ( mat4 *p_result, vec3 location )
{

    // Store the translation matrix
    *p_result = (mat4)
    {
        .a = 1.f       , .b = 0.f       , .c = 0.f       , .d = 0.f,
        .e = 0.f       , .f = 1.f       , .g = 0.f       , .h = 0.f,
        .i = 0.f       , .j = 0.f       , .k = 1.f       , .l = 0.f,
        .m = location.x, .n = location.y, .o = location.z, .p = 1.f
    };

    // Done
    return;
}

void mat4_scale ( mat4 *p_result, vec3 scale )
{

    // Store the scale matrix
    *p_result = (mat4)
    {
        .a = scale.x, .b = 0      , .c = 0      , .d = 0,
        .e = 0      , .f = scale.y, .g = 0      , .h = 0,
        .i = 0      , .j = 0      , .k = scale.z, .l = 0,
        .m = 0      , .n = 0      , .o = 0      , .p = 1
    };

    // Done
    return;
}

void mat4_rotation_from_vec3 ( mat4 *p_result, vec3 rotation )
{

    // Store the rotation matrix
    *p_result = (mat4)
    {
        cosf(rotation.x) + powf(rotation.x, 2) * (1 - cosf(rotation.x))                 , rotation.x * rotation.y * (1 - cosf(rotation.y)) - rotation.z * sinf(rotation.y), rotation.x * rotation.z * (1 - cosf(rotation.z)) + rotation.y * sinf(rotation.z), 0,
        rotation.y * rotation.x * (1 - cosf(rotation.x)) + rotation.z * sinf(rotation.x), cosf(rotation.y) + powf(rotation.y, 2) * (1 - cosf(rotation.y))                 , rotation.y * rotation.z * (1 - cosf(rotation.z)) - rotation.x * sinf(rotation.z), 0,
        rotation.y * rotation.x * (1 - cosf(rotation.x)) + rotation.z * sinf(rotation.x), rotation.y * rotation.x * (1 - cosf(rotation.x)) + rotation.z * sinf(rotation.x), cosf(rotation.x) + powf(rotation.x, 2) * (1 - cosf(rotation.x))                 , 0,
        0                                                                               , 0                                                                               , 0                                                                               , 1
    };

    // Done
    return;
}

void mat4_model_from_vec3 ( mat4 *p_result, vec3 location, vec3 rotation, vec3 scale )
{

    // Uninitialized data
    mat4 _location,
         _rotation,
         _scale,
         _location_scale;

    // Compute the translation matrix
    mat4_translation(&_location, location);

    // Compute the rotation matrix
    mat4_rotation_from_vec3(&_rotation, rotation);

    // Compute the scale matrix
    mat4_scale(&_scale, scale);

    // Compute the location-scale matrix
    mat4_mul_mat4(&_location_scale, _scale, _location);

    // Compute the model matrix
    mat4_mul_mat4(p_result, _location_scale, _rotation);

    // Done
    return;
}
*/