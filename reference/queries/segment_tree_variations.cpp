/*
  Maximum sum subarray problem

  We need to store 4 values in each segment tree node to be able to merge
  child nodes to form a solution to their parent’s node:

  1. Maximum sum of a subarray, starting at the leftmost index of this range
  2. Maximum sum of a subarray, ending at the rightmost index of this range
  3. Maximum sum of any subarray in this range
  4. Sum of all elements in this range
*/
struct SegmentTreeNodeMaxSubarray {
  int prefixMaxSum, suffixMaxSum, maxSum, sum;
  
  void assignLeaf(int value) {
    prefixMaxSum = suffixMaxSum = maxSum = sum = value;
  }
  
  void merge(SegmentTreeNodeMaxSubarray& left, SegmentTreeNodeMaxSubarray& right) {
    sum = left.sum + right.sum;
    prefixMaxSum = max(left.prefixMaxSum, left.sum + right.prefixMaxSum);
    suffixMaxSum = max(right.suffixMaxSum, right.sum + left.suffixMaxSum);
    maxSum = max(prefixMaxSum, max(suffixMaxSum, max(left.maxSum, max(right.maxSum, left.suffixMaxSum + right.prefixMaxSum))));
  }
  
  int getValue() {
    return maxSum;
  }
};

/*
  Maximum pair sum in each subarray 
  Requires updates to individual array elements
*/
struct SegmentTreeNodeMaxPairSum {
  int maxNum, secondMaxNum;
  
  void assignLeaf(int num) {
    maxNum = num;
    secondMaxNum = -1;
  }
  
  void merge(SegmentTreeNodeMaxPairSum& left, SegmentTreeNodeMaxPairSum& right) {
    maxNum = max(left.maxNum, right.maxNum);
    secondMaxNum = min(max(left.maxNum, right.secondMaxNum), max(right.maxNum, left.secondMaxNum));
  }
  
  int getValue() {
    return maxNum + secondMaxNum;
  }
};

/*
  T is the type of input array elements
  V is the type of required aggregate statistic
*/
template<class T, class V>
class SegmentTree {
  SegmentTreeNode* nodes;
  int N;

public:
  SegmentTree(T arr[], int N) {
    this->N = N;
    nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
    buildTree(arr, 1, 0, N-1);
  }
  
  ~SegmentTree() {
    delete[] nodes;
  }
  
  V getValue(int lo, int hi) {
    SegmentTreeNode result = getValue(1, 0, N-1, lo, hi);
    return result.getValue();
  }
  
  void update(int index, T value) {
    update(1, 0, N-1, index, value);
  }
  
private:	
  void buildTree(T arr[], int stIndex, int lo, int hi) {
    if (lo == hi) {
      nodes[stIndex].assignLeaf(arr[lo]);
      return;
    }
    
    int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
    buildTree(arr, left, lo, mid);
    buildTree(arr, right, mid + 1, hi);
    nodes[stIndex].merge(nodes[left], nodes[right]);
    }
    
    SegmentTreeNode getValue(int stIndex, int left, int right, int lo, int hi) {
    if (left == lo && right == hi)
      return nodes[stIndex];
      
    int mid = (left + right) / 2;
    if (lo > mid)
      return getValue(2*stIndex+1, mid+1, right, lo, hi);
    if (hi <= mid)
      return getValue(2*stIndex, left, mid, lo, hi);
      
    SegmentTreeNode leftResult = getValue(2*stIndex, left, mid, lo, mid);
    SegmentTreeNode rightResult = getValue(2*stIndex+1, mid+1, right, mid+1, hi);
    SegmentTreeNode result;
    result.merge(leftResult, rightResult);
    return result;
  }
  
  int getSegmentTreeSize(int N) {
    int size = 1;
    for (; size < N; size <<= 1);
    return size << 1;
  }
  
  void update(int stIndex, int lo, int hi, int index, T value) {
    if (lo == hi) {
    nodes[stIndex].assignLeaf(value);
    return;
  }
  
  int left = 2 * stIndex, right = left + 1, mid = (lo + hi) / 2;
  if (index <= mid)
    update(left, lo, mid, index, value);
  else
    update(right, mid+1, hi, index, value);
  
  nodes[stIndex].merge(nodes[left], nodes[right]);
  }
};
