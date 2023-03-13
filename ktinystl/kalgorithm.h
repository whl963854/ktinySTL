#ifndef KTINY_KALGORITHM_H
#define KTINY_KALGORITHM_H


namespace ktinystl {

	template<class InputIter, class OutputIter>
	OutputIter copy(InputIter first, InputIter last, OutputIter result)
	{
		while (first != last) {
			*result = *first;
			++result; ++first;
		}
		return result;
	}

	template<class InputIter, class OutputIter>
	OutputIter copy_backward(InputIter first, InputIter last, OutputIter result)
	{
		while (last != first) *(--result) = *(--last);
		return result;
	}

	template<class RandomAccessIter, class T>
	void unguardLinearInsert(RandomAccessIter last, T value)
	{
		RandomAccessIter next = last;
		--next;
		auto ptr = (RandomAccessIter)(&value);
		while (*ptr < *next)
		{
			*last = *next;
			last = next;
			--next;
		}
		*last = *ptr;
	}

	template<class RandomAccessIter, class T>
	void linearInsert(RandomAccessIter first, RandomAccessIter last, T value)
	{
		auto val = *last;
		if (val < *first)
		{
			copy_backward(first, last, last + 1);
			*first = val;
		}
		else
			unguardLinearInsert(last, value);
	}

	template<class RandomAccessIter>
	void insertionSort(RandomAccessIter first, RandomAccessIter last)
	{
		if (first == last)
			return;
		for (auto i = first + 1; i != last; i++)
		{
			linearInsert(first, i, *first);
		}
	}

	template<class T>
	const T& median(const T& a, const T& b, const T& c)
	{
		if (a <= b&&b<=c|| c <= b && b <= a)
		{
			return b;
		}
		if (a <= b && c <= a|| a <= c && b <= a)
		{
			return a;
		}
		if (a <= c && c <= b || b <= c && c <= a)
		{
			return c;
		}
	}

	template<class RandomAccessIter,class T>
	RandomAccessIter partition(RandomAccessIter first, RandomAccessIter last, T pivot)
	{
		while (true)
		{
			while (*first < pivot)
				++first;
			--last;
			while (pivot < *last)
				--last;
			if (!(first < last))
				return first;
			auto temp = *first;
			*first = *last;
			*last = temp;
			++first;
		}
	}

	template<class RandomAccessIter>
	void unguardInsertionSort(RandomAccessIter first, RandomAccessIter last)
	{
		for (auto i = first + 1; i != last; i++)
		{
			linearInsert(first, i, first);
		}
	}

	template<class RandomAccessIter>
	void finalInsertSort(RandomAccessIter first, RandomAccessIter last)
	{
		if (last - first > 16)
		{
			insertionSort(first, first + 16);
			unguardInsertionSort(first + 16, last);
		}
		else
		{
			insertionSort(first,last);
		}
	}

	template<class RandomAccessIter>
	void quickSortLoop(RandomAccessIter first, RandomAccessIter last)
	{
		while (last - first > 16)
		{
			auto mid = median(*first, *((last - first) / 2 +first), *(last - 1));
			RandomAccessIter cut = partition(first, last, mid);
			if (cut - first >= last - cut)
			{
				quickSortLoop(cut, last);
				last = cut;
			}
			else
			{
				quickSortLoop(first, cut);
				first = cut;
			}
		}
	}

	template<class RandomAccessIter>
	void sort(RandomAccessIter first, RandomAccessIter last)
	{
		if (!(first == last))
		{
			quickSortLoop(first, last);
			finalInsertSort(first, last);
		}
	}
	
	template <class InputIter, class T>
	InputIter find(InputIter first, InputIter last, const T& value)
	{
		while (first != last && *first != value)
			++first;
		return first;
	}

	template <class InputIter1, class InputIter2>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
				return false;
		}
		return true;
	}

}





#endif //KTINY_KALGORITHM_H