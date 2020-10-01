/*!
	\file
	\brief Решение квадратных уравнений
	\author d0p1er
	\version 0.0.1
	\date сентябрь 2020 года
*/

#include <stdio.h>
#include <math.h>

const int TestOrNot = 0;	///< Проводить Unit Testing или нет

const int NoRoots = 0;	///< Действительных корней нет
const int OneRoot = 1;	///< Уравнение имеет единственное решение
const int TwoRoots = 2; ///< Уравнение имеет два решения
const int Inf = 3;		///< Уравнение имеет бесконечное количество решений

const double Delta = 1E-6;	///< Погрешность

int ScanfCoefficient(char* NameOfCoeff);
int SolveQE(double a, double b, double c, double* x1, double* x2);
int SolveLin(double a, double b, double* x);
int AreNumbersEqual(double Num1, double Num2);
void UnitTest(int TestOrNot);


int main()
	{
	UnitTest(TestOrNot);
	printf("Saluton mia amiko. This program will help you to solve qudratic equation ax² + bx + c = 0\nLet`s start\n");

	double a = ScanfCoefficient("a"), b = ScanfCoefficient("b"), c = ScanfCoefficient("c"), x1 = 0, x2 = 0;

	int AmountOfRoots = SolveQE(a, b, c, &x1, &x2);

	switch(AmountOfRoots)
		{
		case 0:  printf("No roots\n");											break;
		case 1:  printf("There is one root : x = %lf\n", x1);					break;
		case 2:  printf("There are two roots : x1 = %lf, x2 = %lf\n", x1, x2);	break;
		case 3:  printf("There are Infinite roots\n");							break;
		default: printf("ERROR\n");												break;
		}
	}

/*!
	\brief Ввод коэффициентов по его имени
	\param[in] NameOfCoeff Название коэффициента, которое должен ввести пользователь
*/
int ScanfCoefficient(char* NameOfCoeff)
	{
	double TempCoeff = 0;

	printf("%s = ", NameOfCoeff);
	scanf("%lf", &TempCoeff);

	return TempCoeff;
	}

/*!
	\brief Данная функция решает квадратное уравнение вида ax² + bx + c = 0
	\param[in] a Коэффициент квадратного уравнения a
	\param[in] b Коэффициент квадратного уравнения b
	\param[in] c Коэффициент квадратного уравнения c
	\param[in] x1 Указатель первого корня квадратного уравнения
	\param[in] x2 Указатель второго корня квадратного уравнения

	\param[out] AmountOfRoots Количество решений

	Корни квадратного уравнения находятся по формуле:
	\f[
		x_{1,2} = \frac{-b \pm \sqrt{D}}{2a} \, ,где \, D = b^2 -4ac
	\f]
*/
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

/*!
	\brief Данная функция решает уравнение вида ax + b = 0
	\param[in] a Коэффициент квадратного уравнения a
	\param[in] b Коэффициент квадратного уравнения b
	\param[in] x Корень уравнения

	\param[out] AmountOfRoots Количество решений
*/
int SolveLin(double a, double b, double* x)
	{
	if(AreNumbersEqual(a, 0) && AreNumbersEqual(b, 0))
		return Inf;

	if(AreNumbersEqual(a, 0) && !AreNumbersEqual(b, 0))
		return NoRoots;

	*x = -b/a;
	return OneRoot;
	}

/*!
	\brief Данная функция сравнивает два числа с учетом погрешности \link Delta \endlink
	\param[in] Num1 Первое число
	\param[in] Num2 Второе число
*/
int AreNumbersEqual(double Num1, double Num2)
	{
	if(fabs(Num1 - Num2) <= Delta)
		return 1;

	return 0;
	}

/*!
	\brief Unit Testing
	
	Функция юнит тестирования
	
	\param[in] TestOrNot Проводить Unit Testing или нет
*/
void UnitTest(int TestOrNot)
	{
	if(TestOrNot)
		{
		double TestA[] = 				{ 1,   0,   1,   0,   0,   1,    2,         10, 	 1,			  0,   0};
		double TestB[] = 				{ 2,   0,   1,   0,   1,   4,    6,         12, 	 4.000000004, 2,   1};
		double TestC[] = 				{ 1,   0,   1,   1,   0,   5,    2,         2,  	 4.000000001, 0,   1};
		double TestAmountOfRoots[] =	{ 1,   3,   0,   0,   1,   0,    2,         2,  	 1,			  1,   1};
		double TestX1[] = 				{-1,   NAN, NAN, NAN, 0,   NAN, -0.381966, -0.2,    -2,			  0,  -1};
		double TestX2[] = 				{ NAN, NAN, NAN, NAN, NAN, NAN, -2.618034, -1,	     NAN,		  NAN, NAN};

		int AmountOfUnitTests = sizeof(TestAmountOfRoots)/sizeof(double);

		int ResultAmountOfRoots = -1;
		double ResultX1 = NAN;
		double ResultX2 = NAN;

		for(int i = 0; i < AmountOfUnitTests; i++)
			{
			ResultAmountOfRoots = SolveQE(TestA[i], TestB[i], TestC[i], &ResultX1, &ResultX2);

			switch(ResultAmountOfRoots)
				{
				case 1: 	if(AreNumbersEqual(ResultX1, TestX1[i])) 											printf("TEST%i PASSED:)\n", i + 1);	else printf("TEST%i FAILED:(\n", i + 1); 	break;
				case 2: 	if(AreNumbersEqual(ResultX1, TestX1[i]) && AreNumbersEqual(ResultX2, TestX2[i])) 	printf("TEST%i PASSED:)\n", i + 1);	else printf("TEST%i FAILED:(\n", i + 1); 	break;
				default: 	if(ResultAmountOfRoots == TestAmountOfRoots[i]) 									printf("TEST%i PASSED:)\n", i + 1);	else printf("TEST%i FAILED:(\n", i + 1); 	break;
				}
			ResultAmountOfRoots = -1;
			ResultX1 = NAN;
			ResultX2 = NAN;
			}
		}
	}