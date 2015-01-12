#ifndef BYTEBUFF_H_
#define BYTEBUFF_H_

//jsonwu  2014-12-30  in pwrd

class bytebuff
{
public:
	bytebuff(int size);
	~bytebuff();
	//查看数据 主要为解析协议头看数据是否足够长 不改变read_index
	int look_short(short &num);
	int look_int(int &num);

	int read_short(short &num);
	int read_int(int &num);
	int read_bytebuff(bytebuff *bf, const int size);

	int write_short(short num);
	int write_int(int num);

	int read(char *buff, int size);
	int write(char *buff, int size);

	int write(bytebuff *buff);

	void clear();
	int data_len();
	int size();

	char *readable_buff();
	int read_index(const int num);
private:
	int put(char *buff, int size);
	int space_len();
	int expand_buff(int expand_size);
	int discard_readbyte();

private:
	char *buff_;
	int buff_size_;
	int read_index_;
	int write_index_;
};


#endif
