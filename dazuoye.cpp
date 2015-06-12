#include<iostream>
using namespace std;

class index_out_of_range{}; 
class illegal_index{};
class list_empty{};

template<class T> class MyList;
template<class T>
ostream & operator << (ostream &os, const MyList<T> &obj);

template<class T>
class MyList{
private:
	T *a;
	int size;
	int top_p;
	void double_space();//when space is not enough, use this function to double it
public:
	MyList(){
		size = 100;
		top_p = 0;
		a = new T [size];
	}
	MyList(int num, const T &item);//push item into mylist for t times
	MyList(const MyList &l);//copy another mylist
    MyList(T* arr, int len);//construct mylist, using the first len numbers of array arr

	void push(const T &item);//add item to the last if the list 
	T pop() throw(list_empty);//erase the last element of mylist and return it 
	void insert(int index, const T &item) ;//insert item to place
	void clean();//clean the list 
	int get_size() const;//return the number of the elements of mylist
	void erase(int start, int end); //delete the elements in mylist with an index from start to end, both bounderies are included
	T get_item(int index) const throw(index_out_of_range);//return the element with that index
	MyList get_item(int start, int end) const;//return part of mylist as a new list, nagative numbers are acceptable,just like python
	int count(const T &item) const;//return the number of item in the list
	void remove(const T &item);//delete the first element equal to item in mylist


	friend MyList<T> operator + (const MyList<T> &l1, const MyList<T> &l2) //combine two MyLists together and return the result
    {
		int *a;
		int len =  l1.top_p+l2.top_p;
		a = new int [len];
		for (int i = 0; i < l1.top_p; i++) a[i] = l1.a[i];
		for (int i = 0; i < l2.top_p; i++) a[i+l1.top_p] = l2.a[i];
		MyList<T> list(a,len);
		delete [] a;
		return list;	
	}
	
	friend MyList<T> operator + (const MyList<T> &l1, const T &item) //same as push item except the original mylist is unchanged and a new mylist is returned
	{
		MyList<T> l2(l1);
		l2.push(item);
		return l2;
	}
	
	MyList &operator = (const MyList &l);//assign the value
	MyList &operator += (const T &item);//the same as push(T item)
	MyList &operator += (const MyList &l);//add another mylist after this mylist
	T &operator [](int index) const throw(index_out_of_range);//return the element with that index
	friend ostream & operator <<<T> (ostream &os, const MyList<T> &obj) ;//If T can be output directly (like integer),output it, using the same pattern in python
    // for example [1, 2, 5, 4, 1]


	void sort(bool less=true);//sort the list with quick sort method
    // If less=true，from the least to the biggest,otherwise the opposite  
	void reverse();//reverse the elements in mylist

	~MyList(){delete [] a;}
};






template <class T> 
void quickSort(T *s, int l, int r)  
{  
    if (l< r)  
    {        
        int i = l, j = r, x = s[l];  
        while (i < j)  
        {  
            while(i < j && s[j]>= x) 
                j--;   
            if(i < j)  
                s[i++] = s[j];  
            while(i < j && s[i]< x)   
                i++;   
            if(i < j)  
                s[j--] = s[i];  
        }  
        s[i] = x;  
        quickSort(s, l, i - 1); 
        quickSort(s, i + 1, r);  
    }  
}  

template <class T>
void quickSort2(T *s, int l, int r)  
{  
    if (l< r)  
    {        
        int i = l, j = r, x = s[l];  
        while (i < j)  
        {  
            while(i < j && s[j]<= x) 
                j--;   
            if(i < j)  
                s[i++] = s[j];  
            while(i < j && s[i]> x)   
                i++;   
            if(i < j)  
                s[j--] = s[i];  
        }  
        s[i] = x;  
        quickSort2(s, l, i - 1); 
        quickSort2(s, i + 1, r);  
    }  
}  

template <class T> 
void MyList<T>::clean()
{
	top_p = 0;
}

template <class T> 
int MyList<T>::count(const T &item) const
{
	int cou = 0;
	for(int i = 0; i < top_p; ++i)
	{
		if (a[i] == item) cou++;
	}
	return cou;
} 

template <class T>  
void MyList<T>::double_space()
{
	T *b = a;
	size *= 2; 
	a = new T [size];
	for (int i = 0; i < top_p; ++i)
	{
		a[i] = b[i];
	}
	delete [] b;
} 

template <class T> 
void MyList<T>::erase(int start,int end)
{
	if (start < 0) start = top_p + start;
	if (end < 0) end = top_p + end;
	try
	{
		if (start > end ) throw illegal_index();
		if (end > top_p-1 || start < 0) throw index_out_of_range();
		int len = top_p-end-1;
	
		for (int i = 0; i < len; ++i)
		{
			a[start+i] = a[end+i+1];
		
		}
		top_p = top_p-(end-start+1);
	}
	catch (illegal_index) 
	{
		cerr << "Error! Start should be less than end."<<endl;
	}
	catch (index_out_of_range) 
	{
		cerr << "Error! index out of range"<<endl;
	}
}

template <class T> 
T MyList<T>::get_item(int index) const throw(index_out_of_range)
{
	if (index < 0) index = top_p+index;
	if (index > top_p-1 || index < 0) throw index_out_of_range();
	return a[index];
	
}

template <class T> 
MyList<T>::MyList(int num, const T &item)
{
	a = new T [num+10];
	top_p = num;
	for (int i = 0; i < num; i++) a[i] = item;
	size = num+10;

}
	
template <class T> 	
MyList<T>::MyList(const MyList &l)
{
	size = l.size;
	a = new T [size];
	top_p = l.top_p;
	for (int i = 0; i < top_p; i++) a[i] = l.a[i];
}

template <class T> 
MyList<T>::MyList(T* arr, int len)
{
	size = len;
	a = new T [size];
	for (int i = 0; i < size; ++i) a[i]=arr[i];
	top_p = size;
}

template <class T> 
void MyList<T>::push(const T &item)
{
	if (top_p == size) this->double_space();
	a[top_p++] = item;
	 
}

template <class T> 
T MyList<T>::pop() throw(list_empty)
{	
	if (top_p == 0) throw list_empty();
	return a[--top_p];
}

template <class T> 
void MyList<T>::insert(int index, const T &item)
{
	if (index < 0) index = index + top_p;
	try
	{
		if (index > top_p || index < 0) throw index_out_of_range();
		if (top_p == size) this->double_space();
		top_p++;
		for (int i = top_p-1; i > index; i--) a[i] = a[i-1];
		a[index] = item;
	}
	catch (index_out_of_range) 
	{
		cerr << "Error! index out of range"<<endl;
	}	
	
}
	
	
template <class T> 
int MyList<T>::get_size() const
{
	return top_p;
}

template <class T> 	
MyList<T> MyList<T>:: get_item(int start, int end) const
{
	if (start < 0) start = top_p + start;
	if (end < 0) end = top_p + end;
	try
	{
		if (start > end) throw illegal_index();
		if (start < 0 || end > top_p-1) throw index_out_of_range();
		MyList<T> l2(a+start,end-start+1);
		return l2;
	}
	catch (illegal_index) 
	{
		cerr << "Error! Start should be less than end."<<endl;
		MyList<T> l;
		return l;
	}
	catch (index_out_of_range) 
	{
		cerr << "Error! index out of range"<<endl;
		MyList<T> l;
		return l;
	}
		
}

template <class T> 
void MyList<T>::remove(const T &item)
{
	for(int i = 0; i < top_p; i++) 
	{
		if(a[i] == item) 
		{
		    erase(i,i);
		    break;
		}
	}
}





template <class T> 
MyList<T> & MyList<T>::operator = (const MyList &l)
{
	if (this == &l) return *this;
	size = l.size;
	a =  new int [size];
	top_p = l.top_p;
	for (int i = 0; i<top_p; ++i) a[i] = l.a[i];
	return *this;
}

template <class T> 	
MyList<T> & MyList<T>::operator += (const T &item)
{
	this->push(item);
	return *this;
}


template <class T>
MyList<T> & MyList<T>::operator += (const MyList &l)
{
	int len = top_p+l.top_p;
	while(size<top_p+l.top_p) this->double_space();
	for (int i = 0; i < l.top_p; ++i) a[top_p+i]=l.a[i];
	top_p=len;
	return *this;
} 
	
template <class T>
T & MyList<T>::operator [](int index) const throw(index_out_of_range)
{
	if (index < 0) index = top_p+index;
	if (index > top_p-1 || index < 0) throw index_out_of_range();
	return a[index];
} 

template <class T>
ostream & operator<<(ostream &os, const MyList<T> &obj)
{
	os << "[" ;
	if (obj.top_p != 0)
	{
		for (int i = 0;i < obj.top_p-1; ++i ) os << obj.a[i] << ",";
		os << obj.a[obj.top_p-1];
	}
	os << "]";
	return os; 
}

template <class T>
void MyList<T>::sort(bool less )
{
	if (top_p == 0) return;
	if(less)quickSort(a,0,top_p-1);
	else quickSort2(a,0,top_p-1);
}

template <class T> 
void MyList<T>:: reverse()
{
	if (top_p == 0 || top_p == 1) return;
	int *b;
	b = new int [size];
	for(int i = 0; i<top_p; ++i) b[i] = a[top_p-i-1];
	delete [] a;
	a = b;
}

int main(){
	MyList<int> a, b;
	int i;
	for (i=0; i<5; ++i)
		a.push(i);
    // a = [0, 1, 2, 3, 4]
	a[3] = 15; // a = [0, 1, 2, 15, 4]
	a.sort(); // a = [0, 1, 2, 4, 15]
	a.reverse(); // a = [15, 4, 2, 1, 0]
	a += 12; // a = [15, 4, 2, 1, 0, 12]
	try{cout<<a[90];}
	catch (index_out_of_range) 
	{
		cerr << "Error! index out of range"<<endl;
	};
	for (i=0; i<a.get_size(); ++i)
		cout<<a[i]<<endl;
    b = a.get_item(4, -3); // b = [] 
	b = a.get_item(3, -1); // b = [1, 0, 12] 
	a += b; // a = [15, 4, 2, 1, 0, 12, 1, 0, 12]
	for (i=0; i<a.get_size(); ++i)
		try{cout<<a.get_item(i)<<endl;}
	catch (index_out_of_range) 
	{
		cerr << "Error! index out of range"<<endl;
	};
	cout<<a.count(5)<<endl;
	b.clean(); // b = []
	cout<<b.get_size()<<endl;
	a.erase(2, 5); // a = [15, 4, 0, 12]
	b = a + a; // b = [15, 4, 0, 12, 15, 4, 0, 12]
	b.insert(3, 116); // b = [15, 4, 0, 116, 12, 15, 4, 0, 12]
	b.remove(4); // b = [15, 0, 116, ...]
	cout<<b<<endl;
	MyList<double> c(10, 3.14);
	cout<<c<<endl;
	for (i=0; i<100; ++i)
		c.push(1.1*i);
	cout<<c.get_item(100, 105)<<endl;
	MyList<float> d(10,0.5);
	cout<<d.count(0.5)<<endl;
	for (i=0;i<4;i++) try{d.pop();}
	catch (list_empty) 
	{
		cerr << "Error! The list is empty" << endl;
	
	};
	cout<<d<<endl;
	cout<<d[0]<<endl;
	return 0;
}
