#ifndef NOLOCKPIPE_H_
#define NOLOCKPIPE_H_


class nolockpipe
{
public:
	nolockpipe();
	~nolockpipe();
	int init(const int size);
	int read(char *buf, const int size);
	int write(const char *buf, const int size);
private:
	char *buff_;
	char *head_;
	char *tail_;
	int size_;
};

#endif
