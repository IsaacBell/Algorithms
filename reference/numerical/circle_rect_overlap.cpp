// Author: HuaHua

/*
    Given a circle represented as (radius, x_center, y_center) and an 
    axis-aligned rectangle represented as (x1, y1, x2, y2), where (x1, y1) 
    are the coordinates of the bottom-left corner, and (x2, y2) are the 
    coordinates of the top-right corner of the rectangle.

    Return True if the circle and rectangle are overlapped otherwise 
    return False.

    In other words, check if there are any point (xi, yi) such that 
    belongs to the circle and the rectangle at the same time.
*/

bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
  int dx = x_center - max(x1, min(x2, x_center));
  int dy = y_center - max(y1, min(y2, y_center));
  return dx * dx + dy * dy <= radius * radius;
}