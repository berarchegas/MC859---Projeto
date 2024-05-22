#include "Cube.h"

using namespace std;

mt19937 Cube::rng((int) chrono::steady_clock::now().time_since_epoch().count());

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

// temp.set(4, 0, 1, this->getColor(4, 1, 2));

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

int Cube::fitness(const vector<int> &x) {
    Cube temp = this->copyCube();
    int ans = temp.countDif();
    for (int i = 0; i < (int)x.size(); i++) {
        temp.performOperation(x[i]);
        ans = min(ans, temp.countDif());
    }
    return ans;
}

void Cube::scramble() {
    for (int i = 0; i < 100; i++) {
        this->performOperation(rng() % 18);
    }
}

void Cube::findBest(const vector<int> &x) {
    Cube temp = this->copyCube();
    int ans = this->fitness(x);
    for (int i = 0; i < (int)x.size(); i++) {
        temp.performOperation(x[i]);
        if (temp.countDif() == ans) {
            temp.print();
            break;
        }
    }
}