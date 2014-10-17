#ifndef PATTERN_LAYOUT_H_
#define PATTERN_LAYOUT_H_

#include "layout.h"
#include "logitem.h"
using namespace std;

class pattern_layout : public layout
{
public:
	pattern_layout(const char *name);
	virtual void render(logitem &item, std::string &out);
private:
	bool pattern_msg(logitem &item, char c, string &out);
private:
	std::string pattern_;
};

#endif
