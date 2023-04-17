/*
Exercise:

Implement a template class my_map<T1,T2> storing key-value pairs
where keys are of type T1 and values are of type T2.

The class should implement the following methods:

1) default constructor
2) destructor
3) operator[]: given an object i of type T1 and an object M of
   type my_map<T1,T2>, the call M[i] must return a reference
   to j (of type T2) such that the pair (i,j) is in the map.
   If (i,j) is not in the map, a new pair (i,j) is created
   calling the default constructor of T2 to build j.

use the provided list<T1,T2> as the underlying container for
the (key,value) pairs of my_map<T1,T2>.

*/

#include <iostream>
#include <string>


template<typename T1, typename T2>
struct list{

	list() : next(nullptr), key(), val() {}

	list(T1 k, T2 v, list<T1,T2>* n) : key(k), val(v), next(n) {}

	~list(){
		if(next) delete next;
	}

	list<T1,T2>* prepend(T1 k, T2 v){
		return new list<T1,T2>(k,v,this);
	}

	T1 key;
	T2 val;
	list* next;

};


//insert code of my_map here

template<typename Key, typename Val>
struct my_map {
public:
    my_map();
    ~my_map();

    Val& operator[](Key const& k);
private:
    list<Key,Val>* L;
};

int main(){

	my_map<std::string,double> M {};

	M["pi"] = 3.14159;
	M["e"] = 2.71828;

	std::cout << M["pi"] << std::endl;
	std::cout << M["e"] << std::endl;
	std::cout << M["golden ratio"] << std::endl;

}
