#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../StringList/StringList.h"

TEST_CASE("Конструктор по умолчанию создает пустой список")
{
	CStringList list;
	CHECK(list.GetSize() == 0);
	CHECK(list.IsEmpty());
}

TEST_CASE("PushBack() должен добавить строку в конец списка")
{
	CStringList list;

	list.PushBack("123");
	CHECK(list.GetSize() == 1);
	CHECK(list.GetBackElement() == "123");

	list.PushBack("345");
	CHECK(list.GetSize() == 2);
	CHECK(list.GetBackElement() == "345");
}

TEST_CASE("PushFront() должен добавить строку в начало списка")
{
	CStringList list;

	list.PushFront("123");
	CHECK(list.GetSize() == 1);
	CHECK(list.GetFrontElement() == "123");

	list.PushFront("345");
	CHECK(list.GetSize() == 2);
	CHECK(list.GetFrontElement() == "345");
}

TEST_CASE("Clear() должен очистить список (список станет пустым)")
{
	CStringList list;
	list.PushBack("123");
	list.PushBack("345");
	CHECK(list.GetSize() == 2);

	list.Clear();
	CHECK(list.IsEmpty());
}

TEST_CASE("Insert() должен вставить элемент в позицию, задаваемую итератором")
{
	CStringList list;
	list.Insert(list.begin(), "34");
	list.Insert(list.begin(), "12");
	list.Insert(--list.end(), "56");
	CHECK(list.GetSize() == 3);
	CHECK(list.GetFrontElement() == "12");
	CHECK(list.GetBackElement() == "56");
}

TEST_CASE("Erase() должен удалить элемент в позиции, задаваемой итератором")
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

TEST_CASE("Копирующий конструктор должен создавать копию переданного объекта")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CStringList copyList(list);
	CHECK(copyList.GetSize() == 2);
	CHECK(copyList == list);
}

TEST_CASE("Перемещающий конструктор должен перемещать объект")
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

TEST_CASE("Копирующий оператор присваивания должен присваивать одному списку копию другого")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CStringList copyList = list;
	CHECK(copyList.GetSize() == 2);
	CHECK(copyList == list);
}

TEST_CASE("Перемещающий оператор присваивания должен перемещать объект")
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

TEST_CASE("Оператор * должен возвращать ссылку на объект")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	CHECK(*(list.begin()) == "12");
}

TEST_CASE("Постфиксный оператор ++ должен возвращать текущий итератор, а затем его изменить")
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

TEST_CASE("Префиксный оператор ++ должен изменить итератор и вернуть его")
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

TEST_CASE("Постфиксный оператор -- должен возвращать текущий итератор, а затем его изменить")
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

TEST_CASE("Префиксный оператор -- должен изменить итератор и вернуть его")
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

TEST_CASE("Операторы == и != должны проверять на равеноство два итератора")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it1 = list.begin();
	auto it2 = list.rend();
	CHECK(it1 != it2);
	CHECK(it1 == --it2);
}

TEST_CASE("begin() должен возвращать итератор, указывающий на начало списка")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.begin();
	CHECK(*it == "12");
}

TEST_CASE("begin() and cbegin() должны возвращать константный итератор, указывающий на начало списка")
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

TEST_CASE("end() должен возвращать итератор, указывающий элемент следующий за последним")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.end();
	CHECK(*(--it) == "34");
}

TEST_CASE("end() and cend() должны возвращать константный итератор, указывающий элемент следующий за последним")
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

TEST_CASE("rbegin() должен возвращать реверсивный итератор, указывающий на последний элемент списка")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.rbegin();
	CHECK(*(it) == "34");
}

TEST_CASE("rbegin and crbegin() должны возвращать реверсивный константный итератор, указывающий на последний элемент списка")
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

TEST_CASE("rend() должен возвращать реверсивный итератор, указывающий на элемент, стоящий перед первым")
{
	CStringList list;
	list.PushBack("12");
	list.PushBack("34");

	auto it = list.rend();
	CHECK(*(--it) == "12");
}

TEST_CASE("rend and crend() должны возвращать реверсивный константный итератор, указывающий на элемент, стоящий перед первым")
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

TEST_CASE("Операторы == и != должны проверять на равеноство два списка")
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