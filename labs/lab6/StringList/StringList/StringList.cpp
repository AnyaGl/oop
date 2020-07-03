#include "StringList.h"

CStringList::CStringList()
{
	auto lastNode = std::make_unique<Node>(nullptr, nullptr);
	Node* pLastNode = lastNode.get();
	auto firstNode = std::make_unique<Node>(nullptr, std::move(lastNode));

	m_lastNode = pLastNode;
	m_firstNode = std::move(firstNode);
	m_lastNode->prev = m_firstNode.get();
	m_size = 0;
}

CStringList::~CStringList() noexcept
{
	Clear();
}

CStringList::CStringList(const CStringList& list)
{
	CStringList tmp;
	for (const auto& str : list)
	{
		tmp.PushBack(str);
	}
	std::swap(*this, tmp);
}

CStringList::CStringList(CStringList&& list) noexcept
{
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = list.m_lastNode;
	m_size = list.m_size;

	CStringList emptyList;
	list.m_firstNode = std::move(emptyList.m_firstNode);
	list.m_lastNode = emptyList.m_lastNode;
	list.m_size = emptyList.m_size;
}

CStringList& CStringList::operator=(const CStringList& list)
{
	if (&list != this)
	{
		CStringList tmp(list);
		std::swap(*this, tmp);
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& list) noexcept
{
	if (&list != this)
	{
		Clear();
		m_firstNode = std::move(list.m_firstNode);
		m_lastNode = list.m_lastNode;
		m_size = list.m_size;

		CStringList emptyList;
		list.m_firstNode = std::move(emptyList.m_firstNode);
		list.m_lastNode = emptyList.m_lastNode;
		list.m_size = emptyList.m_size;
	}
	return *this;
}

CStringList::iterator CStringList::begin()
{
	return iterator(m_firstNode->next.get());
}
CStringList::iterator CStringList::end()
{
	return iterator(m_lastNode);
}

CStringList::const_iterator CStringList::begin() const
{
	return const_iterator(m_firstNode->next.get());
}
CStringList::const_iterator CStringList::end() const
{
	return const_iterator(m_lastNode);
}

CStringList::const_iterator CStringList::cbegin() const
{
	return const_iterator(m_firstNode->next.get());
}
CStringList::const_iterator CStringList::cend() const
{
	return const_iterator(m_lastNode);
}

std::reverse_iterator<CStringList::iterator> CStringList::rbegin()
{
	return std::reverse_iterator<iterator>(end());
}
std::reverse_iterator<CStringList::iterator> CStringList::rend()
{
	return std::reverse_iterator<iterator>(begin());
}

std::reverse_iterator<CStringList::const_iterator> CStringList::rbegin() const
{
	return std::reverse_iterator<const_iterator>(end());
}
std::reverse_iterator<CStringList::const_iterator> CStringList::rend() const
{
	return std::reverse_iterator<const_iterator>(begin());
}

std::reverse_iterator<CStringList::const_iterator> CStringList::crbegin() const
{
	return std::reverse_iterator<const_iterator>(cend());
}
std::reverse_iterator<CStringList::const_iterator> CStringList::crend() const
{
	return std::reverse_iterator<const_iterator>(cbegin());
}

void CStringList::PushBack(const std::string& data)
{
	Insert(end(), data);
}

void CStringList::PushFront(const std::string& data)
{
	Insert(begin(), data);
}

void CStringList::Insert(const iterator& it, const std::string& data)
{
	if (!it.m_node)
	{
		throw std::runtime_error("Cannot insert to null position");
	}
	auto newNode = std::make_unique<NodeWithData>(data, it.m_node->prev, std::move(it.m_node->prev->next));
	newNode->next->prev = newNode.get();
	newNode->prev->next = std::move(newNode);
	++m_size;
}

void CStringList::Insert(const const_iterator& it, const std::string& data)
{
	Insert(iterator(it.m_node), data);
}

void CStringList::Erase(const iterator& it)
{
	if (!it.m_node)
	{
		throw std::runtime_error("Cannot erase element from null position");
	}
	if (it == end() || it == --begin())
	{
		throw std::runtime_error("Cannot erase element from end position");
	}

	it.m_node->next->prev = it.m_node->prev;
	it.m_node->prev->next = std::move(it.m_node->next);
	--m_size;
}

void CStringList::Erase(const const_iterator& it)
{
	Erase(iterator(it.m_node));
}

void CStringList::Clear()
{
	while (!IsEmpty())
	{
		Erase(begin());
	}
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0);
}

void CStringList::ThrowWithEmptyList() const
{
	if (IsEmpty())
	{
		throw std::runtime_error("Cannot get element from empty list");
	}
}

std::string& CStringList::GetBackElement()
{
	ThrowWithEmptyList();
	return m_lastNode->prev->GetData();
}

std::string const& CStringList::GetBackElement() const
{
	ThrowWithEmptyList();
	return m_lastNode->prev->GetData();
}

std::string& CStringList::GetFrontElement()
{
	ThrowWithEmptyList();
	return m_firstNode->next.get()->GetData();
}

std::string const& CStringList::GetFrontElement() const
{
	ThrowWithEmptyList();
	return m_firstNode->next.get()->GetData();
}

bool CStringList::operator==(const CStringList& list) const
{
	if (m_size != list.m_size)
	{
		return false;
	}
	auto it2 = list.begin();
	for (auto it1 = begin(); it1 != end(); ++it1, ++it2)
	{
		if (*it1 != *it2)
		{
			return false;
		}
	}
	return true;
}

bool CStringList::operator!=(const CStringList& list) const
{
	return !(*this == list);
}

std::string& CStringList::Node::GetData()
{
	throw std::runtime_error("Cannot dereference end iterator");
}

std::string& CStringList::NodeWithData::GetData()
{
	return data;
}
