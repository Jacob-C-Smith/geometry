/** !
 * Linear algebra header
 * 
 * @file geometry/linear.h
 * 
 * @author Jacob Smith
 */

// Include guard
#pragma once

// Standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// geometry
#include <geometry/geometry.h>

// Type definitions
typedef struct { float x, y; }       vec2;
typedef struct { float a, b, c, d; } mat2;

// 2D vectors
/** !
 * Add vector a to vector b; Store result
 *
 * @param p_result a + b
 * @param a        vector a
 * @param b        vector b
 *
 * @sa vec2_sub_vec2
 * @sa vec2_mul_vec2
 * @sa vec2_div_vec2
 * 
 * @return void
 */
DLLEXPORT void vec2_add_vec2 ( vec2 *p_result, vec2 a, vec2 b );

/** !
 * Subtract vector a from vector b; Store result
 *
 * @param p_result a - b
 * @param a        vector a
 * @param b        vector b
 *
 * @sa vec2_add_vec2
 * @sa vec2_mul_vec2
 * @sa vec2_div_vec2
 * 
 * @return void
 */
DLLEXPORT void vec2_sub_vec2 ( vec2 *p_result, vec2 a, vec2 b );

/** !
 * Multiply vector a by vector b; Store result
 *
 * @param p_result a * b
 * @param a        vector a
 * @param b        vector b
 *
 * @sa vec2_add_vec2
 * @sa vec2_sub_vec2
 * @sa vec2_div_vec2
 * 
 * @return void
 */
DLLEXPORT void vec2_mul_vec2 ( vec2 *p_result, vec2 a, vec2 b );

/** !
 * Divide vector a from vector b; Store result
 *
 * @param p_result a / b 
 * @param a        vector a
 * @param b        vector b
 *
 * @sa vec2_add_vec2
 * @sa vec2_sub_vec2
 * @sa vec2_mul_vec2
 * 
 * @return void
 */
DLLEXPORT void vec2_div_vec2 ( vec2 *p_result, vec2 a, vec2 b );

/** !
 * Scale a vector; Store result
 * 
 * @param p_result return
 * @param v        the vector
 * @param s        the scalar
 * 
 * @return void
*/
DLLEXPORT void vec2_mul_scalar ( vec2 *p_result, vec2 v, float s );

// 2x2 matrix
/** !
 * Multiplies a 2x2 matrix by a vector; Store result
 *
 * |1 2| . | 1, 1 | = | 3, 7 |
 * |3 4|
 *
 * @param m 2x2 matrix
 * @param v vector
 *
 * @return vector times matrix
 */
DLLEXPORT void mat2_mul_vec2 ( vec2 *p_result, mat2 m, vec2 v );

/** !
 * Multiply m by n; Store result
 *
 * @param m mat2
 * @param n mat2
 *
 * @return m times n
 */
DLLEXPORT void mat2_mul_mat2 ( mat2 *p_result, mat2 m, mat2 n );

/** !
 * Compute the transpose of a 2x2 matrix; Store result
 *
 * @param p_result return
 * @param m        the matrix
 * 
 * @sa mat4_transpose
 *
 * @return void
 */
DLLEXPORT void mat2_transpose ( mat2 *p_result, mat2 m );

/** !
 * Store a 2x2 identity matrix
 *
 * @param p_result return
 * 
 * @sa mat3_identity
 * @sa mat4_identity
 * 
 * @return void
 */
DLLEXPORT void mat2_identity ( mat2 *p_result );
