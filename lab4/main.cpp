#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readGraph(const string& filename, int& n, int& m, int**& edges) {
    cout << "���� �� �����: " << filename << endl;
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "������� ��� �i������i �����: " << filename << endl;
        return;
    }

    inputFile >> n >> m;

    edges = new int* [m];
    for (int i = 0; i < m; ++i) {
        edges[i] = new int[2];
        inputFile >> edges[i][0] >> edges[i][1];
    }

    inputFile.close();
}

int** createAdjacencyMatrix(int n, int m, int** edges) {
    int** adjacencyMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        adjacencyMatrix[i] = new int[n]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        adjacencyMatrix[v][u] = 1;
    }

    return adjacencyMatrix;
}

int** createIncidenceMatrix(int n, int m, int** edges) {
    int** incidenceMatrix = new int* [n];
    for (int i = 0; i < n; ++i) {
        incidenceMatrix[i] = new int[m]();
    }

    for (int i = 0; i < m; ++i) {
        int v = edges[i][0] - 1;
        int u = edges[i][1] - 1;
        incidenceMatrix[v][i] = 1;
        incidenceMatrix[u][i] = -1;
    }

    return incidenceMatrix;
}

void printMatrix(int** matrix, int rows, int cols, const string& matrixName, const string& outputFile) {
    ofstream outFile(outputFile, ios::app);
    cout << matrixName << ":\n";
    outFile << matrixName << ":\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matrix[i][j] << " ";
            outFile << matrix[i][j] << " ";
        }
        cout << endl;
        outFile << endl;
    }
    cout << endl;
    outFile << endl;
    outFile.close();
}

void deleteMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    int n, m;
    int** edges = nullptr;
    string inputFile = "pds.txt";
    string outputFile = "pds1.txt";

    cout << "����i�� ����� ����� � ��i����� ������ (�� ������������� 'pds.txt'): ";
    getline(cin, inputFile);
    if (inputFile.empty()) inputFile = "pds.txt";

    cout << "����i�� ����� ����� ��� ���������� ���������� (�� ������������� 'pds1.txt'): ";
    getline(cin, outputFile);
    if (outputFile.empty()) outputFile = "pds1.txt";

    readGraph(inputFile, n, m, edges);

    if (edges == nullptr) {
        cout << "�������: ���i ����� �� ���� ����������i." << endl;
        return 1;
    }

    int** adjacencyMatrix = createAdjacencyMatrix(n, m, edges);
    int** incidenceMatrix = createIncidenceMatrix(n, m, edges);

    printMatrix(adjacencyMatrix, n, n, "������� ���i�����i", outputFile);
    printMatrix(incidenceMatrix, n, m, "������� i�����������i", outputFile);

    deleteMatrix(adjacencyMatrix, n);
    deleteMatrix(incidenceMatrix, n);

    for (int i = 0; i < m; ++i) {
        delete[] edges[i];
    }
    delete[] edges;

    cout << "������� ���������, ��������� ��������� � ���� " << outputFile << endl;

    return 0;
}
