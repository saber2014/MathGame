#ifndef EXERCISE_H
#define EXERCISE_H

#include "common.h"
#include "compressed_vector.h"

#define EXERCISE_MIN_VALUE 1
#define EXERCISE_MAX_VALUE 21
#define EXERCISE_INVALID_VALUE -1

enum EXERCISE_TYPE
{
	EXERCISE_TYPE_DEFAULT = 0,
	EXERCISE_TYPE_SIMPLE,
	EXERCISE_TYPE_COMPLEX
};

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
	EXERCISE_HIDE_NUMBER3,
	EXERCISE_HIDE_NUMBER4
};

struct ExerciseTriplet
{
	unsigned __int8 number1;
	unsigned __int8 number2;
	unsigned __int8 number3;
};

class Exercise
{
private:
	EXERCISE_TYPE m_type;
	EXERCISE_SIGN m_sign1;
	EXERCISE_SIGN m_sign2;
	int m_number1;
	int m_number2;
	int m_number3;
	int m_number4;
	EXERCISE_HIDE m_hide1;
	EXERCISE_HIDE m_hide2;

	static CompressedVector m_lookupTable[EXERCISE_SIGN_DIVISION][EXERCISE_SIGN_DIVISION];

public:
	Exercise();

	static void InitLookupTable();
	static int Calculate(int num1, int num2, int num3, EXERCISE_SIGN sign1, EXERCISE_SIGN sign2);
	static int Calculate(int num1, int num2, EXERCISE_SIGN sign);

	void GenerateSimple(int level);
	void GenerateComplex();
	EXERCISE_TYPE GetType();
	char GetSign(int sign);
	int GetNumber(int number);
	int GetSolution(int solution);
	string GetExercise();
	bool IsPossibleSolution(int number);
	bool IsSolved();
};

#endif