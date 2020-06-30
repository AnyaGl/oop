#pragma once

#include <memory>
#include <stdexcept>

template <typename T>
class CMyList
{
	struct Node
	{
		Node(Node* prev, std::unique_ptr<Node>&& next)
			: prev(prev)
			, next(std::move(next))
		{
		}
		virtual T& GetData()
		{
			throw std::runtime_error("Cannot dereference end iterator");
		};
		virtual ~Node() {}
		Node* prev;
		std::unique_ptr<Node> next;
	};
	struct NodeWithData : Node
	{
		NodeWithData(T const& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, Node(prev, std::move(next))
		{
		}
		T& GetData() override
		{
			return data;
		};
		T data;
	};

	const bool REVERSE_ITERATOR = true;
	
	void ThrowWithEmptyList() const
	{
		if (IsEmpty())
		{
			throw std::runtime_error("Cannot get element from empty list");
		}
	}

public:
	CMyList()
	{
		auto lastNode = std::make_unique<Node>(nullptr, nullptr);
		Node* pLastNode = lastNode.get();

		m_firstNode = std::make_unique<Node>(nullptr, std::move(lastNode));
		m_lastNode = pLastNode;
		m_lastNode->prev = m_firstNode.get();
		m_size = 0;
	}
	~CMyList()
	{
		Clear();
		m_firstNode = nullptr;
		m_lastNode = nullptr;
	}
	CMyList(const CMyList& list)
	{
		CMyList tmp;
		for (const auto& item : list)
		{
			tmp.PushBack(item);
		}
		std::swap(*this, tmp);
	}
	CMyList(CMyList&& list) noexcept
	{
		m_firstNode = std::move(list.m_firstNode);
		m_lastNode = list.m_lastNode;
		m_size = list.m_size;

		CMyList emptyList;
		list.m_firstNode = std::move(emptyList.m_firstNode);
		list.m_lastNode = emptyList.m_lastNode;
		list.m_size = emptyList.m_size;
	}

	CMyList& operator=(const CMyList& list)
	{
		if (this != &list)
		{
			CMyList tmp(list);
			std::swap(*this, tmp);
		}
		return *this;
	}
	CMyList& operator=(CMyList&& list) noexcept
	{
		if (this != &list)
		{
			Clear();

			m_firstNode = std::move(list.m_firstNode);
			m_lastNode = list.m_lastNode;
			m_size = list.m_size;

			CMyList emptyList;
			list.m_firstNode = std::move(emptyList.m_firstNode);
			list.m_lastNode = emptyList.m_lastNode;
			list.m_size = emptyList.m_size;
		}
		return *this;
	}

	class CIterator
	{
		friend CMyList;
		CIterator(Node* node, bool isReverse = false)
			: m_node(node)
			, m_isReverse(isReverse)
		{
		}

	public:
		CIterator() = delete;
		T& operator*() const
		{
			if (!m_node)
			{
				throw std::runtime_error("Cannot dereference empty iterator");
			}
			return m_node->GetData();
		}

		CIterator& operator++()
		{
			if (!m_node)
			{
				throw std::runtime_error("Cannot increment empty iterator");
			}
			m_node = m_isReverse ? m_node->prev : m_node->next.get();
			return *this;
		}
		CIterator operator++(int)
		{
			auto copyIt = *this;
			++*this;
			return copyIt;
		}
		CIterator& operator--()
		{
			if (!m_node)
			{
				throw std::runtime_error("Cannot decrement empty iterator");
			}
			m_node = m_isReverse ? m_node->next.get() : m_node->prev;
			return *this;
		}
		CIterator operator--(int)
		{
			auto copyIt = *this;
			--*this;
			return copyIt;
		}

		bool operator==(const CIterator& other) const
		{
			return other.m_node == m_node;
		}
		bool operator!=(const CIterator& other) const
		{
			return other.m_node != m_node;
		}

	private:
		Node* m_node = nullptr;
		bool m_isReverse = false;
	};

	CIterator begin()
	{
		return CIterator(m_firstNode->next.get());
	}
	CIterator end()
	{
		return CIterator(m_lastNode);
	}

	const CIterator begin() const
	{
		return CIterator(m_firstNode->next.get());
	}
	const CIterator end() const
	{
		return CIterator(m_lastNode);
	}

	const CIterator cbegin() const
	{
		return CIterator(m_firstNode->next.get());
	}
	const CIterator cend() const
	{
		return CIterator(m_lastNode);
	}

	CIterator rbegin()
	{
		return CIterator(m_lastNode->prev, REVERSE_ITERATOR);
	}
	CIterator rend()
	{
		return CIterator(m_firstNode.get(), REVERSE_ITERATOR);
	}

	const CIterator rbegin() const
	{
		return CIterator(m_lastNode->prev, REVERSE_ITERATOR);
	}
	const CIterator rend() const
	{
		return CIterator(m_firstNode.get(), REVERSE_ITERATOR);
	}

	const CIterator crbegin() const
	{
		return CIterator(m_lastNode->prev, REVERSE_ITERATOR);
	}
	const CIterator crend() const
	{
		return CIterator(m_firstNode.get(), REVERSE_ITERATOR);
	}

	void PushBack(T const& data)
	{
		Insert(end(), data);
	}
	void PushFront(T const& data)
	{
		Insert(begin(), data);
	}
	void Insert(const CIterator& it, T const& data)
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
	void Clear()
	{
		while (!IsEmpty())
		{
			Erase(begin());
		}
	}
	void Erase(const CIterator& it)
	{
		if (!it.m_node)
		{
			throw std::runtime_error("Cannot erase element from null position");
		}
		if (it == end() || it == rend())
		{
			throw std::runtime_error("Cannot erase element from end position");
		}
		it.m_node->next->prev = it.m_node->prev;
		it.m_node->prev->next = std::move(it.m_node->next);
		--m_size;
	}

	T& GetBackElement()
	{
		ThrowWithEmptyList();
		return m_lastNode->prev->GetData();
	}
	T const& GetBackElement() const
	{
		ThrowWithEmptyList();
		return m_lastNode->prev->GetData();
	}
	T& GetFrontElement()
	{
		ThrowWithEmptyList();
		return m_firstNode->next->GetData();
	}
	T const& GetFrontElement() const
	{
		ThrowWithEmptyList();
		return m_firstNode->next->GetData();
	}

	size_t GetSize() const
	{
		return m_size;
	}
	bool IsEmpty() const
	{
		return m_size == 0;
	}

	bool operator==(const CMyList& list) const
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
	bool operator!=(const CMyList& list) const
	{
		return !(*this == list);
	}

private:
	size_t m_size;
	Node* m_lastNode;
	std::unique_ptr<Node> m_firstNode;
};
