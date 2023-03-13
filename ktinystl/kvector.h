#ifndef KTINYSTL_KVECTOR_H
#define KTINYSTL_KVECTOR_H 

#include<vector>
#include "kallocator.h"
#include "kalgorithm.h"
#include "kinitialized.h"

template<class T>
class KVector {
public:

	
	typedef		T							value_type;
	typedef		value_type*					iterator;
	typedef		value_type*					pointer;
	typedef		value_type&					reference;
	typedef		size_t						size_type;
	typedef		ptrdiff_t					difference_type;
	typedef		ktinystl::Allocator<T>		data_allocator;

protected:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;

public:
	KVector();
	KVector(size_type n);
	KVector(size_type n, const T& value);
	KVector(int n, const T& value);
	KVector(long n, const T& value);
	KVector(iterator first, iterator last);
	~KVector();


	iterator begin();
	iterator end();

	size_type size() const;
	size_type capacity()const;
	bool empty()const;

	reference operator[](size_type n);
	reference at(size_type n);
	reference front();
	reference back();

	void push_back(const value_type& value);
	value_type  pop_back();
	iterator insert(int index, const value_type& value);
	iterator insert(iterator position, const value_type& value);
	iterator insert(iterator position, size_type n, const value_type& value);
	iterator erase(int index);
	iterator erase(iterator iter);
	iterator assign(iterator first, iterator last);
	void clear();

protected:

	void fill_initialize(size_type n, const T& value);
	iterator allocate_and_fill(size_type n, const T& x);

private:
	static const size_type FORWARD = 1;
	static const size_type BACK = -1;


	void sizeInit(size_type reSize = 1);
	void moveElement(int index, size_type direct, size_type len = 1);
};


template<class T>
KVector<T>::KVector()
	: m_start(nullptr)
	, m_finish(nullptr)
	, m_endOfStorage(nullptr)
{
}

template<class T>
KVector<T>::KVector(size_type n)
{
	fill_initialize(n, 0);
}

template<class T>
KVector<T>::KVector(size_type n, const T& value)
{
	fill_initialize(n, value);
}

template<class T>
KVector<T>::KVector(int n, const T& value)
{
	fill_initialize(n, value);
}

template<class T>
KVector<T>::KVector(long n, const T& value)
{
	fill_initialize(n, value);
}

template<class T>
KVector<T>::KVector(iterator first, iterator last)
{
	sizeInit(last - first);
	uninitialized_move(first, last, m_start);
}

template<class T>
KVector<T>::~KVector()
{
	while (m_finish != m_start)
	{
		--m_finish;
		data_allocator::destroy(m_finish);
	}
	data_allocator::deallocate(m_start);
}

template<class T>
void KVector<T>::fill_initialize(size_type n, const T& value)
{
	m_start = allocate_and_fill(n, value);
	m_finish = m_start + n;
	m_endOfStorage = m_finish;
}

template<class T>
typename KVector<T>::iterator KVector<T>::allocate_and_fill(size_type n, const T& x)
{
	iterator result = ktinystl::Allocator<T>::allocate(n);
	uninitialized_fill(result, result +n, x);
	return result;
}

template<class T>
typename KVector<T>::iterator KVector<T>::begin()
{
	return m_start;
}

template<class T>
typename KVector<T>::iterator KVector<T>::end()
{
	return m_finish;
}

template<class T>
typename KVector<T>::size_type KVector<T>::size() const
{
	return size_type(m_finish - m_start);
}

template<class T>
typename KVector<T>::size_type KVector<T>::capacity() const
{
	return size_type(m_endOfStorage - m_start);
}

template<class T>
typename KVector<T>::reference KVector<T>::operator[](size_type n)
{
	return *(begin() + n);
}

template<class T>
typename KVector<T>::reference KVector<T>::at(size_type n)
{
	return this->operator [](n);
}

template<class T>
typename KVector<T>::reference KVector<T>::front()
{
	return *begin();
}

template<class T>
typename KVector<T>::reference KVector<T>::back()
{
	return *(end() - 1);
}

template<class T>
bool KVector<T>::empty() const
{
	return begin() == end();
}

template<class T>
void KVector<T>::push_back(const value_type& value)
{
	if (m_endOfStorage == m_finish)
		sizeInit();
	data_allocator::construct(m_finish, value);
	++m_finish;
}

template<class T>
typename KVector<T>::value_type KVector<T>::pop_back()
{
	data_allocator::destroy(m_finish);
	return *(m_finish--);
}

template<class T>
typename KVector<T>::iterator KVector<T>::insert(int index, const value_type& value)
{
	if (size() == capacity())
	{
		sizeInit();
	}
	if (index == size())
	{
		push_back(value);
		return m_finish;
	}
	moveElement(index, KVector::FORWARD, 1);
	*(m_start + index) = value;
	return (m_start + index);
}

template<class T>
typename KVector<T>::iterator KVector<T>::insert(iterator position, const value_type& value)
{
	return insert(position, 1, value);
}

template<class T>
typename KVector<T>::iterator KVector<T>::insert(iterator position, size_type n, const value_type& value)
{
	int index = position - m_start;
	if (size() + n > capacity())
	{
		sizeInit(size() + n);
	}
	if (index == size())
	{
		while (n > 0) {
			push_back(value);
			n--;
		}
		return m_finish;
	}
	moveElement(index, KVector::FORWARD, n);
	while (n > 0) {
		*(m_start + index) = value;
		n--;
	}
	return position;
}


template<class T>
typename KVector<T>::iterator  KVector<T>::erase(int index)
{
	return erase(m_start + index);
}

template<class T>
typename KVector<T>::iterator KVector<T>::erase(iterator iter)
{
	ktinystl::copy(iter + 1, end(), iter);
	return iter;
}

template<class T>
typename KVector<T>::iterator KVector<T>::assign(iterator first, iterator last)
{
	clear();
	if (last - first > capacity())
	{
		sizeInit(last - first);
	}
	uninitialized_move(first, last, m_start);
	return m_start;
}

template<class T>
void KVector<T>::clear()
{
	while (m_finish != m_start)
	{
		--m_finish;
		data_allocator::destroy(m_finish);
	}
	data_allocator::destroy(m_start);
}

template<class T>
void KVector<T>::sizeInit(size_type reSize)
{
	const size_type oldSize = size();
	size_type newSize = 2 * oldSize;
	newSize = newSize > reSize ? newSize : reSize;
	iterator newStart = data_allocator::allocate(newSize);
	iterator newFinish = newStart + oldSize;
	uninitialized_move(m_start, m_finish, newStart);
	data_allocator::deallocate(m_start);
	m_start = newStart;
	m_finish = newStart + oldSize;
	m_endOfStorage = newStart + newSize;
	uninitialized_fill(m_finish, m_endOfStorage, 0);
}

template<class T>
void KVector<T>::moveElement(int index, size_type direct, size_type len)
{
	int oldSize = size() - 1;
	if (direct == KVector::FORWARD)
	{
		while (oldSize >= index)
		{
			*(m_start + oldSize + len) = *(m_start + oldSize);
			oldSize--;
		}
		m_finish = m_finish + len;
	}
	else if (direct == KVector::BACK)
	{
		while (index + len < oldSize)
		{
			*(m_start + index) = *(m_start + index + len);
			index++;
		}
		m_finish = m_finish - len;
	}
}

#endif // KTINYSTL_KVECTOR_H


