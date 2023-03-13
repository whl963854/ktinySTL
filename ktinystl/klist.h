#ifndef KTINYSTL_KLIST_H
#define KTINYSTL_KLIST_H 

#include<list>
#include "kallocator.h"

template<typename  T>
struct KListNode {
	KListNode* prev;
	KListNode* next;
	T val;
};

template<class T>
struct ListIterator {

	typedef ListIterator<T> self;
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef KListNode<T>* link_type;
	typedef ListIterator<T> iterator;

	link_type m_node;


	ListIterator();
	ListIterator(link_type x);
	ListIterator(const iterator& x);

	bool operator==(const self& x)const;
	bool operator!=(const self& x)const;
	reference operator*()const;
	pointer operator->()const;
	self& operator++();
	self& operator++(int);
	self& operator--();
	self& operator--(int);
};


template<class T>
class KList {

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef KListNode<T>* link_type;
	typedef ListIterator<T> iterator;
	typedef ktinystl::Allocator<KListNode<T>>  list_node_allocator;
	typedef ktinystl::Allocator<T>  data_allocator;

public:
	KList();
	KList(const KList& list);
	~KList();

	iterator begin();
	iterator end();
	iterator rbegin();
	iterator rend();

	bool empty();
	size_type size();

	reference front();
	reference back();

	void emplace_front(value_type& val);
	void push_front(value_type& val);
	void pop_front();
	void emplace_back(value_type& val);
	void push_back(value_type& val);
	void push_back(value_type&& val);
	void pop_back();

	void emplace(iterator position, value_type& val);
	void insert(iterator position, value_type& val);
	iterator erase(iterator position);

	void clear();
	void unique();

protected:
	link_type getNode();
	void putNode(link_type ptr);
	link_type createNode(value_type value);
	void destroyNode(link_type ptr);

private:
	link_type m_node;
	size_type    m_size;

	void transfer(iterator position, iterator first, iterator last);
};

template<class T>
KList<T>::~KList()
{
	auto temp = m_node;
	temp = temp->next;
	while (m_node != temp)
	{
		auto deallo = temp;
		temp = temp->next;
		list_node_allocator::destroy(deallo);
		list_node_allocator::deallocate(deallo);
	}
	list_node_allocator::destroy(m_node);
	list_node_allocator::deallocate(m_node);
}
template<class T>
KList<T>::KList(const KList& list)
{
	clear();
	auto last = list.end();
	auto first = list.begin();
	while (first != last)
	{
		push_back(first->val);
	}
}

template<class T>
KList<T>::KList()
	:m_size(0)
{
	m_node = createNode(0);
	m_node->next = m_node;
	m_node->prev = m_node;
}

template<class T>
void KList<T>::unique()
{
	iterator first = begin();
	iterator last = end();
	if (first == last)
	{
		return;
	}
	iterator next = first;
	while (++next != last)
	{
		if (*first == *next)
		{
			erase(next);
		}
		else
		{
			first = next;
		}
		next = first;
	}
}

template<class T>
typename KList<T>::link_type KList<T>::getNode()
{
	return list_node_allocator::allocate();
}

template<class T>
void KList<T>::putNode(link_type ptr)
{
	list_node_allocator::deallocate(ptr);
}

template<class T>
typename KList<T>::link_type KList<T>::createNode(value_type value)
{
	link_type node = list_node_allocator::allocate();
	list_node_allocator::construct(node);
	node->val = value;
	node->prev = nullptr;
	node->next = nullptr;
	return node;
}

template<class T>
void KList<T>::destroyNode(link_type ptr)
{
	data_allocator::destroy(&ptr->val);
	putNode(ptr);
}

template<class T>
void KList<T>::transfer(iterator position, iterator first, iterator last)
{
	if (position != last)
	{
		last.m_node->prev->next = position.m_node;
		first.m_node->prev->next = last.m_node;
		position.m_node->prev->next = first.node;
		auto tmp = position.m_node->prev;
		position.m_node->prev = last.m_node->prev;
		last.m_node->prev = first.m_node->prev;
		first.m_node->prev = tmp;
	}
}

template<class T>
void KList<T>::clear()
{
	link_type cur = m_node->next;
	while (cur != m_node)
	{
		link_type tmp = cur;
		cur = cur->next;
		destroyNode(tmp);
	}
	m_node->next = m_node;
	m_node->prev = m_node;
}

template<class T>
typename KList<T>::iterator KList<T>::erase(iterator position)
{
	auto tmp = position.m_node;
	auto pre = position.m_node->prev;
	auto nxt = position.m_node->next;
	pre->next = nxt;
	nxt->prev = pre;
	destroyNode(tmp);
	--m_size;
	return iterator(nxt);
}

template<class T>
void KList<T>::insert(iterator position, value_type& val)
{
	KListNode<T>* temp = createNode(val);
	temp->next = position.m_node;
	temp->prev = position.m_node->prev;
	position.m_node->prev->next = temp;
	temp->next->prev = temp;
	++m_size;
}

template<class T>
void KList<T>::emplace(iterator position, value_type& val)
{
	insert(position, val);
}

template<class T>
void KList<T>::pop_back()
{
	erase(--end());
}

template<class T>
void KList<T>::push_back(typename KList<T>::value_type& val)
{
	insert(end(), val);
}

template<class T>
void KList<T>::push_back(typename KList<T>::value_type&& val)
{
	insert(end(), val);
}

template<class T>
void KList<T>::emplace_back(typename KList<T>::value_type& val)
{
	insert(end(), val);
}

template<class T>
void KList<T>::pop_front()
{
	erase(begin());
}

template<class T>
void KList<T>::push_front(typename KList<T>::value_type& val)
{
	insert(begin(), val);
}

template<class T>
void KList<T>::emplace_front(typename KList<T>::value_type& val)
{
	insert(begin(), val);
}

template<class T>
typename KList<T>::reference KList<T>::back()
{
	if (m_size == 0)return nullptr;
	return *(m_node->prev);
}

template<class T>
typename KList<T>::reference KList<T>::front()
{
	if (m_size == 0)return nullptr;
	return *(m_node->next);
}

template<class T>
typename KList<T>::size_type KList<T>::size()
{
	return m_size;
}

template<class T>
bool KList<T>::empty()
{
	return m_size == 0;
}

template<class T>
typename KList<T>::iterator KList<T>::rend()
{
	return m_node;
}

template<class T>
typename KList<T>::iterator KList<T>::rbegin()
{
	return m_node->prev;
}

template<class T>
typename KList<T>::iterator KList<T>::end()
{
	return m_node;
}

template<class T>
typename KList<T>::iterator KList<T>::begin()
{
	return m_node->next;
}





//Iterator
template<class T>
ListIterator<T>::ListIterator()
{
}

template<class T>
ListIterator<T>::ListIterator(link_type x)
	: m_node(x)
{
}

template<class T>
ListIterator<T>::ListIterator(const ListIterator<T>::iterator& x)
	: m_node(x.m_node)
{
}


template<class T>
typename ListIterator<T>::self& ListIterator<T>::operator--(int)
{
	self tmp = *this;
	m_node = m_node->prev;
	return tmp;
}

template<class T>
typename ListIterator<T>::self& ListIterator<T>::operator--()
{
	m_node = m_node->prev;
	return *this;
}

template<class T>
typename ListIterator<T>::self& ListIterator<T>::operator++(int)
{
	self tmp = *this;
	m_node = m_node->next;
	return tmp;
}

template<class T>
typename ListIterator<T>::self& ListIterator<T>::operator++()
{
	m_node = m_node->next;
	return *this;
}

template<class T>
typename ListIterator<T>::pointer ListIterator<T>::operator->() const
{
	return &(operator*());
}

template<class T>
typename ListIterator<T>::reference ListIterator<T>::operator*() const
{
	return (*m_node).val;
}

template<class T>
bool ListIterator<T>::operator==(const self& x) const
{
	return m_node == x.m_node;
}

template<class T>
bool ListIterator<T>::operator!=(const self& x) const
{
	return m_node != x.m_node;
}



#endif // KTINYSTL_KLIST_H


