#ifndef KTINYSTL_ALLOCATOR_H
#define KTINYSTL_ALLOCATOR_H


namespace ktinystl {

	template<class T>
	class Allocator
	{
	public:
		typedef		T						value_type;
		typedef		value_type*				iterator;
		typedef		value_type*				pointer;
		typedef		const value_type&		const_reference;
		typedef		const value_type*		const_pointer;
		typedef		value_type&				reference;
		typedef		size_t					size_type;
		typedef		ptrdiff_t				difference_type;

	public:

		static pointer allocate();
		static pointer allocate(size_type n);

		static void deallocate(pointer p);
		static void deallocate(pointer p, size_type n);

		static void construct(T* ptr, const T& value);
		static void construct(T* ptr);

		static void destroy(T* ptr);
		static void destroy(T* first, T* last);

	};


	template<class T>
	typename Allocator<T>::pointer Allocator<T>::allocate(size_type n)
	{
		if (n == 0)
			return nullptr;
		auto ret = static_cast<T*>(::operator new(n * sizeof(T)));
		return ret;
	}

	template <class T>
	typename Allocator<T>::pointer Allocator<T>::allocate()
	{
		return static_cast<T*>(::operator new(sizeof(T)));
	}

	template<class T>
	void Allocator<T>::deallocate(pointer p)
	{
		::operator delete(p);
	}

	template<class T>
	void Allocator<T>::deallocate(pointer p, size_type n)
	{
		if (p == nullptr)
			return;
		::operator delete(p);
	}

	template<class T>
	void Allocator<T>::construct(T* ptr, const T& value)
	{
		new(ptr)T(value);
	}

	template<class T>
	void Allocator<T>::construct(T* ptr)
	{
		new(ptr)T();
	}

	template<class T>
	void Allocator<T>::destroy(T* ptr)
	{
		ptr->~T();
	}

	template<class T>
	void Allocator<T>::destroy(T* first, T* last)
	{
		for (; first != last; ++first)
			destroy(first);
	}




}



#endif //KTINYSTL_ALLOCATOR_H
