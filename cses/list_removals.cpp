#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> information; // stores the actual array with our data in
vector<int> results;

struct node {
	// left child manages data from left to midpoint
	// right child manages data from midpoint+1 to right
	int left, right, midpoint;
	node* left_child;
	node* right_child;
	node* parent;
	int count; // stores the number of elements in the subtree
	node(int left, int right, node* parent) : left(left), right(right), midpoint((left+right)/2), parent(parent) {
		if (left != right) {
			left_child = new node(left, midpoint, this);
			right_child = new node(midpoint+1, right, this);
			count = left_child->count + right_child->count;
		} else {
			count = 1;
		}
	}

	// this function deletes index'th element in the subtree and also removes
	// one from the count
	void del(int index) {
		// Uncomment the following line to see how it traverses the segment tree
		// cout << "left: " << left << " right: " << right << " count: " << count << " ind: " << index << endl;
		if (count < index) {
			throw std::runtime_error("Element doesn't exist");
		} else {
			count--;
			if (left == right) {
				results.push_back(information[left]);
			} else if (left_child->count > index) {
				left_child->del(index);
			} else {
				right_child->del(index - left_child->count);
			}
		}
	}
};


int main() {
	int n;
	cin >> n;
	information.resize(n);
	for (auto& i : information) cin >> i;

	node root(0, n-1, nullptr);
	for (int i = 0; i < n; i++) {
		int index;
		cin >> index;
		index--; // 1-indexed to 0-indexed
		root.del(index);
	}
	for (int i = 0; i < n; i++) {
		cout << results[i] << " \n"[i == n-1];
	}
}