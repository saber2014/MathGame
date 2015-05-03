#ifndef COMPRESSED_VECTOR_H
#define COMPRESSED_VECTOR_H

#include "common.h"

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