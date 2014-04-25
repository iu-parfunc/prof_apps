
#line 1 "./instrumented/./lzw.c"
/* lzw.c -- compress files in LZW format.
 * This is a dummy version avoiding patent problems.
 */

#ifdef RCSID
static char rcsid[] = "$Id: lzw.c,v 0.9 1993/06/10 13:27:31 jloup Exp $";
#endif

#include "tailor.h"
#include "gzip.h"
#include "lzw.h"

static int msg_done = 0;

/* Compress in to out with lzw method. */
int lzw(in, out)
    int in, out;
{

#line 18

__notify_intrinsic((void*)"int lzw() C_start", (void *)&global_x);

#line 18
{
    if (msg_done) 
#line 19
{ int tau_ret_val =  ERROR; __notify_intrinsic((void*)"int lzw() C_end", (void *)&global_x); return (tau_ret_val); }

#line 19

    msg_done = 1;
    fprintf(stderr,"output in compress .Z format not supported\n");
    if (in != out) { /* avoid warnings on unused variables */
        exit_code = ERROR;
    }
    
#line 25
{ int tau_ret_val =  ERROR; __notify_intrinsic((void*)"int lzw() C_end", (void *)&global_x); return (tau_ret_val); }

#line 25


#line 26

}
	

#line 26
}
