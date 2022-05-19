/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 08:57:16 by mlazzare          #+#    #+#             */
/*   Updated: 2022/05/18 22:25:02 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#include "utils.cpp"

#ifndef STL
# define STL 0
#endif

#if STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "../src/map.hpp"
	#include "../src/stack.hpp"
	#include "../src/vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

void subject_tests( )
{
	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
};

namespace vector
{
	static void	ft_constructor(void)
	{
		ft::vector<int> first;                                // empty vector of ints
		ft::vector<int> second (4,100);                       // four ints with value 100
		ft::vector<int> third (second.begin(),second.end());  // iterating through second
		ft::vector<int> fourth (third);                       // a copy of third

		// the iterator constructor can also be used to construct from arrays:
		int myints[] = {16,2,77,29};
		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

		std::cout << "The contents of fifth are:\n";
		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	void	ft_operator_equal(void)
	{
		ft::vector<int> foo (3,0);
		ft::vector<int> bar (5,0);

		bar = foo;
		foo = ft::vector<int>();

		std::cout << "Size of foo and bar:\n" << int(foo.size()) << " and " << int(bar.size());
		std::cout << std::endl;
	}

	void	ft_begin_end(void)
	{
		ft::vector<int> myvector;
		for (int i=1; i<=5; i++) myvector.push_back(i);

		std::cout << "myvector contains:\n";
		for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	void	ft_rbegin_rend(void)
	{
		ft::vector<int> myvector (5);  // 5 default-constructed ints

		int i=0;

		ft::vector<int>::reverse_iterator rit = myvector.rbegin();
		for (; rit!= myvector.rend(); ++rit)
			*rit = ++i;

		std::cout << "myvector contains:\n";
		for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	static void	ft_size(void)
	{
		ft::vector<int> myints;
		std::cout << "size:\n" << myints.size();

		for (int i=0; i<10; i++) myints.push_back(i);
		std::cout << ", " << myints.size();

		myints.insert (myints.end(),10,100);
		std::cout << ", " << myints.size();

		myints.pop_back();
		std::cout << ", " << myints.size();
		std::cout << std::endl;
	}

	void	ft_max_size(void)
	{
		ft::vector<int> myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);

		std::cout << "size, capacity and max_size:\n" << myvector.size();
		std::cout << ", " << myvector.capacity();
		std::cout << " and " << myvector.max_size();
		std::cout << std::endl;
	}

	void	ft_resize(void)
	{
		ft::vector<int> myvector;

		// set some initial content:
		for (int i=1;i<10;i++) myvector.push_back(i);

		myvector.resize(5);
		myvector.resize(8,100);
		myvector.resize(12);

		std::cout << "myvector contains:\n";
		for (size_t i=0;i<myvector.size();i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}

	void	ft_capacity(void)
	{
		ft::vector<int> myvector;

		// set some content in the vector:
		for (int i=0; i<100; i++) myvector.push_back(i);

		std::cout << "size, capacity and max_size:\n" << myvector.size();
		std::cout << ", " << myvector.capacity();
		std::cout << " and " << myvector.max_size();
		std::cout << std::endl;
	}

	static void	ft_empty(void)
	{
		ft::vector<int> myvector;
		int sum (0);

		for (int i=1;i<=10;i++) myvector.push_back(i);

		while (!myvector.empty())
		{
			sum += myvector.back();
			myvector.pop_back();
		}

		std::cout << "total:\n" << sum;
		std::cout << std::endl;
	}

	void	ft_reserve(void)
	{
		ft::vector<int>::size_type sz;

		ft::vector<int> foo;
		sz = foo.capacity();
		std::cout << "capacity changed:\n";
		for (int i=0; i<100; ++i) {
			foo.push_back(i);
			if (sz!=foo.capacity()) {
				sz = foo.capacity();
				std::cout << sz << ", ";
			}
		}

		ft::vector<int> bar;
		sz = bar.capacity();
		bar.reserve(100);   // this is the only difference with foo above
		for (int i=0; i<100; ++i) {
			bar.push_back(i);
			if (sz!=bar.capacity()) {
				sz = bar.capacity();
				std::cout << sz << ", ";
			}
		}
		std::cout << std::endl;
	}

	void	ft_operator_brackets(void)
	{
		ft::vector<int> myvector (10);   // 10 zero-initialized elements

		ft::vector<int>::size_type sz = myvector.size();

		// assign some values:
		for (unsigned i=0; i<sz; i++) myvector[i]=i;

		// reverse vector using operator[]:
		for (unsigned i=0; i<sz/2; i++)
		{
			int temp;
			temp = myvector[sz-1-i];
			myvector[sz-1-i]=myvector[i];
			myvector[i]=temp;
		}

		std::cout << "myvector contains:\n";
		for (unsigned i=0; i<sz; i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}

	void	ft_at(void)
	{
		ft::vector<int> myvector (10);   // 10 zero-initialized ints

		// assign some values:
		for (unsigned i=0; i<myvector.size(); i++)
			myvector.at(i)=i;

		std::cout << "myvector contains:\n";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector.at(i);
		std::cout << std::endl;
	}

	void	ft_front(void)
	{
		ft::vector<int> myvector;

		myvector.push_back(78);
		myvector.push_back(16);

		// now front equals 78, and back 16

		myvector.front() -= myvector.back();

		std::cout << "myvector.front() is now " << myvector.front();
		std::cout << std::endl;
	}

	void	ft_back(void)
	{
		ft::vector<int> myvector;

		myvector.push_back(10);

		while (myvector.back() != 0)
		{
			myvector.push_back ( myvector.back() -1 );
		}

		std::cout << "myvector contains:\n";
		for (unsigned i=0; i<myvector.size() ; i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}

	void	ft_assign(void)
	{
		ft::vector<int> first;
		ft::vector<int> second;
		ft::vector<int> third;

		first.assign (7,100);             // 7 ints with a value of 100

		ft::vector<int>::iterator it;
		it=first.begin()+1;

		second.assign (it,first.end()-1); // the 5 central values of first

		int myints[] = {1776,7,4};
		third.assign (myints,myints+3);   // assigning from array.

		std::cout << "Size:\n" << int (first.size()) << ", " << int (second.size()) << ", " << int (third.size());
		std::cout << std::endl;
	}

	void	ft_push_back(void)
	{
		ft::vector<int> myvector;

		for (int i = 0; i < 100; i += 1)
			myvector.push_back (i);

		std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";
	}

	void	ft_pop_back(void)
	{
		ft::vector<int> myvector;
		int sum (0);
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		while (!myvector.empty())
		{
			sum+=myvector.back();
			myvector.pop_back();
		}

		std::cout << "The elements of myvector add up to " << sum;
		std::cout << std::endl;
	}

	static void	ft_insert(void)
	{
		ft::vector<int> myvector (3,100);
		ft::vector<int>::iterator it;

		it = myvector.begin();
		it = myvector.insert ( it , 200 );

		myvector.insert (it,2,300);

		// "it" no longer valid, get a new one:
		it = myvector.begin();

		ft::vector<int> anothervector (2,400);
		myvector.insert (it+2,anothervector.begin(),anothervector.end());

		int myarray [] = { 501,502,503 };
		myvector.insert (myvector.begin(), myarray, myarray+3);

		std::cout << "myvector contains:\n";
		for (it=myvector.begin(); it<myvector.end(); it++)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}

	static void	ft_erase(void)
	{
		ft::vector<int> myvector;

		// set some values (from 1 to 10)
		for (int i=1; i<=10; i++) myvector.push_back(i);

		// erase the 6th element
		myvector.erase (myvector.begin()+5);

		// erase the first 3 elements:
		myvector.erase (myvector.begin(),myvector.begin()+3);

		std::cout << "myvector contains:\n";
		for (unsigned i=0; i<myvector.size(); ++i)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}

	static void	ft_swap(void)
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo and bar contain:\n";
		for (unsigned i=0; i<foo.size(); i++)
			std::cout << ' ' << foo[i];

		for (unsigned i=0; i<bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << std::endl;
	}

	static void	ft_clear(void)
	{
		ft::vector<int> myvector;
		myvector.push_back (100);
		myvector.push_back (200);
		myvector.push_back (300);

		std::cout << "myvector contains:\n";
		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];

		myvector.clear();
		myvector.push_back (1101);
		myvector.push_back (2202);

		for (unsigned i=0; i<myvector.size(); i++)
			std::cout << ' ' << myvector[i];
		std::cout << std::endl;
	}

	void	ft_get_allocator(void)
	{
		ft::vector<int> myvector;
		int * p;
		unsigned int i;

		// allocate an array with space for 5 elements using vector's allocator:
		p = myvector.get_allocator().allocate(5);

		// construct values in-place on the array:
		for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

		std::cout << "The allocated array contains:\n";
		for (i=0; i<5; i++) std::cout << ' ' << p[i];

		// destroy and deallocate:
		for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
		myvector.get_allocator().deallocate(p,5);
		std::cout << std::endl;
	}

	void	ft_relational_operators(void)
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (2,200);   // two ints with a value of 200

		if (foo==bar) std::cout << "1";
		if (foo!=bar) std::cout << "2";
		if (foo< bar) std::cout << "3";
		if (foo> bar) std::cout << "4";
		if (foo<=bar) std::cout << "5";
		if (foo>=bar) std::cout << "6";
		std::cout << std::endl;
	}

	void	ft_swapv(void)
	{
		ft::vector<int> foo (3,100);   // three ints with a value of 100
		ft::vector<int> bar (5,200);   // five ints with a value of 200

		foo.swap(bar);

		std::cout << "foo and bar contain:\n";
		for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
			std::cout << ' ' << *it;

		for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
			std::cout << ' ' << *it;
		std::cout << std::endl;
	}
}

namespace map
{
	bool fncomp (char lhs, char rhs) {return lhs<rhs;}

	struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
	};

	static void	ft_constructor(void)
	{
		ft::map< char,int > first;

		first['a']=10;
		first['b']=30;
		first['c']=50;
		first['d']=70;

		ft::map<char,int> second (first.begin(), first.end());
		std::cout << "Size of second: " << second.size() << '\n';

		ft::map<char,int> third (second);

		ft::map<char,int,classcomp> fourth;                 // class as Compare

		bool(*fn_pt)(char,char) = fncomp;
		ft::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

		second=first;                // second now contains 3 ints
		first=ft::map<char,int>();  // and first is now empty

		std::cout << "Size of first: " << first.size() << '\n';
		std::cout << "Size of second: " << second.size() << '\n';
	}

	static void	ft_empty(void)
	{
		ft::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		
		while (!mymap.empty())
		{
			std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
			mymap.erase(mymap.begin());   
		}

		std::cout << "mymap.size() is " << mymap.size() << '\n';
		std::cout << "mymap.max_size() is " << mymap.max_size() << '\n';

	}

	void	ft_iterators(void)
	{
		ft::map<char,int> mymap;

		mymap['b'] = 100;
		mymap['a'] = 200;
		mymap['c'] = 300;

		// show content:
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

		ft::map<char,int> rmap;

		rmap['x'] = 100;
		rmap['y'] = 200;
		rmap['z'] = 300;

		// show content:
		ft::map<char,int>::reverse_iterator rit;
		for (rit=rmap.rbegin(); rit!=rmap.rend(); ++rit)
		std::cout << rit->first << " => " << rit->second << '\n';
	}

	void	ft_insert(void)
	{
		ft::map<char,int> mymap;

		// first insert function version (single parameter):
		mymap.insert ( ft::pair<char,int>('a',100) );
		mymap.insert ( ft::pair<char,int>('z',200) );

		ft::pair<ft::map<char,int>::iterator,bool> ret;
		ret = mymap.insert ( ft::pair<char,int>('z',500) );
		if (ret.second==false) {
			std::cout << "element 'z' already existed";
			std::cout << " with a value of " << ret.first->second << '\n';
		}

		// second insert function version (with hint position):
		ft::map<char,int>::iterator it = mymap.begin();
		mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
		mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

		//third insert function version (range insertion):
		ft::map<char,int> anothermap;
		anothermap.insert(mymap.begin(), mymap.find('c'));

		// showing contents:
		std::cout << "mymap contains:\n";
		for (it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "anothermap contains:\n";
		for (it=anothermap.begin(); it!=anothermap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	void	ft_access(void)
	{
		ft::map<char,std::string> mymap;

		mymap['a']="an element";
		mymap['b']="another element";
		mymap['c']=mymap['b'];

		std::cout << "mymap['a'] is " << mymap['a'] << '\n';
		std::cout << "mymap['b'] is " << mymap['b'] << '\n';
		std::cout << "mymap['c'] is " << mymap['c'] << '\n';
		std::cout << "mymap['d'] is " << mymap['d'] << '\n';

		std::cout << "mymap now contains " << mymap.size() << " elements.\n";
	}

	void	ft_erase(void)
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator it;

		// insert some values:
		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;
		mymap['d']=40;
		mymap['e']=50;
		mymap['f']=60;

		it = mymap.find('b');
		mymap.erase(it);                   // erasing by iterator

		mymap.erase ('c');                  // erasing by key

		it=mymap.find ('e');
		mymap.erase ( it, mymap.end() );    // erasing by range

		// show content:
		for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	}

	void	ft_swap(void)
	{
		ft::map<char,int> foo,bar;

		foo['x']=100;
		foo['y']=200;

		bar['a']=11;
		bar['b']=22;
		bar['c']=33;

		foo.swap(bar);

		std::cout << "foo contains:\n";
		for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		std::cout << "bar contains:\n";
		for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	}

	static void	ft_clear(void)
	{
		ft::map<char,int> mymap;

		mymap['x']=100;
		mymap['y']=200;
		mymap['z']=300;

		std::cout << "mymap contains:\n";
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';

		mymap.clear();
		mymap['a']=1101;
		mymap['b']=2202;

		std::cout << "mymap contains:\n";
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	}

	void	ft_keycomp(void)
	{
		ft::map<char,int> mymap;

		ft::map<char,int>::key_compare mycomp = mymap.key_comp();

		mymap['a']=100;
		mymap['b']=200;
		mymap['c']=300;

		std::cout << "mymap contains:\n";

		char highest = mymap.rbegin()->first;     // key value of last element

		ft::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mycomp((*it++).first, highest) );
	}

	void	ft_valuecomp(void)
	{
		ft::map<char,int> mymap;

		mymap['x']=1001;
		mymap['y']=2002;
		mymap['z']=3003;

		std::cout << "mymap contains:\n";

		ft::pair<char,int> highest = *mymap.rbegin();          // last element

		ft::map<char,int>::iterator it = mymap.begin();
		do {
			std::cout << it->first << " => " << it->second << '\n';
		} while ( mymap.value_comp()(*it++, highest) );
	}

	void	ft_find(void)
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator it;

		mymap['a']=50;
		mymap['b']=100;
		mymap['c']=150;
		mymap['d']=200;

		it = mymap.find('b');
		if (it != mymap.end())
			mymap.erase (it);

		// print content:
		std::cout << "elements in mymap:" << '\n';
		std::cout << "a => " << mymap.find('a')->second << '\n';
		std::cout << "c => " << mymap.find('c')->second << '\n';
		std::cout << "d => " << mymap.find('d')->second << '\n';
	}

	void	ft_count(void)
	{
		ft::map<char,int> mymap;
		char c;

		mymap ['a']=101;
		mymap ['c']=202;
		mymap ['f']=303;

		for (c='a'; c<'h'; c++)
		{
			std::cout << c;
			if (mymap.count(c)>0)
			std::cout << " is an element of mymap.\n";
			else 
			std::cout << " is not an element of mymap.\n";
		}
	}

	void	ft_bounds(void)
	{
		ft::map<char,int> mymap;
		ft::map<char,int>::iterator itlow,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;

		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)

		mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
			std::cout << it->first << " => " << it->second << '\n';
	}

	void	ft_equalrange(void)
	{
		ft::map<char,int> mymap;

		mymap['a']=10;
		mymap['b']=20;
		mymap['c']=30;

		ft::pair<ft::map<char,int>::iterator,ft::map<char,int>::iterator> ret;
		ret = mymap.equal_range('b');

		std::cout << "lower bound points to: ";
		std::cout << ret.first->first << " => " << ret.first->second << '\n';

		std::cout << "upper bound points to: ";
		std::cout << ret.second->first << " => " << ret.second->second << '\n';
	}

	void	ft_allocator(void)
	{
		int psize;
		ft::map<char,int> mymap;
		ft::pair<const char,int>* p;

		// allocate an array of 5 elements using mymap's allocator:
		p=mymap.get_allocator().allocate(5);

		// assign some values to array
		psize = sizeof(ft::map<char,int>::value_type)*5;

		std::cout << "The allocated array has a size of " << psize << " bytes.\n";

		mymap.get_allocator().deallocate(p,5);
	}
}

namespace stack
{
	static void	ft_constructor(void)
	{
		ft::vector<int> myvector (2,200);        // vector with 2 elements

		ft::stack<int> first;                    // empty stack

		ft::stack<int,ft::vector<int> > second;  // empty stack using vector
		ft::stack<int,ft::vector<int> > third (myvector);
		ft::stack<int,std::deque<int> > fourth;

		std::cout << "size of first: " << first.size() << '\n';
		std::cout << "size of second: " << second.size() << '\n';
		std::cout << "size of third: " << third.size() << '\n';
		std::cout << "size of fourth: " << fourth.size() << '\n';
	}

	void	ft_empty(void)
	{
		ft::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);
		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}
		std::cout << "total: " << sum << '\n';
	}

	void	ft_size(void)
	{
		ft::stack<int> myints;
		std::cout << "0. size: " << myints.size() << '\n';

		for (int i=0; i<5; i++) myints.push(i);
		std::cout << "1. size: " << myints.size() << '\n';

		myints.pop();
		std::cout << "2. size: " << myints.size() << '\n';
	}

	void	ft_top(void)
	{
		ft::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;

		std::cout << "mystack.top() is now " << mystack.top() << '\n';
	}

	void	ft_push_pop(void)
	{
		ft::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		std::cout << "Popping out elements...";
		while (!mystack.empty())
		{
			std::cout << ' ' << mystack.top();
			mystack.pop();
		}
		std::cout << std::endl;
	}

	void	ft_relational_operators(void)
	{
		ft::stack<int> foo,bar;
		foo.push (10); foo.push(20); foo.push(30);
		bar.push (111); bar.push(222);

		if (foo==bar) std::cout << "1";
		if (foo!=bar) std::cout << "2";
		if (foo< bar) std::cout << "3";
		if (foo> bar) std::cout << "4";
		if (foo<=bar) std::cout << "5";
		if (foo>=bar) std::cout << "6";
		std::cout << std::endl;
	}

	void	ft_swaps(void)
	{
		ft::stack<int> foo,bar;
		foo.push (10); foo.push(20); foo.push(30);
		bar.push (111); bar.push(222);

		ft::swap(foo,bar);
		std::cout << "size of foo and bar: " << foo.size() << ", " << bar.size();
		std::cout << std::endl;
	}
}


void	vector_tests(void)
{
	header("VECTOR");
	test_it(vector::ft_constructor, "constructor");
	test_it(vector::ft_operator_equal, "operator=");
	test_it(vector::ft_begin_end, "begin_end");
	test_it(vector::ft_rbegin_rend, "rbegin_rend");
	test_it(vector::ft_size, "size");
	test_it(vector::ft_max_size, "max_size");
	test_it(vector::ft_resize, "resize");
	test_it(vector::ft_capacity, "capacity");
	test_it(vector::ft_empty, "empty");
	test_it(vector::ft_reserve, "reserve");
	test_it(vector::ft_operator_brackets, "operator[]");
	test_it(vector::ft_at, "at");
	test_it(vector::ft_front, "front");
	test_it(vector::ft_back, "back");
	test_it(vector::ft_assign, "assign");
	test_it(vector::ft_push_back, "push_back");
	test_it(vector::ft_pop_back, "pop_back");
	test_it(vector::ft_insert, "insert");
	test_it(vector::ft_erase, "erase");
	test_it(vector::ft_swap, "swap");
	test_it(vector::ft_clear, "clear");
	test_it(vector::ft_get_allocator, "get_allocator");
	test_it(vector::ft_relational_operators, "operators");
	test_it(vector::ft_swapv, "swap (vector)");
}

void	map_tests(void)
{
	header("MAP");
	test_it(map::ft_constructor, "constructor");
	test_it(map::ft_iterators, "iterators");
	test_it(map::ft_empty, "empty and size");
	test_it(map::ft_access, "element access");
	test_it(map::ft_insert, "insert"); 
	test_it(map::ft_erase, "erase"); 
	test_it(map::ft_swap, "swap"); 
	test_it(map::ft_clear, "clear"); 
	test_it(map::ft_keycomp, "key_comp"); 
	test_it(map::ft_valuecomp, "value_comp"); 
	test_it(map::ft_find, "find"); 
	test_it(map::ft_count, "count"); 
	test_it(map::ft_bounds, "bounds"); 
	test_it(map::ft_equalrange, "equal_range"); 
	test_it(map::ft_allocator, "allocator");
}

void	stack_tests(void)
{
	header("STACK");
	test_it(stack::ft_constructor, "constructor");
	test_it(stack::ft_empty, "empty");
	test_it(stack::ft_size, "size");
	test_it(stack::ft_top, "top");
	test_it(stack::ft_push_pop, "push and pop");
	test_it(stack::ft_relational_operators, "operators");
	test_it(stack::ft_swaps, "swap (stack)");
}


int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	test_it(subject_tests, "SUBJECT TESTS");
	vector_tests();
	map_tests();
	stack_tests();
	
	return (0);
}