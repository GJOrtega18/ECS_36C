#ifndef _FINDMAX_H
#define	_FINDMAX_H
#include "RunFind.h"
#include "BinaryHeap.h"
#include "Intersection.h"

class FindMax {
public:
  FindMax(int citySize, const StreetBlock *streets, int numStreets);
  void find(Coordinate fireHouses[4], Coordinate *furthest, int *time);



 private:
  void initializeGraph(const StreetBlock *streets, int numStreets);
  void initializeHeap();
  void printGraph();

  Intersection* graph[1000][1000];
  BinaryHeap<Intersection*> heap;
  int numVertices;

};


// class FindMax

#endif	/* _FINDMAX_H */

