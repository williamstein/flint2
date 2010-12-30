/*=============================================================================

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

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 William Hart

******************************************************************************/

#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "nmod_vec.h"
#include "nmod_poly.h"

void
nmod_poly_mulhigh_n(nmod_poly_t res, const nmod_poly_t poly1, 
                    const nmod_poly_t poly2, long n)
{
    long bits, bits2;

    if (n <= 6)
    {
        if (n == 0)
            nmod_poly_mul_classical(res, poly1, poly2);
        else
            nmod_poly_mulhigh_classical(res, poly1, poly2, n - 1);
        return;
    }

    bits = FLINT_BITS - (long) poly1->mod.norm;
    bits2 = FLINT_BIT_COUNT(FLINT_MAX(poly1->length, poly2->length));

    if (2 * bits + bits2 <= FLINT_BITS)
        nmod_poly_mulhigh_classical(res, poly1, poly2, n - 1);
    else
        nmod_poly_mul_KS(res, poly1, poly2, 0);
}
