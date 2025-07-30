#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

class minecraftCoords {
    pair<int, pair<int, int>> coords = {};
    public:
        bool operator==(const minecraftCoords& other) const {
        return coords == other.coords;
    }
    bool operator!=(const minecraftCoords& other) const {
        return !(*this == other);
    }
        void setCoords(int x, int y, int z) {
            coords.first = x;
            coords.second.first = y;
            coords.second.second = z;
        };
        void printCoords() {
            cout << "Location: " << coords.first << ", " << coords.second.first << ", " << coords.second.second << endl;
        };
        pair<int, pair<int,int>> getCoords() {
            return coords;
        }
        pair<int, pair<int,int>> changeX(int change) {
            if ((coords.first + change > -30) && (coords.first + change < 30)) {
            coords.first = coords.first + change;
            }
            return coords;
        };
        pair<int, pair<int,int>> changeY(int change) {
            if ((coords.second.first + change > -30) && (coords.second.first + change < 30)) {
            coords.second.first = coords.second.first + change;
            }
            return coords;
        };
        pair<int, pair<int,int>> changeZ(int change) {
            if ((coords.second.second + change > -30) && (coords.second.second + change < 30)) {
            coords.second.second = coords.second.second + change;
            }
            return coords;
        };

        double distanceTo(pair<int, pair<int, int>> otherCoords) {
            int x1 = coords.first;
            int y1 = coords.second.first;
            int z1 = coords.second.second;

            int x2 = otherCoords.first;
            int y2 = otherCoords.second.first;
            int z2 = otherCoords.second.second;

    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) + pow(z2 - z1, 2));
}
    bool isInKillZone(pair<int, pair<int, int>> otherCoords) {
    int x1 = coords.first;
    int y1 = coords.second.first;
    int z1 = coords.second.second;

    int x2 = otherCoords.first;
    int y2 = otherCoords.second.first;
    int z2 = otherCoords.second.second;

    return (abs(x1 - x2) <= 1) && (abs(y1 - y2) <= 1) && (abs(z1 - z2) <= 1);
}


    void startGame() {
        minecraftCoords myCoords;
        myCoords.setCoords(0, 0, 0);
        myCoords.printCoords();
        char input;
        vector<pair<int, pair<int,int>>> path;
        int numBombs = 5 + (rand() % 21);
        vector<pair<int, pair<int, int>>> bombs;
        for (int i = 0; i < numBombs; i++) {
            int bombX = -25 + (rand() % 51);
            int bombY = -25 + (rand() % 51);
            int bombZ = -25 + (rand() % 51);
            bombs.push_back({bombX, {bombY, bombZ}});
        }
        ofstream bombFile("bombs.txt");
        for (const auto& b : bombs) {
            bombFile << b.first << " " << b.second.first << " " << b.second.second << endl;
        }
        bombFile.close();
        int treasureX = -25 + (rand() % 51);
        int treasureY = -25 + (rand() % 51);
        int treasureZ = -25 + (rand() % 51);
        pair<int, pair<int, int>> treasureCoords = {};
        treasureCoords.first = treasureX;
        treasureCoords.second.first = treasureY;
        treasureCoords.second.second = treasureZ;
        ofstream treasureFile("treasure.txt");
        treasureFile << treasureCoords.first << " " << treasureCoords.second.first << " " << treasureCoords.second.second << endl;
        treasureFile.close();
        double startingDistance = myCoords.distanceTo(treasureCoords);
        double counter = 0;
        double score;
        while (true) {
            cin >> input;
            minecraftCoords beforeCoords = myCoords;
            if (input == 'w') {
                myCoords.changeX(1);   
                myCoords.printCoords();
            }
            if (input == 's') {
                myCoords.changeX(-1);   
                myCoords.printCoords();
            }
            if (input == 'a') {
                myCoords.changeZ(-1);   
                myCoords.printCoords();
            }
            if (input == 'd') {
                myCoords.changeZ(1);   
                myCoords.printCoords();
            }
            if (input == '-') {
                myCoords.changeY(1);   
                myCoords.printCoords();
            }
            if (input == 'c') {
                myCoords.changeY(-1);   
                myCoords.printCoords();
            }
            if (input == 'x') {
                goto end;
            }
            if (beforeCoords != myCoords) {
                counter += 1;
                path.push_back(myCoords.getCoords());
            }
            for (auto bomb : bombs) {
                if (myCoords.isInKillZone(bomb)) {
                    cout << "BOOM! You entered the kill zone. Game over." << endl;
                    goto end;
                }
        }
            if (myCoords.getCoords() == treasureCoords) {
                cout << "Treasure found, you win!" << endl;
                score = counter / startingDistance;
                cout << "Score: " << score << endl;
                goto end;
            }
            cout << "Thermometer: ";
            double d = myCoords.distanceTo(treasureCoords);
            if (d >= 86){
                cout << "freezing fucking cold" << endl;
            }
            else if (d >= 75 && d <= 86) {
                cout << "iceberg" << endl;
            }
            else if (d >= 60 && d <= 75) {
                cout << "COLD" << endl;
            }
            else if (d >= 40 && d <= 60) {
                cout << "chilly" << endl;
            }
            else if (d >= 33 && d <= 40) {
                cout << "getting a bit chilly" << endl;
            }
            else if (d >= 22 && d <= 33) {
                cout << "room temp" << endl;
            }
            else if (d >= 15 && d <= 22) {
                cout << "getting warmer" << endl;
            }
            else if (d >= 10 && d <= 15) {
                cout << "heating up" << endl;
            }
            else if (d >= 7 && d <= 10) {
                cout << "HOT" << endl;
            }
            else if (d >= 3 && d <= 7) {
                cout << "FLAMING HOT" << endl;
            }
            else if (d >= 1 && d <= 3) {
                cout << "SUPER FUCKING HOT" << endl;
                cout << "Distance: " << myCoords.distanceTo(treasureCoords) << endl;
            }
        }
        end:
        ofstream outFile("path_data.txt");
        for (const auto& p : path) {
            outFile << p.first << " " << p.second.first << " " << p.second.second << endl;
        }
        outFile.close();
        system("python visual.py");
    };
};



int main() {
    srand(time(0));
    minecraftCoords myCoords;
    myCoords.startGame();
    return 0;
}