#ifndef EXERCISE_H
#define EXERCISE_H

#include "common.h"

enum EXERCISE_SIGN
{
	EXERCISE_SIGN_DEFAULT = 0,
	EXERCISE_SIGN_PLUS,
	EXERCISE_SIGN_MINUS,
	EXERCISE_SIGN_MULTIPLICATION,
	EXERCISE_SIGN_DIVISION
};

enum EXERCISE_HIDE
{
	EXERCISE_HIDE_DEFAULT = 0,
	EXERCISE_HIDE_NUMBER1,
	EXERCISE_HIDE_NUMBER2,
	EXERCISE_HIDE_NUMBER3
};

class Exercise
{
private:
	EXERCISE_SIGN m_sign;
	int m_number1;
	int m_number2;
	int m_number3;
	EXERCISE_HIDE m_hide;

public:
	Exercise();

	void GenerateSimple(int level);
	string GetExercise();
	int GetSolution();
};

#endif