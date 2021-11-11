//Rishabh Vemparala rxv200022
//Brian Pham bap200003

#include <iostream>
#include <algorithm>
#include "BST.h"
#include "Node.h"

using namespace std;

int getHeight(Node *node){
	if (node == nullptr){ 
		return 0;
	}
	int left = getHeight(node->getLeft());
  int right = getHeight(node->getRight());
  return max(left, right) + 1;
}

int main() {
  BST tree(8);
  Node* node2 = new Node(3);
  Node* node3 = new Node(1);
  Node* node4 = new Node(6);
  Node* node5 = new Node(4);
  Node* node6 = new Node(7);
  Node* node7 = new Node(10);
  Node* node8 = new Node(14);
  Node* node9 = new Node(13);
  Node* node10 = new Node(18);
  Node* node11 = new Node(19);
  tree.add(node2);
  tree.add(node3);
  tree.add(node4);
  tree.add(node5);
  tree.add(node6);
  tree.add(node7);
  tree.add(node8);
  tree.add(node9);
  tree.add(node10);
  tree.add(node11);
  cout << getHeight(tree.getRoot()) << endl;
  cout << endl << endl;
  tree.display();
  cout << endl << endl;
  return 0;

} 