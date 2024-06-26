#include "Cube.h"

using namespace std;

mt19937 Cube::rng((int) chrono::steady_clock::now().time_since_epoch().count());
vector<vector<array<int, 3>>> Cube::cornerPositions;
map<array<int, 3>, int> Cube::cornerToInt;
vector<int> Cube::eightMap;
vector<int> Cube::sixMap;
vector<char> Cube::cornerDistance;
vector<char> Cube::edgeDistance1;
vector<char> Cube::edgeDistance2;
vector<vector<array<int, 3>>> Cube::edgePositions;
map<array<int, 2>, int> Cube::edgeToInt;
bool Cube::initialized = false;
vector<int> Cube::factorial;

void Cube::initializeStatics() {
    if (initialized) return;
    initialized = true;

    cornerPositions = {
        {{1, 0, 0}, {0, 2, 0}, {2, 2, 2}},
        {{1, 0, 2}, {0, 2, 2}, {4, 2, 0}},
        {{1, 2, 0}, {2, 2, 0}, {5, 2, 2}},
        {{1, 2, 2}, {4, 2, 2}, {5, 2, 0}},
        {{3, 0, 0}, {2, 0, 0}, {5, 0, 2}},
        {{3, 0, 2}, {4, 0, 2}, {5, 0, 0}},
        {{3, 2, 0}, {0, 0, 0}, {2, 0, 2}},
        {{3, 2, 2}, {0, 0, 2}, {4, 0, 0}},
    };

    cornerToInt = {
        {{0, 1, 2}, 0},
        {{0, 1, 4}, 1},
        {{0, 2, 3}, 2},
        {{0, 3, 4}, 3},
        {{1, 2, 5}, 4},
        {{1, 4, 5}, 5},
        {{2, 3, 5}, 6},
        {{3, 4, 5}, 7},
    };

    edgePositions = {
        {{0, 1, 0}, {2, 1, 2}},
        {{0, 1, 2}, {4, 1, 0}},
        {{5, 1, 0}, {4, 1, 2}},
        {{5, 1, 2}, {2, 1, 0}},
        {{1, 0, 1}, {0, 2, 1}},
        {{3, 0, 1}, {5, 0, 1}},
        {{1, 1, 0}, {2, 2, 1}},
        {{1, 1, 2}, {4, 2, 1}},
        {{1, 2, 1}, {5, 2, 1}},
        {{3, 1, 0}, {2, 0, 1}},
        {{3, 1, 2}, {4, 0, 1}},
        {{3, 2, 1}, {0, 0, 1}},
    };

    edgeToInt = {
        {{0, 1}, 0},
        {{0, 2}, 1},
        {{0, 4}, 2},
        {{2, 5}, 3},
        {{3, 5}, 4},
        {{4, 5}, 5},
        {{0, 3}, 6},
        {{1, 2}, 7},
        {{1, 4}, 8},
        {{1, 5}, 9},
        {{2, 3}, 10},
        {{3, 4}, 11},
    };

    factorial = {
        1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800
    };

    initializeEightMap();
    initializeSixMap();
    initializeCornerDistance();
    initializeEdgeDistance();
}

void Cube::initializeEightMap() {
    eightMap.resize(16777216);
    vector<int> permutation(8);
    iota(permutation.begin(), permutation.end(), 0);
    int id = 0;
    do {
        int calc = 0, pwr = 1;
        for (int x : permutation) {
            calc += pwr * x;
            pwr *= 8;
        }
        eightMap[calc] = id++;
    } while (next_permutation(permutation.begin(), permutation.end()));
}

void Cube::initializeSixMap() {
    sixMap.resize(46656);
    vector<int> permutation(6);
    iota(permutation.begin(), permutation.end(), 0);
    int id = 0;
    do {
        int calc = 0, pwr = 1;
        for (int x : permutation) {
            calc += pwr * x;
            pwr *= 6;
        }
        sixMap[calc] = id++;
    } while (next_permutation(permutation.begin(), permutation.end()));
}

// BFS to calculate the distance to the solved state for every configuration of corner pieces
void Cube::initializeCornerDistance() {
    // N = 8! * 3 ^ 7
    // const int N = 88179840;
    // cornerDistance.resize(N);
    // cout << N << endl;
    // Cube c;
    // queue<Cube> fila;
    // fila.push(c);
    // cornerDistance[c.cornerMapping()] = 1;
    // int cnt = 0;
    // while (!fila.empty()) {
    //     c = fila.front();
    //     fila.pop();
    //     int d = cornerDistance[c.cornerMapping()];
    //     for (int i = 0; i < 18; i++) {
    //         c.performOperation(i);
    //         int cm = c.cornerMapping();
    //         if (!cornerDistance[cm]) {
    //             cornerDistance[cm] = d + 1;
    //             fila.push(c); 
    //         }
    //         if (i&1) c.performOperation(i - 1);
    //         else c.performOperation(i + 1);
    //     }
    //     cnt++;
    //     if (cnt % 100000 == 0) cout << cnt << endl;
    // }
    // for (int i = 0; i < N; i++) cout << cornerDistance[i] - 1 << '\n';
}

// BFS to calculate the distance to the solved state for every configuration of the first and second set of edge pieces
void Cube::initializeEdgeDistance() {
    // N = nck(12, 6) * 6! * 2 ^ 6
    const int N = 42577920;
    edgeDistance1.resize(N);
    edgeDistance2.resize(N);
    cout << N << endl;
    Cube c;
    queue<Cube> fila;
    fila.push(c);
    pair<int, int> em = c.edgeMapping();
    edgeDistance1[em.first] = 1;
    edgeDistance2[em.second] = 1;
    int cnt = 0;
    while (!fila.empty()) {
        c = fila.front();
        fila.pop();
        em = c.edgeMapping();
        int d1 = edgeDistance1[em.first], d2 = edgeDistance2[em.second];
        for (int i = 0; i < 18; i++) {
            c.performOperation(i);
            em = c.edgeMapping();
            if (!edgeDistance1[em.first] || !edgeDistance2[em.second]) {
                if (!edgeDistance1[em.first])
                    edgeDistance1[em.first] = d1 + 1;
                if (!edgeDistance2[em.second])
                    edgeDistance2[em.second] = d2 + 1;
                fila.push(c); 
            }
            if (i&1) c.performOperation(i - 1);
            else c.performOperation(i + 1);
        }
        cnt++;
        if (cnt % 100000 == 0) cout << cnt << endl;
    }
    for (int i = 0; i < N; i++) cout << edgeDistance1[i] - 1 << '\n';
    for (int i = 0; i < N; i++) cout << edgeDistance2[i] - 1 << '\n';
}

Cube::Cube() : v(6) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) 
                this->set(i, j, k, i);
        }
    }
}

Cube::Cube(const vector<int>& _v) : v(_v) {}

Cube::Cube(const Cube& other) : v(other.v) {}

void Cube::set(int face, int i, int j, int cor) {
    int bit = 9 * i + 3 * j;
    int val = this->v[face];
    for (int add = 0; add < 3; add++)
        if (!!(val & (1 << (bit + add))) != !!(cor & (1 << add))) 
            val ^= (1 << (bit + add));
    this->v[face] = val;
}

int Cube::getColor(int face, int i, int j) const {
    int bit = 9 * i + 3 * j;
    return (this->v[face] >> bit) & 7;
}

Cube Cube::copyCube() const {
    return Cube(*this);
}

void Cube::print() const {
    cout << "Printing Cube:" << endl;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cout << this->getColor(i, j, k);
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}

/*
Convenções:
0 é azul
1 é branco
2 é laranja
3 é amarelo
4 é vermelho
5 é verde

A face frontal é a branca, cuja orientação aponta pra face azul
A orientação da face amarela aponta pra face verde
A orientação das outras têm a branca como base, ou seja, apontam para a amarela
*/

void Cube::rightClock() {
    Cube temp = this->copyCube();

    temp.set(4, 0, 1, this->getColor(4, 1, 0));
    temp.set(4, 1, 0, this->getColor(4, 2, 1));
    temp.set(4, 2, 1, this->getColor(4, 1, 2));
    temp.set(4, 1, 2, this->getColor(4, 0, 1));

    temp.set(4, 0, 0, this->getColor(4, 2, 0));
    temp.set(4, 2, 0, this->getColor(4, 2, 2));
    temp.set(4, 2, 2, this->getColor(4, 0, 2));
    temp.set(4, 0, 2, this->getColor(4, 0, 0));

    temp.set(0, 0, 2, this->getColor(1, 0, 2));
    temp.set(0, 1, 2, this->getColor(1, 1, 2));
    temp.set(0, 2, 2, this->getColor(1, 2, 2));

    temp.set(3, 0, 2, this->getColor(0, 0, 2));
    temp.set(3, 1, 2, this->getColor(0, 1, 2));
    temp.set(3, 2, 2, this->getColor(0, 2, 2));

    temp.set(5, 2, 0, this->getColor(3, 0, 2));
    temp.set(5, 1, 0, this->getColor(3, 1, 2));
    temp.set(5, 0, 0, this->getColor(3, 2, 2));

    temp.set(1, 0, 2, this->getColor(5, 2, 0));
    temp.set(1, 1, 2, this->getColor(5, 1, 0));
    temp.set(1, 2, 2, this->getColor(5, 0, 0));

    *this = temp;
}

void Cube::rightAntiClock() {
    Cube temp = this->copyCube();

    temp.set(4, 0, 1, this->getColor(4, 1, 2));
    temp.set(4, 1, 0, this->getColor(4, 0, 1));
    temp.set(4, 2, 1, this->getColor(4, 1, 0));
    temp.set(4, 1, 2, this->getColor(4, 2, 1));

    temp.set(4, 0, 0, this->getColor(4, 0, 2));
    temp.set(4, 2, 0, this->getColor(4, 0, 0));
    temp.set(4, 2, 2, this->getColor(4, 2, 0));
    temp.set(4, 0, 2, this->getColor(4, 2, 2));

    temp.set(0, 0, 2, this->getColor(3, 0, 2));
    temp.set(0, 1, 2, this->getColor(3, 1, 2));
    temp.set(0, 2, 2, this->getColor(3, 2, 2));

    temp.set(3, 0, 2, this->getColor(5, 2, 0));
    temp.set(3, 1, 2, this->getColor(5, 1, 0));
    temp.set(3, 2, 2, this->getColor(5, 0, 0));

    temp.set(5, 0, 0, this->getColor(1, 2, 2));
    temp.set(5, 1, 0, this->getColor(1, 1, 2));
    temp.set(5, 2, 0, this->getColor(1, 0, 2));

    temp.set(1, 0, 2, this->getColor(0, 0, 2));
    temp.set(1, 1, 2, this->getColor(0, 1, 2));
    temp.set(1, 2, 2, this->getColor(0, 2, 2));

    *this = temp;
}

void Cube::upClock() {
    Cube temp = this->copyCube();

    temp.set(0, 0, 1, this->getColor(0, 1, 0));
    temp.set(0, 1, 0, this->getColor(0, 2, 1));
    temp.set(0, 2, 1, this->getColor(0, 1, 2));
    temp.set(0, 1, 2, this->getColor(0, 0, 1));

    temp.set(0, 0, 0, this->getColor(0, 2, 0));
    temp.set(0, 2, 0, this->getColor(0, 2, 2));
    temp.set(0, 2, 2, this->getColor(0, 0, 2));
    temp.set(0, 0, 2, this->getColor(0, 0, 0));

    temp.set(2, 0, 2, this->getColor(1, 0, 0));
    temp.set(2, 1, 2, this->getColor(1, 0, 1));
    temp.set(2, 2, 2, this->getColor(1, 0, 2));

    temp.set(3, 2, 0, this->getColor(2, 2, 2));
    temp.set(3, 2, 1, this->getColor(2, 1, 2));
    temp.set(3, 2, 2, this->getColor(2, 0, 2));

    temp.set(4, 0, 0, this->getColor(3, 2, 0));
    temp.set(4, 1, 0, this->getColor(3, 2, 1));
    temp.set(4, 2, 0, this->getColor(3, 2, 2));

    temp.set(1, 0, 0, this->getColor(4, 2, 0));
    temp.set(1, 0, 1, this->getColor(4, 1, 0));
    temp.set(1, 0, 2, this->getColor(4, 0, 0));

    *this = temp;
}

void Cube::upAntiClock() {
    Cube temp = this->copyCube();

    temp.set(0, 0, 1, this->getColor(0, 1, 2));
    temp.set(0, 1, 0, this->getColor(0, 0, 1));
    temp.set(0, 2, 1, this->getColor(0, 1, 0));
    temp.set(0, 1, 2, this->getColor(0, 2, 1));

    temp.set(0, 0, 0, this->getColor(0, 0, 2));
    temp.set(0, 2, 0, this->getColor(0, 0, 0));
    temp.set(0, 2, 2, this->getColor(0, 2, 0));
    temp.set(0, 0, 2, this->getColor(0, 2, 2));

    temp.set(2, 0, 2, this->getColor(3, 2, 2));
    temp.set(2, 1, 2, this->getColor(3, 2, 1));
    temp.set(2, 2, 2, this->getColor(3, 2, 0));

    temp.set(3, 2, 2, this->getColor(4, 2, 0));
    temp.set(3, 2, 1, this->getColor(4, 1, 0));
    temp.set(3, 2, 0, this->getColor(4, 0, 0));

    temp.set(4, 0, 0, this->getColor(1, 0, 2));
    temp.set(4, 1, 0, this->getColor(1, 0, 1));
    temp.set(4, 2, 0, this->getColor(1, 0, 0));

    temp.set(1, 0, 0, this->getColor(2, 0, 2));
    temp.set(1, 0, 1, this->getColor(2, 1, 2));
    temp.set(1, 0, 2, this->getColor(2, 2, 2));

    *this = temp;
}

void Cube::leftClock() {
    Cube temp = this->copyCube();

    temp.set(2, 0, 1, this->getColor(2, 1, 0));
    temp.set(2, 1, 0, this->getColor(2, 2, 1));
    temp.set(2, 2, 1, this->getColor(2, 1, 2));
    temp.set(2, 1, 2, this->getColor(2, 0, 1));

    temp.set(2, 0, 0, this->getColor(2, 2, 0));
    temp.set(2, 2, 0, this->getColor(2, 2, 2));
    temp.set(2, 2, 2, this->getColor(2, 0, 2));
    temp.set(2, 0, 2, this->getColor(2, 0, 0));

    temp.set(0, 0, 0, this->getColor(3, 0, 0));
    temp.set(0, 1, 0, this->getColor(3, 1, 0));
    temp.set(0, 2, 0, this->getColor(3, 2, 0));

    temp.set(3, 0, 0, this->getColor(5, 2, 2));
    temp.set(3, 1, 0, this->getColor(5, 1, 2));
    temp.set(3, 2, 0, this->getColor(5, 0, 2));

    temp.set(5, 0, 2, this->getColor(1, 2, 0));
    temp.set(5, 1, 2, this->getColor(1, 1, 0));
    temp.set(5, 2, 2, this->getColor(1, 0, 0));

    temp.set(1, 0, 0, this->getColor(0, 0, 0));
    temp.set(1, 1, 0, this->getColor(0, 1, 0));
    temp.set(1, 2, 0, this->getColor(0, 2, 0));

    *this = temp;
}

void Cube::leftAntiClock() {
    Cube temp = this->copyCube();

    temp.set(2, 0, 1, this->getColor(2, 1, 2));
    temp.set(2, 1, 0, this->getColor(2, 0, 1));
    temp.set(2, 2, 1, this->getColor(2, 1, 0));
    temp.set(2, 1, 2, this->getColor(2, 2, 1));

    temp.set(2, 0, 0, this->getColor(2, 0, 2));
    temp.set(2, 2, 0, this->getColor(2, 0, 0));
    temp.set(2, 2, 2, this->getColor(2, 2, 0));
    temp.set(2, 0, 2, this->getColor(2, 2, 2));

    temp.set(0, 0, 0, this->getColor(1, 0, 0));
    temp.set(0, 1, 0, this->getColor(1, 1, 0));
    temp.set(0, 2, 0, this->getColor(1, 2, 0));

    temp.set(3, 0, 0, this->getColor(0, 0, 0));
    temp.set(3, 1, 0, this->getColor(0, 1, 0));
    temp.set(3, 2, 0, this->getColor(0, 2, 0));

    temp.set(5, 0, 2, this->getColor(3, 2, 0));
    temp.set(5, 1, 2, this->getColor(3, 1, 0));
    temp.set(5, 2, 2, this->getColor(3, 0, 0));

    temp.set(1, 0, 0, this->getColor(5, 2, 2));
    temp.set(1, 1, 0, this->getColor(5, 1, 2));
    temp.set(1, 2, 0, this->getColor(5, 0, 2));

    *this = temp;
}

void Cube::downClock() {
    Cube temp = this->copyCube();

    temp.set(5, 0, 1, this->getColor(5, 1, 0));
    temp.set(5, 1, 0, this->getColor(5, 2, 1));
    temp.set(5, 2, 1, this->getColor(5, 1, 2));
    temp.set(5, 1, 2, this->getColor(5, 0, 1));

    temp.set(5, 0, 0, this->getColor(5, 2, 0));
    temp.set(5, 2, 0, this->getColor(5, 2, 2));
    temp.set(5, 2, 2, this->getColor(5, 0, 2));
    temp.set(5, 0, 2, this->getColor(5, 0, 0));

    temp.set(2, 0, 0, this->getColor(3, 0, 2));
    temp.set(2, 1, 0, this->getColor(3, 0, 1));
    temp.set(2, 2, 0, this->getColor(3, 0, 0));

    temp.set(3, 0, 0, this->getColor(4, 0, 2));
    temp.set(3, 0, 1, this->getColor(4, 1, 2));
    temp.set(3, 0, 2, this->getColor(4, 2, 2));

    temp.set(4, 0, 2, this->getColor(1, 2, 2));
    temp.set(4, 1, 2, this->getColor(1, 2, 1));
    temp.set(4, 2, 2, this->getColor(1, 2, 0));

    temp.set(1, 2, 2, this->getColor(2, 2, 0));
    temp.set(1, 2, 1, this->getColor(2, 1, 0));
    temp.set(1, 2, 0, this->getColor(2, 0, 0));

    *this = temp;
}

void Cube::downAntiClock() {
    Cube temp = this->copyCube();

    temp.set(5, 0, 1, this->getColor(5, 1, 2));
    temp.set(5, 1, 0, this->getColor(5, 0, 1));
    temp.set(5, 2, 1, this->getColor(5, 1, 0));
    temp.set(5, 1, 2, this->getColor(5, 2, 1));

    temp.set(5, 0, 0, this->getColor(5, 0, 2));
    temp.set(5, 2, 0, this->getColor(5, 0, 0));
    temp.set(5, 2, 2, this->getColor(5, 2, 0));
    temp.set(5, 0, 2, this->getColor(5, 2, 2));

    temp.set(2, 0, 0, this->getColor(1, 2, 0));
    temp.set(2, 1, 0, this->getColor(1, 2, 1));
    temp.set(2, 2, 0, this->getColor(1, 2, 2));

    temp.set(3, 0, 0, this->getColor(2, 2, 0));
    temp.set(3, 0, 1, this->getColor(2, 1, 0));
    temp.set(3, 0, 2, this->getColor(2, 0, 0));

    temp.set(4, 0, 2, this->getColor(3, 0, 0));
    temp.set(4, 1, 2, this->getColor(3, 0, 1));
    temp.set(4, 2, 2, this->getColor(3, 0, 2));

    temp.set(1, 2, 0, this->getColor(4, 2, 2));
    temp.set(1, 2, 1, this->getColor(4, 1, 2));
    temp.set(1, 2, 2, this->getColor(4, 0, 2));

    *this = temp;
}

void Cube::frontClock() {
    Cube temp = this->copyCube();

    temp.set(1, 0, 1, this->getColor(1, 1, 0));
    temp.set(1, 1, 0, this->getColor(1, 2, 1));
    temp.set(1, 2, 1, this->getColor(1, 1, 2));
    temp.set(1, 1, 2, this->getColor(1, 0, 1));

    temp.set(1, 0, 0, this->getColor(1, 2, 0));
    temp.set(1, 2, 0, this->getColor(1, 2, 2));
    temp.set(1, 2, 2, this->getColor(1, 0, 2));
    temp.set(1, 0, 2, this->getColor(1, 0, 0));

    temp.set(0, 2, 0, this->getColor(2, 2, 0));
    temp.set(0, 2, 1, this->getColor(2, 2, 1));
    temp.set(0, 2, 2, this->getColor(2, 2, 2));

    temp.set(4, 2, 0, this->getColor(0, 2, 0));
    temp.set(4, 2, 1, this->getColor(0, 2, 1));
    temp.set(4, 2, 2, this->getColor(0, 2, 2));

    temp.set(5, 2, 0, this->getColor(4, 2, 0));
    temp.set(5, 2, 1, this->getColor(4, 2, 1));
    temp.set(5, 2, 2, this->getColor(4, 2, 2));

    temp.set(2, 2, 0, this->getColor(5, 2, 0));
    temp.set(2, 2, 1, this->getColor(5, 2, 1));
    temp.set(2, 2, 2, this->getColor(5, 2, 2));

    *this = temp;
}

void Cube::frontAntiClock() {
    Cube temp = this->copyCube();

    temp.set(1, 0, 1, this->getColor(1, 1, 2));
    temp.set(1, 1, 0, this->getColor(1, 0, 1));
    temp.set(1, 2, 1, this->getColor(1, 1, 0));
    temp.set(1, 1, 2, this->getColor(1, 2, 1));

    temp.set(1, 0, 0, this->getColor(1, 0, 2));
    temp.set(1, 2, 0, this->getColor(1, 0, 0));
    temp.set(1, 2, 2, this->getColor(1, 2, 0));
    temp.set(1, 0, 2, this->getColor(1, 2, 2));

    temp.set(5, 2, 0, this->getColor(2, 2, 0));
    temp.set(5, 2, 1, this->getColor(2, 2, 1));
    temp.set(5, 2, 2, this->getColor(2, 2, 2));

    temp.set(2, 2, 0, this->getColor(0, 2, 0));
    temp.set(2, 2, 1, this->getColor(0, 2, 1));
    temp.set(2, 2, 2, this->getColor(0, 2, 2));

    temp.set(0, 2, 0, this->getColor(4, 2, 0));
    temp.set(0, 2, 1, this->getColor(4, 2, 1));
    temp.set(0, 2, 2, this->getColor(4, 2, 2));

    temp.set(4, 2, 0, this->getColor(5, 2, 0));
    temp.set(4, 2, 1, this->getColor(5, 2, 1));
    temp.set(4, 2, 2, this->getColor(5, 2, 2));

    *this = temp;
}

void Cube::backClock() {
    Cube temp = this->copyCube();

    temp.set(3, 0, 1, this->getColor(3, 1, 0));
    temp.set(3, 1, 0, this->getColor(3, 2, 1));
    temp.set(3, 2, 1, this->getColor(3, 1, 2));
    temp.set(3, 1, 2, this->getColor(3, 0, 1));

    temp.set(3, 0, 0, this->getColor(3, 2, 0));
    temp.set(3, 2, 0, this->getColor(3, 2, 2));
    temp.set(3, 2, 2, this->getColor(3, 0, 2));
    temp.set(3, 0, 2, this->getColor(3, 0, 0));

    temp.set(5, 0, 0, this->getColor(2, 0, 0));
    temp.set(5, 0, 1, this->getColor(2, 0, 1));
    temp.set(5, 0, 2, this->getColor(2, 0, 2));

    temp.set(2, 0, 0, this->getColor(0, 0, 0));
    temp.set(2, 0, 1, this->getColor(0, 0, 1));
    temp.set(2, 0, 2, this->getColor(0, 0, 2));

    temp.set(0, 0, 0, this->getColor(4, 0, 0));
    temp.set(0, 0, 1, this->getColor(4, 0, 1));
    temp.set(0, 0, 2, this->getColor(4, 0, 2));

    temp.set(4, 0, 0, this->getColor(5, 0, 0));
    temp.set(4, 0, 1, this->getColor(5, 0, 1));
    temp.set(4, 0, 2, this->getColor(5, 0, 2));

    *this = temp;
}

void Cube::backAntiClock() {
    Cube temp = this->copyCube();

    temp.set(3, 0, 1, this->getColor(3, 1, 2));
    temp.set(3, 1, 0, this->getColor(3, 0, 1));
    temp.set(3, 2, 1, this->getColor(3, 1, 0));
    temp.set(3, 1, 2, this->getColor(3, 2, 1));

    temp.set(3, 0, 0, this->getColor(3, 0, 2));
    temp.set(3, 2, 0, this->getColor(3, 0, 0));
    temp.set(3, 2, 2, this->getColor(3, 2, 0));
    temp.set(3, 0, 2, this->getColor(3, 2, 2));

    temp.set(0, 0, 0, this->getColor(2, 0, 0));
    temp.set(0, 0, 1, this->getColor(2, 0, 1));
    temp.set(0, 0, 2, this->getColor(2, 0, 2));

    temp.set(4, 0, 0, this->getColor(0, 0, 0));
    temp.set(4, 0, 1, this->getColor(0, 0, 1));
    temp.set(4, 0, 2, this->getColor(0, 0, 2));

    temp.set(5, 0, 0, this->getColor(4, 0, 0));
    temp.set(5, 0, 1, this->getColor(4, 0, 1));
    temp.set(5, 0, 2, this->getColor(4, 0, 2));

    temp.set(2, 0, 0, this->getColor(5, 0, 0));
    temp.set(2, 0, 1, this->getColor(5, 0, 1));
    temp.set(2, 0, 2, this->getColor(5, 0, 2));

    *this = temp;
}

void Cube::verticalClock() {
    this->leftClock();
    this->rightAntiClock();
}

void Cube::verticalAntiClock() {
    this->leftAntiClock();
    this->rightClock();
}

void Cube::horizontalClock() {
    this->upClock();
    this->downAntiClock();
}

void Cube::horizontalAntiClock() {
    this->upAntiClock();
    this->downClock();
}

void Cube::transversalClock() {
    this->frontClock();
    this->backAntiClock();
}

void Cube::transversalAntiClock() {
    this->frontAntiClock();
    this->backClock();
}

void Cube::performOperation(int operationIndex) {
    switch (operationIndex) {
        case 0:
            rightAntiClock();
            break;
        case 1:
            rightClock();
            break;
        case 2:
            upClock();
            break;
        case 3:
            upAntiClock();
            break;
        case 4:
            leftClock();
            break;
        case 5:
            leftAntiClock();
            break;
        case 6:
            downClock();
            break;
        case 7:
            downAntiClock();
            break;
        case 8:
            frontClock();
            break;
        case 9:
            frontAntiClock();
            break;
        case 10:
            backClock();
            break;
        case 11:
            backAntiClock();
            break;
        case 12:
            verticalClock();
            break;
        case 13:
            verticalAntiClock();
            break;
        case 14:
            horizontalClock();
            break;
        case 15:
            horizontalAntiClock();
            break;
        case 16:
            transversalClock();
            break;
        case 17:
            transversalAntiClock();
            break;
        default:
            throw out_of_range("Invalid operation index. Index must be between 0 and 17.");
    }
}

// How many stickers are in the wrong place
int Cube::countDif() const {
    int ans = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                ans += this->getColor(i, j, k) != i;
            }
        }
    }
    return ans;

}

// Fitness based on Wrong Stickers
int Cube::fitnessWrongStickers(const vector<int> &x) {
    Cube temp = this->copyCube();
    int ans = temp.countDif();
    for (int i = 0; i < (int)x.size(); i++) {
        temp.performOperation(x[i]);
        ans = min(ans, temp.countDif());
    }
    return ans;
}

// LowerBound = max distance out of the three sets that we precalculated
char lowerBound(Cube &temp) {
    pair<int, int> em = temp.edgeMapping();
    int cm = temp.cornerMapping();
    return max({Cube::cornerDistance[cm], Cube::edgeDistance1[em.first], Cube::edgeDistance2[em.second]});
}

// Fitness based on Korf's pattern databases
int Cube::fitnessLowerBound(const vector<int> &x) {
    Cube temp = this->copyCube();
    char ans = cornerDistance[temp.cornerMapping()];
    for (int i = 0; i < (int)x.size(); i++) {
        temp.performOperation(x[i]);
        ans = min(ans, lowerBound(temp));
    }
    return ans;
}

int Cube::fitness(const vector<int> &x) {
    return this->fitnessLowerBound(x);
}

void Cube::scramble() {
    for (int i = 0; i < 100; i++) {
        this->performOperation(rng() % 18);
    }
}

// Prints the cube at the point that minimizes the fitness function
void Cube::findBest(const vector<int> &x) {
    Cube temp = this->copyCube();
    int ans = this->fitness(x);
    for (int i = 0; i < (int)x.size(); i++) {
        temp.performOperation(x[i]);

        // Change here if you are using the stickers fitness
        if (lowerBound(temp) == ans) {
            temp.print();
            break;
        }
    }
}

// Maps the corners to an int in the range [0, 8! * 3 ^ 7 - 1]
int Cube::cornerMapping() const {
    vector<int> permutation(8), orientation(8);
    for (int i = 0; i < 8; i++) {
        array<int, 3> colors, sortedColors;
        for (int j = 0; j < 3; j++) {
            colors[j] = this->getColor(cornerPositions[i][j][0], cornerPositions[i][j][1], cornerPositions[i][j][2]);
        }
        sortedColors = colors;
        sort(sortedColors.begin(), sortedColors.end());
        permutation[i] = cornerToInt[sortedColors];
        for (int j = 0; j < 3; j++) {
            if (colors[j] == sortedColors[0]) orientation[i] = j;
        }
    }
    int fat = 1, valFat = 0, pwr = 1, valPwr = 0;
    for (int i = 0; i < 8; i++) {
        valFat += fat * permutation[i];
        fat *= 8;
        if (i < 7) {
            valPwr += pwr * orientation[i];
            pwr *= 3;
        }
    }
    return valPwr * 40320 + eightMap[valFat];
}

// Maps a vector with 6 elements between 0 and 11 to an integer in the range [0, nck(12, 6) - 1]
int calculateNck(vector<int> &pos) {
    int id = 0, ans = 0;
    for (int i = 0; i < 12; i++) {
        if (pos[id] == i) {
            id++;
            if (id == 6) break;
        }
        else {
            ans += Cube::factorial[11 - i] / (Cube::factorial[5 - id] * Cube::factorial[6 - i + id]);
        }
    }
    return ans;
}

// Maps the first and second set of edges to an int in the range [0, nck(12, 6) * 6! * 2 ^ 6 - 1]
pair<int, int> Cube::edgeMapping() const{
    vector<int> permutation(12), orientation(12), positions1(6), positions2(6), perm1(6), perm2(6), orient1(6), orient2(6);
    for (int i = 0; i < 12; i++) {
        array<int, 2> colors, sortedColors;
        for (int j = 0; j < 2; j++) {
            colors[j] = this->getColor(edgePositions[i][j][0], edgePositions[i][j][1], edgePositions[i][j][2]);
        }
        sortedColors = colors;
        sort(sortedColors.begin(), sortedColors.end());
        permutation[i] = edgeToInt[sortedColors];
        for (int j = 0; j < 2; j++) {
            if (colors[j] == sortedColors[0]) orientation[i] = j;
        }
    }
    int id1 = 0, id2 = 0;
    for (int i = 0; i < 12; i++) {
        if (permutation[i] < 6) {
            positions1[id1] = i;
            perm1[id1] = permutation[i];
            orient1[id1] = orientation[i];
            id1++;
        }
        else {
            positions2[id2] = i;
            perm2[id2] = permutation[i] - 6;
            orient2[id2] = orientation[i];
            id2++;
        }
    }
    int fat = 1, valFat1 = 0, valFat2 = 0, pwr = 1, valPwr1 = 0, valPwr2 = 0;
    for (int i = 0; i < 6; i++) {
        valFat1 += fat * perm1[i];
        valFat2 += fat * perm2[i];
        fat *= 6;
        valPwr1 += pwr * orient1[i];
        valPwr2 += pwr * orient2[i];
        pwr *= 2;
    }
    int valNck1 = calculateNck(positions1), valNck2 = calculateNck(positions2);
    return {valNck1 * 64 * 720 + sixMap[valFat1] * 64 + valPwr1, valNck2 * 64 * 720 + sixMap[valFat2]* 64 + valPwr2};
}