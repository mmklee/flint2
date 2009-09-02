/*============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

===============================================================================*/
/****************************************************************************

   Copyright (C) 2009 William Hart

*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"

int main(void)
{
   int result;
   printf("is_square....");
   fflush(stdout);
   
   for (ulong i = 0; i < 100000UL; i++) /* Test that non-squares pass */
   {
      mp_limb_t a, s, bits;
      
      bits = n_randint(32) + 1;
      a = n_randbits(bits);
      s = a*a + n_randint(2*a) + 1;

      result = !n_is_square(s);
      
      if (!result)
      {
         printf("FAIL\n");
         printf("s = %lu is declared square\n", s); 
         abort();
      }
   }
         
   for (ulong i = 0; i < 100000UL; i++) /* Test that squares pass */
   {
      mp_limb_t a, s, bits;
      
      bits = n_randint(32);
      a = n_randbits(bits);
      s = a*a;

      result = n_is_square(s);
      
      if (!result)
      {
         printf("FAIL\n");
         printf("s = %lu is declared square\n", s); 
         abort();
      }
   }

   printf("PASS\n");
   return 0;
}