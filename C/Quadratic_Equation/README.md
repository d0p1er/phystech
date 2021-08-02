# Quadratic Equation
> sorry for my English

# Content
1. [Introduction](#intro)
2. [How it works](#how)
3. [Example](#ex)
4. [Conclusion](#conc)

<a name="intro"></a>
## 1. Introduction

It's my first C project in MIPT. So don't judge harshly and treat with understanding.
This program solves equations of the form **ax² + bx + c = 0**.
User enters coefficients a, b, c. And then gets answer.
The program gives out amount of roots and the roots of equation. 

<a name="how"></a>
## 2. How it works
There is one general function:
```C
int SolveQE(double a, double b, double c, double* x1, double* x2)
	{
	if(AreNumbersEqual(a, 0))
		return SolveLin(b, c, x1);

	if(AreNumbersEqual(b, 0) && AreNumbersEqual(c, 0))
		{
		*x1 = 0;
		return OneRoot;
		}

	if(AreNumbersEqual(c, 0))
		{
		*x1 = 0;
		return OneRoot + SolveLin(a, b, x2);
		}

	double D = b*b - 4*a*c;		

	if(AreNumbersEqual(D, 0))
		{
		*x1 = -b/(2*a);
		return OneRoot;
		}

	if(D < 0)
		return NoRoots;

	D = sqrt(D);

	*x1 = (-b + D)/(2*a);
	*x2 = (-b - D)/(2*a);

	return TwoRoots;
	}
```
It compares coefficients with zero to optimize calculations ( in some cases quadratic equation reduces to the linear ), because function of finding sqrt of the discriminant is costly.

Also there are 11 unit tests to check how the program works correctly.
If you want to use `void UnitTest(int TestOrNot)` you need to change `const int TestOrNot` to 1.

<a name="ex"></a>
## 3. Example:

```zsh
[out] Saluton mia amiko. This program will help you to solve qudratic equation ax² + bx + c = 0
[out] Let`s start

[in]  a = 5
[in]  b = 2
[in]  c = -2

[out] There are two roots : x1 = 0.463325, x2 = -0.863325
```
<a name="intro"></a>
## 4. Conclusion

