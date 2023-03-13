#ifndef KTINYSTL_UNINITIALIZED_H
#define KTINYSTL_UNINITIALIZED_H

template<class ForwardIter, class T>
void uninitialized_fill(ForwardIter first, ForwardIter last, const T& value)
{
	for (; first != last; ++first)
		::new (static_cast<void*>(first)) T(value);
}

template<class InputIter, class ForwardIter>
ForwardIter uninitialized_move(InputIter first, InputIter last, ForwardIter result)
{
	using T = typename std::iterator_traits<ForwardIter>::value_type;
	for (; first != last; ++first,  ++result) {
		::new (static_cast<void*>(result)) T(std::move(*first));
	}
	return result;

}

template<class InputIter, class ForwardIter>
ForwardIter uninitialized_copy(InputIter first, InputIter last, ForwardIter result)
{
	using T = typename std::iterator_traits<ForwardIter>::value_type;
	for (; first != last; ++first, ++result) {
		::new (static_cast<void*>(result)) T(*first);
	}
	return result;
}

//template<class InputIter, class Size, class ForwardIter>
//ForwardIter uninitialized_copy_n(InputIter first, Size count, ForwardIter result)
//{
//	for (; count > 0; ++first, ++result, --count) {
//		::new (static_cast<void*>(result)) T(*first);
//	}
//	return result;
//}



#endif //KTINYSTL_UNINITIALIZED_H
