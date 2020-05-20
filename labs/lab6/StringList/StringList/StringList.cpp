#include "StringList.h"
#include <stdexcept>

CStringList::CStringList()
{
	m_size = 0;
	auto lastNode = std::make_unique<Node>(nullptr, nullptr);
	m_lastNode = lastNode.get();
	m_firstNode = std::make_unique<Node>(nullptr, std::move(lastNode));
	m_lastNode->prev = m_firstNode.get();
}

CStringList::~CStringList()
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
	list.m_lastNode = nullptr;
	list.m_size = 0;
}

CStringList& CStringList::operator=(const CStringList& list)
{
	if (&list != this)
	{
		CStringList tmp(list);
		std::swap(m_size, tmp.m_size);
		std::swap(m_lastNode, tmp.m_lastNode);
		std::swap(m_firstNode, tmp.m_firstNode);
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
		list.m_lastNode = nullptr;
		list.m_size = 0;
	}
	return *this;
}

CStringList::CIterator::CIterator(Node* node, bool isReverse)
	: m_node(node)
	, m_isReverse(isReverse)
{
}

std::string& CStringList::CIterator::operator*() const
{
	if (!m_node)
	{
		throw std::runtime_error("Cannot dereference empty iterator");
	}
	return m_node->GetData();
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	if (!m_node)
	{
		throw std::runtime_error("Cannot increment empty iterator");
	}
	m_node = (m_isReverse) ? (m_node->prev) : (m_node->next.get());
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	auto copyIt = *this;
	++*this;
	return copyIt;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	if (!m_node)
	{
		throw std::runtime_error("Cannot decrement empty iterator");
	}
	m_node = (m_isReverse) ? (m_node->next.get()) : (m_node->prev);
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator--(int)
{
	auto copyIt = *this;
	--*this;
	return copyIt;
}

bool CStringList::CIterator::operator==(const CIterator& other) const
{
	return (other.m_node == m_node);
}

bool CStringList::CIterator::operator!=(const CIterator& other) const
{
	return (other.m_node != m_node);
}

CStringList::CIterator CStringList::begin()
{
	return (IsEmpty()) ? CIterator(m_lastNode) : CIterator(m_firstNode->next.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::begin() const
{
	return (IsEmpty()) ? CIterator(m_lastNode) : CIterator(m_firstNode->next.get());
}

const CStringList::CIterator CStringList::end() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::cbegin() const
{
	return (IsEmpty()) ? CIterator(m_lastNode) : CIterator(m_firstNode->next.get());
}

const CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::rbegin()
{
	return (IsEmpty()) ? CIterator(m_firstNode.get(), true) : CIterator(m_lastNode->prev, true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(m_firstNode.get(), true);
}

const CStringList::CIterator CStringList::rbegin() const
{
	return (IsEmpty()) ? CIterator(m_firstNode.get(), true) : CIterator(m_lastNode->prev, true);
}

const CStringList::CIterator CStringList::rend() const
{
	return CIterator(m_firstNode.get(), true);
}

const CStringList::CIterator CStringList::crbegin() const
{
	return (IsEmpty()) ? CIterator(m_firstNode.get(), true) : CIterator(m_lastNode->prev, true);
}

const CStringList::CIterator CStringList::crend() const
{
	return CIterator(m_firstNode.get(), true);
}

void CStringList::PushBack(const std::string& data)
{
	auto newNode = std::make_unique<NodeWithData>(data, m_lastNode->prev, std::move(m_lastNode->prev->next));
	Node* newBackNode = newNode.get();
	if (IsEmpty())
	{
		m_firstNode->next = std::move(newNode);
	}
	else
	{
		newNode->prev->next = std::move(newNode);
	}
	m_lastNode->prev = newBackNode;
	++m_size;
}

void CStringList::PushFront(const std::string& data)
{
	auto newNode = std::make_unique<NodeWithData>(data, m_firstNode.get(), std::move(m_firstNode->next));
	Node* newFrontNode = newNode.get();
	if (IsEmpty())
	{
		m_lastNode->prev = newFrontNode;
	}
	else
	{
		newNode->next->prev = newFrontNode;
	}
	m_firstNode->next = std::move(newNode);
	++m_size;
}

void CStringList::Insert(const CIterator& it, const std::string& data)
{
	if (!it.m_node)
	{
		throw std::runtime_error("Cannot insert to null position");
	}
	if (it == begin())
	{
		PushFront(data);
	}
	else if (it == end())
	{
		PushBack(data);
	}
	else
	{
		auto newNode = std::make_unique<NodeWithData>(data, it.m_node->prev, std::move(it.m_node->prev->next));
		it.m_node->prev->next = std::move(newNode);
		it.m_node->prev = newNode.get();
		++m_size;
	}
}

void CStringList::Erase(const CIterator& it)
{
	if (!it.m_node)
	{
		throw std::runtime_error("Cannot erase element from null position");
	}
	if (it == end() || it == rend())
	{
		throw std::runtime_error("Cannot erase element from end position");	
	}

	if (m_size == 1)
	{
		m_firstNode->next = std::make_unique<Node>(nullptr, std::move(m_lastNode->prev->next));
		m_lastNode->prev = m_firstNode.get();
	}
	else
	{
		it.m_node->next->prev = it.m_node->prev;
		it.m_node->prev->next = std::move(it.m_node->next);
	}
	--m_size;
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
