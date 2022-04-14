/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 08:57:16 by mlazzare          #+#    #+#             */
/*   Updated: 2022/04/14 08:06:41 by mlazzare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <map>
# include <iostream>

# include "../src/containers/map.hpp"

void	decorator(std::string title)
{
	int space = (20 - title.length()) / 2;
	std::cout << "#####";
	for (int i = 0; i < space; i += 1)
		std::cout << " ";
	std::cout << "\x1B[31m" << title << "\033[0m";
	for (int i = 0; i < space; i += 1)
		std::cout << " ";
	std::cout << "#####";
	std::cout << std::endl;
}

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

void	std_constructor(void)
{
	std::map<char,int> first;

  	first['a']=10;
  	first['b']=30;
  	first['c']=50;
  	first['d']=70;

 	std::map<char,int> second (first.begin(),first.end());
	 std::cout << "first: " << first.begin()->second << '\n';
	 std::cout << "end: " << first.end()->second << '\n';
	std::cout << "Size of second: " << second.size() << '\n';

  	std::map<char,int> third (second);

  	std::map<char,int,classcomp> fourth;                 // class as Compare

  	bool(*fn_pt)(char,char) = fncomp;
  	std::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	second=first;                // second now contains 3 ints
  	first=std::map<char,int>();  // and first is now empty

  	std::cout << "Size of first: " << first.size() << '\n';
  	std::cout << "Size of second: " << second.size() << '\n';
}

void	ft_constructor(void)
{
	ft::map< char,int > first;

  	first['a']=10;
  	first['b']=30;
  	first['c']=50;
  	first['d']=70;

 	ft::map<char,int> second (first.begin(), first.end());
	 std::cout << "first: " << first.begin()->second << '\n';
	 std::cout << "end: " << first.end()->second << '\n';
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

void	std_empty(void)
{
	std::map<char,int> mymap;

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

void	ft_empty(void)
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

void	std_iterators(void)
{
	std::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
	std::cout << it->first << " => " << it->second << '\n';

	std::map<char,int> rmap;

	rmap['x'] = 100;
	rmap['y'] = 200;
	rmap['z'] = 300;

	// show content:
	std::map<char,int>::reverse_iterator rit;
	for (rit=rmap.rbegin(); rit!=rmap.rend(); ++rit)
	std::cout << rit->first << " => " << rit->second << '\n';
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
	// ft::map<char,int>::reverse_iterator rit;
	// for (rit=rmap.rbegin(); rit!=rmap.rend(); ++rit)
	// std::cout << rit->first << " => " << rit->second << '\n';
}

void	std_insert(void)
{
	std::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( std::pair<char,int>('a',100) );
	mymap.insert ( std::pair<char,int>('z',200) );

	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( std::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	std::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, std::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, std::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	std::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
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

	// third insert function version (range insertion):
	ft::map<char,int> anothermap;
	anothermap.insert(mymap.begin(), mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	// std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
}


// void	std_access(void)
// {
// 	std::map<char,std::string> mymap;

// 	mymap['a']="an element";
// 	mymap['b']="another element";
// 	mymap['c']=mymap['b'];

// 	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
// 	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
// 	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
// 	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

// 	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
// }

// void	ft_access(void)
// {
// 	ft::map<char,std::string> mymap;

// 	mymap['a']="an element";
// 	mymap['b']="another element";
// 	mymap['c']=mymap['b'];

// 	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
// 	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
// 	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
// 	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

// 	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
// }

// void	std_erase(void)
// {
// 	std::map<char,int> mymap;
// 	std::map<char,int>::iterator it;

// 	// insert some values:
// 	mymap['a']=10;
// 	mymap['b']=20;
// 	mymap['c']=30;
// 	mymap['d']=40;
// 	mymap['e']=50;
// 	mymap['f']=60;

// 	it=mymap.find('b');
// 	mymap.erase (it);                   // erasing by iterator

// 	mymap.erase ('c');                  // erasing by key

// 	it=mymap.find ('e');
// 	mymap.erase ( it, mymap.end() );    // erasing by range

// 	// show content:
// 	for (it=mymap.begin(); it!=mymap.end(); ++it)
// 	std::cout << it->first << " => " << it->second << '\n';
// }

// void	ft_erase(void)
// {
// 	ft::map<char,int> mymap;
// 	ft::map<char,int>::iterator it;

// 	// insert some values:
// 	mymap['a']=10;
// 	mymap['b']=20;
// 	mymap['c']=30;
// 	mymap['d']=40;
// 	mymap['e']=50;
// 	mymap['f']=60;

// 	it=mymap.find('b');
// 	mymap.erase (it);                   // erasing by iterator

// 	mymap.erase ('c');                  // erasing by key

// 	it=mymap.find ('e');
// 	mymap.erase ( it, mymap.end() );    // erasing by range

// 	// show content:
// 	for (it=mymap.begin(); it!=mymap.end(); ++it)
// 	std::cout << it->first << " => " << it->second << '\n';
// }

// void	std_swap(void)
// {
// 	std::map<char,int> foo,bar;

// 	foo['x']=100;
// 	foo['y']=200;

// 	bar['a']=11;
// 	bar['b']=22;
// 	bar['c']=33;

// 	foo.swap(bar);

// 	std::cout << "foo contains:\n";
// 	for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
// 		std::cout << it->first << " => " << it->second << '\n';

// 	std::cout << "bar contains:\n";
// 	for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
// 	std::cout << it->first << " => " << it->second << '\n';
// }

// void	ft_swap(void)
// {
// 	ft::map<char,int> foo,bar;

// 	foo['x']=100;
// 	foo['y']=200;

// 	bar['a']=11;
// 	bar['b']=22;
// 	bar['c']=33;

// 	foo.swap(bar);

// 	std::cout << "foo contains:\n";
// 	for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
// 		std::cout << it->first << " => " << it->second << '\n';

// 	std::cout << "bar contains:\n";
// 	for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
// 	std::cout << it->first << " => " << it->second << '\n';
// }

// void	std_clear(void)
// {
// 	std::map<char,int> mymap;

// 	mymap['x']=100;
// 	mymap['y']=200;
// 	mymap['z']=300;

// 	std::cout << "mymap contains:\n";
// 	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 		std::cout << it->first << " => " << it->second << '\n';

// 	mymap.clear();
// 	mymap['a']=1101;
// 	mymap['b']=2202;

// 	std::cout << "mymap contains:\n";
// 	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 	std::cout << it->first << " => " << it->second << '\n';
// }

// void	ft_clear(void)
// {
// 	ft::map<char,int> mymap;

// 	mymap['x']=100;
// 	mymap['y']=200;
// 	mymap['z']=300;

// 	std::cout << "mymap contains:\n";
// 	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 		std::cout << it->first << " => " << it->second << '\n';

// 	mymap.clear();
// 	mymap['a']=1101;
// 	mymap['b']=2202;

// 	std::cout << "mymap contains:\n";
// 	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 	std::cout << it->first << " => " << it->second << '\n';
// }

// void	std_keycomp(void)
// {
// 	std::map<char,int> mymap;

// 	std::map<char,int>::key_compare mycomp = mymap.key_comp();

// 	mymap['a']=100;
// 	mymap['b']=200;
// 	mymap['c']=300;

// 	std::cout << "mymap contains:\n";

// 	char highest = mymap.rbegin()->first;     // key value of last element

// 	std::map<char,int>::iterator it = mymap.begin();
// 	do {
// 		std::cout << it->first << " => " << it->second << '\n';
// 	} while ( mycomp((*it++).first, highest) );
// }

// void	ft_keycomp(void)
// {
// 	ft::map<char,int> mymap;

// 	ft::map<char,int>::key_compare mycomp = mymap.key_comp();

// 	mymap['a']=100;
// 	mymap['b']=200;
// 	mymap['c']=300;

// 	std::cout << "mymap contains:\n";

// 	char highest = mymap.rbegin()->first;     // key value of last element

// 	ft::map<char,int>::iterator it = mymap.begin();
// 	do {
// 		std::cout << it->first << " => " << it->second << '\n';
// 	} while ( mycomp((*it++).first, highest) );
// }

// void	std_valuecomp(void)
// {
// 	std::map<char,int> mymap;

// 	mymap['x']=1001;
// 	mymap['y']=2002;
// 	mymap['z']=3003;

// 	std::cout << "mymap contains:\n";

// 	std::pair<char,int> highest = *mymap.rbegin();          // last element

// 	std::map<char,int>::iterator it = mymap.begin();
// 	do {
// 		std::cout << it->first << " => " << it->second << '\n';
// 	} while ( mymap.value_comp()(*it++, highest) );
// }

// void	ft_valuecomp(void)
// {
// 	ft::map<char,int> mymap;

// 	mymap['x']=1001;
// 	mymap['y']=2002;
// 	mymap['z']=3003;

// 	std::cout << "mymap contains:\n";

// 	ft::pair<char,int> highest = *mymap.rbegin();          // last element

// 	ft::map<char,int>::iterator it = mymap.begin();
// 	do {
// 		std::cout << it->first << " => " << it->second << '\n';
// 	} while ( mymap.value_comp()(*it++, highest) );
// }

// void	std_find(void)
// {
// 	std::map<char,int> mymap;
// 	std::map<char,int>::iterator it;

// 	mymap['a']=50;
// 	mymap['b']=100;
// 	mymap['c']=150;
// 	mymap['d']=200;

// 	it = mymap.find('b');
// 	if (it != mymap.end())
// 		mymap.erase (it);

// 	// print content:
// 	std::cout << "elements in mymap:" << '\n';
// 	std::cout << "a => " << mymap.find('a')->second << '\n';
// 	std::cout << "c => " << mymap.find('c')->second << '\n';
// 	std::cout << "d => " << mymap.find('d')->second << '\n';
// }

// void	ft_find(void)
// {
// 	ft::map<char,int> mymap;
// 	ft::map<char,int>::iterator it;

// 	mymap['a']=50;
// 	mymap['b']=100;
// 	mymap['c']=150;
// 	mymap['d']=200;

// 	it = mymap.find('b');
// 	if (it != mymap.end())
// 		mymap.erase (it);

// 	// print content:
// 	std::cout << "elements in mymap:" << '\n';
// 	std::cout << "a => " << mymap.find('a')->second << '\n';
// 	std::cout << "c => " << mymap.find('c')->second << '\n';
// 	std::cout << "d => " << mymap.find('d')->second << '\n';
// }

// void	std_count(void)
// {
// 	std::map<char,int> mymap;
// 	char c;

// 	mymap ['a']=101;
// 	mymap ['c']=202;
// 	mymap ['f']=303;

// 	for (c='a'; c<'h'; c++)
// 	{
// 		std::cout << c;
// 		if (mymap.count(c)>0)
// 		std::cout << " is an element of mymap.\n";
// 		else 
// 		std::cout << " is not an element of mymap.\n";
// 	}
// }

// void	ft_count(void)
// {
// 	ft::map<char,int> mymap;
// 	char c;

// 	mymap ['a']=101;
// 	mymap ['c']=202;
// 	mymap ['f']=303;

// 	for (c='a'; c<'h'; c++)
// 	{
// 		std::cout << c;
// 		if (mymap.count(c)>0)
// 		std::cout << " is an element of mymap.\n";
// 		else 
// 		std::cout << " is not an element of mymap.\n";
// 	}
// }

// void	std_bounds(void)
// {
// 	std::map<char,int> mymap;
// 	std::map<char,int>::iterator itlow,itup;

// 	mymap['a']=20;
// 	mymap['b']=40;
// 	mymap['c']=60;
// 	mymap['d']=80;
// 	mymap['e']=100;

// 	itlow=mymap.lower_bound ('b');  // itlow points to b
// 	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

// 	mymap.erase(itlow,itup);        // erases [itlow,itup)

// 	// print content:
// 	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 		std::cout << it->first << " => " << it->second << '\n';
// }

// void	ft_bounds(void)
// {
// 	ft::map<char,int> mymap;
// 	ft::map<char,int>::iterator itlow,itup;

// 	mymap['a']=20;
// 	mymap['b']=40;
// 	mymap['c']=60;
// 	mymap['d']=80;
// 	mymap['e']=100;

// 	itlow=mymap.lower_bound ('b');  // itlow points to b
// 	itup=mymap.upper_bound ('d');   // itup points to e (not d!)

// 	mymap.erase(itlow,itup);        // erases [itlow,itup)

// 	// print content:
// 	for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
// 		std::cout << it->first << " => " << it->second << '\n';
// }

// void	std_equalrange(void)
// {
// 	std::map<char,int> mymap;

// 	mymap['a']=10;
// 	mymap['b']=20;
// 	mymap['c']=30;

// 	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
// 	ret = mymap.equal_range('b');

// 	std::cout << "lower bound points to: ";
// 	std::cout << ret.first->first << " => " << ret.first->second << '\n';

// 	std::cout << "upper bound points to: ";
// 	std::cout << ret.second->first << " => " << ret.second->second << '\n';
// }

// void	ft_equalrange(void)
// {
// 	ft::map<char,int> mymap;

// 	mymap['a']=10;
// 	mymap['b']=20;
// 	mymap['c']=30;

// 	ft::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
// 	ret = mymap.equal_range('b');

// 	std::cout << "lower bound points to: ";
// 	std::cout << ret.first->first << " => " << ret.first->second << '\n';

// 	std::cout << "upper bound points to: ";
// 	std::cout << ret.second->first << " => " << ret.second->second << '\n';
// }

// void	std_allocator(void)
// {
// 	int psize;
// 	std::map<char,int> mymap;
// 	std::pair<const char,int>* p;

// 	// allocate an array of 5 elements using mymap's allocator:
// 	p=mymap.get_allocator().allocate(5);

// 	// assign some values to array
// 	psize = sizeof(std::map<char,int>::value_type)*5;

// 	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

// 	mymap.get_allocator().deallocate(p,5);
// }

// void	ft_allocator(void)
// {
// 	int psize;
// 	ft::map<char,int> mymap;
// 	ft::pair<const char,int>* p;

// 	// allocate an array of 5 elements using mymap's allocator:
// 	p=mymap.get_allocator().allocate(5);

// 	// assign some values to array
// 	psize = sizeof(std::map<char,int>::value_type)*5;

// 	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

// 	mymap.get_allocator().deallocate(p,5);
// }

void	caller(void (*f1)(void), void (*f2)(void), std::string title)
{
	std::cout << std::endl;
	decorator(title);

	std::cout << "\x1B[36mft:\033[0m\t\n";
	// std::chrono::steady_clock::time_point b1 = std::chrono::high_resolution_clock::now();
	f1();
	// std::chrono::steady_clock::time_point e1 = std::chrono::high_resolution_clock::now();
	// std::cout << " (" << std::chrono::duration_cast<std::chrono::microseconds>(e1 - b1).count() << " microseconds)" << std::endl;

	std::cout << "\x1B[33mstd:\033[0m\t\n";
	// std::chrono::steady_clock::time_point b2 = std::chrono::high_resolution_clock::now();
	f2();
	// std::chrono::steady_clock::time_point e2 = std::chrono::high_resolution_clock::now();
	// std::cout << " (" << std::chrono::duration_cast<std::chrono::microseconds>(e2 - b2).count() << " microseconds)" << std::endl;

	std::cout << std::endl;
}

void	test_start(void)
{
	caller(ft_constructor, std_constructor, "constructor");
	caller(ft_iterators, std_iterators, "iterators");
	caller(ft_empty, std_empty, "empty and size"); // capacity
	// caller(ft_access, std_access, "element access");
	caller(ft_insert, std_insert, "insert"); // modifiers
	// caller(ft_erase, std_erase, "erase"); // modifiers
	// caller(ft_swap, std_swap, "swap"); // modifiers
	// caller(ft_clear, std_clear, "clear"); // modifiers
	// caller(ft_keycomp, std_keycomp, "key_comp"); // observers
	// caller(ft_valuecomp, std_valuecomp, "value_comp"); // observers
	// caller(ft_find, std_find, "find"); // operations
	// caller(ft_count, std_count, "count"); // operations
	// caller(ft_bounds, std_bounds, "lower and upper bound"); // operations
	// caller(ft_equalrange, std_equalrange, "equal_range"); // operations
	// caller(ft_allocator, std_allocator, "allocator"); // allocator
}

int	main(void)
{
	std::cout << "##############################" << std::endl;
	decorator("MAP");
	std::cout << "##############################" << std::endl;
	test_start();

	return (0);
}