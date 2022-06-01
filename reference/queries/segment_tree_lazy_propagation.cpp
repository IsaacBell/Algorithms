/*
  Given an array A of N integers, support two operations on any range A[a..b] (0<=a<=b<N):

  - replace each A[i] (a<=i<=b) by floor(sqrt(A[i]))
  - find sum A[a]+…+A[b]

  SegmentTree<ll,bool,ll> st(A, N);
  ...
  while (q--) {
    scanf("%d %d %d", &i, &x, &y);
    if (i == 1)
      st.update(min(x,y)-1, max(x,y)-1, true);
    else
      put(st.query(min(x,y)-1, max(x,y)-1));
  }
*/

struct SegmentTreeNode {
	int start, end; // this node is responsible for the segment [start...end]
	ll total;
	bool pendingUpdate;
	
	SegmentTreeNode() : total(0), pendingUpdate(false) {}
	
	void assignLeaf(ll value) {
		total = value;
	}
	
	void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
		total = left.total + right.total;
	}
	
	ll query() {
		return total;
	}
	
	// For this particular problem, propagation is not required
	// if all elements in this segment are 1's
	bool isPropagationRequired() {
		return total > end-start+1;
	}
	
	void applyPendingUpdate() {
		total = (ll) sqrt(total);
		pendingUpdate = false;
	}
	
	// For this particular problem, the value of the update is dummy
	// and is just an instruction to square root the leaf value
	void addUpdate(bool value) {
		pendingUpdate = true;
	}
	
	// returns a dummy value
	bool getPendingUpdate() {
		return true;
	}
	
	void clearPendingUpdate() {
		pendingUpdate = false;
	}
};

SegmentTreeNode nodes[300000];

template<class InputType, class UpdateType, class OutputType>
class SegmentTree {
	//SegmentTreeNode* nodes;
	int N;
	
public:
	SegmentTree(InputType arr[], int N) {
		this->N = N;
		//nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
		buildTree(arr, 1, 0, N-1);
	}
	
	~SegmentTree() {
		//delete[] nodes;
	}
	
	// get the value associated with the segment [start...end]
	OutputType query(int start, int end) {
  SegmentTreeNode result = query(1, start, end);
  return result.query();
	}
	
	// range update: update the range [start...end] by value
	// Exactly what is meant by an update is determined by the
	// problem statement and that logic is captured in segment tree node
	void update(int start, int end, UpdateType value) {
		update(1, start, end, value);
	}
	
private:
	void buildTree(InputType arr[], int stIndex, int start, int end) {
		// nodes[stIndex] is responsible for the segment [start...end]
		nodes[stIndex].start = start, nodes[stIndex].end = end;
		
		if (start == end) {
			// a leaf node is responsible for a segment containing only 1 element
			nodes[stIndex].assignLeaf(arr[start]);
			return;
		}
		
		int mid = (start + end) / 2,
			leftChildIndex = 2 * stIndex,
			rightChildIndex = leftChildIndex + 1;
			
		buildTree(arr, leftChildIndex, start, mid);
		buildTree(arr, rightChildIndex, mid + 1, end);
		nodes[stIndex].merge(nodes[leftChildIndex], nodes[rightChildIndex]);
	}
	
	int getSegmentTreeSize(int N) {
		int size = 1;
		for (; size < N; size <<= 1);
		return size << 1;
	}
	
	SegmentTreeNode query(int stIndex, int start, int end) {
		if (nodes[stIndex].start == start && nodes[stIndex].end == end)
			return nodes[stIndex];
		
		int mid = (nodes[stIndex].start + nodes[stIndex].end) >> 1,
			leftChildIndex = stIndex << 1,
			rightChildIndex = leftChildIndex + 1;			
		SegmentTreeNode result;
		
		if (start > mid) result = query(rightChildIndex, start, end);
		else if (end <= mid) result = query(leftChildIndex, start, end);
		else {
			SegmentTreeNode leftResult = query(leftChildIndex, start, mid),
							rightResult = query(rightChildIndex, mid+1, end);
			result.start = leftResult.start;
			result.end = rightResult.end;
			result.merge(leftResult, rightResult);
		}
		
		return result;
	}
	
	void update(int stIndex, int start, int end, UpdateType value) {
		if (nodes[stIndex].start == start && nodes[stIndex].end == end) {
			lazyPropagatePendingUpdateToSubtree(stIndex, value);
			return;
		}
		
		int mid = (nodes[stIndex].start + nodes[stIndex].end) >> 1,
			leftChildIndex = stIndex << 1,
			rightChildIndex = leftChildIndex + 1;
			
		if (start > mid) update(rightChildIndex, start, end, value);
		else if (end <= mid) update(leftChildIndex, start, end, value);
		else {
			update(leftChildIndex, start, mid, value);
			update(rightChildIndex, mid+1, end, value);
		}
		nodes[stIndex].merge(nodes[leftChildIndex], nodes[rightChildIndex]);
	}
	
	void lazyPropagatePendingUpdateToSubtree(int stIndex, UpdateType value) {
		nodes[stIndex].addUpdate(value);
		if (!nodes[stIndex].isPropagationRequired())
			return;
			
		if (nodes[stIndex].start == nodes[stIndex].end) {
			nodes[stIndex].applyPendingUpdate();
			return;
		}
		
		UpdateType pendingUpdate = nodes[stIndex].getPendingUpdate();
		nodes[stIndex].clearPendingUpdate();
		int mid = (nodes[stIndex].start + nodes[stIndex].end) >> 1,
			leftChildIndex = stIndex << 1,
			rightChildIndex = leftChildIndex + 1;
				
		lazyPropagatePendingUpdateToSubtree(leftChildIndex, pendingUpdate);
		lazyPropagatePendingUpdateToSubtree(rightChildIndex, pendingUpdate);		
		nodes[stIndex].merge(nodes[leftChildIndex], nodes[rightChildIndex]);
	}
};

/*
  Given an array A of N integers, support two operations on any range A[a..b] (0<=a<=b<N):

    - add a given value v to each A[i] (a<=i<=b)
    - find sum A[a]+…+A[b]

  SegmentTree<int,ll,ll> st(A, N);
  ...
  while (q--) {
    scanf("%d", &i);			
    if (i == 1) {
      rd(p >> q >> v);
      st.update(p-1, q-1, v);
    } else {
      rd(p, q);
      put(st.query(p-1, q-1));
    }
  }
*/

struct SegmentTreeNode {
	int start, end; // this node is responsible for the segment [start...end]
	ll total, pendingUpdate;
	
	SegmentTreeNode() : total(0), pendingUpdate(0) {}
	
	void assignLeaf(ll value) {
		total = value;
	}
	
	void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
		total = left.total + right.total;
		if (left.pendingUpdate > 0)
			total += left.pendingUpdate * (left.end - left.start + 1);
		if (right.pendingUpdate > 0)
			total += right.pendingUpdate * (right.end - right.start + 1);
	}
	
	ll query() {
		return total;
	}
	
	bool hasPendingUpdate() {
		return pendingUpdate != 0;
	}
	
	void applyPendingUpdate() {
		total += (end - start + 1) * pendingUpdate;
		pendingUpdate = 0;
	}
	
	void addUpdate(ll value) {
		pendingUpdate += value;
	}
	
	ll getPendingUpdate() {
		return pendingUpdate;
	}
};

template<class InputType, class UpdateType, class OutputType>
class SegmentTree {
	SegmentTreeNode* nodes;
	int N;
	
public:
	SegmentTree(InputType arr[], int N) {
		this->N = N;
		nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
		buildTree(arr, 1, 0, N-1);
	}
	
	~SegmentTree() {
		delete[] nodes;
	}
	
	// get the value associated with the segment [start...end]
	OutputType query(int start, int end) {
		SegmentTreeNode result = query(1, start, end);
		return result.query();
	}
	
	// range update: update the range [start...end] by value
	// Exactly what is meant by an update is determined by the
	// problem statement and that logic is captured in segment tree node
	void update(int start, int end, UpdateType value) {
		update(1, start, end, value);
	}
	
private:
	void buildTree(InputType arr[], int stIndex, int start, int end) {
		// nodes[stIndex] is responsible for the segment [start...end]
		nodes[stIndex].start = start, nodes[stIndex].end = end;
		
		if (start == end) {
			// a leaf node is responsible for a segment containing only 1 element
			nodes[stIndex].assignLeaf(arr[start]);
			return;
		}
		
		int mid = (start + end) / 2,
			leftChildIndex = 2 * stIndex,
			rightChildIndex = leftChildIndex + 1;
			
		buildTree(arr, leftChildIndex, start, mid);
		buildTree(arr, rightChildIndex, mid + 1, end);
		nodes[stIndex].merge(nodes[leftChildIndex], nodes[rightChildIndex]);
	}
	
	int getSegmentTreeSize(int N) {
		int size = 1;
		for (; size < N; size <<= 1);
		return size << 1;
	}
	
	SegmentTreeNode query(int stIndex, int start, int end) {
		if (nodes[stIndex].start == start && nodes[stIndex].end == end) {
			SegmentTreeNode result = nodes[stIndex];
			if (result.hasPendingUpdate())
				result.applyPendingUpdate();
			return result;
		}
		
		int mid = (nodes[stIndex].start + nodes[stIndex].end) >> 1,
			leftChildIndex = stIndex << 1,
			rightChildIndex = leftChildIndex + 1;			
		SegmentTreeNode result;
		
		if (start > mid)
			result = query(rightChildIndex, start, end);
		else if (end <= mid)
			result = query(leftChildIndex, start, end);
		else {
			SegmentTreeNode leftResult = query(leftChildIndex, start, mid),
							rightResult = query(rightChildIndex, mid+1, end);
			result.start = leftResult.start;
			result.end = rightResult.end;
			result.merge(leftResult, rightResult);
		}
		
		if (nodes[stIndex].hasPendingUpdate()) {
			result.addUpdate(nodes[stIndex].getPendingUpdate());
			result.applyPendingUpdate();
		}		
		return result;
	}
	
	void update(int stIndex, int start, int end, UpdateType value) {
		if (nodes[stIndex].start == start && nodes[stIndex].end == end) {
			nodes[stIndex].addUpdate(value);
			return;
		}
		
		int mid = (nodes[stIndex].start + nodes[stIndex].end) >> 1,
			leftChildIndex = stIndex << 1,
			rightChildIndex = leftChildIndex + 1;
			
		if (start > mid)
			update(rightChildIndex, start, end, value);
		else if (end <= mid)
			update(leftChildIndex, start, end, value);
		else {
			update(leftChildIndex, start, mid, value);
			update(rightChildIndex, mid+1, end, value);
		}
		nodes[stIndex].merge(nodes[leftChildIndex], nodes[rightChildIndex]);
	}
};

/*
  Given an array A of N booleans, support two operations on any range A[a..b] (0<=a<=b<N):

    - flip each A[i] (a<=i<=b)
    - count how many of A[a],…,A[b] are true

  SegmentTree<bool,bool,int> st(tailsUp, N);
	while (q--) {
		rd(cmd, A, B);
		if (cmd == 1)
			st.update(A, B, true);
		else
			put(st.query(A, B));
	}
*/

bool tailsUp[100005];

struct SegmentTreeNode {
  int start, end; // this node is responsible for the segment [start...end]
  int count;
  bool pendingUpdate;
  
  SegmentTreeNode() : count(0), pendingUpdate(false) {}
  
  void assignLeaf(bool value) {}
  
  void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
    count = (left.pendingUpdate ? (left.end - left.start + 1 - left.count) : left.count)
    	    + (right.pendingUpdate ? (right.end - right.start + 1 - right.count) : right.count);
  }
  
  int query() {
    return count;
  }
  
  bool hasPendingUpdate() {
    return pendingUpdate;
  }
  
  void applyPendingUpdate() {
    count = (end - start + 1) - count;
    pendingUpdate = false;
  }
  
  void addUpdate(bool value) {
    pendingUpdate = !pendingUpdate;
  }
  
  bool getPendingUpdate() {
    return true;
  }
};