#ifndef OBJECT_POOL_H_
#define OBJECT_POOL_H_

template<typename Type>
class object_pool
{
public:
	object_pool();
	object_pool();
	Type* alloc()
	{
		if (this->free_list_ != NULL)
		{
			object *p = this->free_list_;
			this->free_list_ = p->next;
			return (Type *)p;
		}
		object *tmp = new object;
		return (Type *)tmp;
	}
	void release(Type *data)
	{
		object *p = (object *)data;
		p->next = this->free_list_;
		this->free_list_ = p;
	}
private:
	object *free_list_;
}

#endif
