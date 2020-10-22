template <class ForwardIterator1, class ForwardIterator2, class Predicate>
bool sequence_contains(ForwardIterator1 first1, ForwardIterator1 last1,
	ForwardIterator2 first2, ForwardIterator2 last2,
	Predicate pred) {
	while (first1 != last1 && first2 != last2) {
		if (pred(*first1, *first2)) {
			first1++;
		}
		else if (pred(*first2, first1*)) {
			return false;
		}
		else {
			first1++;
			first2++;
		}
	}
	return first1 == last1 ? true : false;
}