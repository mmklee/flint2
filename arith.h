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
/******************************************************************************

 Copyright (C) 2010-2011 Fredrik Johansson

******************************************************************************/

#ifndef ARITH_H
#define ARITH_H

#include <mpir.h>
#include <mpfr.h>
#include "flint.h"
#include "fmpz.h"
#include "fmpz_mat.h"
#include "fmpz_poly.h"
#include "fmpq_poly.h"
#include "fmpq.h"

#ifdef __cplusplus
 extern "C" {
#endif

void fmpz_primorial(fmpz_t res, long n);

void fmpz_poly_ramanujan_tau(fmpz_poly_t res, long n);

void fmpz_ramanujan_tau(fmpz_t res, const fmpz_t n);

void fmpz_divisors(fmpz_poly_t res, const fmpz_t n);

void fmpz_divisor_sigma(fmpz_t res, const fmpz_t n, ulong k);

int fmpz_moebius_mu(const fmpz_t n);

void fmpz_euler_phi(fmpz_t res, const fmpz_t n);

void _harmonic_number(fmpz_t num, fmpz_t den, long n);

void harmonic_number(fmpq_t x, long n);

/* Stirling numbers **********************************************************/

void stirling_number_1u(fmpz_t s, long n, long k);
void stirling_number_1(fmpz_t s, long n, long k);
void stirling_number_2(fmpz_t s, long n, long k);

void stirling_number_1u_vec(fmpz * row, long n, long klen);
void stirling_number_1_vec(fmpz * row, long n, long klen);
void stirling_number_2_vec(fmpz * row, long n, long klen);

void stirling_number_1u_vec_next(fmpz * row, fmpz * prev, long n, long klen);
void stirling_number_1_vec_next(fmpz * row, fmpz * prev, long n, long klen);
void stirling_number_2_vec_next(fmpz * row, fmpz * prev, long n, long klen);

void stirling_number_1u_mat(fmpz_mat_t mat);
void stirling_number_1_mat(fmpz_mat_t mat);
void stirling_number_2_mat(fmpz_mat_t mat);

/* Bell numbers **************************************************************/

#if FLINT64
#define BELL_NUMBER_TAB_SIZE 26
#else
#define BELL_NUMBER_TAB_SIZE 16
#endif

extern const mp_limb_t bell_number_tab[];

double bell_number_size(ulong n);

void bell_number(fmpz_t b, ulong n);

void bell_number_bsplit(fmpz_t res, ulong n);

void bell_number_multi_mod(fmpz_t res, ulong n);

void bell_number_vec(fmpz * b, long n);

void bell_number_vec_recursive(fmpz * b, long n);

void bell_number_vec_multi_mod(fmpz * b, long n);

mp_limb_t bell_number_nmod(ulong n, nmod_t mod);

void bell_number_nmod_vec(mp_ptr b, long n, nmod_t mod);

void bell_number_nmod_vec_recursive(mp_ptr b, long n, nmod_t mod);

void bell_number_nmod_vec_series(mp_ptr b, long n, nmod_t mod);


/* Zeta Euler product ********************************************************/

void _zeta_inv_euler_product(mpfr_t res, ulong s, int char_4);


/* Euler numbers *************************************************************/

#if FLINT64
#define SMALL_EULER_LIMIT 25
#else
#define SMALL_EULER_LIMIT 15
#endif

static const mp_limb_t euler_number_small[] = {
    1UL, 1UL, 5UL, 61UL, 1385UL, 50521UL, 2702765UL,
    199360981UL,
#if FLINT64
    19391512145UL, 2404879675441UL, 370371188237525UL,
    69348874393137901UL, 15514534163557086905UL
#endif
};

double euler_number_size(ulong n);

void euler_number_vec(fmpz * res, long n);

void _euler_number_zeta(fmpz_t res, ulong n);

void euler_number(fmpz_t res, ulong n);

void euler_polynomial(fmpq_poly_t poly, ulong n);

/* Bernoulli numbers *********************************************************/

#if FLINT64
#define BERNOULLI_SMALL_NUMER_LIMIT 35
#else
#define BERNOULLI_SMALL_NUMER_LIMIT 27
#endif

static const long _bernoulli_numer_small[] = {
    1L, 1L, -1L, 1L, -1L, 5L, -691L, 7L, -3617L, 43867L, -174611L, 854513L,
    -236364091L, 8553103L,
#if FLINT64
    -23749461029L, 8615841276005L, -7709321041217L, 2577687858367L
#endif
};

void _bernoulli_number(fmpz_t num, fmpz_t den, ulong n);

void bernoulli_number(fmpq_t x, ulong n);

void _bernoulli_number_vec(fmpz * num, fmpz * den, long n);

void bernoulli_number_vec(fmpq * num, long n);

void bernoulli_number_denom(fmpz_t den, ulong n);

double bernoulli_number_size(ulong n);

void bernoulli_polynomial(fmpq_poly_t poly, ulong n);

void _bernoulli_number_zeta(fmpz_t num, fmpz_t den, ulong n);

void _bernoulli_number_vec_multi_mod(fmpz * num, fmpz * den, long n);

void _bernoulli_number_vec_recursive(fmpz * num, fmpz * den, long n);

void _bernoulli_number_vec_zeta(fmpz * num, fmpz * den, long n);

/* Cyclotomic polynomials ****************************************************/

void _cyclotomic_polynomial(fmpz * a, ulong n, mp_ptr factors,
                                        long num_factors, ulong phi);

void cyclotomic_polynomial(fmpz_poly_t poly, ulong n);

void _cyclotomic_cos_polynomial(fmpz * coeffs, long d, ulong n);

void cyclotomic_cos_polynomial(fmpz_poly_t poly, ulong n);

/* Legendre polynomials ******************************************************/

void legendre_polynomial(fmpq_poly_t poly, ulong n);

/* Chebyshev polynomials *****************************************************/

void chebyshev_t_polynomial(fmpz_poly_t poly, ulong n);

void chebyshev_u_polynomial(fmpz_poly_t poly, ulong n);

/* Swinnerton-Dyer polynomials ***********************************************/

void swinnerton_dyer_polynomial(fmpz_poly_t poly, ulong n);

/* Landau function ***********************************************************/

void landau_function_vec(fmpz * res, long len);

/* Dedekind sums *************************************************************/

void dedekind_sum_naive(fmpq_t s, const fmpz_t h, const fmpz_t k);

double dedekind_sum_coprime_d(double h, double k);

void dedekind_sum_coprime_large(fmpq_t s, const fmpz_t h, const fmpz_t k);

void dedekind_sum_coprime(fmpq_t s, const fmpz_t h, const fmpz_t k);

void dedekind_sum(fmpq_t s, const fmpz_t h, const fmpz_t k);

/* Exponential sums **********************************************************/

typedef struct
{
    int n;
    int prefactor;
    mp_limb_t sqrt_p;
    mp_limb_t sqrt_q;
    mp_limb_signed_t cos_p[FLINT_BITS];
    mp_limb_t cos_q[FLINT_BITS];
} trig_prod_struct;

typedef trig_prod_struct trig_prod_t[1];

static __inline__
void trig_prod_init(trig_prod_t sum)
{
    sum->n = 0;
    sum->prefactor = 1;
    sum->sqrt_p = 1;
    sum->sqrt_q = 1;
}

void dedekind_cosine_sum_factored(trig_prod_t prod, mp_limb_t k, mp_limb_t n);

/* Number of partitions ******************************************************/

void number_of_partitions_nmod_vec(mp_ptr res, long len, nmod_t mod);

void number_of_partitions_vec(fmpz * res, long len);

void number_of_partitions_mpfr(mpfr_t x, ulong n);

void number_of_partitions(fmpz_t x, ulong n);

void number_of_distinct_partitions_vec(fmpz * res, long len);

void number_of_distinct_partitions_nmod_vec(mp_ptr res, long len, nmod_t mod);

/* Number of sums of squares representations *********************************/

void sum_of_squares(fmpz_t r, ulong k, const fmpz_t n);

void sum_of_squares_vec(fmpz * r, ulong k, long n);

/* MPFR extras ***************************************************************/

void mpfr_pi_chudnovsky(mpfr_t res, mpfr_rnd_t rnd);

void mpfr_const_euler_brent_mcmillan(mpfr_t res, mpfr_rnd_t rnd);

void mpfr_zeta_ui_bsplit(mpfr_t x, ulong s, mpfr_rnd_t rnd);

#ifdef __cplusplus
}
#endif

#endif
