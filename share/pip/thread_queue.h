#ifndef THREAD_QUEUE_H_
#define THREAD_QUEUE_H_

template<typename TYPE>
class thread_queue
{
public:
	int push(TYPE *type);
	TYPE* pop();
private:

};

#endif
