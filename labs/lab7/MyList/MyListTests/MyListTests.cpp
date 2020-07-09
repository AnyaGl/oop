#define CATCH_CONFIG_MAIN
#include "../MyList/MyList.h"
#include "catch2/catch.hpp"

TEST_CASE("Default constructor must create an empty list")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		CHECK(list.GetSize() == 0);
		CHECK(list.IsEmpty());
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		CHECK(list.GetSize() == 0);
		CHECK(list.IsEmpty());
	}
}

TEST_CASE("PushBack() must add element to the end of list")
{
	SECTION("String list")
	{
		CMyList<std::string> list;

		list.PushBack("123");
		CHECK(list.GetSize() == 1);
		CHECK(list.GetBackElement() == "123");

		list.PushBack("345");
		CHECK(list.GetSize() == 2);
		CHECK(list.GetBackElement() == "345");
	}
	SECTION("Int list")
	{
		CMyList<int> list;

		list.PushBack(2);
		CHECK(list.GetSize() == 1);
		CHECK(list.GetBackElement() == 2);

		list.PushBack(1);
		CHECK(list.GetSize() == 2);
		CHECK(list.GetBackElement() == 1);
	}
}

TEST_CASE("PushFront() must add element to the begin of list")
{
	SECTION("String list")
	{
		CMyList<std::string> list;

		list.PushFront("123");
		CHECK(list.GetSize() == 1);
		CHECK(list.GetFrontElement() == "123");

		list.PushFront("345");
		CHECK(list.GetSize() == 2);
		CHECK(list.GetFrontElement() == "345");
		CHECK(list.GetBackElement() == "123");
	}
	SECTION("Int list")
	{
		CMyList<int> list;

		list.PushFront(3);
		CHECK(list.GetSize() == 1);
		CHECK(list.GetFrontElement() == 3);

		list.PushFront(1);
		CHECK(list.GetSize() == 2);
		CHECK(list.GetFrontElement() == 1);
		CHECK(list.GetBackElement() == 3);
	}
}

TEST_CASE("Clear() must clear list (list will become empty)")
{
	CMyList<std::string> list;
	list.PushBack("123");
	list.PushBack("345");
	CHECK(list.GetSize() == 2);

	list.Clear();
	CHECK(list.IsEmpty());
}

TEST_CASE("Insert() must insert element at the position specified by iterator")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		list.Insert(list.cbegin(), "12");
		list.Insert(list.end(), "56");
		list.Insert(--list.end(), "34");

		CHECK(list.GetSize() == 3);
		CHECK(list.GetFrontElement() == "12");
		CHECK(list.GetBackElement() == "56");

		CHECK_THROWS(list.Insert(++list.end(), "34"));
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		list.Insert(list.begin(), 1);
		list.Insert(list.end(), 3);
		list.Insert(--list.end(), 2);

		CHECK(list.GetSize() == 3);
		CHECK(list.GetFrontElement() == 1);
		CHECK(list.GetBackElement() == 3);

		CHECK_THROWS(list.Insert(++list.end(), 4));
	}
}

TEST_CASE("Erase() must delete element at the position specified by iterator")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	CHECK(list.GetSize() == 3);
	CHECK(list.GetBackElement() == "56");

	list.Erase(--list.cend());
	CHECK(list.GetSize() == 2);
	CHECK(list.GetBackElement() == "34");

	CHECK_THROWS(list.Erase(++list.end()));
	CHECK_THROWS(list.Erase(list.end()));
	CHECK_THROWS(list.Erase(--list.begin()));
}

TEST_CASE("GetBackElement() must return last element from list")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		CHECK_THROWS(list.GetBackElement());

		list.PushBack("12");
		list.PushBack("34");

		CHECK(list.GetBackElement() == "34");

		SECTION("Can be const")
		{
			const CMyList<std::string> constList(list);
			CHECK(constList.GetBackElement() == "34");
		}
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		CHECK_THROWS(list.GetBackElement());

		list.PushBack(15);
		list.PushBack(123);

		CHECK(list.GetBackElement() == 123);

		SECTION("Can be const")
		{
			const CMyList<int> constList(list);
			CHECK(constList.GetBackElement() == 123);
		}
	}
}
TEST_CASE("GetFrontElement() must return first element from list")
{
	CMyList<std::string> list;
	CHECK_THROWS(list.GetFrontElement());

	list.PushBack("12");
	list.PushBack("34");

	CHECK(list.GetFrontElement() == "12");

	SECTION("Can be const")
	{
		const CMyList<std::string> constList(list);
		CHECK(constList.GetFrontElement() == "12");
	}
}

TEST_CASE("Copy constructor must create a copy of the passed object")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		list.PushBack("12");
		list.PushBack("34");

		CMyList<std::string> copyList(list);
		CHECK(copyList.GetSize() == 2);
		CHECK(copyList == list);
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		list.PushBack(14);
		list.PushBack(21);

		CMyList<int> copyList(list);
		CHECK(copyList.GetSize() == 2);
		CHECK(copyList == list);
	}
}

TEST_CASE("Move constructor must move the object")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		list.PushBack("12");
		list.PushBack("34");

		CMyList<std::string> copyList(list);

		CMyList<std::string> moveList(std::move(list));
		CHECK(moveList.GetSize() == 2);
		CHECK(moveList == copyList);
		CHECK(list.GetSize() == 0);
		CHECK(list == CMyList<std::string>());
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		list.PushBack(14);
		list.PushBack(23);

		CMyList<int> copyList(list);

		CMyList<int> moveList(std::move(list));
		CHECK(moveList.GetSize() == 2);
		CHECK(moveList == copyList);
		CHECK(list.GetSize() == 0);
		CHECK(list == CMyList<int>());
	}
}

TEST_CASE("Copy assignment operator must assign copy of one list to another")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		list.PushBack("12");
		list.PushBack("34");

		CMyList<std::string> copyList;
		copyList = list;
		CHECK(copyList.GetSize() == 2);
		CHECK(copyList == list);
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		list.PushBack(12);
		list.PushBack(23);

		CMyList<int> copyList;
		copyList = list;
		CHECK(copyList.GetSize() == 2);
		CHECK(copyList == list);
	}
}

TEST_CASE("Move assignment operator must assign list of another list that will be cleared")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		list.PushBack("12");
		list.PushBack("34");

		CMyList<std::string> copyList(list);

		CMyList<std::string> moveList = std::move(list);
		CHECK(moveList.GetSize() == 2);
		CHECK(moveList == copyList);
		CHECK(list.GetSize() == 0);
		CHECK(list == CMyList<std::string>());
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		list.PushBack(12);
		list.PushBack(23);

		CMyList<int> copyList(list);

		CMyList<int> moveList = std::move(list);
		CHECK(moveList.GetSize() == 2);
		CHECK(moveList == copyList);
		CHECK(list.GetSize() == 0);
		CHECK(list == CMyList<int>());
	}
}

TEST_CASE("The * operator must return an object reference")
{
	SECTION("String list")
	{
		CMyList<std::string> list;
		list.PushBack("12");
		list.PushBack("34");

		CHECK(*(list.begin()) == "12");

		CHECK_THROWS(*(list.end()));
		CHECK_THROWS(*(++list.end()));
	}
	SECTION("Int list")
	{
		CMyList<int> list;
		list.PushBack(12);
		list.PushBack(23);

		CHECK(*(list.begin()) == 12);

		CHECK_THROWS(*(list.end()));
		CHECK_THROWS(*(++list.end()));
	}
}

TEST_CASE("Postfix operator ++ must return the current iterator and then change it")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	auto it = list.begin();
	CHECK(*(it++) == "12");

	auto rit = list.rbegin();
	CHECK(*(rit++) == "56");

	SECTION("Cannot increment null")
	{
		CHECK_THROWS(++(++list.end()));
	}
}

TEST_CASE("Prefix operator ++ must change the iterator and return it")
{
	CMyList<std::string> list;
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
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");
	list.PushBack("56");

	auto it = --list.end();
	CHECK(*(it--) == "56");

	auto rit = --list.rend();
	CHECK(*(rit--) == "12");

	SECTION("Cannot decrement null")
	{
		CHECK_THROWS(--(--(--list.begin())));
	}
}

TEST_CASE("Prefix operator -- must change the iterator and return it")
{
	CMyList<std::string> list;
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
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	auto it1 = list.begin();
	auto it2 = --list.end();
	CHECK(it1 != it2);
	CHECK_FALSE(it1 == it2);
	--it2;
	CHECK(it1 == it2);
	CHECK_FALSE(it1 != it2);
}

TEST_CASE("begin() must return an iterator pointing to begin of the list")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.begin();
	CHECK(*it == "12");
}

TEST_CASE("begin() and cbegin() must return a constant iterator pointing to begin of the list")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	const CMyList<std::string> clist = list;

	auto cit = clist.cbegin();
	CHECK(*cit == "12");
	auto it = clist.begin();
	CHECK(*it == "12");
}

TEST_CASE("end() must return an iterator pointing to the element following the last")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.end();
	CHECK(*(--it) == "34");
}

TEST_CASE("end() and cend() must return a constant iterator pointing to the element following the last")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	const CMyList<std::string> clist = list;

	auto cit = clist.cend();
	CHECK(*(--cit) == "34");
	auto it = clist.end();
	CHECK(*(--it) == "34");
}

TEST_CASE("rbegin() must return reverse iterator pointing to the last element of the list")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.rbegin();
	CHECK(*(it) == "34");
}

TEST_CASE("rbegin and crbegin() must return reverse constant iterator pointing to the last element of the list")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	const CMyList<std::string> clist = list;

	auto cit = clist.crbegin();
	CHECK(*cit == "34");
	auto it = clist.rbegin();
	CHECK(*it == "34");
}

TEST_CASE("rend() must return reverse iterator pointing to the element before the first")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.rend();
	CHECK(*(--it) == "12");
}

TEST_CASE("rend and crend() must return reverse constant iterator pointing to the element before the first")
{
	CMyList<std::string> list;
	list.PushBack("12");
	list.PushBack("34");

	const CMyList<std::string> clist = list;

	auto cit = clist.crend();
	CHECK(*(--cit) == "12");
	auto it = clist.rend();
	CHECK(*(--it) == "12");
}

TEST_CASE("Operators == and != must check for equality of two lists")
{
	SECTION("String list")
	{
		CMyList<std::string> list1;
		list1.PushBack("12");
		list1.PushBack("34");

		CMyList<std::string> list2;
		list2.PushBack("12");
		CHECK(list1 != list2);
		CHECK_FALSE(list1 == list2);

		list2.PushBack("34");
		CHECK(list1 == list2);
		CHECK_FALSE(list1 != list2);

		list2.Erase(--list2.end());
		list2.PushBack("123");
		CHECK(list1 != list2);
		CHECK_FALSE(list1 == list2);
	}
	SECTION("Int list")
	{
		CMyList<int> list1;
		list1.PushBack(12);
		list1.PushBack(23);

		CMyList<int> list2;
		list2.PushBack(12);
		CHECK(list1 != list2);
		CHECK_FALSE(list1 == list2);

		list2.PushBack(23);
		CHECK(list1 == list2);
		CHECK_FALSE(list1 != list2);

		list2.Erase(--list2.end());
		list2.PushBack(123);
		CHECK(list1 != list2);
		CHECK_FALSE(list1 == list2);
	}
}
