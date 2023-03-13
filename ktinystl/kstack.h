#ifndef KTINYSTL_KSTACK_H
#define KTINYSTL_KSTACK_H 

#include"KDQueue.h"

template<class T,class Sequence = KDQueue<T>>
class KStack {

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
	reference top();
	const reference top()const;
	void push(const value_type& x);
	void pop();
	bool operator==(const KStack<T, Sequence>& x);
	bool operator<(const KStack<T, Sequence>& x);

};

template<class T, class Sequence /*= KDQueue<T>*/>
bool KStack<T, Sequence>::operator<(const KStack<T, Sequence>& x)
{
	return this->m_deq < x.m_deq;
}

template<class T, class Sequence /*= KDQueue<T>*/>
bool KStack<T, Sequence>::operator==(const KStack<T, Sequence>& x)
{
	return this->m_deq == x.m_deq;
}

template<class T, class Sequence /*= KDQueue<T>*/>
void KStack<T, Sequence>::pop()
{
	m_deq.pop_back();
}

template<class T, class Sequence /*= KDQueue<T>*/>
void KStack<T, Sequence>::push(const value_type& x)
{
	m_deq.push_back(x);
}

template<class T, class Sequence /*= KDQueue<T>*/>
const typename KStack<T, Sequence>::reference KStack<T, Sequence>::top() const
{
	return m_deq.back();
}

template<class T, class Sequence /*= KDQueue<T>*/>
typename KStack<T, Sequence>::reference KStack<T, Sequence>::top()
{
	return m_deq.back();
}

template<class T, class Sequence /*= KDQueue<T>*/>
typename KStack<T, Sequence>::size_type KStack<T, Sequence>::size() const
{
	return m_deq.size();
}

template<class T, class Sequence /*= KDQueue<T>*/>
bool KStack<T, Sequence>::empty() const
{
	return m_deq.empty();
}

#endif // KTINYSTL_KSTACK_H
