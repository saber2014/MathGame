#include "exercise.h"

Exercise::Exercise()
{
	this->m_sign = EXERCISE_SIGN_DEFAULT;
	this->m_number1 = 0;
	this->m_number2 = 0;
	this->m_number3 = 0;
	this->m_hide = EXERCISE_HIDE_DEFAULT;
}

void Exercise::GenerateSimple(int level)
{
	this->m_sign = (EXERCISE_SIGN)(1 + rand() % 4);
	this->m_number1 = 1 + rand() % (10 + level);
	this->m_number2 = 1 + rand() % (10 + level);

	if (this->m_sign == EXERCISE_SIGN_PLUS || this-> m_sign == EXERCISE_SIGN_MULTIPLICATION)
	{
		if (this->m_sign == EXERCISE_SIGN_PLUS)
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

		if (this->m_sign == EXERCISE_SIGN_MINUS)
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

	this->m_hide = (EXERCISE_HIDE)(2 + rand() % 2);
}

string Exercise::GetExercise()
{
	switch (this->m_hide)
	{
	case EXERCISE_HIDE_NUMBER2:
	{
		char buf[255];

		switch (this->m_sign)
		{
		case EXERCISE_SIGN_PLUS:
			sprintf(buf, "%d + _ = %d", this->m_number1, this->m_number3);
			break;

		case EXERCISE_SIGN_MINUS:
			sprintf(buf, "%d - _ = %d", this->m_number1, this->m_number3);
			break;

		case EXERCISE_SIGN_MULTIPLICATION:
			sprintf(buf, "%d * _ = %d", this->m_number1, this->m_number3);
			break;

		case EXERCISE_SIGN_DIVISION:
			sprintf(buf, "%d / _ = %d", this->m_number1, this->m_number3);
			break;
		}

		return buf;
	}
	break;

	case EXERCISE_HIDE_NUMBER3:
	{
		char buf[255];

		switch (this->m_sign)
		{
		case EXERCISE_SIGN_PLUS:
			sprintf(buf, "%d + %d = _", this->m_number1, this->m_number2);
			break;

		case EXERCISE_SIGN_MINUS:
			sprintf(buf, "%d - %d = _", this->m_number1, this->m_number2);
			break;

		case EXERCISE_SIGN_MULTIPLICATION:
			sprintf(buf, "%d * %d = _", this->m_number1, this->m_number2);
			break;

		case EXERCISE_SIGN_DIVISION:
			sprintf(buf, "%d / %d = _", this->m_number1, this->m_number2);
			break;
		}

		return buf;
	}
	break;
	}

	return "";
}

int Exercise::GetSolution()
{
	switch (this->m_hide)
	{
	case EXERCISE_HIDE_NUMBER2:
		return this->m_number2;
		break;

	case EXERCISE_HIDE_NUMBER3:
		return this->m_number3;
		break;
	}

	return 0;
}