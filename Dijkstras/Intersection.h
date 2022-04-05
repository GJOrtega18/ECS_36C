//
// Created by george on 3/2/20.
//

#ifndef ECS36C_PHW5_INTERSECTION_H
#define ECS36C_PHW5_INTERSECTION_H


#include "RunFind.h"
#include "BinaryHeap.h"

class Intersection {

  friend class FindMax;

public:
    Intersection(Coordinate vertex);
    Intersection(int xCoord, int yCoord);
//    Intersection* operator=(Intersection* rhs); // copy constructor

    void addAdjIntersection(Intersection* intersection, int weight);
    void printIntersection();
    void updateAdjacentVertices(BinaryHeap<Intersection*>& heap);
//    Intersection* findMaxDv();

//    bool operator<(Intersection& rhs) const;
    int dV;

 private:

    Coordinate vertex;
    Intersection* adjacentIntersection[4]; // max length is 4, 4 way intersection.
    //StreetBlock* streetBlocks[4]; // block in direction of intersection
    int weights[4];
    int intersectionCount; // number of paths from an intersection

    // variables for Dijkstra's table
    bool isKnown;

};





#endif //ECS36C_PHW5_INTERSECTION_H
