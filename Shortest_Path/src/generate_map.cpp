#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateMap(int N, vector<vector<char>>& map, const vector<char>& tileTypes) {
    int numTileTypes = tileTypes.size();

    srand(time(0));

    for (int i = 0; i < N; i++) {   //generate random tiles for the map
        for (int j = 0; j < N; j++) {
            map[i][j] = tileTypes[rand() % numTileTypes];
        }
    }
}

//function to write map to a .txt file
void saveMapToFile(const string& filename, int N, const vector<char>& tileTypes, const vector<int>& tileValues, const vector<vector<char>>& map, int startX, int startY, int endX, int endY) {
    ofstream outFile(filename);

    outFile << tileTypes.size() << endl;    //write number of tile types

    for (int i = 0; i < (int)tileTypes.size(); i++) {    //write each tile type and its value
        outFile << tileTypes[i] << " " << tileValues[i] << endl;
    }

    outFile << N << " " << N << endl;  //write the grid dimensions

    for (int i = 0; i < N; i++) {   //write the map without extra space at the end of each line
        for (int j = 0; j < N; j++) {
            outFile << map[i][j];
            if (j < N - 1) {
                outFile << " "; 
            }
        }
        outFile << endl;
    }

    outFile << startX << " " << startY << endl; //write the map without extra space at the end of each line
    outFile << endX << " " << endY << endl;

    outFile.close();
}

int main() {
    int N;
    cout << "Enter the size of the map (N): ";
    cin >> N;

    vector<char> tileTypes = {'f', 'g', 'G', 'h', 'm', 'r'}; //tile types
    vector<int> tileValues = {3, 1, 2, 4, 7, 5}; //tile values

    vector<vector<char>> map(N, vector<char>(N));

    generateMap(N, map, tileTypes); //generate the random map
 
    int startX = 0, startY = 0; //start and end points
    int endX = N - 1, endY = N - 1;

    saveMapToFile("random_map.txt", N, tileTypes, tileValues, map, startX, startY, endX, endY);

    return 0;
}
