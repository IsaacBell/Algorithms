/* Notes
   - Overrides any macro named "P"
   - Removes any macro w/ name "F". I re-add "F" at the end to compile to "first", based on my main template
   - 3D structures still not stress-tested
*/

ll a, b, c, n, m, k, w;
string s, t;

// Remove macro - we use "F" for our geometry templates
#undef F

template <class F>
struct Point {
  F x, y;
  Point() : x(0), y(0) {}
  Point(const F& x, const F& y) : x(x), y(y) {}

  void swap(Point& other) { using std::swap; swap(x, other.x); swap(y, other.y); }
  template <class F1> explicit operator Point<F1> () const {
    return Point<F1>(static_cast<F1>(x), static_cast<F1>(y)); }
  template <class F1> Point& operator = (const Point<F1>& other) {
    x = other.x; y = other.y; return *this; }
  template <class F1> Point& operator += (const Point<F1>& other) {
    x += other.x; y += other.y; return *this; }
  template <class F1> Point& operator -= (const Point<F1>& other) {
    x -= other.x; y -= other.y; return *this; }
  template <class F1> Point& operator *= (const F1& factor) {
    x *= factor; y *= factor; return *this; }
  template <class F1> Point& operator /= (const F1& factor) {
    x /= factor; y /= factor; return *this; }
};

template <class F = ll> using P = Point<F>;
template <class F = ll> using Polygon = vector<Point<F>>;

template <class F> int read(Point<F>& point) { return read(point.x, point.y) / 2; }
template <class F> int write(const Point<F>& point) { return write(point.x, point.y); }

template <class F> istream& operator >> (istream& is, Point<F>& point) {
  return is >> point.x >> point.y; }
template <class F> ostream& operator << (ostream& os, const Point<F>& point) {
  return os << point.x << ' ' << point.y; }

template <class F> inline Point<F> makePoint(const F& x, const F& y) { return Point<F>(x, y); }
template <class F> void swap(Point<F>& lhs, Point<F>& rhs) { lhs.swap(rhs); }

#define FUNC1(name, arg, expr) \
template <class F> inline auto name(const arg) -> decltype(expr) { return expr; }
#define FUNC2(name, arg1, arg2, expr) \
template <class F1, class F2> \
inline auto name(const arg1, const arg2) -> decltype(expr) { return expr; }
#define FUNC3(name, arg1, arg2, arg3, expr) \
template <class F1, class F2, class F3> \
inline auto name(const arg1, const arg2, const arg3) -> decltype(expr) { return expr; }

FUNC1(operator -, Point<F>& point, makePoint(-point.x, -point.y))
FUNC2(operator +, Point<F1>& lhs, Point<F2>& rhs, makePoint(lhs.x + rhs.x, lhs.y + rhs.y))
FUNC2(operator -, Point<F1>& lhs, Point<F2>& rhs, makePoint(lhs.x - rhs.x, lhs.y - rhs.y))
FUNC2(operator *, F1& factor, Point<F2>& rhs, makePoint(factor * rhs.x, factor * rhs.y))
FUNC2(operator *, Point<F1>& lhs, F2& factor, makePoint(lhs.x * factor, lhs.y * factor))
FUNC2(operator /, Point<F1>& lhs, F2& factor, makePoint(lhs.x / factor, lhs.y / factor))

FUNC2(operator *, Point<F1>& lhs, Point<F2>& rhs, lhs.x * rhs.x + lhs.y * rhs.y)
FUNC2(operator ^, Point<F1>& lhs, Point<F2>& rhs, lhs.x * rhs.y - lhs.y * rhs.x)

// < 0 if rhs <- lhs counter-clockwise, 0 if collinear, > 0 if clockwise.
FUNC2(ccw, Point<F1>& lhs, Point<F2>& rhs, rhs ^ lhs)
FUNC3(ccw, Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin, ccw(lhs - origin, rhs - origin))

FUNC2(operator ==, Point<F1>& lhs, Point<F2>& rhs, lhs.x == rhs.x && lhs.y == rhs.y)
FUNC2(operator !=, Point<F1>& lhs, Point<F2>& rhs, !(lhs == rhs))

FUNC2(operator <, Point<F1>& lhs, Point<F2>& rhs,
    lhs.y < rhs.y || (lhs.y == rhs.y && lhs.x < rhs.x))
FUNC2(operator >, Point<F1>& lhs, Point<F2>& rhs, rhs < lhs)
FUNC2(operator <=, Point<F1>& lhs, Point<F2>& rhs, !(lhs > rhs))
FUNC2(operator >=, Point<F1>& lhs, Point<F2>& rhs, !(lhs < rhs))

template <class F = ll>
bool pointlineintersect(Point<F> P1, Point<F> P2, Point<F> P3){
    if(ccw<F, F, F>(P1, P2, P3)) return false;
    return (min(P2.x, P3.x) <= P1.x && P1.x <= max(P2.x, P3.x))
        && (min(P2.y, P3.y) <= P1.y && P1.y <= max(P2.y, P3.y));
}

template <class F1 = ll, class F2 = ll>
F1 euclidean_dist(Point<F1>& lhs, Point<F2>& rhs) {
  return pow(lhs.x-rhs.x, 2) + pow(lhs.y-rhs.y, 2);
}

template <class F = ll>
F euclidean_dist_sqrt(Point<F>& lhs, Point<F>& rhs) {
  return sqrt(euclidean_dist<F, F> (lhs, rhs));
}

template <class F = ll>
F signed_area_parallelogram(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3) {
  return (p2 - p1) ^ (p3 - p2);
}

template <class F = ll>
double triangle_area(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3) {
  return abs((double) signed_area_parallelogram(p1, p2, p3)) / 2.0;
}

template <class F = ll>
bool clockwise(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3) {
  return signed_area_parallelogram(p1, p2, p3) < 0;
}

template <class F = ll>
bool counter_clockwise(const Point<F>& p1, const Point<F>& p2, const Point<F>& p3) {
  return signed_area_parallelogram(p1, p2, p3) > 0;
}


// Angles and rotations (counter-clockwise).
FUNC1(angle, Point<F>& point, atan2(point.y, point.x))
FUNC2(angle, Point<F1>& lhs, Point<F2>& rhs, atan2(lhs ^ rhs, lhs * rhs))
FUNC3(angle, Point<F1>& lhs, Point<F2>& rhs, Point<F3>& origin,
      angle(lhs - origin, rhs - origin))
FUNC3(rotate, Point<F1>& point, F2& angleSin, F3& angleCos,
      makePoint(angleCos * point.x - angleSin * point.y,
                angleSin * point.x + angleCos * point.y))
FUNC2(rotate, Point<F1>& point, F2& angle, rotate(point, sin(angle), cos(angle)))
FUNC3(rotate, Point<F1>& point, F2& angle, Point<F3>& origin,
      origin + rotate(point - origin, angle))
FUNC1(perp, Point<F>& point, makePoint(-point.y, point.x))

// Distances.
FUNC1(abs, Point<F>& point, point * point)
FUNC1(norm, Point<F>& point, sqrt(abs(point)))
FUNC2(dist, Point<F1>& lhs, Point<F2>& rhs, norm(lhs - rhs))
FUNC2(dist2, Point<F1>& lhs, Point<F2>& rhs, abs(lhs - rhs))
FUNC2(bisector, Point<F1>& lhs, Point<F2>& rhs, lhs * norm(rhs) + rhs * norm(lhs))

template <class F>
struct P3d { // 3d point
  F x, y, z;
  P3d() {}
  P3d(F x, F y, F z): x(x), y(y), z(z) {}
  P3d& operator+=(const P3d &t) {
    x += t.x;
    y += t.y;
    z += t.z;
    return *this;
  }
  P3d& operator-=(const P3d &t) {
    x -= t.x;
    y -= t.y;
    z -= t.z;
    return *this;
  }
  P3d& operator*=(F t) {
    x *= t;
    y *= t;
    z *= t;
    return *this;
  }
  P3d& operator/=(F t) {
    x /= t;
    y /= t;
    z /= t;
    return *this;
  }
  P3d operator+(const P3d &t) const {
    return P3d(*this) += t;
  }
  P3d operator-(const P3d &t) const {
    return P3d(*this) -= t;
  }
  P3d operator*(F t) const {
    return P3d(*this) *= t;
  }
  P3d operator/(F t) const {
    return P3d(*this) /= t;
  }
  F operator*(P3d<F>& rhs) const {
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  P3d operator^(P3d& rhs) const {
    return P3d<F>(y * rhs.z - z * rhs.y,
                z * rhs.x - x * rhs.z,
                x * rhs.y - y * rhs.x);
  }
};

template <class F = ll> using P3d = P3d<F>;
template <class F = ll> using Point3d = P3d<F>;
template <class F = ll> using point3d = P3d<F>;

template <class F = ll>
P3d<F> operator*(F a, P3d<F> b) {
  return b * a;
}
template <class F = ll>
F dot(point3d<F> a, point3d<F> b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}
template <class F = ll>
P3d<F> cross(P3d<F> a, P3d<F> b) {
  return P3d(a.y * b.z - a.z * b.y,
             a.z * b.x - a.x * b.z,
             a.x * b.y - a.y * b.x);
}
template <class F = ll>
F triple(P3d<F> a, P3d<F> b, P3d<F> c) {
  return dot(a, cross(b, c));
}
template <class F = ll>
P3d<F> intersect(P3d<F> a1, P3d<F> n1, P3d<F> a2, P3d<F> n2, P3d<F> a3, P3d<F> n3) {
  P3d<F> x(n1.x, n2.x, n3.x);
  P3d<F> y(n1.y, n2.y, n3.y);
  P3d<F> z(n1.z, n2.z, n3.z); 
  P3d<F> d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
  return P3d<F>(triple(d, y, z),
                triple(x, d, z),
                triple(x, y, d)) / triple(n1, n2, n3);
}


#undef FUNC1
#undef FUNC2
#undef FUNC3

template <class F>
struct Line {
  Point<F> a, ab;
  Line() : a(), ab() {}
  Line(const Point<F>& a, const Point<F>& b, bool twoPoints = true)
    : a(a), ab(twoPoints ? b - a : b) {}
  Line(const F& xa, const F& ya, const F& xb, const F& yb)
    : a(xa, ya), ab(xb - xa, yb - ya) {}

  void swap(Line& other) { using std::swap; swap(a, other.a); swap(ab, other.ab); }
  template <class F1> explicit operator Line<F1> () const {
    return Line<F1>(Point<F1>(a), Point<F1>(ab), false); }
  template <class F1> Line& operator = (const Line<F1>& other) {
    a = other.a; ab = other.ab; return *this; }

  Point<F> b() const { return a + ab; }
  operator bool () const { return ab != Point<F>(); }
};

template <class F> int read(Line<F>& line) {
  int res = read(line.a, line.ab) / 2;
  return line.ab -= line.a, res;
}

template <class F>
inline Line<F> makeLine(const Point<F>& a, const Point<F>& b, bool twoPoints = true) {
  return Line<F>(a, b, twoPoints);
}

template <class F> void swap(Line<F>& lhs, Line<F>& rhs) { lhs.swap(rhs); }

template <class F1, class F2>
bool onLine(const Point<F1>& point, const Line<F2>& line) {
  if (!line) return point == line.a;
  return ((point - line.a) ^ line.ab) == 0;
}

template <class F1, class F2>
bool onSegment(const Point<F1>& point, const Line<F2>& seg) {
  if (!seg) return point == seg.a;
  auto vecta = seg.a - point, vectb = seg.b() - point;
  return (vecta ^ vectb) == 0 && (vecta * vectb) <= 0;
}

template <class F1, class F2> using distF = decltype(sqrt(F1() + F2()));

template <class F1, class F2>
distF<F1, F2> distLine(const Point<F1>& point, const Line<F2>& line) {
  if (!line) return dist(point, line.a);
  return abs((point - line.a) ^ line.ab) / norm(line.ab);
}

template <class F1, class F2>
distF<F1, F2> distSegment(const Point<F1>& point, const Line<F2>& seg) {
  if (((point - seg.a) * seg.ab) <= 0) return dist(point, seg.a);
  if (((point - seg.b()) * seg.ab) >= 0) return dist(point, seg.b());
  return distLine(point, seg);
}

template <class F1, class F2, class F3>
void projection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
  res = line.a;
  if (line) res += line.ab * static_cast<F3>((point - line.a) * line.ab) / abs(line.ab);
}

template <class F1, class F2, class F3>
void reflection(const Point<F1>& point, const Line<F2>& line, Point<F3>& res) {
  projection(point, line, res);
  res = 2 * res - point;
}

template <class F1, class F2, class F3>
void closest(const Point<F1>& point, const Line<F2>& seg, Point<F3>& res) {
  if (((point - seg.a) * seg.ab) <= 0) res = seg.a;
  else if (((point - seg.b()) * seg.ab) >= 0) res = seg.b();
  else projection(point, seg, res);
}

template <int TYPE> struct EndpointChecker {};
template <> struct EndpointChecker<0> {  // no endpoint (ray)
  template <class F> bool operator ()(const F& a, const F& b) const { return true; }};
template <> struct EndpointChecker<1> {  // closed endpoint
  template <class F> bool operator ()(const F& a, const F& b) const { return a <= b; }};
template <> struct EndpointChecker<2> {  // open endpoint
  template <class F> bool operator ()(const F& a, const F& b) const { return a < b; }};

template <int LA, int LB, int RA, int RB, class F1, class F2, class F3>
bool intersectLines(const Line<F1>& lhs, const Line<F2>& rhs, Point<F3>& res) {
  assert(lhs && rhs);
  auto s = lhs.ab ^ rhs.ab;
  if (s == 0) return false;
  auto ls = (rhs.a - lhs.a) ^ rhs.ab;
  auto rs = (rhs.a - lhs.a) ^ lhs.ab;
  if (s < 0) s = -s, ls = -ls, rs = -rs;
  bool intersect =
    EndpointChecker<LA>()(decltype(ls)(0), ls) && EndpointChecker<LB>()(ls, s) &&
    EndpointChecker<RA>()(decltype(rs)(0), rs) && EndpointChecker<RB>()(rs, s);
  if (intersect) res = lhs.a + lhs.ab * static_cast<F3>(ls) / s;
  return intersect;
}

template <class F = ll>
bool intersectSegments(const Line<F>& lhs, const Line<F>& rhs, Line<F>& res) {
  auto s = lhs.ab ^ rhs.ab;
  auto ls = (rhs.a - lhs.a) ^ rhs.ab;
  if (s == 0) {
    if (ls != 0) return false;
    auto lhsa = lhs.a, lhsb = lhs.b();
    auto rhsa = rhs.a, rhsb = rhs.b();
    if (lhsa > lhsb) swap(lhsa, lhsb);
    if (rhsa > rhsb) swap(rhsa, rhsb);
    res = Line<F>(max(lhsa, rhsa), min(lhsb, rhsb));
    return res.ab >= Point<F>();
  }
  auto rs = (rhs.a - lhs.a) ^ lhs.ab;
  if (s < 0) s = -s, ls = -ls, rs = -rs;
  bool intersect = 0 <= ls && ls <= s && 0 <= rs && rs <= s;
  if (intersect)
    res = Line<F>(lhs.a + lhs.ab * static_cast<F>(ls) / s, Point<F>());
  return intersect;
}

template <class F>
struct AngleCompare {
  const Point<F> origin;
  const bool zero;

  AngleCompare(const Point<F>& origin = Point<F>())
    : origin(origin), zero(origin == Point<F>()) {}

  template <class F1, class F2>
  bool operator () (const Point<F1>& lhs, const Point<F2>& rhs) const {
    return zero ? ccw(lhs, rhs) < 0 : ccw(lhs, rhs, origin) < 0;
  }
};

template <class Iterator, class F>
void sortByAngle(Iterator first, Iterator last, const Point<F>& origin) {
  first = partition(first, last, [&origin](const decltype(*first)& point) {
    return point == origin; });
  auto pivot = partition(first, last, [&origin](const decltype(*first)& point) {
    return point > origin; });
  AngleCompare<F> acmp(origin);
  sort(first, pivot, acmp);
  sort(pivot, last, acmp);
}

/* Circles
*/

template <class F>
struct circle : Point<F> {
    double r;

    ll countLatticePoints()
    {
      if (r <= 0) return 0; 

      // Initialize result as 4 for (r, 0), (-r. 0), (0, r) and (0, -r)
      ll result = 4;

      // Check every value that can be potential x
      for (ll X=1; X<r; X++) {
        // Find a potential y
        ll ySquare = r*r - X*X;
        ll Y = sqrt(ySquare);

        // checking whether square root is an lleger
        // or not. Count increments by 4 for four 
        // different quadrant values
        if (Y*Y == ySquare) result += 4;
      }

      return result;
    }
};

double sqr(double a);

template <class F = ll>
void tangents (Point<F> c, double r1, double r2, vector<Line<F>> & ans) {
  double r = r2 - r1;
  double z = sqr(c.x) + sqr(c.y);
  double d = z - sqr(r);

  if (d < -mod)  return;
  d = sqrt (abs (d));

  Line<F> l;
  l.a = (c.x * r + c.y * d) / z;
  l.b = (c.y * r - c.x * d) / z;
  l.c = r1;
  ans.push_back (l);
}

template <class F = ll>
vector<Line<F>> tangents (circle<F> a, circle<F> b) {
  vector<Line<F>> ans;
  for (int i=-1; i<=1; i+=2)
      for (int j=-1; j<=1; j+=2)
          tangents (b-a, a.r*i, b.r*j, ans);
  for (size_t i=0; i<ans.size(); ++i)
      ans[i].c -= ans[i].a * a.x + ans[i].b * a.y;
  return ans;
}


/* Inclusion tests
Given a point, sometimes we need to check whether it lies inside or outside the given polygon. All the functions below return

-1 if the point is strictly inside the polygon;
0 if the point is on the boundary;
1 if the point is outside the polygon
*/

// See: "Inclusion Tests"
template <class F1, class F2>
int pointVsTriangle(const Point<F1>& point, const Polygon<F2>& triangle) {
  assert(triangle.size() == 3);
  constexpr auto prev = [](F1 i, F1 n) { return i == 0 ? n-1 : i-1; };
  constexpr auto next = [](F1 i, F1 n) { return i == n-1 ? 0 : i+1; };

  int signs[3];
  fo (i,3) signs[i] = sgn(ccw(point, triangle[next(i, 3)], triangle[i]));

  if (signs[0] == signs[1] && signs[1] == signs[2]) return -1;
  fo (i,3) if (signs[i] * signs[next(i, 3)] == -1) return 1;
  return 0;
}

// See: "Inclusion Tests"
template <class F1, class F2>
int pointVConvexPolygon(const Point<F1>& point, const Polygon<F2>& poly) {
  if (poly.empty()) return 1;
  if (poly.size() == 1) return point == poly[0] ? 0 : 1;
  if (ccw(point, poly[1], poly[0]) < 0) return 1;
  AngleCompare<F2> acmp(poly[0]);
  auto i = lower_bound(begin(poly) + 1, end(poly), point, acmp) - begin(poly);
  if (i == poly.size()) return 0;
  if (i == 1) return (point - poly[0]) * (point - poly[1]) <= 0 ? 0 : 1;
  if (i+1 == poly.size() && onSegment(point, makeLine(poly[0], poly.back())))
    return 0;
  return sgn(ccw(point, poly[i-1], poly[i]));
}

template <class F = ll>
int pointVConvexPolygon(const Point<F>& point, const Polygon<F>& poly) {
  return pointVConvexPolygon<ll,ll>(point, poly);
}

template <class F1, class F2>
int pointVsConvexPolygon(const Point<F1>& point, const Polygon<F2>& poly, int top) {
  if (point < poly[0] || point > poly[top]) return 1;
  auto orientation = ccw(point, poly[top], poly[0]);
  if (orientation == 0) {
    if (point == poly[0] || point == poly[top]) return 0;
    return top == 1 || top + 1 == poly.size() ? 0 : -1;
  } else if (orientation < 0) {
    auto itRight = lower_bound(begin(poly) + 1, begin(poly) + top, point);
    return sgn(ccw(itRight[0], point, itRight[-1]));
  } else {
    auto itLeft = upper_bound(poly.rbegin(), poly.rend() - top-1, point);
    return sgn(ccw(itLeft == poly.rbegin() ? poly[0] : itLeft[-1], point, itLeft[0]));
  }
}

// Simple Polygon
template <class F1, class F2>
int pointVsPolygon(const Point<F1>& point, const Polygon<F2>& poly) {
  int n = static_cast<int>(poly.size()), windingNumber = 0;
  constexpr auto prev = [](int i, int n) { return i == 0 ? n-1 : i-1; };
  constexpr auto next = [](int i, int n) { return i == n-1 ? 0 : i+1; };

  for (int i = 0; i < n; ++i) {
    if (point == poly[i]) return 0;
    int j = next(i, n);
    if (poly[i].y == point.y && poly[j].y == point.y) {
      if (min(poly[i].x, poly[j].x) <= point.x &&
          point.x <= max(poly[i].x, poly[j].x)) return 0;
    } else {
      bool below = poly[i].y < point.y;
      if (below != (poly[j].y < point.y)) {
        auto orientation = ccw(point, poly[j], poly[i]);
        if (orientation == 0) return 0;
        if (below == (orientation > 0)) windingNumber += below ? 1 : -1;
      }
    }
  }
  return windingNumber == 0 ? 1 : -1;
}

// Doubled oriented area
template <class F = ll>
F area(const Polygon<F>& poly) {
  F n_ = static_cast<F>(poly.size());

  constexpr auto prev = [](F i, F n) { return i == 0 ? n-1 : i-1; };
  constexpr auto next = [](F i, F n) { return i == n-1 ? 0 : i+1; };
  F area = F(0);
  fo(i,n) area += poly[i].x * (poly[next(i, n_)].y - poly[prev(i, n_)].y);
  return area;
}

// True if orientation of a simple polygon is counter-clockwise.
template <class F = ll> 
bool orientation(const Polygon<F>& poly) {
  F sz = static_cast<F>(poly.size());
  F i = static_cast<F>(*min_element(all(poly)) - poly.begin());
  return ccw(poly[prev(i, sz)], poly[next(i, sz)], poly[i]) > 0;
}

template <class F = ll>
void reorder_polygon(Polygon<F>& P){
  size_t pos = 0;
  for(size_t i = 1; i < P.size(); i++){
    if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
      pos = i;
  }
  rotate(P.begin(), P.begin() + pos, P.end());
}

template <class F = ll>
Polygon<F> minkowski(Polygon<F> P, Polygon<F> Q){
  // the first vertex must be the lowest
  reorder_polygon(P), reorder_polygon(Q);

  // we must ensure cyclic indexing
  P.pb(P[0]), P.pb(P[1]),
  Q.pb(Q[0]), Q.pb(Q[1]);

  // main part
  Polygon<F> result;
  size_t i = 0, j = 0;
  while(i < P.size() - 2 || j < Q.size() - 2){
    result.push_back(P[i] + Q[j]);
    auto cross = (P[i + 1] - P[i]) ^ (Q[j + 1] - Q[j]);
    if(cross >= 0)
      ++i;
    if(cross <= 0)
      ++j;
  }
  return result;
}

template <class F = ll>
Polygon<F> convexHull(Polygon<F> points) {
  sortall(points);
  Polygon<F> hull;
  // hull.reserve(points.sz() + 1);
  fo (phase,2) {
    auto start = hull.sz();
    trav(point, points) {
      while (
        hull.sz() >= start+2 &&
        ccw(point, hull.back(), hull[hull.sz()-2]) > 0
      ) hull.pop_back();
      hull.pb(point);
    }
    hull.pop_back();
    reverse(all(points));
  }

  // Degenerate case when all the points coincide
  if (hull.sz() == 2 && hull[0] == hull[1]) hull.pop_back();
  return hull;
}

double sqr (double a) {
  return a * a;
}

// replace macro we cleared above
#define F first