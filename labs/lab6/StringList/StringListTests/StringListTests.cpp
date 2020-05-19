#define CATCH_CONFIG_MAIN
#include "../StringList/StringList.h"
#include "catch2/catch.hpp"

TEST_CASE("Default constructor must create an empty list")
{
	CStringList list;
	CHECK(list.GetSize() == 0);
	CHECK(list.IsEmpty());
}

TEST_CASE("PushBack() must add string to the end of list")
{
	CStringList list;

	list.PushBack("123");
	CHECK(list.GetSize() == 1);
	CHECK(list.GetBackElement() == "123");

	list.PushBack("345");
	CHECK(list.GetSize() == 2);
	CHECK(list.GetBackElement() == "345");
}

TEST_CASE("PushFront() must add string to the begin of list")
{
	CStringList list;

	list.PushFront("123");
	CHECK(list.GetSize() == 1);
	CHECK(list.GetFrontElement() == "123");

	list.PushFront("345");
	CHECK(list.GetSize() == 2);
	CHECK(list.GetFrontElement() == "345");
	CHECK(list.GetBackElement() == "123");
}

TEST_CASE("Clear() must clear list (list will become empty)")
{
	CStringList list;
	list.PushBack("123");
	list.PushBack("345");
	CHECK(list.GetSize() == 2);

	list.Clear();
	CHECK(list.IsEmpty());
}

TEST_CASE("Insert() must insert element at the position specified by iterator")
{
	CStringList list;
	list.Insert(list.begin(), "56");
	list.Insert(list.begin(), "12");
	list.Insert(--list.end(), "34");

	CHECK(list.GetSize() == 3);
	CHECK(list.GetFrontElement() == "12");
	CHECK(list.GetBackElement() == "56");
}

TEST_CASE("Erase() must delete element at the position specified by iterator")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	CHECK(list.GetSize() == 3);
	CHECK(list.GetBackElement() == "56");

	list.Erase(--list.end());
	CHECK(list.GetSize() == 2);
	CHECK(list.GetBackElement() == "34");
}

TEST_CASE("Copy constructor must create a copy of the passed object")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CStringList copyList(list);
	CHECK(copyList.GetSize() == 2);
	CHECK(copyList == list);
}

TEST_CASE("Move constructor must move the object")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CStringList copyList(list);

	CStringList moveList(std::move(list));
	CHECK(moveList.GetSize() == 2);
	CHECK(moveList == copyList);
	CHECK(list.GetSize() == 0);
	CHECK(list == CStringList());
}

TEST_CASE("Copy assignment operator must assign copy of one list to another")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CStringList copyList = list;
	CHECK(copyList.GetSize() == 2);
	CHECK(copyList == list);
}

TEST_CASE("Move assignment operator must assign list of another list that will be cleared")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CStringList copyList(list);

	CStringList moveList = std::move(list);
	CHECK(moveList.GetSize() == 2);
	CHECK(moveList == copyList);
	CHECK(list.GetSize() == 0);
	CHECK(list == CStringList());
}

TEST_CASE("The * operator must return an object reference")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CHECK(*(list.begin()) == "12");
}

TEST_CASE("Postfix operator ++ must return the current iterator and then change it")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	auto it = list.begin();
	CHECK(*(it++) == "12");

	auto rit = list.rbegin();
	CHECK(*(rit++) == "56");
}

TEST_CASE("Prefix operator ++ must change the iterator and return it")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	auto it = list.begin();
	CHECK(*(++it) == "34");

	auto rit = list.rbegin();
	CHECK(*(++rit) == "34");
}

TEST_CASE("Postfix operator -- must return the current iterator and then change it")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	auto it = --list.end();
	CHECK(*(it--) == "56");

	auto rit = --list.rend();
	CHECK(*(rit--) == "12");
}

TEST_CASE("Prefix operator -- must change the iterator and return it")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	auto it = list.end();
	CHECK(*(--it) == "56");

	auto rit = list.rend();
	CHECK(*(--rit) == "12");
}

TEST_CASE("Operators == and != must check for equality of two iterators")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it1 = list.begin();
	auto it2 = list.rend();
	CHECK(it1 != it2);
	CHECK(it1 == --it2);
}

TEST_CASE("begin() must return an iterator pointing to begin of the list")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.begin();
	CHECK(*it == "12");
}

TEST_CASE("begin() and cbegin() must return a constant iterator pointing to begin of the list")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	const CStringList clist = list;

	auto cit = clist.cbegin();
	CHECK(*cit == "12");
	auto it = clist.begin();
	CHECK(*it == "12");
}

TEST_CASE("end() must return an iterator pointing to the element following the last")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.end();
	CHECK(*(--it) == "34");
}

TEST_CASE("end() and cend() must return a constant iterator pointing to the element following the last")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	const CStringList clist = list;

	auto cit = clist.cend();
	CHECK(*(--cit) == "34");
	auto it = clist.end();
	CHECK(*(--it) == "34");
}

TEST_CASE("rbegin() must return reverse iterator pointing to the last element of the list")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.rbegin();
	CHECK(*(it) == "34");
}

TEST_CASE("rbegin and crbegin() must return reverse constant iterator pointing to the last element of the list")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	const CStringList clist = list;

	auto cit = clist.crbegin();
	CHECK(*cit == "34");
	auto it = clist.rbegin();
	CHECK(*it == "34");
}

TEST_CASE("rend() must return reverse iterator pointing to the element before the first")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.rend();
	CHECK(*(--it) == "12");
}

TEST_CASE("rend and crend() must return reverse constant iterator pointing to the element before the first")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	const CStringList clist = list;

	auto cit = clist.crend();
	CHECK(*(--cit) == "12");
	auto it = clist.rend();
	CHECK(*(--it) == "12");
}

TEST_CASE("Operators == and != must check for equality of two lists")
{
	CStringList list1;
	list1.PushBack("12");
	list1.PushBack("34");

	CStringList list2;
	list2.PushBack("12");
	CHECK(list1 != list2);

	list2.PushBack("34");
	CHECK(list1 == list2);
}