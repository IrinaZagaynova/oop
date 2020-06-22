#pragma once

#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node(const std::string& data, Node* prev, std::unique_ptr<Node>&& next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node* prev;
		std::unique_ptr<Node> next;
	};
public:
	CStringList() = default;
	CStringList(const CStringList& list); 
	CStringList(CStringList&& list) noexcept;
	~CStringList();

	size_t GetSize() const;
	void PushBack(const std::string& data);
	void PushFront(const std::string& data);

	CStringList& operator=(const CStringList& other);
	CStringList& operator=(CStringList&& other) noexcept;

	bool operator==(const CStringList& other) const;
	bool operator!=(const CStringList& other) const;

	class CIterator
	{
		friend CStringList;
		CIterator(Node* node, bool isReverse = false);
	public:
		CIterator() = default;
		std::string& operator*() const;
		CIterator& operator++();
		CIterator& operator--();
		bool operator==(const CIterator& iter) const;
		bool operator!=(const CIterator& iter) const;
	private:
		Node* m_node = nullptr;
		bool m_isReverse = false;
	};

	CIterator begin();
	CIterator end();

	const CIterator begin() const;
	const CIterator end() const;

	CIterator rbegin();
	CIterator rend();

	const CIterator rbegin() const;
	const CIterator rend() const;

	void Insert(const CIterator& iter, const std::string& data);
	void Delete(const CIterator& iter);
	void Clear();

	std::string& GetBackElement();
	std::string const& GetBackElement() const;

	std::string& GetFrontElement();
	std::string const& GetFrontElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node* m_lastNode = nullptr;
};