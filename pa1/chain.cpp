#include "chain.h"
#include "chain_given.cpp"

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
	clear();
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata)
{

	if (empty()) {
		Node * newNode = new Node(ndata);
		newNode->prev = head_;
		head_->next = newNode;

		newNode->next = tail_;
		tail_->prev = newNode;
		length_ = 1;
		return;
	}

	if (!empty()) {
		// get the size of list  -> int size();

		// the last node before using this function
		Node* lastNode = tail_->prev;

		// make insert node of the data
		Node* newNode = new Node(ndata);

		// new node prev, next
		newNode->prev = lastNode;
		newNode->next = tail_;

		// tail prev
		tail_->prev = newNode;

		// make the last node next to new Node
		lastNode->next = newNode;

		length_ = length_ + 1;
		return;
	}

}

/**
 * Modifies the Chain by moving a contiguous subset of len Nodes
 * dist nodes toward the end of the chain beginning from startPos
 * (maintaining the sentinel at the end). Their order is
 * not changed in the move. You may assume that the startPos and
 * len parameters are kind: startPos + len -1 <= length. If there
 * are not enough nodes to shift by dist, just shift as many as
 * possible.
 */
void Chain::moveBack(int startPos, int len, int dist)
{

	// base case 0: no element
	if (empty()) {
		return;
	}
	// base case 1: 1 element
	if (length_ == 1) {
		return;
	}
	// base case 2: 0 distance
	if (dist == 0) {
		return;
	}
	// base case 3: more than 1 element;
	if (length_ > 1) {
		Node* front = walk(head_, startPos);
		Node* rear = walk(front, len - 1);

		// front connection
		Node* frontPrev = front->prev;

		// rear connection
		Node* rearNext = rear->next;

		// merge front and rear connection;
		frontPrev->next = rearNext;
		rearNext->prev = frontPrev;

		int rearPos = startPos + len - 1;

		// distance is too big check
		if (rearPos + dist > length_) {
			dist = length_ - rearPos;
		}
		// get new nodes
		Node* newFront = walk(rear, dist);
		Node* newRear = newFront->next;

		// switch
		front->prev = newFront;
		newFront->next = front;
		rear->next = newRear;
		newRear->prev = rear;
	}
}

/**
 * Rolls the current Chain by k nodes: removes the last
 * k nodes from the Chain and attaches them, in order, at
 * the start of the chain (maintaining the sentinel at the front).
 */
void Chain::roll(int k)
{

	// base case 0: no element
	if (empty()) {
		return;
	}
	// base case 1: 1 element
	if (length_ == 1) {
		return;
	}
	// base case 2: k bigger than or equal to length
	if (k >= length_) {
		return;
	}
	// base case 3: k = 1
	if (k == 1) {
		Node* curr = tail_->prev;
		Node* newLast = curr->prev;
		Node* oldFront = head_->next;

		// curr in the front
		head_->next = curr;
		curr->prev = head_;
		curr->next = oldFront;
		oldFront->prev = curr;

		// newLast
		newLast->next = tail_;
		tail_->prev = newLast;
		return;
	}

	// base case 4 : k > 1
	if (k > 1) {
		// rear
		Node* rearFront = walk(head_, length_ - k + 1);
		Node* rearLast = walk(rearFront, k - 1);
		Node* newLast = rearFront->prev;

		// Front
		Node* oldFront = head_->next;

		// put in the front
		head_->next = rearFront;
		rearFront->prev = head_;
		rearLast->next = oldFront;
		oldFront->prev = rearLast;

		// newLast
		newLast->next = tail_;
		tail_->prev = newLast;
		return;
	}

}


/**
 * Modifies the current chain by reversing the subchain
 * between pos1 and pos2, inclusive. The positions are
 * 1-based. You may assume that pos1 and pos2 are valid
 * locations in the Chain, and that pos2 >= pos1.
 */
void Chain::reverseSub(int pos1, int pos2)
{
	// base case 0: no element
	if (empty()) {
		return;
	}
	// base case 1: pos1 is larger pos2, or pos2 larger than the length
	if (pos1 > pos2 || pos2 > length_) {
		return;
	}
	// base case 2: 1 element in the list
	if (length_ == 1) {
		return;
	}
	// base case 3: pos2 right after pos1
	if (pos1 + 1 == pos2) {
		Node* node1 = walk(head_, pos1);
		Node* node2 = walk(node1, 1);

		Node* node1prev = node1->prev;
		Node* node2next = node2->next;

		node1prev->next = node2;
		node2->prev = node1prev;
		node2->next = node1;

		node2next->prev = node1;
		node1->prev = node2;
		node1->next = node2next;
		return;
	}

	// base case 4: pos2 2 after pos1
	if (pos1 + 2 == pos2) {
		Node* node1 = walk(head_, pos1);
		Node* node2 = walk(head_, pos2);

		Node* node1prev = node1->prev;
		Node* middle = node1->next;
		Node* node2next = node2->next;

		node1prev->next = node2;
		node2->prev = node1prev;
		node2->next = middle;
		middle->prev = node2;
		middle->next = node1;
		node1->prev = middle;
		node1->next = node2next;
		node2next->prev = node1;
		return;
	}

	// base case 5: 
	if (pos1 + 3 <= pos2) {
		Node* node1 = walk(head_, pos1);
		Node* node2 = walk(head_, pos2);
		Node* node1prev = node1->prev;
		Node* node1next = node1->next;

		Node* node2prev = node2->prev;
		Node* node2next = node2->next;

		//node 2 in the front
		node1prev->next = node2;
		node1next->prev = node2;
		node2->prev = node1prev;
		node2->next = node1next;

		//node 1 in the back
		node2prev->next = node1;
		node2next->prev = node1;
		node1->prev = node2prev;
		node1->next = node2next;


		reverseSub(pos1 + 1, pos2 - 1);
	}


}

/*
* Modifies both the current and input chains by removing
* nodes from other, and interleaving them between the Nodes
* from the current Chain. The nodes from the other Chain
* should occupy the even locations in the result. length
* of the resulting chain should be the sums of the lengths
* of current and the other. The other chain should have only
* two sentinels and no data nodes at the end of the operation.
* the weave fails and the original
* chains should be unchanged if block sizes are different.
* in that case, the result of the function should be:
* cout << "Block sizes differ." << endl;
*/
void Chain::weave(Chain & other)
{
	// leaves other empty.
	// base case 0 : both chains empty
	if (empty() && other.empty()) {
		return;
	}
	// base case 1 : other chain is empty
	if (other.empty()) {
		return;
	}

	// base case 2: this chain is empty
	if (empty()) {
		head_->next = other.head_->next;
		tail_->prev = other.tail_->prev;
		clearWeave(other);
	}

	// base case : block sizes differ
	if (head_->next->data.width() != other.head_->next->data.width()
		|| head_->next->data.height() != other.head_->next->data.height()) {
		cout << "Block sizes differ." << endl;
		return;
	}

	// base case 3: same size
	if (size() == other.size()) {
		Node * curr = head_->next;
		Node * otherCurr = other.head_->next;
		Node * afterNew = curr->next;

		while (afterNew != tail_) { //
			Node * newNode = otherCurr;
			otherCurr = otherCurr->next;
			curr->next = newNode;
			newNode->prev = curr;
			newNode->next = afterNew;
			afterNew->prev = newNode;

			curr = afterNew;
			afterNew = curr->next;
		} //if afterNew is the tail, it's finished

		Node * newNode = otherCurr;
		curr->next = newNode;
		newNode->prev = curr;
		newNode->next = afterNew;
		afterNew->prev = newNode;

		length_ = length_ + other.size();
		clearWeave(other);
		return;
	}

	// base case 4: this is larger
	if (size() > other.size()) {
		Node * curr = head_->next;
		Node * otherCurr = other.head_->next;
		Node * afterNew = curr->next;

		while (otherCurr != other.tail_) {//
			Node * newNode = otherCurr;
			otherCurr = otherCurr->next;
			curr->next = newNode;
			newNode->prev = curr;
			newNode->next = afterNew;
			afterNew->prev = newNode;

			curr = afterNew;
			afterNew = curr->next;
		}

		//otherCurr is other tail
		//weave finished
		length_ = length_ + other.size();
		clearWeave(other);
		return;
	}

	// base case 5 : other is larger
	if (size() < other.size()) {
		Node * curr = head_->next;
		Node * otherCurr = other.head_->next;
		Node * afterNew = curr->next;

		while (afterNew != tail_) {//
			Node * newNode = otherCurr;
			otherCurr = otherCurr->next;
			curr->next = newNode;
			newNode->prev = curr;
			newNode->next = afterNew;
			afterNew->prev = newNode;

			curr = afterNew;
			afterNew = curr->next;
		}
		// curr is the last node in this chain
		// afterNew is this tail
		// copy the other chain
		otherCurr->prev = curr;
		curr->next = otherCurr;

		otherCurr = other.tail_->prev;
		otherCurr->next = tail_; // afterNew = tail
		tail_->prev = otherCurr;

		//weave finished
		length_ = length_ + other.size();
		clearWeave(other);
		return;
	}



}


void Chain::clearWeave(Chain & other)
{
	other.head_->next = other.tail_;
	other.tail_->prev = other.head_;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear()
{

	if (empty()) {
		delete head_;
		delete tail_;
		head_ = NULL;
		tail_ = NULL;
		return;
	}


	if (!empty()) {
		Node * curr = head_->next;
		Node * temp;
		while (curr->next != NULL) {
			temp = curr;
			curr = curr->next;
			delete temp;
		}


		delete head_;
		delete curr;
		//tail will be deleted
			// after curr deletes the last node and 
			// points to tail
	}

}


/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const& other)
{


	// Base case1: no list
	if (other.head_ == NULL) {
		return;
	}

	// Base case2: empty list
	if (other.empty()) {
		length_ = other.length_;
		height_ = other.height_;
		width_ = other.width_;

		head_ = new Node();
		tail_ = new Node();
		head_->next = tail_;
		tail_->prev = head_;

		return;
	}

	// Base Case3: 1 node in the list
	if (other.size() == 1) {
		length_ = other.length_;
		height_ = other.height_;
		width_ = other.width_;


		head_ = new Node();
		tail_ = new Node();

		Node* tempMiddle = other.head_->next;

		Node* middle = new Node(tempMiddle->data);

		head_->next = middle;
		middle->prev = head_;
		middle->next = tail_;
		tail_->prev = middle;

		return;
	}


	// Base Case4: more than 1 node in the list
	if (other.size() > 1) {
		length_ = other.length_;
		height_ = other.height_;
		width_ = other.width_;

		head_ = new Node();
		tail_ = new Node();

		Node * curr, *otherCurr, *temp;

		//----

		//----
		otherCurr = other.head_->next;
		curr = new Node(otherCurr->data);
		head_->next = curr;
		curr->prev = head_;


		temp = curr; // holds the previous curr
		while (otherCurr->next != other.tail_) { // when otherCurr becomes other.tail, it's finished
			otherCurr = otherCurr->next;
			curr = new Node(otherCurr->data);
			temp->next = curr;
			curr->prev = temp;
			temp = curr;
		}


		curr->next = tail_;
		tail_->prev = curr;

		return;




	}

}

