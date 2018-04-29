#ifndef ListTemplate
#define ListTemplate

typedef List<class T>* Listptr;
template <class T>
class List
{
public:
	List(size_t size = 0);
	~List();
	void insert(T data, const int &node);
	T destroy(const int &node);
	T getdata(const int &node);
	void print();
	static int getcount();
private:
	bool isEmpty();
	T data;
	Listptr nextptr;
	static int count;
};




#endif