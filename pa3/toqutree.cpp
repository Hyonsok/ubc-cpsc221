
/**
 *
 * toqutree (pa3)
 * significant modification of a quadtree .
 * toqutree.cpp
 * This file will be used for grading.
 *
 */

#include "toqutree.h"

toqutree::Node::Node(pair<int,int> ctr, int dim, HSLAPixel a)
	:center(ctr),dimension(dim),avg(a),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
	{}

toqutree::~toqutree(){
	clear(root);
}

toqutree::toqutree(const toqutree & other) {
	root = copy(other.root);
}


toqutree & toqutree::operator=(const toqutree & rhs){
	if (this != &rhs) {
		clear(root);
		root = copy(rhs.root);
	}
	return *this;
}

toqutree::toqutree(PNG & imIn, int k){ 

/* This constructor grabs the 2^k x 2^k sub-image centered */
/* in imIn and uses it to build a quadtree. It may assume  */
/* that imIn is large enough to contain an image of that size. */

/* your code here */
	stats newStats = stats(imIn);
	height = imIn.height();
	width = imIn.width();

	pair<int, int> rootUL;
	pair<int, int> rootLR;
	rootUL = make_pair(0, 0);
	rootLR = make_pair(imIn.width() - 1, imIn.height() - 1);
	root = buildTree()
}

int toqutree::size() {
/* your code here */
}


toqutree::Node * toqutree::buildTree(PNG * im, int k) {

/* your code here */

// Note that you will want to practice careful memory use
// In this function. We pass the dynamically allocated image
// via pointer so that it may be released after it is used .
// similarly, at each level of the tree you will want to 
// declare a dynamically allocated stats object, and free it
// once you've used it to choose a split point, and calculate
// an average.
	HSLAPixel avg = s.getAvg()

}

PNG toqutree::render(){

// My algorithm for this problem included a helper function
// that was analogous to Find in a BST, but it navigated the 
// quadtree, instead.

/* your code here */
	PNG newPNG = PNG(width, height);
	renderNode(newPNG, root);
	return newPNG;
}

void toqutree::renderNode(PNG & PNG, Node* n)
{
	if (n->LT == NULL && n->RB == NULL) {
		for (int x = n->upLeft.first; x <= n->lowRight.first; x++) {
			for (int y = n->upLeft.second; y <= n->lowRight.second; y++) {
				*PNG.getPixel(x, y) = n->avg;

			}
		}
	}
	else {
		if (n->RB != NULL) {
			renderNode(PNG, n->RB);
		}
		if (n->LT != NULL) {
			renderNode(PNG, n->LT);
		}
	}
}

/* oops, i left the implementation of this one in the file! */
void toqutree::prune(double tol){

	// I need to define this 
	//prune(root,tol);

}

/* called by destructor and assignment operator*/
void toqutree::clear(Node * & curr){
/* your code here */
	clearNode(root);
	width = 0;
	height = 0;
	root = NULL;
}

void toqutree::clearNode(Node* n)
{
	if (n != NULL) {
		clearNode(n->LT);
		clearNode(n->RB);
		n->LT = NULL;
		n->RB = NULL;
		delete n;
		n = NULL;
		return;
	}
	return;
}

/* done */
/* called by assignment operator and copy constructor */
toqutree::Node * toqutree::copy(const Node * other) {
	if (!other.root) {
		root = NULL;
		width = 0;
		height = 0;
		return;
	}
	height = other.height;
	width = other.width;
	return copyNode(root, other.root);
}

toqutree::Node * toqutree::copyNode(Node* &n, Node* oth)
{
	if (!oth) {
		n = NULL;
	}
	else {
		n = new Node(oth->upLeft, oth->lowRight, oth->avg);
		copyNode(n->LT, oth->LT);
		copyNode(n->RB, oth->RB);
	}
}


