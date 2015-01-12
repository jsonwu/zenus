#ifndef NET_LOGIC_DATA_H_
#define NET_LOGIC_DATA_H_

class bytebuff;
class net_logic_data
{
public:
	int sock_id_;
	int data_type_;
	bytebuff *buff;
};

#endif
