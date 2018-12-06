/*
    Copyright (C) 2018 Daniel Schultz

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpz_mpoly.h"

void fmpz_mpoly_randtest_bounds(fmpz_mpoly_t A, flint_rand_t state,
                      slong length, mp_bitcnt_t coeff_bits, ulong * exp_bounds,
                                                    const fmpz_mpoly_ctx_t ctx)
{
    slong i, j, nvars = ctx->minfo->nvars;
    fmpz_t coeff;
    ulong * exp;
    TMP_INIT;

    TMP_START;

    exp = (ulong *) TMP_ALLOC(nvars*sizeof(ulong));

    fmpz_mpoly_zero(A, ctx);
    for (i = 0; i < length; i++)
    {
        for (j = 0; j < nvars; j++)
            exp[j] = n_randint(state, exp_bounds[j]);

        fmpz_init(coeff);
        fmpz_randtest(coeff, state, coeff_bits);
        _fmpz_mpoly_emplacebackterm_fmpz_ui(A, coeff, exp, ctx);
        /* emplace stole coeff */
    }

    TMP_END;

    fmpz_mpoly_sort_terms(A, ctx);
    fmpz_mpoly_combine_like_terms(A, ctx);
}