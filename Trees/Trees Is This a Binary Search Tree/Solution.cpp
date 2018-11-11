//URL for problem:
//https://www.hackerrank.com/challenges/ctci-is-binary-search-tree/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=trees

//Solved by doing an inorder traversal and checking if the values were sorted in ascending order. time complexity is theta(n) 

bool checkBST(Node* root) {
	static int val = -1; //value of previous node during inorder traversal. Initialized to -1
											 //since the range for data values is 0 <= data <= 10^4
	if (root == NULL) return true;
	if (!(checkBST(root->left))) return false;
	if (root->data <= val) return false; //if current node is <= to previous node value during                                             
																			 //inorder traversal, then the tree is not a bst
	val = root->data;
	if (!(checkBST(root->right))) return false;
	return true;
}