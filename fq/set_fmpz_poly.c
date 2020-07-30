/*
    Copyright (C) 2020 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fq.h"

void fq_set_fmpz_poly(fq_t a, const fmpz_poly_t b, const fq_ctx_t ctx)
{
    if (b->length <= 2*(ctx->modulus->length - 1))
    {
        fmpz_poly_set(a, b);
        fq_reduce(a, ctx);
    }
    else
    {
        fmpz_mod_poly_t bp, q, r;
        fmpz_mod_poly_init(bp, fq_ctx_prime(ctx));
        fmpz_mod_poly_init(q, fq_ctx_prime(ctx));
        fmpz_mod_poly_init(r, fq_ctx_prime(ctx));
        fmpz_mod_poly_set_fmpz_poly(bp, b);
        fmpz_mod_poly_divrem(q, r, bp, ctx->modulus);
        fmpz_mod_poly_get_fmpz_poly(a, r);
        fmpz_mod_poly_clear(bp);
        fmpz_mod_poly_clear(q);
        fmpz_mod_poly_clear(r);
    }
}