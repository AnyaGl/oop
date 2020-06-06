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
			: prev(prev)
			, Node(prev, std::move(next))
		{
		}
		T& GetData() override
		{
			return data;
		};
		T data;
	};

public:
	CMyList()
	{
		m_size = 0;
		m_firstNode = nullptr;
		m_lastNode = nullptr;
	}

	~CMyList() {}
	CMyList(const CMyList& list)
	{
		m_size = 0;
		m_firstNode = nullptr;
		m_lastNode = nullptr;
	}
	CMyList(CMyList&& list) noexcept
	{
		m_size = 0;
		m_firstNode = nullptr;
		m_lastNode = nullptr;
	}

	CMyList& operator=(const CMyList& list) 
	{
		return *this;
	}
	CMyList& operator=(CMyList&& list) noexcept 
	{
		return *this;
	}

	class CIterator
	{
		friend CMyList;
		CIterator(Node* node, bool isReverse = false);

	public:
		CIterator() = delete;
		T& operator*() const 
		{
			return m_node->GetData();
		}

		CIterator& operator++() 
		{
			return *this;
		}
		CIterator operator++(int) 
		{
			return *this;
		}
		CIterator& operator--() 
		{
			return *this;
		}
		CIterator operator--(int) 
		{
			return *this;
		}

		bool operator==(const CIterator& other) const
		{
			return false;
		}
		bool operator!=(const CIterator& other) const
		{
			return false;
		}

	private:
		Node* m_node = nullptr;
		bool m_isReverse = false;
	};

	CIterator begin() 
	{
		return CIterator(m_lastNode);
	}
	CIterator end()
	{
		return CIterator(m_lastNode);
	}

	const CIterator begin() const
	{
		return CIterator(m_lastNode);
	}
	const CIterator end() const
	{
		return CIterator(m_lastNode);
	}

	const CIterator cbegin() const
	{
		return CIterator(m_lastNode);
	}
	const CIterator cend() const
	{
		return CIterator(m_lastNode);
	}

	CIterator rbegin()
	{
		return CIterator(m_lastNode);
	}
	CIterator rend()
	{
		return CIterator(m_lastNode);
	}

	const CIterator rbegin() const
	{
		return CIterator(m_lastNode);
	}
	const CIterator rend() const
	{
		return CIterator(m_lastNode);
	}

	const CIterator crbegin() const
	{
		return CIterator(m_lastNode);
	}
	const CIterator crend() const
	{
		return CIterator(m_lastNode);
	}

	void PushBack(T const& data) {}
	void PushFront(T const& data) {}

	void Insert(const CIterator& it, T const& data) {}
	void Erase(const CIterator& it) {}
	void Clear() {}

	size_t GetSize() const 
	{
		return m_size;
	}
	bool IsEmpty() const 
	{
		return false;
	}

	T& GetBackElement() 
	{
		return m_lastNode->GetData();
	}
	T const& GetBackElement() const 
	{
		return m_lastNode->GetData();
	}

	T& GetFrontElement()
	{
		return m_firstNode->GetData();
	}
	T const& GetFrontElement() const
	{
		return m_firstNode->GetData();
	}

	bool operator==(const CMyList& list) const 
	{
		return false;
	}
	bool operator!=(const CMyList& list) const
	{
		return false;
	}

private:
	size_t m_size;
	Node* m_lastNode;
	std::unique_ptr<Node> m_firstNode;
};
