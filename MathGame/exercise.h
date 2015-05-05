/*
 * MathGame - a competitive math game
 * Copyright (C) 2015  saber2014
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef EXERCISE_H
#define EXERCISE_H

#include "common.h"
#include "compressed_vector.h"

#define EXERCISE_MIN_VALUE 1
#define EXERCISE_MAX_VALUE 21
#define EXERCISE_INVALID_VALUE -1

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