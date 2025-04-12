/* Project 4: Dijkstra's Algorithm
 *
 * Authors: Barnes, Stanley; Canes, Kevin
 *  Emails: wbarne12@vols.utk.edu, hyg486@vols.utk.edu 
 *   NetID: wbarne12, hyg468
 *  Github: https://github.com/Dafunkmonk/Project-4-dijkstra-s
 * 
 * Description: This program is designed for specific input for Dijsktra's algorithm. 
 *   Look at READ_ME.md for input info and data folder for examples. 
 * 
 * Lab write up: https://utk.instructure.com/courses/218164/assignments/2261309
 * 
 * Help recieved: https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
 */
#include <map>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
  int id;
  vector <int> edges;
  int weight;
};

struct Graph {
  unordered_map<int, Node*> node_map;

  // Destructor
  ~Graph() {
    unordered_map<int, Node*>::iterator it;
    for (it = node_map.begin(); it != node_map.end(); it++) {
      delete it->second;
    }
  }

  /* Find a node with a given id. If found == node pointer. Not found == nullptr.
  Don't really need function but since I had to refractor I didn't feel like changing. */
  Node* find_node(int id) {
    unordered_map<int, Node*>::const_iterator it;
    it = node_map.find(id);
    if (it != node_map.end()) {
      return it->second;
    }
    return nullptr;
  }


  /* Addes an edge from one node to the next. 
    * If either id or edge does not exist, it will create and insert into graph*/
  void add_edge(int id, int edge, int weight) {
    // Make sure id node exists.
    Node* n = find_node(id);
    if (n == nullptr) {
      n = new Node();
      n->id = id;
      node_map[id] = n;
    }
    n->edges.push_back(edge);

    // Make sure target exists.
    Node *target = find_node(edge);
    if (target == nullptr) {
      target = new Node();
      target->id = edge;
      node_map[edge] = target;
    }

    n->weight = weight;
  }


  /* First entry in the vector will be the cost of the graph. 
   * The next numbers will be the pairs to move to. */
  pair<int, vector<int>> dijkstra(int start_id, int end_id, int cols) {
    unordered_map<int, int> distances;  // Stores shortest distance to each node.
    unordered_map<int, int> prev;       // Stores reverse path to the first entry.
    unordered_map<int, int> visited;    // Stores what nodes have been visited.
    multimap<int, int> pq;              // Priority queue w/ distance as first and id as second.

    // Initialize distances for all nodes.
    for (int i = 0; i < (int)node_map.size(); i++) {
      distances[i] = numeric_limits<int>::max();
    }

    // Start node initialization.
    distances[start_id] = 0;
    pq.insert(make_pair(0, start_id));

    while (!pq.empty()) {
      multimap<int, int>::iterator it = pq.begin();
      int cur_dis = it->first;
      int cur_id = it->second;
      pq.erase(it);

      if (visited[cur_id]) continue; // Skip if processed.
      visited[cur_id] = true;

      Node* cur = find_node(cur_id);
      
      // Iterate through all adjacent nodes.
      for (int i = 0; i < (int)cur->edges.size(); i++) {
        Node* adjacent = find_node(cur->edges[i]);
        int new_dis = cur_dis + cur->weight; 

        // If new calculated distance is smaller than old distance.
        if (new_dis < distances[adjacent->id]) {
          distances[adjacent->id] = new_dis;
          prev[adjacent->id] = cur_id;
          pq.insert(make_pair(new_dis, adjacent->id));
        }
      }
    }

    // At this point prev will contain a path from any node.
    int start = end_id;
    int total_cost = distances[end_id];
    vector<int> final_path;

    while (start != start_id) {
      final_path.push_back(start % cols);
      final_path.push_back(start / cols);
      start = prev[start];
    }

    final_path.push_back(start % cols);
    final_path.push_back(start / cols);
    reverse(final_path.begin(), final_path.end());

    return {total_cost, final_path};
  }
};

/* When we read in the nodes, we need to make a unique id for the node.
 * The weight we assign to each node will depend on the character we read in. */
vector<int> read_and_store(Graph &graph) {
  int n_tiles, tile_cost, rows, cols, weight, start_r, start_c, end_r, end_c;
  char tile_char;
  unordered_map <char, int> tile_map;

  // Get weight mapping from cin
  cin >> n_tiles;
  for (int i = 0; i < n_tiles; i++) {
    cin >> tile_char >> tile_cost;
    tile_map[tile_char] = tile_cost;
  }

  // Read in the board and store in the provided graph.
  cin >> rows >> cols;
  for (int i = 0; i < rows; i++) {
    for (int k = 0; k < cols; k++) {
      // Getting weight
      cin >> tile_char;
      weight = tile_map[tile_char];

      if (i < rows - 1) { // Square below exists.
        graph.add_edge(i * cols + k, (i + 1) * cols + k, weight);
      }
      if (i > 0) { // Square above exists.
        graph.add_edge(i * cols + k, (i - 1) * cols + k, weight);
      }
      if (k < cols - 1) { // Square right exists
        graph.add_edge(i * cols + k, i * cols + (k + 1), weight);
      }
      if (k > 0) { // Square left exists
        graph.add_edge(i * cols + k, i * cols + (k - 1), weight);
      }
    }
  }

  cin >> start_r >> start_c >> end_r >> end_c;
  
  // Returning metadata
  return {rows, cols, start_r, start_c, end_r, end_c};
}

int main() {
  vector<int> data; 
  int start_pos, end_pos;
  Graph board;

  // {rows, cols, start_r, start_c, end_r, end_c}
  data = read_and_store(board);

  start_pos = data[1] * data[2] + data[3];
  end_pos   = data[1] * data[4] + data[5];

  // {total cost, path to follow}
  pair<int, vector<int>> path;
  path = board.dijkstra(start_pos, end_pos, data[1]);

  cout << path.first << endl;
  for (int i = 0; i < (int)path.second.size(); i+=2) {
    cout << path.second[i] << " " << path.second[i+1] << endl;
  }
}