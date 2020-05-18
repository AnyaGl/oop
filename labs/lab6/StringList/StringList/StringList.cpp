#include "StringList.h"
#include <stdexcept>

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
	return m_node->data;
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
	return (m_firstNode) ? CIterator(m_firstNode.get()) : CIterator();
}

CStringList::CIterator CStringList::end()
{
	return (m_lastNode) ? CIterator(m_lastNode->next.get()) : CIterator();
}

const CStringList::CIterator CStringList::begin() const
{
	return (m_firstNode) ? CIterator(m_firstNode.get()) : CIterator();
}

const CStringList::CIterator CStringList::end() const
{
	return (m_lastNode) ? CIterator(m_lastNode->next.get()) : CIterator();
}

const CStringList::CIterator CStringList::cbegin() const
{
	return (m_firstNode) ? CIterator(m_firstNode.get()) : CIterator();
}

const CStringList::CIterator CStringList::cend() const
{
	return (m_lastNode) ? CIterator(m_lastNode->next.get()) : CIterator();
}

CStringList::CIterator CStringList::rbegin()
{
	return (m_lastNode) ? CIterator(m_lastNode, true) : CIterator();
}

CStringList::CIterator CStringList::rend()
{
	return (m_firstNode) ? CIterator(m_lastNode->prev, true) : CIterator();
}

const CStringList::CIterator CStringList::rbegin() const
{
	return (m_lastNode) ? CIterator(m_lastNode, true) : CIterator();
}

const CStringList::CIterator CStringList::rend() const
{
	return (m_firstNode) ? CIterator(m_lastNode->prev, true) : CIterator();
}

const CStringList::CIterator CStringList::crbegin() const
{
	return (m_lastNode) ? CIterator(m_lastNode, true) : CIterator();
}

const CStringList::CIterator CStringList::crend() const
{
	return (m_firstNode) ? CIterator(m_lastNode->prev, true) : CIterator();
}

void CStringList::PushBack(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = std::move(newNode);
	}
	else
	{
		m_firstNode = std::move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::PushFront(const std::string& data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, std::move(m_firstNode));
	Node* newFirstNode = newNode.get();
	if (m_firstNode)
	{
		m_firstNode->prev = newFirstNode;
	}
	else
	{
		m_lastNode = newFirstNode;
	}
	m_firstNode = std::move(newNode);
	++m_size;
}

void CStringList::Insert(const CIterator& it, const std::string& data)
{
}

void CStringList::Erase(const CIterator& it)
{
}

void CStringList::Clear()
{
	while (m_lastNode)
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

std::string& CStringList::GetBackElement()
{
	if (!m_lastNode)
	{
		throw std::runtime_error("GetBackElement() called on empty list");
	}
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement() const
{
	if (!m_lastNode)
	{
		throw std::runtime_error("GetBackElement() called on empty list");
	}
	return m_lastNode->data;
}

std::string& CStringList::GetFrontElement()
{
	if (!m_firstNode)
	{
		throw std::runtime_error("GetFrontElement() called on empty list");
	}
	return m_firstNode.get()->data;
}

std::string const& CStringList::GetFrontElement() const
{
	if (!m_firstNode)
	{
		throw std::runtime_error("GetFrontElement() called on empty list");
	}
	return m_firstNode.get()->data;
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
