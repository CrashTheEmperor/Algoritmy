/** \file fibonacci.c
 *  \brief Definice různých variant implementace výpočtu hodnot Fibonacciho posloupnosti
 *  \author Petyovský
 *  \version 2025
 *  $Id: fibonacci.c 3039 2025-03-28 16:01:33Z petyovsky $
 */

#include "fibonacci.h"

//-----------------------------------------------------------------------
// Implementace stromovou rekurzi
unsigned fibonacci1(unsigned n)
	{
	if (n < 2)
		return n;
	return fibonacci1(n - 1) + fibonacci1(n - 2);
	}

//-----------------------------------------------------------------------
// Implementace iteraci
unsigned fibonacci2(unsigned n)
	{
	unsigned fib_n_1 = 1;	// fibonacci(n-1)
	unsigned fib_n_2 = 0;	// fibonacci(n-2)

	while (n-- > 0)
	{
		unsigned tmp = fib_n_1 + fib_n_2;
		fib_n_2 = fib_n_1; // předám hodnotu
		fib_n_1 = tmp;
	}
	return fib_n_2;
	}

//-----------------------------------------------------------------------
// Implementace stromovou rekurzi s memoizaci
struct TMemoizer m_fibonacci3 = { 0, };	// Instance memoizeru pro funkci fibonacci3()

unsigned fibonacci3(unsigned n)
	{
	if (n < 2)
		return n;

	return memoizer_eval(&m_fibonacci3, n - 1) + memoizer_eval(&m_fibonacci3, n - 2);

	// 	return fibonacci1(n - 1) + fibonacci1(n - 2);
	}

unsigned fibonacci3_wrapper(unsigned n)
	{
	return memoizer_eval(&m_fibonacci3, n);
	}

//-----------------------------------------------------------------------
// Implementace s koncovou rekurzi
/** \brief Vnitřní a lokální funkce realizující koncovou rekurzi
 */
[[nodiscard]] static unsigned fibonacci4_worker(unsigned n, unsigned fib_n_1, unsigned fib_n_2)
	{
	if (n == 0)
		return fib_n_2;
	return fibonacci4_worker(n - 1, fib_n_1 + fib_n_2, fib_n_1);
	}

unsigned fibonacci4(unsigned n)
	{
	return fibonacci4_worker(n, 1, 0);
	}
