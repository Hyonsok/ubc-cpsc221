/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    
    return currentIdx*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    
    return currentIdx*2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
	if (currentIdx % 2 == 0) {
		return currentIdx / 2;
	}
	else {
		return (currentIdx - 1) / 2;
	}

}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    
	if (leftChild(currentIdx) >= _elems.size()) return false;
	return true;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
	size_t leftChildIdx = leftChild(currentIdx);
	size_t rightChildIdx = rightChild(currentIdx);
    
	if (rightChildIdx >= _elems.size()) return leftChildIdx;

	if (higherPriority(_elems[leftChildIdx], _elems[rightChildIdx])) return leftChildIdx;
	return rightChildIdx;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
	if (!hasAChild(currentIdx)) {
		return;
	}
	size_t maxChild = maxPriorityChild(currentIdx);
	if (!higherPriority(_elems[currentIdx], _elems[maxChild])) {
		std::swap(_elems[currentIdx], _elems[maxChild]);
		heapifyDown(maxChild);
	}
	

}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
	_elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    /// Your algorithm should use heapifyDown() so that it constructs
    /// the same heap as our test case.

	_elems.push_back(T());

	for (size_t j = 0; j < elems.size(); j++) {
		_elems.push_back(elems[j]);
	}
	for (size_t i = 1; i < _elems.size() / 2; i++) {
		heapifyDown(_elems.size() / 2 - i);
	}
   
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
	T retVal = _elems[root()];
	_elems[root()] = _elems[_elems.size() - 1];
	_elems.pop_back();
	heapifyDown(root());
    return retVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
	T retVal = _elems[root()];
	return retVal;
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);


}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    
    return _elems.size()==1;
}
