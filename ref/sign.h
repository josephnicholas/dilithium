#ifndef SIGN_H
#define SIGN_H

#include "params.h"
#include "poly.h"
#include "polyvec.h"

void expand_mat(polyvecl mat[K], const unsigned char rho[SEEDBYTES]);
void challenge(poly *c, const unsigned char mu[CRHBYTES],
               const polyveck *w1);

int crypto_sign_dilithium_keypair(unsigned char *pk, unsigned char *sk, const unsigned char *seed);

int crypto_sign_dilithium(unsigned char *sm, unsigned long long *smlen,
                const unsigned char *msg, unsigned long long len,
                const unsigned char *sk);

int crypto_sign_dilithium_open(unsigned char *m, unsigned long long *mlen,
                     const unsigned char *sm, unsigned long long smlen,
                     const unsigned char *pk);

#endif
