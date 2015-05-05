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

#include "compressed_vector.h"

CompressedVector::CompressedVector()
{
	this->m_pData = NULL;
	this->m_nSize = 0;
	this->m_nLength = 0;

	this->m_currentPosition = 0;
	this->m_currentBit = 0;

	this->Allocate(1);
}

CompressedVector::~CompressedVector()
{
	if (this->m_pData)
		delete[] this->m_pData;
}

unsigned __int8 CompressedVector::GetBits8(unsigned __int8 value, int start, int end)
{
	unsigned __int8 mask = 0;

	for (int i = COMPRESSED_VECTOR_BITS - 1; i >= 0; i--)
		mask = (mask << 1) | ((start <= i && i <= end) ? 1 : 0);

	return (value & mask) >> start;
}

unsigned __int16 CompressedVector::GetBits16(unsigned __int16 value, int start, int end)
{
	unsigned __int16 mask = 0;

	for (int i = 8 * sizeof(unsigned __int16) - 1; i >= 0; i--)
		mask = (mask << 1) | ((start <= i && i <= end) ? 1 : 0);

	return (value & mask) >> start;
}

void CompressedVector::SetBits(unsigned __int16 &dst, unsigned __int8 value, int start, int end)
{
	unsigned __int16 mask = 0;

	for (int i = 8 * sizeof(unsigned __int16) - 1; i >= 0; i--)
		mask = (mask << 1) | ((start > i || i > end) ? 1 : 0);

	dst = (dst & mask) | (value << start);
}

int CompressedVector::GetLength()
{
	return this->m_nLength;
}

void CompressedVector::Allocate(int size)
{
	if (this->m_nSize == 0)
		this->m_pData = (unsigned __int16 *)malloc(sizeof(unsigned __int16) * size);
	else
		this->m_pData = (unsigned __int16 *)realloc(this->m_pData, sizeof(unsigned __int16) * size);

	memset(this->m_pData + this->m_nSize, 0, sizeof(unsigned __int16) * (size - this->m_nSize));

	this->m_nSize = size;
}

unsigned __int8 CompressedVector::Get(int index)
{
	unsigned __int8 res = 0;

	int position = (index * COMPRESSED_VECTOR_BITS) / (8 * sizeof(unsigned __int16));
	int bit = (index * COMPRESSED_VECTOR_BITS) % (8 * sizeof(unsigned __int16));

	int readBits = 0;

	while (readBits != COMPRESSED_VECTOR_BITS)
	{
		if (bit > 8 * sizeof(unsigned __int16) - 1)
		{
			position++;
			bit = 0;
		}

		int bitsToRead = min((int)(COMPRESSED_VECTOR_BITS - readBits), (int)(8 * sizeof(unsigned __int16) - bit));
		res |= (CompressedVector::GetBits16(this->m_pData[position], bit, bit + bitsToRead - 1)) << readBits;

		readBits += bitsToRead;
		bit += bitsToRead;
	}

	return res;
}

void CompressedVector::Set(unsigned __int8 value, int index)
{
	this->Insert(value, index);
}

void CompressedVector::Insert(unsigned __int8 value, int index)
{
	int oldPosition = 0;
	int oldBit = 0;

	if (index != COMPRESSED_VECTOR_INSERT_TO_END)
	{
		oldPosition = this->m_currentPosition;
		oldBit = this->m_currentBit;

		this->m_currentPosition = (index * COMPRESSED_VECTOR_BITS) / (8 * sizeof(unsigned __int16));
		this->m_currentBit = (index * COMPRESSED_VECTOR_BITS) % (8 * sizeof(unsigned __int16));
	}

	int writtenBits = 0;

	while (writtenBits != COMPRESSED_VECTOR_BITS)
	{
		if (this->m_currentBit > 8 * sizeof(unsigned __int16) - 1)
		{
			if (this->m_currentPosition + 1 >= this->m_nSize) this->Allocate(2 * this->m_nSize);

			this->m_currentPosition++;
			this->m_currentBit = 0;
		}

		int bitsToWrite = min((int)(8 * sizeof(unsigned __int16) - this->m_currentBit - 1), (int)(COMPRESSED_VECTOR_BITS - writtenBits - 1));
		CompressedVector::SetBits(this->m_pData[this->m_currentPosition], CompressedVector::GetBits8(value, writtenBits, writtenBits + bitsToWrite), this->m_currentBit, this->m_currentBit + bitsToWrite);

		writtenBits += bitsToWrite + 1;
		this->m_currentBit += bitsToWrite + 1;
	}

	if (index != COMPRESSED_VECTOR_INSERT_TO_END)
	{
		this->m_currentPosition = oldPosition;
		this->m_currentBit = oldBit;
	}
	else
		this->m_nLength++;
}