# Project 04: Path Finding
==============================================

Authors: Barnes, Stanley; Canes, Kevin
Emails:  wbarne12@vols.utk.edu, hyg486@vols.utk.edu 
NetID:   wbarne12, hyg468
Github:  https://github.com/Dafunkmonk/Project-4-dijkstra-s

===============================================

## src/dijkstra
- Implements Dijkstra's Algorithm to perform rudimentary path finding on a 2D tile-based map. 
- Useage: ./dijkstra < input_file
- Make sure input file is in the correct format or else it will not work.

## src/generate_map 
- Generates a random grid in the style of the write-up
- Useage: ./generate_map
- Will ask you for a number, it will then make a N by N grid.
- Output file will be in the project folder.

## Compliation
- For src/dijkstra: make
- For generate_map: make

## Input
  TILES_N
  TILE_NAME_0	TILE_COST_0
  ...
  TILE_NAME_N-1	TILE_COST_N-1

  MAP_ROWS MAP_COLUMNS
  TILE_0_0    ...
  ...

  TRAVELER_START_ROW TRAVELER_START_COL
  TRAVELER_END_ROW   TRAVELER_END_COL

## Output
  Cost
  [(ROW_0, COL_0), ...]

## Benchmark
| N             | Elapsed Time (S) | Memory Usage   |
|---------------|------------------|----------------|
| 10            | 0.0014           | 111.652 KB     |
| 20            | 0.002            | 203.004 KB     |
| 50            | 0.0066           | 757.130 KB     |
| 100           | 0.02             | 2.81775 MB     |
| 200           | 0.0772           | 11.1141 MB     |
| 500           | 0.502            | 76.0618 MB     |
| 1000          | 2.096            | 307.373 MB     |
|---------------|------------------|----------------|

## Lab Questions
1. How did you represent the map as a graph?
    The graph is represented as an adjacency list. Each node has a unique ID. 
    Additionally, each node contains a vector of adjacent nodes and a weight assigned from the board. 
    To get the edge weight, it was simply the weight of the current ID. 

2. What is complexity of your implementation of Dijkstra's Algorithm?
    Our implementation is time complexity O(N+E*log(E)) where V is number of vertices and E is number of edges.
    The while loop that runs until the priority que is time O(N). The lookups of edges is O(E*log(E)).

3. How well does your implementation scale?
    The implementation scales decently well. 
    The running time could be improved by using linked list so that the vector does not need to be reversed. 
    We also refractored the edges vector to be a unordered_map, and the find_node method is redundant, but we did
    not have time to refractor. 

## Contributions:
Stanley: Wrote dijkstra's

Kevin: Wrote random number and benchmarking. 