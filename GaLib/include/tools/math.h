#ifndef TOOLS_MATH_H
#define	TOOLS_MATH_H

/**
 *  \file math.h
 *  \brief Mathematics macro
 */
 
#define MIN(a, b)  (   ( (a) < (b) ) ?  (a) : (b)   )
#define MAX(a, b)  (   ( (a) > (b) ) ?  (a) : (b)   )
#define ABS(a)     (   ( (a) <  0  ) ? -(a) : (a)   )
#define SIGN(a)    (   ( (a) <  0  ) ?  -1  :  1    )
#define SIGN0(a)   (   ( (a) <= 0  ) ? (( (a) == 0 ) ? 0 : -1 ) :  1    )
#define DIRECTION(a)    (   ( (a) <  0  ) ?   0  :  1    )

#define PI (3.141592653589793238462643383279502884197169399375105820f)

#endif	/* TOOLS_MATH_H */

