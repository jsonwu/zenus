#ifndef NOLOCKPIPE_H_
#define NOLOCKPIPE_H_


class nolockpipe
{
public:
	nolockpipe();
	~nolockpipe();

	bool init(const int size);
	bool read(const char *buf, const int size);
	bool write(const char *buf, const int size);
private:
	char *buff_;
	char *head_;
	char *tail_;
	int size_;
};

#endif
