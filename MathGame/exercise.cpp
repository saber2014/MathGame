#include "exercise.h"

CompressedVector Exercise::m_lookupTable[EXERCISE_SIGN_DIVISION][EXERCISE_SIGN_DIVISION];

Exercise::Exercise()
{
	this->m_type = EXERCISE_TYPE_DEFAULT;
	this->m_sign1 = EXERCISE_SIGN_DEFAULT;
	this->m_sign2 = EXERCISE_SIGN_DEFAULT;
	this->m_number1 = 0;
	this->m_number2 = 0;
	this->m_number3 = 0;
	this->m_number4 = 0;
	this->m_hide1 = EXERCISE_HIDE_DEFAULT;
	this->m_hide2 = EXERCISE_HIDE_DEFAULT;
}

void Exercise::InitLookupTable()
{
	for (int num1 = EXERCISE_MIN_VALUE; num1 <= EXERCISE_MAX_VALUE; num1++)
	{
		for (int num2 = EXERCISE_MIN_VALUE; num2 <= EXERCISE_MAX_VALUE; num2++)
		{
			for (int num3 = EXERCISE_MIN_VALUE; num3 <= EXERCISE_MAX_VALUE; num3++)
			{
				for (int i = EXERCISE_SIGN_PLUS; i <= EXERCISE_SIGN_DIVISION; i++)
				{
					for (int j = EXERCISE_SIGN_PLUS; j <= EXERCISE_SIGN_DIVISION; j++)
					{
						int res = Exercise::Calculate(num1, num2, num3, (EXERCISE_SIGN)i, (EXERCISE_SIGN)j);

						if (res != EXERCISE_INVALID_VALUE)
						{
							Exercise::m_lookupTable[i - 1][j - 1].Insert(num1);
							Exercise::m_lookupTable[i - 1][j - 1].Insert(num2);
							Exercise::m_lookupTable[i - 1][j - 1].Insert(num3);
						}
					}
				}
			}
		}
	}
}

int Exercise::Calculate(int num1, int num2, int num3, EXERCISE_SIGN sign1, EXERCISE_SIGN sign2)
{
	if ((sign2 == EXERCISE_SIGN_MULTIPLICATION || sign2 == EXERCISE_SIGN_DIVISION) &&
		(sign1 == EXERCISE_SIGN_PLUS || sign1 == EXERCISE_SIGN_MINUS))
	{
		int res = Exercise::Calculate(num2, num3, sign2);

		return (res == EXERCISE_INVALID_VALUE) ? res : Exercise::Calculate(num1, res, sign1);
	}
	else
	{
		int res = Exercise::Calculate(num1, num2, sign1);

		return (res == EXERCISE_INVALID_VALUE) ? res : Exercise::Calculate(res, num3, sign2);
	}

	return EXERCISE_INVALID_VALUE;
}

int Exercise::Calculate(int num1, int num2, EXERCISE_SIGN sign)
{
	switch (sign)
	{
	case EXERCISE_SIGN_PLUS:
		return num1 + num2;
		break;

	case EXERCISE_SIGN_MINUS:
		if (num1 - num2 <= 0)
			return EXERCISE_INVALID_VALUE;
		
		return num1 - num2;
		break;

	case EXERCISE_SIGN_MULTIPLICATION:
		return num1 * num2;
		break;

	case EXERCISE_SIGN_DIVISION:
		if (num1 % num2 != 0 || num2 == 0)
			return EXERCISE_INVALID_VALUE;
		
		return num1 / num2;
		break;
	}

	return EXERCISE_INVALID_VALUE;
}

void Exercise::GenerateSimple(int level)
{
	this->m_type = EXERCISE_TYPE_SIMPLE;
	this->m_sign1 = (EXERCISE_SIGN)(1 + rand() % 4);
	this->m_number1 = 1 + rand() % (10 + level);
	this->m_number2 = 1 + rand() % (10 + level);

	if (this->m_sign1 == EXERCISE_SIGN_PLUS || this->m_sign1 == EXERCISE_SIGN_MULTIPLICATION)
	{
		if (this->m_sign1 == EXERCISE_SIGN_PLUS)
			this->m_number3 = this->m_number1 + this->m_number2;
		else
			this->m_number3 = this->m_number1 * this->m_number2;
	}
	else
	{
		int max = (int)fmax(this->m_number1, this->m_number2);
		int min = (int)fmin(this->m_number1, this->m_number2);

		this->m_number1 = max;
		this->m_number2 = min;

		if (this->m_sign1 == EXERCISE_SIGN_MINUS)
		{
			if (max - min == 0)
			{
				this->m_number1++;
				max++;
			}

			this->m_number3 = max - min;
		}
		else
		{
			if (max % min != 0)
				this->m_number1 -= max % min;

			this->m_number3 = max / min;
		}
	}

	this->m_hide1 = (EXERCISE_HIDE)(2 + rand() % 2);
}

void Exercise::GenerateComplex()
{
	this->m_type = EXERCISE_TYPE_COMPLEX;
	this->m_sign1 = (EXERCISE_SIGN)(1 + rand() % 4);
	this->m_sign2 = (EXERCISE_SIGN)(1 + rand() % 4);

	int r = rand() % ((Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].GetLength()) / 3);

	ExerciseTriplet triplet =
	{
		Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].Get(3 * r),
		Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].Get(3 * r + 1),
		Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].Get(3 * r + 2)
	};

	this->m_number1 = triplet.number1;
	this->m_number2 = triplet.number2;
	this->m_number3 = triplet.number3;

	this->m_number4 = Exercise::Calculate(this->m_number1, this->m_number2, this->m_number3, this->m_sign1, this->m_sign2);

	int min1 = EXERCISE_MAX_VALUE + 1, min2 = EXERCISE_MAX_VALUE + 1;
	EXERCISE_HIDE hide1 = EXERCISE_HIDE_DEFAULT, hide2 = EXERCISE_HIDE_DEFAULT;

	for (int i = 0; i < 4; i++)
	{
		if (this->GetNumber(i + 1) < min1)
		{
			min1 = this->GetNumber(i + 1);
			hide1 = (EXERCISE_HIDE)(i + 1);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (min1 <= this->GetNumber(i + 1) && this->GetNumber(i + 1) < min2 && (EXERCISE_HIDE)(i + 1) != hide1)
		{
			min2 = this->GetNumber(i + 1);
			hide2 = (EXERCISE_HIDE)(i + 1);
		}
	}

	this->m_hide1 = (EXERCISE_HIDE)((int)fmin((double)hide1, (double)hide2));
	this->m_hide2 = (EXERCISE_HIDE)((int)fmax((double)hide1, (double)hide2));

#if defined(_DEBUG) && defined(_MSC_VER)
	char buf[255];
	sprintf(buf, "%d %d %d %d\n", this->m_number1, this->m_number2, this->m_number3, this->m_number4);
	
	OutputDebugMessage(buf);
#endif
}

EXERCISE_TYPE Exercise::GetType()
{
	return this->m_type;
}

char Exercise::GetSign(int sign)
{
	EXERCISE_SIGN es = (sign == 1) ? this->m_sign1 : this->m_sign2;

	switch (es)
	{
	case EXERCISE_SIGN_PLUS:
		return '+';
		break;

	case EXERCISE_SIGN_MINUS:
		return '-';
		break;

	case EXERCISE_SIGN_MULTIPLICATION:
		return '*';
		break;

	case EXERCISE_SIGN_DIVISION:
		return '/';
		break;
	}

	return EXERCISE_SIGN_DEFAULT;
}

int Exercise::GetNumber(int number)
{
	switch (number)
	{
	case 1:
		return this->m_number1;
		break;

	case 2:
		return this->m_number2;
		break;

	case 3:
		return this->m_number3;
		break;

	case 4:
		return this->m_number4;
		break;
	}

	return EXERCISE_INVALID_VALUE;
}

int Exercise::GetSolution(int solution)
{
	EXERCISE_HIDE eh = EXERCISE_HIDE_DEFAULT;

	if (solution == 1)
		eh = this->m_hide1;
	else
	{
		if (this->m_hide2 == EXERCISE_HIDE_DEFAULT) eh = this->m_hide1;
		else eh = this->m_hide2;
	}

	switch (eh)
	{
	case EXERCISE_HIDE_NUMBER1:
		return this->m_number1;
		break;
		
	case EXERCISE_HIDE_NUMBER2:
		return this->m_number2;
		break;
	case EXERCISE_HIDE_NUMBER3:
		return this->m_number3;
		break;
		
	case EXERCISE_HIDE_NUMBER4:
		return this->m_number4;
		break;
	}

	return EXERCISE_INVALID_VALUE;
}

string Exercise::GetExercise()
{
	const int LENGTH = (this->m_type == EXERCISE_TYPE_SIMPLE) ? 3 : 4;

	char buf[255] = { 0 };

	for (int i = 0; i < LENGTH; i++)
	{
		if (this->m_hide1 == (EXERCISE_HIDE)(i + 1) || this->m_hide2 == (EXERCISE_HIDE)(i + 1))
			strcat(buf, "_");
		else
		{
			char temp[16];
			sprintf(temp, "%d", this->GetNumber(i + 1));

			strcat(buf, temp);
		}

		if (0 <= i && i <= LENGTH - 2)
		{
			char temp[] = { ' ', ' ', ' ', 0 };

			if (this->m_type == EXERCISE_TYPE_SIMPLE)
			{
				switch (i)
				{
				case 0:
					temp[1] = this->GetSign(1);
					break;

				case 1:
					temp[1] = '=';
					break;
				}
			}
			else
			{
				switch (i)
				{
				case 0:
					temp[1] = this->GetSign(1);
					break;

				case 1:
					temp[1] = this->GetSign(2);
					break;

				case 2:
					temp[1] = '=';
					break;
				}
			}

			strcat(buf, temp);
		}
	}

	return buf;
}

bool Exercise::IsPossibleSolution(int number)
{
	int arr[] = { 0, 0, 0, 0 };

	if (this->m_hide1 != EXERCISE_HIDE_NUMBER1 && this->m_hide2 != EXERCISE_HIDE_NUMBER1)
		arr[0] = this->m_number1;

	if (this->m_hide1 != EXERCISE_HIDE_NUMBER2 && this->m_hide2 != EXERCISE_HIDE_NUMBER2)
		arr[1] = this->m_number2;

	if (this->m_hide1 != EXERCISE_HIDE_NUMBER3 && this->m_hide2 != EXERCISE_HIDE_NUMBER3)
		arr[2] = this->m_number3;

	if (this->m_hide1 != EXERCISE_HIDE_NUMBER4 && this->m_hide2 != EXERCISE_HIDE_NUMBER4)
		arr[3] = this->m_number4;

	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		if (!arr[i])
		{
			arr[i] = number;
			break;
		}
	}

	for (int i = 0; i < Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].GetLength(); i += 3)
	{
		ExerciseTriplet et =
		{
			Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].Get(i),
			Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].Get(i + 1),
			Exercise::m_lookupTable[this->m_sign1 - 1][this->m_sign2 - 1].Get(i + 2)
		};

		int res = Exercise::Calculate(et.number1, et.number2, et.number3, this->m_sign1, this->m_sign2);

		bool b1 = false, b2 = false, b3 = false, b4 = false;

		if (arr[0] == 0 || arr[0] == et.number1) b1 = true;
		if (arr[1] == 0 || arr[1] == et.number2) b2 = true;
		if (arr[2] == 0 || arr[2] == et.number3) b3 = true;
		if (arr[3] == 0 || arr[3] == res) b4 = true;

		if (b1 && b2 && b3 && b4)
		{
			this->m_number1 = et.number1;
			this->m_number2 = et.number2;
			this->m_number3 = et.number3;
			this->m_number4 = res;

			if (this->m_hide1 != EXERCISE_HIDE_DEFAULT && this->m_hide2 != EXERCISE_HIDE_DEFAULT)
			{
				this->m_hide1 = this->m_hide2;
				this->m_hide2 = EXERCISE_HIDE_DEFAULT;
			}
			else
				this->m_hide1 = EXERCISE_HIDE_DEFAULT;

			return true;
		}
	}

	return false;
}

bool Exercise::IsSolved()
{
	if (this->m_hide1 == EXERCISE_HIDE_DEFAULT && this->m_hide2 == EXERCISE_HIDE_DEFAULT)
		return true;

	return false;
}