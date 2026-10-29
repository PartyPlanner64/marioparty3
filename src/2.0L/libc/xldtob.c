#include "macros.h"
#include "gcc/string.h"
#include "stdlib.h"
#include "xstdio.h"

#define BUFF_LEN 0x20

/* float properties */
#define _D0 0
#define _DBIAS 0x3ff
#define _DLONG 1
#define _DOFF 4
#define _FBIAS 0x7e
#define _FOFF 7
#define _FRND 1
#define _LBIAS 0x3ffe
#define _LOFF 15
/* integer properties */
#define _C2 1
#define _CSIGN 1
#define _ILONG 0
#define _MBMAX 8
#define NAN 2
#define INF 1
#define FINITE -1
#define _DFRAC ((1 << _DOFF) - 1)
#define _DMASK (0x7fff & ~_DFRAC)
#define _DMAX ((1 << (15 - _DOFF)) - 1)
#define _DNAN (0x8000 | _DMAX << _DOFF | 1 << (_DOFF - 1))
#define _DSIGN 0x8000
#define _D1 1 /* big-endian order */
#define _D2 2
#define _D3 3

static const double pows[] = { 10e0L, 10e1L, 10e3L, 10e7L, 10e15L, 10e31L, 10e63L, 10e127L, 10e255L };

static short _Ldunscale(short *, _Pft *);
static void _Genld(_Pft *, char, char *, short, short);

void _Ldtob(_Pft *args, char type) {
    char buff[BUFF_LEN];
    char *p;
    double ldval;
    short err;
    short nsig;
    short exp;

    p = buff;
    ldval = args->v.ld;
    if (args->prec < 0) {
        args->prec = 6;
    } else {
        if (args->prec == 0 && (type == 'g' || type == 'G')) {
            args->prec = 1;
        }
    }
    err = _Ldunscale(&exp, args);
    if (err > 0) {
        memcpy(args->s, err == 2 ? "NaN" : "Inf", args->n1 = 3);
        return;
    }
    if (err == 0) {
        nsig = 0;
        exp = 0;
    } else {
        int i;
        int n;

        if (ldval < 0) {
            ldval = -ldval;
        }
        exp = exp * 30103 / 0x000186A0 - 4;
        if (exp < 0) {
            n = (-exp + 3) & ~3;
            exp = -n;
            for (i = 0; n > 0; n >>= 1, i++) {
                if ((n & 1) != 0) {
                    ldval *= pows[i];
                }
            }
        } else {
            if (exp > 0) {
                double factor;
                factor = 1;
                exp &= ~3;
                for (n = exp, i = 0; n > 0; n >>= 1, i++) {
                    if ((n & 1) != 0) {
                        factor *= pows[i];
                    }
                }
                ldval /= factor;
            }
        }
        {
            int gen;
            gen = args->prec + ((type == 'f') ? exp + 10 : 6);
            if (gen > 0x13) {
                gen = 0x13;
            }
            *p++ = '0';
            while (gen > 0 && 0 < ldval) {
                int j;
                int lo;
                lo = ldval;
                if ((gen -= 8) > 0) {
                    ldval = (ldval - lo) * 1.0e8;
                }
                p = p + 8;
                for (j = 8; lo > 0 && --j >= 0;) {
                    ldiv_t qr = ldiv(lo, 10);
                    *--p = qr.rem + '0';
                    lo = qr.quot;
                }
                while (--j >= 0) {
                    p--;
                    *p = '0';
                }
                p += 8;
            }

            gen = p - &buff[1];
            for (p = &buff[1], exp += 7; *p == '0'; p++) {
                --gen, --exp;
            }

            nsig = args->prec + ((type == 'f') ? exp + 1 : ((type == 'e' || type == 'E') ? 1 : 0));
            if (gen < nsig) {
                nsig = gen;
            }
            if (nsig > 0) {
                char drop;
                int n;
                if (nsig < gen && p[nsig] > '4') {
                    drop = '9';
                } else {
                    drop = '0';
                }

                for (n = nsig; p[--n] == drop;) {
                    nsig--;
                }
                if (drop == '9') {
                    p[n]++;
                }
                if (n < 0) {
                    --p, ++nsig, ++exp;
                }
            }
        }
    }
    _Genld(args, type, p, nsig, exp);
}

static short _Ldunscale(short *pex, _Pft *px) {

    unsigned short *ps = (unsigned short *)px;
    short xchar = (ps[_D0] & _DMASK) >> _DOFF;
    if (xchar == _DMAX) { /* NaN or INF */
        *pex = 0;
        return (short)(ps[_D0] & _DFRAC || ps[_D1] || ps[_D2] || ps[_D3] ? NAN : INF);
    } else if (0 < xchar) {
        ps[_D0] = (ps[_D0] & ~_DMASK) | (_DBIAS << _DOFF);
        *pex = xchar - (_DBIAS - 1);
        return (FINITE);
    }
    if (0 > xchar) {
        return NAN;
    } else {
        *pex = 0;
        return (0);
    }
}

static void _Genld(_Pft *px, char code, char *p, short nsig, short xexp) {
    const char point = '.';
    if (nsig <= 0) {
        nsig = 1,

        p = "0";
    }

    if (code == 'f' || ((code == 'g' || code == 'G') && (-4 <= xexp) && (xexp < px->prec))) { /* 'f' format */
        ++xexp;                                                                               /* change to leading digit count */
        if (code != 'f') {                                                                    /* fixup for 'g' */
            if (!(px->flags & FLAGS_HASH) && nsig < px->prec) {
                px->prec = nsig;
            }
            if ((px->prec -= xexp) < 0) {
                px->prec = 0;
            }
        }
        if (xexp <= 0) { /* digits only to right of point */
            px->s[px->n1++] = '0';
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = point;
            }
            if (px->prec < -xexp) {
                xexp = -px->prec;
            }
            px->nz1 = -xexp;
            px->prec += xexp;
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p, px->n2 = nsig);
            px->nz2 = px->prec - nsig;
        } else if (nsig < xexp) { /* zeros before point */
            memcpy(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = xexp - nsig;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1] = point, ++px->n2;
            }
            px->nz2 = px->prec;
        } else { /* enough digits before point */
            memcpy(&px->s[px->n1], p, xexp);
            px->n1 += xexp;
            nsig -= xexp;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = point;
            }
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p + xexp, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
    } else {                              /* 'e' format */
        if (code == 'g' || code == 'G') { /* fixup for 'g' */
            if (nsig < px->prec) {
                px->prec = nsig;
            }
            if (--px->prec < 0) {
                px->prec = 0;
            }
            code = code == 'g' ? 'e' : 'E';
        }
        px->s[px->n1++] = *p++;
        if (0 < px->prec || px->flags & FLAGS_HASH) {
            px->s[px->n1++] = point;
        }
        if (0 < px->prec) { /* put fraction digits */
            if (px->prec < --nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
        p = &px->s[px->n1]; /* put exponent */
        *p++ = code;
        if (0 <= xexp) {
            *p++ = '+';
        } else { /* negative exponent */
            *p++ = '-';
            xexp = -xexp;
        }
        if (100 <= xexp) { /* put oversize exponent */
            if (1000 <= xexp) {
                *p++ = xexp / 1000 + '0', xexp %= 1000;
            }
            *p++ = xexp / 100 + '0', xexp %= 100;
        }
        *p++ = xexp / 10 + '0', xexp %= 10;
        *p++ = xexp + '0';
        px->n2 = p - &px->s[px->n1];
    }
    if ((px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) { /* pad with leading zeros */
        int n =
            px->n0 + px->n1 + px->nz1 + px->n2 + px->nz2;

        if (n < px->width) {
            px->nz0 = px->width - n;
        }
    }
}
