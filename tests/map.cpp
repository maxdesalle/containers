/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 08:57:16 by mlazzare          #+#    #+#             */
/*   Updated: 2022/03/06 13:32:04 by mlazzare         ###   ########.fr       */
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

// void	std_constructor(void)
// {
// 	std::vector<int> myvector (2,200);        // vector with 2 elements

// 	std::map<int> first;                    // empty map

// 	std::map<int,std::vector<int> > second;  // empty map using vector
// 	std::map<int,std::vector<int> > third (myvector);

// 	std::cout << "sizes: " << first.size() << ", " << second.size() << ", " << third.size();
// }

// void	ft_constructor(void)
// {
// 	ft::vector<int> myvector (2,200);        // vector with 2 elements

// 	ft::map<int> first;                    // empty map

// 	ft::map<int,ft::vector<int> > second;  // empty map using vector
// 	ft::map<int,ft::vector<int> > third (myvector);

// 	std::cout << "sizes: " << first.size() << ", " << second.size() << ", " << third.size();
// }

// void	std_empty(void)
// {
// 	std::map<int> mymap;
// 	int sum (0);

// 	for (int i=1;i<=10;i++) mymap.push(i);

// 	while (!mymap.empty())
// 	{
// 		sum += mymap.top();
// 		mymap.pop();
// 	}

// 	std::cout << "total: " << sum;
// }

// void	ft_empty(void)
// {
// 	ft::map<int> mymap;
// 	int sum (0);

// 	for (int i=1;i<=10;i++) mymap.push(i);

// 	while (!mymap.empty())
// 	{
// 		sum += mymap.top();
// 		mymap.pop();
// 	}

// 	std::cout << "total: " << sum;
// }

// void	std_size(void)
// {
// 	std::map<int> myints;
// 	std::cout << "sizes: " << myints.size();

// 	for (int i=0; i<5; i++) myints.push(i);
// 	std::cout << ", " << myints.size();

// 	myints.pop();
// 	std::cout << ", " << myints.size();
// }

// void	ft_size(void)
// {
// 	ft::map<int> myints;
// 	std::cout << "sizes: " << myints.size();

// 	for (int i=0; i<5; i++) myints.push(i);
// 	std::cout << ", " << myints.size();

// 	myints.pop();
// 	std::cout << ", " << myints.size();
// }

// void	std_top(void)
// {
// 	std::map<int> mymap;

// 	mymap.push(10);
// 	mymap.push(20);

// 	mymap.top() -= 5;

// 	std::cout << "mymap.top() is now " << mymap.top();
// }

// void	ft_top(void)
// {
// 	ft::map<int> mymap;

// 	mymap.push(10);
// 	mymap.push(20);

// 	mymap.top() -= 5;

// 	std::cout << "mymap.top() is now " << mymap.top();
// }

// void	std_push(void)
// {
// 	std::map<int> mymap;

// 	for (int i=0; i<5; ++i) mymap.push(i);

// 	std::cout << "Popping out elements...";
// 	while (!mymap.empty())
// 	{
// 		std::cout << ' ' << mymap.top();
// 		mymap.pop();
// 	}
// }

// void	ft_push(void)
// {
// 	ft::map<int> mymap;

// 	for (int i=0; i<5; ++i) mymap.push(i);

// 	std::cout << "Popping out elements...";
// 	while (!mymap.empty())
// 	{
// 		std::cout << ' ' << mymap.top();
// 		mymap.pop();
// 	}
// }

// void	std_pop(void)
// {
// 	std::map<int> mymap;

// 	for (int i=0; i<5; ++i) mymap.push(i);

// 	std::cout << "Popping out elements...";
// 	while (!mymap.empty())
// 	{
// 		std::cout << ' ' << mymap.top();
// 		mymap.pop();
// 	}
// }

// void	ft_pop(void)
// {
// 	ft::map<int> mymap;

// 	for (int i=0; i<5; ++i) mymap.push(i);

// 	std::cout << "Popping out elements...";
// 	while (!mymap.empty())
// 	{
// 		std::cout << ' ' << mymap.top();
// 		mymap.pop();
// 	}
// }

// void	std_relational_operators(void)
// {
// 	std::map<int> foo,bar;
// 	foo.push (10); foo.push(20); foo.push(30);
// 	bar.push (111); bar.push(222);

// 	if (foo==bar) std::cout << "1";
// 	if (foo!=bar) std::cout << "2";
// 	if (foo< bar) std::cout << "3";
// 	if (foo> bar) std::cout << "4";
// 	if (foo<=bar) std::cout << "5";
// 	if (foo>=bar) std::cout << "6";
// }

// void	ft_relational_operators(void)
// {
// 	ft::map<int> foo,bar;
// 	foo.push (10); foo.push(20); foo.push(30);
// 	bar.push (111); bar.push(222);

// 	if (foo==bar) std::cout << "1";
// 	if (foo!=bar) std::cout << "2";
// 	if (foo< bar) std::cout << "3";
// 	if (foo> bar) std::cout << "4";
// 	if (foo<=bar) std::cout << "5";
// 	if (foo>=bar) std::cout << "6";
// }

// void	std_swaps(void)
// {
// 	std::map<int> foo,bar;
// 	foo.push (10); foo.push(20); foo.push(30);
// 	bar.push (111); bar.push(222);

// 	swap(foo,bar);

// 	std::cout << "size of foo and bar: " << foo.size() << ", " << bar.size();
// }

// void	ft_swaps(void)
// {
// 	ft::map<int> foo,bar;
// 	foo.push (10); foo.push(20); foo.push(30);
// 	bar.push (111); bar.push(222);

// 	swap(foo,bar);

// 	std::cout << "size of foo and bar: " << foo.size() << ", " << bar.size();
}

void	caller(void (*f1)(void), void (*f2)(void), std::string title)
{
	std::cout << std::endl;
	decorator(title);

	std::cout << "\x1B[36mft:\033[0m\t";
	// std::chrono::steady_clock::time_point b1 = std::chrono::high_resolution_clock::now();
	f1();
	// std::chrono::steady_clock::time_point e1 = std::chrono::high_resolution_clock::now();
	std::cout << " (" << std::chrono::duration_cast<std::chrono::microseconds>(e1 - b1).count() << " microseconds)" << std::endl;

	std::cout << "\x1B[33mstd:\033[0m\t";
	// std::chrono::steady_clock::time_point b2 = std::chrono::high_resolution_clock::now();
	f2();
	// std::chrono::steady_clock::time_point e2 = std::chrono::high_resolution_clock::now();
	std::cout << " (" << std::chrono::duration_cast<std::chrono::microseconds>(e2 - b2).count() << " microseconds)" << std::endl;

	std::cout << std::endl;
}

void	test_start(void)
{
	caller(ft_constructor, std_constructor, "constructor");
	caller(ft_empty, std_empty, "empty");
	caller(ft_size, std_size, "size");
	caller(ft_top, std_top, "top");
	caller(ft_push, std_push, "push");
	caller(ft_pop, std_pop, "pop");
	caller(ft_relational_operators, std_relational_operators, "operators");
	caller(ft_swaps, std_swaps, "swap (map)");
}

int	main(void)
{
	std::cout << "##############################" << std::endl;
	decorator("MAP");
	std::cout << "##############################" << std::endl;
	test_start();

	return (0);
}