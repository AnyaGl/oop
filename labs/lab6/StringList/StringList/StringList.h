#pragma once

#include <memory>
#include <string>
#include <stdexcept>

class CStringList
{
	struct Node
	{
		Node(Node* prev, std::unique_ptr<Node>&& next)
			: prev(prev)
			, next(std::move(next))
		{
		}
		virtual std::string& GetData();
		virtual ~Node() {}
		Node* prev;
		std::unique_ptr<Node> next;
	};
	struct NodeWithData : Node
	{
		NodeWithData(std::string data, Node* prev, std::unique_ptr<Node>&& next)
			: data(std::move(data))
			, Node(prev, std::move(next))
		{
		}
		std::string& GetData() override;
		std::string data;
	};

	template <bool IsConst>
	class CIterator
	{
		friend CStringList;

		CIterator(Node* node)
			: m_node(node)
		{
		}

	public:
		using MyType = CIterator<IsConst>;
		using value_type = std::conditional_t<IsConst, const std::string, std::string>;
		using reference = value_type&;
		using pointer = value_type*;
		using difference_type = ptrdiff_t;
		using iterator_category = std::random_access_iterator_tag;

		CIterator() = default;

		reference& operator*() const
		{
			if (!m_node)
			{
				throw std::runtime_error("Cannot dereference empty iterator");
			}
			return m_node->GetData();
		}

		MyType& operator++()
		{
			if (!m_node)
			{
				throw std::runtime_error("Cannot increment empty iterator");
			}
			m_node = m_node->next.get();
			return *this;
		}
		MyType operator++(int)
		{
			auto copyIt = *this;
			++*this;
			return copyIt;
		}

		MyType& operator--()
		{
			if (!m_node)
			{
				throw std::runtime_error("Cannot decrement empty iterator");
			}
			m_node = m_node->prev;
			return *this;
		}
		MyType operator--(int)
		{
			auto copyIt = *this;
			--*this;
			return copyIt;
		}

		bool operator==(const MyType& other) const
		{
			return (other.m_node == m_node);
		}
		bool operator!=(const MyType& other) const
		{
			return (other.m_node != m_node);
		}

	private:
		Node* m_node = nullptr;
	};

public:
	CStringList();
	~CStringList() noexcept;
	CStringList(const CStringList& list);
	CStringList(CStringList&& list) noexcept;

	CStringList& operator=(const CStringList& list);
	CStringList& operator=(CStringList&& list) noexcept;

	using iterator = CIterator<false>;
	using const_iterator = CIterator<true>;

	iterator begin();
	iterator end();

	const_iterator begin() const;
	const_iterator end() const;

	const_iterator cbegin() const;
	const_iterator cend() const;

	std::reverse_iterator<iterator> rbegin();
	std::reverse_iterator<iterator> rend();

	std::reverse_iterator<const_iterator> rbegin() const;
	std::reverse_iterator<const_iterator> rend() const;

	std::reverse_iterator<const_iterator> crbegin() const;
	std::reverse_iterator<const_iterator> crend() const;

	void PushBack(const std::string& data);
	void PushFront(const std::string& data);

	void Insert(const iterator& it, const std::string& data);
	void Insert(const const_iterator& it, const std::string& data);

	void Erase(const iterator& it);
	void Erase(const const_iterator& it);

	void Clear();

	size_t GetSize() const;
	bool IsEmpty() const;

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	std::string& GetFrontElement();
	std::string const& GetFrontElement() const;

	bool operator==(const CStringList& list) const;
	bool operator!=(const CStringList& list) const;

private:
	void ThrowWithEmptyList() const;

	size_t m_size;
	Node* m_lastNode;
	std::unique_ptr<Node> m_firstNode;
};
