#include <math.h>
#include <float.h>
#include <errno.h>

#pragma function(exp)

#ifndef M_LN2
#define M_LN2 0.69314718055994530941723212145817657
#endif
#ifndef M_LOG2E
#define M_LOG2E 1.44269504088896340735992468100189213
#endif
#ifndef M_LN_MAX_D
#define M_LN_MAX_D (M_LN2 * DBL_MAX_EXP)
#endif
#ifndef M_LN_MIN_D
#define M_LN_MIN_D (M_LN2 * (DBL_MIN_EXP - 1))
#endif

#ifndef POLYNOM3
#define POLYNOM1(x, a) ((a)[1] * (x) + (a)[0])
#define POLYNOM2(x, a) (POLYNOM1((x), (a) + 1) * (x) + (a)[0])
#define POLYNOM3(x, a) (POLYNOM2((x), (a) + 1) * (x) + (a)[0])
#endif

double __cdecl exp(double x)
{
	const double p[] = {
		0.25000000000000000000e+0,
		0.75753180159422776666e-2,
		0.31555192765684646356e-4
	};
	const double q[] = {
		0.50000000000000000000e+0,
		0.56817302698551221787e-1,
		0.63121894374398503557e-3,
		0.75104028399870046114e-6
	};

	double xn, g, x1, x2;
	int    n;
	int    negative;

	if (_isnan(x)) {
		errno = EDOM;
		return x;
	}
	if (x < M_LN_MIN_D) {
		errno = ERANGE;
		return 0.0;
	}
	if (x > M_LN_MAX_D) {
		errno = ERANGE;
		return HUGE_VAL;
	}
	negative = x < 0;
	if (negative)
		x = -x;
	n = (int)(x * M_LOG2E + 0.5);
	xn = n;
	x2 = modf(x, &x1);
	g = ((x1 - xn * 0.693359375) + x2) - xn * (-2.1219444005469058277e-4);
	if (negative) {
		g = -g;
		n = -n;
	}
	xn = g * g;
	x = g * POLYNOM2(xn, p);
	n += 1;
	return ldexp(0.5 + x / (POLYNOM3(xn, q) - x), n);
}
