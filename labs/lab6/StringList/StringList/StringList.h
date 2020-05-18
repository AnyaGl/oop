#pragma once

#include <memory>
#include <string>

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data)
			, prev(prev)
			, next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};

public:
	CStringList() = default;
	~CStringList();
	CStringList(const CStringList& list);
	CStringList(CStringList && list) noexcept;

	CStringList& operator=(const CStringList& list);
	CStringList& operator=(CStringList&& list) noexcept;

	class CIterator
	{
		friend CStringList;
		CIterator(Node* node, bool isReverse = false);

	public:
		CIterator() = default;
		std::string& operator*() const;

		CIterator& operator++();
		CIterator operator++(int);

		CIterator& operator--();
		CIterator operator--(int);

		bool operator==(const CIterator& other) const;
		bool operator!=(const CIterator& other) const;

	private:
		Node* m_node = nullptr;
		bool m_isReverse = false;
	};

	CIterator begin();
	CIterator end();

	const CIterator begin() const;
	const CIterator end() const;

	const CIterator cbegin() const;
	const CIterator cend() const;

	CIterator rbegin();
	CIterator rend();

	const CIterator rbegin() const;
	const CIterator rend() const;

	const CIterator crbegin() const;
	const CIterator crend() const;

	void PushBack(const std::string& data);
	void PushFront(const std::string& data);

	void Insert(const CIterator& it, const std::string& data);
	void Erase(const CIterator& it);
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
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};
