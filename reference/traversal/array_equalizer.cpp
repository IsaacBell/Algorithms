// WIP
template <class T = ll>
struct ArrayEqualizer {
  using vt = vector<T>;
  const int n;
  vt A;

  ArrayEqualizer(int n_): n(n_) {
    A.rsz(n_);
    iota(all(A), 1);
  };
  ArrayEqualizer(vt& in): n(in.sz()) {
    A = std::forward(in);
  };

  template <typename ...Args>
  T process(Args)
};