#pragma once

#include <math.h>
#include <iostream>
#include <iomanip>

void CeilingFloorTrunc(double d)
{
	std::cout << "floor: " << std::floor(d) << std::endl;
	std::cout << "ceil: " << std::ceil(d) << std::endl;
	std::cout << "trunk: " << std::trunc(d) << std::endl;
	std::cout << "round: " << std::round(d) << std::endl;
}

template<typename T>
void FloatingPointManipulation(T& t)
{
	int i;
	T t2 = std::frexp(t, &i);

	//t2*exp^i = t;
	std::cout << "exp: " << std::dec << i << " mantissa: " << t2 << std::endl;

	T k;
	T t3 = std::modf(t, &k);
	// k + t3 = t;
	std::cout << "fractional " << k << "integral" << t3 << std::endl;

	std::cout << "hexfloat: " << std::hexfloat << t << std::defaultfloat << std::endl;
	std::cout << "hex: " << t << std::endl;
}

template<typename T>
void FloatingPointExtra(T& t)
{
	std::cout << "inf: " << std::numeric_limits<T>::infinity() << std::endl;
	std::cout << "epsilon: " << std::numeric_limits<T>::epsilon() << std::endl;
	std::cout << "max round err: " << std::numeric_limits<T>::round_error() << std::endl;
	std::cout << "quite nan: " << std::numeric_limits<T>::quiet_NaN() << std::endl;
	std::cout << "signalling nan: " << std::numeric_limits<T>::signaling_NaN() << std::endl;

	T from1 = 2.0, to1 = std::nextafter(from1, t + 0.5);

	std::cout << "The next representable float after " << std::setprecision(50) << from1
			  << " is " << to1 << std::defaultfloat << std::endl;

	std::cout << "diff: " << to1 - from1 << std::endl;

	auto diff = 0.0000001;
	auto target = from1;

	while(target < 3.0)
	{
		target+= diff;
	}

	std::cout << "target: " << target << std::endl;

	auto x1 = 0.5323222321123;
	auto x2 = 2.232322232222;
	auto x3 = 0.11231232222322;

	auto result = x1*x2 + x3;
	auto result2 = std::fma(x1, x2, x3);

	std::cout << "result1: " << result << " result2: " << result2 << " diff: " << result2 - result << std::endl;
	std::cout << "INFINITY: " << std::exp(800) << std::endl;
	std::cout << "NAN: " << std::sqrt(-1) << std::endl;
}

double calculateSum()
{
	double S = 2.0; double K=65.0;
	double h = 1.0;

	double sum = 0.0;
	for(int i=1; i <=5; ++i)
	{
		sum+= std::sqrt(S / K);
		std::cout << "i: " << i << " sum:" << sum << " S: " << S << std::endl;
		S-=h;
	}

	std::cout << "sum: " << sum << std::endl;
}

double computeEpsilon()
{
	double x = 1.0;
	double epsilon = x;

	while(x + epsilon != 1.0)
	{
		epsilon*= 0.5;
	}

	return epsilon / 0.5;
}