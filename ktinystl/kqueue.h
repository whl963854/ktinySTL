#ifndef KTINYSTL_KQUEUE_H
#define KTINYSTL_KQUEUE_H 

#include "kdqueue.h"

template<class T, class Sequence=KDQueue<T>>
class KQueue {

public:
	typedef T value_type;
	typedef value_type* iterator;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

protected:
	Sequence m_deq;

public:
	bool empty()const;
	size_type size()const;
	reference front();
	const reference front()const;
	reference back();
	const reference back()const;
	void push(const value_type& x);
	void pop();
	bool operator==(const KQueue<T, Sequence>& x);
	bool operator<(const KQueue<T, Sequence>& x);

};


template<class T, class Sequence /*= KDQueue<T>*/>
bool KQueue<T, Sequence>::operator<(const KQueue<T, Sequence>& x)
{
	return this->m_deq < x.m_deq;
}

template<class T, class Sequence /*= KDQueue<T>*/>
bool KQueue<T, Sequence>::operator==(const KQueue<T, Sequence>& x)
{
	return this->m_deq == x.m_deq;
}

template<class T, class Sequence /*= KDQueue<T>*/>
void KQueue<T, Sequence>::pop()
{
	m_deq.pop_front();
}

template<class T, class Sequence /*= KDQueue<T>*/>
void KQueue<T, Sequence>::push(const value_type& x)
{
	m_deq.push_back(x);
}

template<class T, class Sequence /*= KDQueue<T>*/>
const typename KQueue<T, Sequence>::reference KQueue<T, Sequence>::front() const
{
	return m_deq.front();
}

template<class T, class Sequence /*= KDQueue<T>*/>
typename KQueue<T, Sequence>::reference KQueue<T, Sequence>::front()
{
	return m_deq.front();
}

template<class T, class Sequence /*= KDQueue<T>*/>
const typename KQueue<T, Sequence>::reference KQueue<T, Sequence>::back() const
{
	return m_deq.back();
}

template<class T, class Sequence /*= KDQueue<T>*/>
typename KQueue<T, Sequence>::reference KQueue<T, Sequence>::back()
{
	return m_deq.back();
}

template<class T, class Sequence /*= KDQueue<T>*/>
typename KQueue<T, Sequence>::size_type KQueue<T, Sequence>::size() const
{
	return m_deq.size();
}

template<class T, class Sequence /*= KDQueue<T>*/>
bool KQueue<T, Sequence>::empty() const
{
	return m_deq.empty();
}

#endif // KTINYSTL_KQUEUE_H
