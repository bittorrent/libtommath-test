/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is library that provides for multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library is designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@iahu.ca, http://math.libtomcrypt.org
 */
#include <tommath.h>

/* read a bigint from a file stream in ASCII */
int mp_fread(mp_int *a, int radix, FILE *stream)
{
   int err, ch, neg, y;
   
   /* clear a */
   mp_zero(a);
   
   /* if first digit is - then set negative */
   ch = fgetc(stream);
   if (ch == '-') {
      neg = MP_NEG;
      ch = fgetc(stream);
   } else {
      neg = MP_ZPOS;
   }
   
   for (;;) {
      /* find y in the radix map */
      for (y = 0; y < radix; y++) {
          if (mp_s_rmap[y] == ch) {
             break;
          }
      }
      if (y == radix) {
         break;
      }
      
      /* shift up and add */
      if ((err = mp_mul_d(a, radix, a)) != MP_OKAY) {
         return err;
      }
      if ((err = mp_add_d(a, y, a)) != MP_OKAY) {
         return err;
      }
      
      ch = fgetc(stream);
   }
   if (mp_cmp_d(a, 0) != MP_EQ) {
      a->sign = neg;
   }
   
   return MP_OKAY;
}

