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

    Copyright (C) 2011 Sebastian Pancratz

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <mpir.h>
#include "flint.h"
#include "ulong_extras.h"
#include "long_extras.h"
#include "padic.h"

int
main(void)
{
    int i, result;
    flint_rand_t state;

    printf("add... ");
    fflush(stdout);

    flint_randinit(state);

    /* Check aliasing: a = a + b */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        long N;
        padic_ctx_t ctx;

        padic_t a, b, d;

        fmpz_init(p);
        fmpz_set_ui(p, n_randprime(state, 5, 1));
        N = z_randint(state, 50) + 1;
        padic_ctx_init(ctx, p, N, PADIC_SERIES);

        padic_init(a, ctx);
        padic_init(b, ctx);
        padic_init(d, ctx);

        padic_randtest(a, state, ctx);
        padic_randtest(b, state, ctx);

        padic_add(d, a, b, ctx);
        padic_add(a, a, b, ctx);

        result = (padic_equal(a, d, ctx));
        if (!result)
        {
            printf("FAIL:\n\n");
            printf("a = "), _padic_print(a, ctx), printf("\n");
            printf("b = "), _padic_print(b, ctx), printf("\n");
            printf("d = "), _padic_print(d, ctx), printf("\n");
            abort();
        }

        padic_clear(a, ctx);
        padic_clear(b, ctx);
        padic_clear(d, ctx);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    /* Check aliasing: b = a + b */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        long N;
        padic_ctx_t ctx;

        padic_t a, b, d;

        fmpz_init(p);
        fmpz_set_ui(p, n_randprime(state, 5, 1));
        N = z_randint(state, 50) + 1;
        padic_ctx_init(ctx, p, N, PADIC_SERIES);

        padic_init(a, ctx);
        padic_init(b, ctx);
        padic_init(d, ctx);

        padic_randtest(a, state, ctx);
        padic_randtest(b, state, ctx);

        padic_add(d, a, b, ctx);
        padic_add(b, a, b, ctx);

        result = (padic_equal(b, d, ctx));
        if (!result)
        {
            printf("FAIL:\n\n");
            printf("a = "), _padic_print(a, ctx), printf("\n");
            printf("b = "), _padic_print(b, ctx), printf("\n");
            printf("d = "), _padic_print(d, ctx), printf("\n");
            abort();
        }

        padic_clear(a, ctx);
        padic_clear(b, ctx);
        padic_clear(d, ctx);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    /* Check aliasing: a = a + a */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        long N;
        padic_ctx_t ctx;

        padic_t a, d;

        fmpz_init(p);
        fmpz_set_ui(p, n_randprime(state, 5, 1));
        N = z_randint(state, 50) + 1;
        padic_ctx_init(ctx, p, N, PADIC_SERIES);

        padic_init(a, ctx);
        padic_init(d, ctx);

        padic_randtest(a, state, ctx);

        padic_add(d, a, a, ctx);
        padic_add(a, a, a, ctx);

        result = (padic_equal(a, d, ctx));
        if (!result)
        {
            printf("FAIL:\n\n");
            printf("a = "), _padic_print(a, ctx), printf("\n");
            printf("d = "), _padic_print(d, ctx), printf("\n");
            abort();
        }

        padic_clear(a, ctx);
        padic_clear(d, ctx);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    /* Check that a + b == b + a */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        long N;
        padic_ctx_t ctx;

        padic_t a, b, c, d;

        fmpz_init(p);
        fmpz_set_ui(p, n_randprime(state, 5, 1));
        N = z_randint(state, 50) + 1;
        padic_ctx_init(ctx, p, N, PADIC_SERIES);

        padic_init(a, ctx);
        padic_init(b, ctx);
        padic_init(c, ctx);
        padic_init(d, ctx);

        padic_randtest(a, state, ctx);
        padic_randtest(b, state, ctx);

        padic_add(c, a, b, ctx);
        padic_add(d, b, a, ctx);

        result = (padic_equal(c, d, ctx));
        if (!result)
        {
            printf("FAIL:\n\n");
            printf("a = "), _padic_print(a, ctx), printf("\n");
            printf("b = "), _padic_print(b, ctx), printf("\n");
            printf("c = "), _padic_print(c, ctx), printf("\n");
            printf("d = "), _padic_print(d, ctx), printf("\n");
            abort();
        }

        padic_clear(a, ctx);
        padic_clear(b, ctx);
        padic_clear(c, ctx);
        padic_clear(d, ctx);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    /* Check that (a + b) + c == a + (b + c) */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        long N;
        padic_ctx_t ctx;

        padic_t a, b, c, d, e;

        fmpz_init(p);
        fmpz_set_ui(p, n_randprime(state, 5, 1));
        N = z_randint(state, 50) + 1;
        padic_ctx_init(ctx, p, N, PADIC_SERIES);

        padic_init(a, ctx);
        padic_init(b, ctx);
        padic_init(c, ctx);
        padic_init(d, ctx);
        padic_init(e, ctx);

        padic_randtest(a, state, ctx);
        padic_randtest(b, state, ctx);
        padic_randtest(c, state, ctx);

        padic_add(d, a, b, ctx);
        padic_add(d, d, c, ctx);

        padic_add(e, b, c, ctx);
        padic_add(e, a, e, ctx);

        result = (padic_equal(d, e, ctx));
        if (!result)
        {
            printf("FAIL:\n\n");
            printf("a = "), _padic_print(a, ctx), printf("\n");
            printf("b = "), _padic_print(b, ctx), printf("\n");
            printf("c = "), _padic_print(c, ctx), printf("\n");
            printf("d = "), _padic_print(d, ctx), printf("\n");
            printf("e = "), _padic_print(e, ctx), printf("\n");
            abort();
        }

        padic_clear(a, ctx);
        padic_clear(b, ctx);
        padic_clear(c, ctx);
        padic_clear(d, ctx);
        padic_clear(e, ctx);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    /* Check that a + 0 == a */
    for (i = 0; i < 10000; i++)
    {
        fmpz_t p;
        long N;
        padic_ctx_t ctx;

        padic_t a, b;

        fmpz_init(p);
        fmpz_set_ui(p, n_randprime(state, 5, 1));
        N = z_randint(state, 50) + 1;
        padic_ctx_init(ctx, p, N, PADIC_SERIES);

        padic_init(a, ctx);
        padic_init(b, ctx);

        padic_randtest(a, state, ctx);
        padic_zero(b);

        padic_add(b, a, b, ctx);

        result = (padic_equal(a, b, ctx));
        if (!result)
        {
            printf("FAIL:\n\n");
            printf("a = "), _padic_print(a, ctx), printf("\n");
            printf("b = "), _padic_print(b, ctx), printf("\n");
            abort();
        }

        padic_clear(a, ctx);
        padic_clear(b, ctx);

        fmpz_clear(p);
        padic_ctx_clear(ctx);
    }

    flint_randclear(state);
    _fmpz_cleanup();
    printf("PASS\n");
    return EXIT_SUCCESS;
}

