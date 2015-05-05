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

#ifndef COMPRESSED_VECTOR_H
#define COMPRESSED_VECTOR_H

#include "common.h"

#if !defined(_MSC_VER)
#define __int8 char
#define __int16 short
#endif

#define COMPRESSED_VECTOR_BITS 5
#define COMPRESSED_VECTOR_INSERT_TO_END -1

class CompressedVector
{
private:
	unsigned __int16 *m_pData;
	int m_nSize;
	int m_nLength;

	int m_currentPosition;
	int m_currentBit;

public:
	CompressedVector();
	~CompressedVector();

	static unsigned __int8 GetBits8(unsigned __int8 value, int start, int end);
	static unsigned __int16 GetBits16(unsigned __int16 value, int start, int end);
	static void SetBits(unsigned __int16 &dst, unsigned __int8 value, int start, int end);

	int GetLength();
	void Allocate(int size);
	unsigned __int8 Get(int index);
	void Set(unsigned __int8 value, int index);
	void Insert(unsigned __int8 value, int index = COMPRESSED_VECTOR_INSERT_TO_END);
};

#endif