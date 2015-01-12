#include "digital.h"

int num_2n(const int size)
{
	// 第一个大于size 的2的n次方的数
	
	if (size > 0x80000000 || size < 0)
		return -1;

	int num_1 = 0x40000000;
	for (int i = 0; i < 32; ++i)
	{
		if ((num_1 & size) != 0 )
			break;
		num_1 = num_1 >> 1;
	}
	if (num_1 == size)
		return num_1;
	return num_1 << 1;
}
