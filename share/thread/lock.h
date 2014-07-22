#ifndef LOCK_H_
#define LOCK_H_

class lock
{
public:
	virtual int acquire() = 0;
	virtual int release() = 0;
};

#endif
