#pragma once
#include"Tree.h"


class BiTreeApplication {
public:
	
	//---------CONSTRUCTORS__AND__DESCTRUCTORS-------------

	BiTreeApplication();

	~BiTreeApplication();

	//----------------MAIN PROCEDURE-------------

	void init(); //initialization £¬input char code and its weight

	void constructHuffTree(); //make huffman tree depend on chars 

	void encoding(); // making huffman code and output it

	void decoding(); // input huffman code and output its char code
	
	void mainBody(); // enter main body

	//---------------OTHER FUNCTIONS-----------------

	void selectNode(int& s1, int limit, int& s2); // select the min weight node

private:

	HuffNode* huffTree; // store the huffman tree, it's a array

	int nodeCount; //start from 1, and extends to 2 * n - 1

	int maxLength; // max length of the tree

	int hasConstruct; //whether the tree has been constructeds
};

