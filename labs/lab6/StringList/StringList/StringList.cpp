#include "StringList.h"

CStringList::~CStringList()
{
}

CStringList::CStringList(const CStringList& list)
{
}

CStringList::CStringList(CStringList&& list) noexcept
{
}

CStringList& CStringList::operator=(const CStringList& list)
{
	return *this;
}

CStringList& CStringList::operator=(CStringList&& list) noexcept
{
	return *this;
}

CStringList::CIterator::CIterator(Node* node, bool isReverse)
	: m_isReverse(isReverse)
{

}

std::string& CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator++(int)
{
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	return *this;
}

CStringList::CIterator CStringList::CIterator::operator--(int)
{
	return *this;
}

bool CStringList::CIterator::operator==(const CIterator& other) const
{
	return false;
}

bool CStringList::CIterator::operator!=(const CIterator& other) const
{
	return false;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::begin() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::end() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::rbegin() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::rend() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::crbegin() const
{
	return CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::crend() const
{
	return CIterator(m_lastNode);
}

void CStringList::PushBack(const std::string& data)
{
}

void CStringList::PushFront(const std::string& data)
{
}

void CStringList::Insert(const CIterator& it, const std::string& data)
{
}

void CStringList::Erase(const CIterator& it)
{
}

void CStringList::Clear()
{
}

size_t CStringList::GetSize() const
{
	return size_t();
}

bool CStringList::IsEmpty() const
{
	return false;
}

std::string& CStringList::GetBackElement()
{
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement() const
{
	return m_lastNode->data;
}

std::string& CStringList::GetFrontElement()
{
	return m_lastNode->data;
}

std::string const& CStringList::GetFrontElement() const
{
	return m_lastNode->data;
}

bool operator==(const CStringList& list1, const CStringList& list2)
{
	return false;
}

bool operator!=(const CStringList& list1, const CStringList& list2)
{
	return false;
}
