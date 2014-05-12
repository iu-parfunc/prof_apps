
#line 1 "./instrumented/./lzw.c"
/* lzw.c -- compress files in LZW format.
 * This is a dummy version avoiding patent problems.
 */

#include "config.h"
#include "tailor.h"
#include "gzip.h"
#include "lzw.h"

static int msg_done = 0;

/* Compress in to out with lzw method. */
int lzw(in, out)
    int in, out;
{

#line 15

__notify_intrinsic((void*)"lzw:start", (void *)&global_x);

#line 15
{
    if (msg_done) 
#line 16
{ int tau_ret_val =  ERROR; __notify_intrinsic((void*)"lzw:end", (void *)&global_x); return (tau_ret_val); }

#line 16

    msg_done = 1;
    fprintf(stderr,"output in compress .Z format not supported\n");
    if (in != out) { /* avoid warnings on unused variables */
        exit_code = ERROR;
    }
    
#line 22
{ int tau_ret_val =  ERROR; __notify_intrinsic((void*)"lzw:end", (void *)&global_x); return (tau_ret_val); }

#line 22


#line 23

}
	

#line 23
}
