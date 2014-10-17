#ifndef WRITER_H_
#define WRITER_H_

#include <string>

using namespace std;

class writer
{
public:
	writer()
	{ }
	virtual ~writer()
	{ }

	virtual int open(const string &name) = 0;
	virtual int write(const string &msg) = 0;
	virtual int write(const char *msg) = 0;
	virtual int flush() = 0;
	virtual int close() = 0;

protected:
	int write_size_;
};
#endif
