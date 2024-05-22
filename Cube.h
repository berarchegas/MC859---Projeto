#ifndef CUBE_H
#define CUBE_H

#include <bits/stdc++.h>

using namespace std;

struct Cube {

    static mt19937 rng;

    vector<int> v;

    Cube();  // Constructor declaration
    Cube(const vector<int>& _v);
    Cube(const Cube& other);
    void set(int face, int i, int j, int cor);
    int getColor(int face, int i, int j) const;
    Cube copyCube() const;
    void print() const; // Method to print the cube
    void rightAntiClock(); // Rotate right face anticlockwise
    void rightClock(); // Rotate right face clockwise
    void upClock(); // Rotate up face clockwise
    void upAntiClock(); // Rotate up face anticlockwise
    void leftClock(); // Rotate left face clockwise
    void leftAntiClock(); // Rotate left face anticlockwise
    void downClock(); // Rotate down face clockwise
    void downAntiClock(); // Rotate down face anticlockwise
    void frontClock(); // Rotate front face clockwise
    void frontAntiClock(); // Rotate front face anticlockwise
    void backClock(); // Rotate back face clockwise
    void backAntiClock(); // Rotate back face anticlockwise
    void verticalClock(); // Combination of vertical rotations
    void verticalAntiClock(); // Combination of vertical rotations
    void horizontalClock(); // Combination of horizontal rotations
    void horizontalAntiClock(); // Combination of horizontal rotations
    void transversalClock(); // Combination of transversal rotations
    void transversalAntiClock(); // Combination of transversal rotations
    void performOperation(int operationIndex); // Perform operation based on index
    int countDif() const; // Count the number of tiles that have the wrong color
    int fitness(const vector<int> &x); // Calculates the fitness function
    void scramble(); // Scrambles the cube
    void findBest(const vector<int> &x); // prints the cube at the lowest fitness point
};

#endif // CUBE_H