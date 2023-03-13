#ifndef KTINYSTL_KDQUEUE_H
#define KTINYSTL_KDQUEUE_H
#include <stddef.h>

#include <iostream>
#include "kallocator.h"
#include "kdqueue.h"
#include "kinitialized.h"
#include "kalgorithm.h"

template<class T, size_t BufSize>
struct KDequeIterator {
	typedef T value_type;
	typedef KDequeIterator<T, BufSize> iterator;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef pointer* map_pointer;
	typedef KDequeIterator self;
	typedef KDequeIterator<T, BufSize> iterator;

	pointer m_cur;
	pointer m_first;
	pointer m_last;
	map_pointer m_node;

	KDequeIterator();
	static size_t buffer_size();
	void setNode(map_pointer newNode);
	difference_type operator-(const self& x)const;
	reference operator*()const;
	pointer operator->()const;
	self& operator++();
	self& operator++(int);
	self& operator--();
	self& operator--(int);
	self& operator+=(difference_type n);
	self& operator-=(difference_type n);
	self& operator+(difference_type n);
	self& operator-(difference_type n);
	reference operator[](int n);
	bool operator==(const self& x)const;
	bool operator!=(const self& x)const;
	bool operator<(const self& x)const;

};



template<class T, size_t BufSize = 0>
class KDQueue {

public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef KDequeIterator<T, BufSize> iterator;
	typedef ktinystl::Allocator<T> data_allocator;
	typedef ktinystl::Allocator<T*> map_allocator;

protected:
	//TODO map_allocator
	//TODO data_allocator
	typedef pointer* map_pointer;

	map_pointer m_map;
	size_type m_size;
	iterator m_start;
	iterator m_finish;

public:

	KDQueue();
	KDQueue(int n, const value_type& value);
	~KDQueue();
	iterator begin();
	iterator end();
	reference operator[](size_type n);
	reference front();
	reference back();
	size_type size()const;
	bool empty()const;

	void push_front(const value_type& t);
	void push_back(const value_type& t);
	void pop_back();
	void pop_front();
	iterator erase(iterator pos);
	iterator insert(iterator position, const value_type& x);
	void clear();


private:
	void createMapAndNodes(size_type numsElements);
	void fill_initialize(size_type n, const value_type& value);
	void push_back_aux(const value_type& t);
	void push_front_aux(const value_type& t);
	void reserve_map_at_back(size_type nodes_to_add = 1);
	void reserve_map_at_front(size_type nodes_to_add = 1);
	void reallocate_map(size_type nodes_to_add, bool add_at_front);
	iterator insert_aux(iterator pos, const value_type& x);
	size_t buffer_size();
};

template<class T, size_t BufSize>
KDQueue<T, BufSize>::KDQueue()
	: m_start()
	, m_finish()
	, m_map(nullptr)
	, m_size(0)
{
	fill_initialize(0, 0);
}

template<class T, size_t BufSize>
KDQueue<T, BufSize>::KDQueue(int n, const value_type& value)
	: m_start()
	, m_finish()
	, m_map(nullptr)
	, m_size(0)
{
	fill_initialize(n, value);
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::createMapAndNodes(size_type numsElements)
{
	size_type numNodes = numsElements / buffer_size() + 1;
	m_size = 8 > numNodes + 2 ? 8 : numNodes + 2;

	m_map = map_allocator::allocate(m_size);
	map_pointer nstart = m_map + (m_size - numNodes) / 2;
	map_pointer nfinish = nstart + numNodes - 1;

	map_pointer cur;
	for (cur = nstart; cur <= nfinish; ++cur)
	{
		*cur = data_allocator::allocate(buffer_size());
	}

	m_start.setNode(nstart);
	m_finish.setNode(nfinish);
	m_start.m_cur = m_start.m_first;
	m_start.m_last = m_start.m_first + buffer_size();
	m_finish.m_cur = m_finish.m_first + numsElements % buffer_size();
	m_finish.m_last = m_finish.m_first + buffer_size();
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::fill_initialize(size_type n, const value_type& value)
{
	createMapAndNodes(n);
	map_pointer cur;
	for (cur = m_start.m_node; cur < m_finish.m_node; cur++)
	{
		uninitialized_fill(*cur, *cur+buffer_size(), value);
	}
	uninitialized_fill(m_finish.m_first, m_finish.m_cur, value);
}


template<class T, size_t BufSize>
KDQueue<T, BufSize>::~KDQueue()
{
	clear();
	data_allocator::deallocate(*(m_start.m_node));
	map_allocator::deallocate(m_map);
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::clear()
{
	for (auto node = m_start.m_node + 1; node < m_finish.m_node; ++node)
	{
		data_allocator::destroy(*node, *node + buffer_size());
		data_allocator::deallocate(*node);
	}
	if (m_start.m_node != m_finish.m_node)
	{ // 有两个以上的缓冲区
		data_allocator::destroy(m_start.m_cur, m_start.m_last);
		data_allocator::destroy(m_finish.m_first, m_finish.m_cur);
		data_allocator::deallocate(m_finish.m_first);
	}
	else
	{
		data_allocator::destroy(m_start.m_cur, m_finish.m_cur);
	}
	m_finish = m_start;
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::iterator KDQueue<T, BufSize>::begin()
{
	return m_start;
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::iterator KDQueue<T, BufSize>::end()
{
	return m_finish;
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::reference KDQueue<T, BufSize>::operator[](size_type n)
{
	return m_start[difference_type(n)];
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::reference KDQueue<T, BufSize>::front()
{
	return *m_start;
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::reference KDQueue<T, BufSize>::back()
{
	iterator tmp = m_finish;
	--tmp;
	return *tmp;

}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::size_type KDQueue<T, BufSize>::size() const
{
	return m_finish - m_start;
}

template<class T, size_t BufSize>
bool KDQueue<T, BufSize>::empty() const
{
	return m_finish == m_start;
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::push_front(const value_type& t)
{
	if (m_start.m_cur != m_start.m_first)
	{
		data_allocator::construct(m_start.m_cur - 1, t);
		--m_start.m_cur;
	}
	else
	{
		push_front_aux(t);
	}
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::push_back(const value_type& t)
{
	if (m_finish.m_cur != m_finish.m_last - 1)
	{
		data_allocator::construct(m_finish.m_cur, t);
		++m_finish.m_cur;
	}
	else
	{
		push_back_aux(t);
	}
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::push_back_aux(const value_type& t)
{
	reserve_map_at_back();
	*(m_finish.m_node + 1) = data_allocator::allocate(buffer_size());
	data_allocator::construct(m_finish.m_cur, t);
	m_finish.setNode(m_finish.m_node + 1);
	m_finish.m_cur = m_finish.m_first;
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::push_front_aux(const value_type& t)
{
	reserve_map_at_front();
	*(m_start.m_node - 1) = data_allocator::allocate(buffer_size());
	m_start.setNode(m_start.m_node - 1);
	m_start.m_cur = m_start.m_last - 1;
	data_allocator::construct(m_start.m_cur, t);
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::reserve_map_at_back(size_type nodes_to_add)
{
	
	if (nodes_to_add + 1 > m_size - (m_finish - m_start))
	{
		reallocate_map(nodes_to_add, false);
	}
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::reserve_map_at_front(size_type nodes_to_add)
{
	if (nodes_to_add > m_start.m_node - m_map)
	{
		reallocate_map(nodes_to_add, true);
	}
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front)
{
	size_type oldNumNodes = m_finish.m_node - m_start.m_node + 1;
	size_type newNumNodes = oldNumNodes * 2;
	size_type newMapSize = m_size + newNumNodes + 2;
	map_pointer newMap = map_allocator::allocate(newMapSize);
	map_pointer newStart = newMap + (newMapSize - newNumNodes) / 2 + (add_at_front ? nodes_to_add : 0);
	map_pointer newFinish = newStart + newNumNodes - 1;
	uninitialized_move(m_start.m_node, m_finish.m_node, newStart);
	map_allocator::deallocate(m_map, m_size);
	m_start.setNode(newStart);
	m_finish.setNode(newFinish);
	m_size = newMapSize;
	m_map = newMap;
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::pop_back()
{
	if (m_finish.m_cur == m_finish.m_first)
	{
		auto tmp = m_finish.m_node - 1;
		data_allocator::destroy(m_finish.m_first);
		data_allocator::deallocate(m_finish.m_first);
		m_finish.setNode(tmp);
		m_finish.m_cur = m_finish.m_last - 1;
		data_allocator::destroy(m_finish.m_cur);
	}
	else
	{
		--m_finish.m_cur;
		data_allocator::destroy(m_finish.m_cur);
	}
}

template<class T, size_t BufSize>
void KDQueue<T, BufSize>::pop_front()
{
	if (m_start.m_cur == m_start.m_last - 1)
	{
		map_pointer tmp = m_start.m_node + 1;
		data_allocator::destroy(m_start.m_cur);
		data_allocator::destroy(m_start.m_first);
		m_start.setNode(tmp);
		m_start.m_cur = m_start.m_first;
	}
	else
	{
		data_allocator::destroy(m_start.m_cur);
		++m_start.m_cur;
	}
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::iterator KDQueue<T, BufSize>::erase(iterator pos)
{
	iterator next = pos;
	++next;
	difference_type index = pos - m_start;
	if (index < (size() >> 1))
	{
		ktinystl::copy_backward(m_start, pos, next);
		pop_front();
	}
	else
	{
		ktinystl::copy(next, m_finish, pos);
		pop_back();
	}
	return m_start + index;
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::iterator KDQueue<T, BufSize>::insert(iterator position, const value_type& x)
{
	if (position.m_cur == m_start.m_cur)
	{
		push_front(x);
		return m_start;
	}
	else if (position.m_cur == m_finish.m_cur)
	{
		push_back(x);
		iterator tmp = m_finish;
		--tmp;
		return tmp;
	}
	else
	{
		return insert_aux(position, x);
	}
}

template<class T, size_t BufSize>
typename KDQueue<T, BufSize>::iterator KDQueue<T, BufSize>::insert_aux(iterator pos, const value_type& x)
{
	size_type index = pos - m_start;
	if (index < (size() / 2))
	{
		push_front(front());
		iterator front1 = m_start;
		++front1;
		iterator front2 = front1;
		++front2;
		pos = m_start + index;
		iterator pos1 = pos;
		++pos1;
		ktinystl::copy(front2, pos1, front1);
	}
	else
	{
		push_back(back());
		iterator back1 = m_finish;
		--back1;
		iterator back2 = back1;
		--back2;
		pos = m_start + index;
		ktinystl::copy_backward(pos, back2, back1);
	}
	*pos = x;
	return pos;
}

template<class T, size_t BufSize>
size_t KDQueue<T, BufSize>::buffer_size()
{
	return sizeof(T) < 256 ? 4096 / sizeof(T) : 16;
}







template<class T, size_t BufSize>
KDequeIterator<T, BufSize>::KDequeIterator()
{
	
}

//Iterator
template<class T, size_t BufSize>
size_t KDequeIterator<T, BufSize>::buffer_size()
{
	return sizeof(T) < 256 ? 4096 / sizeof(T) : 16;
}

template<class T, size_t BufSize>
void KDequeIterator<T, BufSize>::setNode(map_pointer newNode)
{
	m_node = newNode;
	m_first = *newNode;
	m_last = m_first + size_type(buffer_size());
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::difference_type KDequeIterator<T, BufSize>::operator-(const self& x) const
{
	return difference_type(buffer_size()) * (m_node - x.m_node - 1) + (m_cur - m_first)
		+ (x.m_last - x.m_cur);
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::reference KDequeIterator<T, BufSize>::operator*() const
{
	return *m_cur;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::pointer KDequeIterator<T, BufSize>::operator->() const
{
	return m_cur;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator++()
{
	++m_cur;
	if (m_cur == m_last)
	{
		setNode(m_node + 1);
		m_cur = m_first;
	}
	return *this;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator++(int)
{
	auto tmp = *this;
	++* this;
	return tmp;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator--()
{
	if (m_cur == m_first)
	{
		setNode(m_node - 1);
		m_cur = m_last;
	}
	--m_cur;
	return *this;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator--(int)
{
	auto tmp = *this;
	--* this;
	return tmp;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator+=(difference_type n)
{
	difference_type offset = n + m_cur - m_first;
	if (offset >= 0 && offset < difference_type(buffer_size()))
	{
		m_cur += n;
	}
	else
	{
		difference_type nodeOffset = offset > 0 ? offset / difference_type(buffer_size()) :
			-difference_type((-offset - 1) / buffer_size()) - 1;
		setNode(m_node + nodeOffset);
		m_cur = m_first + (offset - nodeOffset * difference_type(buffer_size()));
	}
	return *this;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator-=(difference_type n)
{
	return *this += -n;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator+(difference_type n)
{
	self tmp = *this;
	return tmp += n;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::self& KDequeIterator<T, BufSize>::operator-(difference_type n)
{
	self tmp = *this;
	return tmp -= n;
}

template<class T, size_t BufSize>
typename KDequeIterator<T, BufSize>::reference KDequeIterator<T, BufSize>::operator[](int n)
{
	return *(*this + n);
}

template<class T, size_t BufSize>
bool KDequeIterator<T, BufSize>::operator==(const self& x) const
{
	return m_cur == x.m_cur;
}

template<class T, size_t BufSize>
bool KDequeIterator<T, BufSize>::operator!=(const self& x) const
{
	return !(*this == x);
}

template<class T, size_t BufSize>
bool KDequeIterator<T, BufSize>::operator<(const self& x) const
{
	return (m_node == x.m_node) ? (m_cur < x.m_cur) : (m_node < x.m_node);
}



#endif // !KTINYSTL_KDQUEUE_H

