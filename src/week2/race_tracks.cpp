#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
  int x;
  int y;
  Point(int x = 0 , int y = 0) : x(x), y(y) {};
  bool operator==(const Point& a) const{
    return (x == a.x && y == a.y);
  }
  Point& operator=(const Point& a) {
    x = a.x;
    y = a.y;
    return *this;
  }
};

struct Obstacle {
  Point start;
  Point end;
  Obstacle& operator=(const Obstacle& o) {
    start = o.start;
    end = o.end;
    return *this;
  }
};

struct Node {
  Point position;
  Point velocity;
  Node* parent;
  int depth;
  Node(Point position, Point velocity, Node* parent, int depth = 0) : position(position), velocity(velocity), parent(parent), depth(depth){ }
  Node& operator=(const Node& n) {
    position = n.position;
    velocity = n.velocity;
    depth = n.depth;
    parent = n.parent;
    return *this;
  }
  bool operator==(const Node& n) const{
    return (position == n.position && velocity == n.velocity);
  }
};
set<pair<pair<int, int>, pair<int, int> > > visitedNodes;

bool obstacles[31][31];

bool isObstacle(Point p);
void addObstacle(const Obstacle& obstacle);
bool between(int a, int x, int y);
void bfs_search(Point start, Point end, Point board);

void addNeightbours(Node& current, queue<Node>& q, Point board) ;
bool isValidVelocity(Point velocity);
bool isValidPoint(Point position, Point board);
void clearVisitedAndObstacles();

/*int main(void) {*/
int race_tracks(void) {

  int cases, obs_number;
  Point grid, start, end;
  cin >> cases;
  for (int i = 0; i < cases; i++) {
    cin >> grid.x >> grid.y;
    cin >> start.x >> start.y >> end.x >> end.y;
    cin >> obs_number;
    Obstacle currentObstacle;
    for (int j = 0; j < obs_number; j++) {
      cin >> currentObstacle.start.x 	>> currentObstacle.start.y
        >> currentObstacle.end.x 	>> currentObstacle.end.y;
      addObstacle(currentObstacle);
    }
    bfs_search(start, end,grid);
  }
  return 0;
}

/*
 * Perform the actual search
 */
void bfs_search(Point start, Point end, Point board) {
  queue<Node> q;
  visitedNodes.clear();
  Node current(start,Point(0,0),NULL, 0);
  q.push(current);
  pair<int, int> pos(start.x, start.y);
  pair<int, int> spd(0, 0);
  pair<pair<int, int>, pair<int, int> >  pr(pos, spd);
  visitedNodes.insert(pr);
  bool done = false;
  while (!q.empty() && !done) {
    current = q.front();
    q.pop();
    if (current.position == end) {
      cout << "Optimal solution takes " << current.depth << " hops.\n";
      done = true;
    } else {
      addNeightbours(current, q,board);
    }
  }
  if (!done) {
    cout << "No solution.\n";
  }
  clearVisitedAndObstacles();

}

/*
 *	Add valid neighbours to q.
 */
void addNeightbours(Node& current, queue<Node>& q, Point board) {
  int nextVx, nextVy;
  Point potentialNeighbour;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      nextVx = current.velocity.x + i;
      nextVy = current.velocity.y + j;
      if (isValidVelocity(Point(nextVx,nextVy))) {
        potentialNeighbour = Point(current.position.x + nextVx , current.position.y + nextVy);
        if (isValidPoint(potentialNeighbour, board) && !isObstacle(potentialNeighbour)) {
          Node potentialNode = Node(potentialNeighbour, Point(nextVx, nextVy), &current, current.depth + 1);
          pair<int, int> pos(potentialNeighbour.x, potentialNeighbour.y);
		  pair<int, int> spd(nextVx, nextVy);
		  pair<pair<int, int>, pair<int, int> >  pr(pos, spd);
          if (visitedNodes.find(pr) == visitedNodes.end()) {
            q.push(potentialNode);
            visitedNodes.insert(pr);
          }
        }
      }
    }
  }
}

bool isObstacle(Point p) {
	return obstacles[p.x][p.y];
}

void clearVisitedAndObstacles() {
	for (int i = 0; i < 31; i++) {
		for (int j = 0; j < 31; j++) {
			/*for (int k = 0; k < 7; k++) {
				for (int l = 0; l < 7; l++) {
					visited[i][j][k][l] = false;
				}
			}*/
			obstacles[i][j] = false;
		}
	}
}

void addObstacle(const Obstacle& obstacle) {
	for (int i = obstacle.start.x; i <= obstacle.end.x; i++) {
		for (int j = obstacle.start.y; j <= obstacle.end.y; j++) {
			obstacles[i][j] = true;
		}
	}
}

bool isValidPoint(Point position, Point board) {
  return between(position.x, 0, board.x-1) && between(position.y, 0, board.y-1);
}

bool isValidVelocity(Point velocity) {
  return between(velocity.x, -3, 3) && between(velocity.y, -3,3);
}

bool between(int a, int x, int y) {
  return (a >= x && a <= y);
}
