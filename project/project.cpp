#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <cctype>
using namespace std;

const int MAX = 100;
float A[MAX][MAX] = { 0 }; 
float B[MAX] = { 0 };      
int n;                  
int vars = 0;             


void parseEquation(string eq, int row) {
    int i = 0;
    int sign = 1;
    float num = 0;
    bool hasNum = false;

    while (eq[i] != '=') {
        if (eq[i] == '+') {
            sign = 1;
            i++;
        }
        else if (eq[i] == '-') {
            sign = -1;
            i++;
        }

        num = 0;
        hasNum = false;
        while (isdigit(eq[i]) || eq[i] == '.') {
            hasNum = true;
            num = num * 10 + (eq[i] - '0');
            i++;
        }

        if (eq[i] == 'x') {
            if (!hasNum) num = 1;  
            i++;                    
            int idx = 0;
            while (isdigit(eq[i])) {
                idx = idx * 10 + (eq[i] - '0');
                i++;
            }
            idx--; 
            A[row][idx] += sign * num;
            if (idx + 1 > vars) vars = idx + 1;
        }
    }

    i++; 
    B[row] = atof(eq.substr(i).c_str());
}


void printNumVars() {
    cout << vars << endl;
}


void printEquation(int i) {
    bool first = true;
    for (int j = 0; j < vars; j++) {
        if (A[i][j] != 0) {
            if (!first && A[i][j] > 0) cout << "+";
            if (A[i][j] == 1) cout << "x" << j + 1;
            else if (A[i][j] == -1) cout << "-x" << j + 1;
            else cout << A[i][j] << "x" << j + 1;
            first = false;
        }
    }
    cout << "=" << B[i] << endl;
}


void printColumn(int x) {
    for (int i = 0; i < n; i++)
        cout << A[i][x] << endl;
}


void addEq(int a, int b) {
    bool first = true;
    for (int j = 0; j < vars; j++) {
        float val = A[a][j] + A[b][j];
        if (val != 0) {
            if (!first && val > 0) cout << "+";
            if (val == 1) cout << "x" << j + 1;
            else if (val == -1) cout << "-x" << j + 1;
            else cout << val << "x" << j + 1;
            first = false;
        }
    }
    cout << "=" << B[a] + B[b] << endl;
}

void subtractEq(int a, int b) {
    bool first = true;
    for (int j = 0; j < vars; j++) {
        float val = A[a][j] - A[b][j];
        if (val != 0) {
            if (!first && val > 0) cout << "+";
            if (val == 1) cout << "x" << j + 1;
            else if (val == -1) cout << "-x" << j + 1;
            else cout << val << "x" << j + 1;
            first = false;
        }
    }
    cout << "=" << B[a] - B[b] << endl;
}


float det3(float mat[3][3]) {
    return
        mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
        mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
        mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}


void solve3() {
    if (vars != 3 || n != 3) {
        cout << "Cannot solve: only 3x3 supported" << endl;
        return;
    }

    float D[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            D[i][j] = A[i][j];

    float D_value = det3(D);
    if (D_value == 0) {
        cout << "No Solution" << endl;
        return;
    }

    for (int k = 0; k < 3; k++) {
        float temp = 0;
        for (int i = 0; i < 3; i++) {
            temp = D[i][k];
            D[i][k] = B[i];
        }
        float Dx = det3(D);
        cout << "x" << k + 1 << "=" << Dx / D_value << endl;
        for (int i = 0; i < 3; i++) D[i][k] = temp;
    }
}

int main() {
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string eq;
        getline(cin, eq);
        parseEquation(eq, i);
    }

    string cmd;
    while (cin >> cmd) {
        if (cmd == "quit") break;
        else if (cmd == "num_vars") printNumVars();
        else if (cmd == "equation") {
            int i; cin >> i;
            printEquation(i - 1);
        }
        else if (cmd == "column") {
            string var; cin >> var;
            int x = stoi(var.substr(1)) - 1; // x2 -> index 1
            printColumn(x);
        }
        else if (cmd == "add") {
            int a, b; cin >> a >> b;
            addEq(a - 1, b - 1);
        }
        else if (cmd == "subtract") {
            int a, b; cin >> a >> b;
            subtractEq(a - 1, b - 1);
        }
        else if (cmd == "solve") {
            solve3();
        }
    }

    return 0;
}
