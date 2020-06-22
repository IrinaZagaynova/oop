#include "stdafx.h"
#include "StringList.h"
#include <cassert>

using namespace std;

CStringList::CStringList(const CStringList& list)
{
	CStringList copy;
	for (const auto& str : list)
	{
		copy.PushBack(str);
	}
	swap(*this, copy);
}

CStringList::CStringList(CStringList&& list) noexcept
{
	m_size = list.m_size; 
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = list.m_lastNode; 
	list.m_firstNode = nullptr;
	list.m_lastNode = nullptr;
	list.m_size = 0;
}

CStringList::~CStringList()
{
	Clear();
}

size_t CStringList::GetSize() const
{
	return m_size;
}

void CStringList::PushBack(const string& data)
{
	auto newNode = make_unique<Node>(data, m_lastNode, nullptr);
	Node* newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::PushFront(const string& data)
{
	auto newNode = make_unique<Node>(data, nullptr, move(m_firstNode));
	m_firstNode = move(newNode);
	if (!m_lastNode)
	{
		m_lastNode = m_firstNode.get();
	}
	++m_size;
}

CStringList& CStringList::operator=(const CStringList& other)
{
	if (*this != other)
	{ 
		CStringList copy;
		for (const auto& str : other)
		{
			copy.PushBack(str);
		}
		swap(*this, copy);
	}
	return *this;
}

CStringList& CStringList::operator=(CStringList&& other) noexcept
{ 
	if (*this != other)
	{
		m_size = other.m_size;
		m_firstNode = std::move(other.m_firstNode);
		m_lastNode = other.m_lastNode;
		other.m_firstNode = nullptr;
		other.m_lastNode = nullptr;
		other.m_size = 0;
	}
	return *this;
}

bool CStringList::operator==(const CStringList& other) const
{
	if (m_size != other.GetSize())
	{
		return false;
	}

	for (auto iter1 = begin(), iter2 = other.begin(); iter1 != end(); ++iter1, ++iter2)
	{
		if (*iter1 != *iter2)
		{
			return false;
		}
	}

	return true;
}

bool CStringList::operator!=(const CStringList& other) const
{
	return !(*this == other);
}

CStringList::CIterator CStringList::begin()
{

	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	if (m_size == 0)
	{
		return begin();
	}
	return CIterator(m_lastNode->next.get());
}

const CStringList::CIterator CStringList::begin() const
{

	return CIterator(m_firstNode.get());
}

const CStringList::CIterator CStringList::end() const
{
	if (m_size == 0)
	{
		return begin();
	}
	return  CIterator(m_lastNode->next.get());
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode);
}

CStringList::CIterator CStringList::rend()
{
	if (m_size == 0)
	{
		return rbegin();
	}
	return CIterator(m_firstNode->prev);
}

const CStringList::CIterator CStringList::rbegin() const
{
	return  CIterator(m_lastNode);
}

const CStringList::CIterator CStringList::rend() const
{
	if (m_size == 0)
	{
		return rbegin();
	}
	return CIterator(m_firstNode->prev);
}

void CStringList::Insert(const CStringList::CIterator& iter, const std::string& data)
{
	if (iter == begin())
	{
		PushFront(data);
	}
	else if (iter == end())
	{
		PushBack(data);
	}
	else 
	{
		auto newNode = std::make_unique<Node>(data, iter.m_node->prev, std::move(iter.m_node->prev->next));  
		newNode->next->prev = newNode.get(); 
		newNode->prev->next = std::move(newNode);  
		m_size++;
	}
}

void CStringList::Delete(const CStringList::CIterator& iter)
{	
	if (!iter.m_node)
	{
		throw exception();
	}

	if (m_size == 1)
	{
		m_firstNode = nullptr;
		m_lastNode = nullptr;
	}
	else if (iter == begin())
	{
		m_firstNode = move(iter.m_node->next);
		m_firstNode->prev = nullptr;
	}
	else
	{
		iter.m_node->next->prev = iter.m_node->prev;
		iter.m_node->prev->next = move(iter.m_node->next);
	}
	--m_size;
}

void CStringList::Clear()
{	
	for (auto iter = begin(); iter != end(); iter = begin())
	{
		Delete(iter);
	}
}

std::string& CStringList::GetBackElement()
{
	if (!m_lastNode)
	{
		throw exception();
	}
	return m_lastNode->data;
}

std::string const& CStringList::GetBackElement() const
{
	if (!m_lastNode)
	{
		throw exception();
	}
	return m_lastNode->data;
}

std::string& CStringList::GetFrontElement()
{
	if (!m_firstNode)
	{
		throw exception();
	}
	return m_firstNode->data;
}

std::string const& CStringList::GetFrontElement() const
{
	if (!m_firstNode)
	{
		throw exception();
	}
	return m_firstNode->data;
}

CStringList::CIterator::CIterator(Node* node, bool isReverse)
	:m_node(node), m_isReverse(isReverse)
{
}

std::string& CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::CIterator& CStringList::CIterator::operator++()
{
	m_node = (m_isReverse) ? (m_node->prev) : (m_node->next.get());
	return *this;
}

CStringList::CIterator& CStringList::CIterator::operator--()
{
	m_node = (!m_isReverse) ? (m_node->prev) : (m_node->next.get());
	return *this;
}

bool CStringList::CIterator::operator==(const CIterator& iter) const
{
	return (m_node == iter.m_node);
}

bool CStringList::CIterator::operator!=(const CIterator& iter) const
{
	return (m_node != iter.m_node);
}