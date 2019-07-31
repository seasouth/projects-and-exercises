#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void Q1(vector<int> &v, int n)
{
    int i;
    v.clear();
    for (i = 0; i < n; i++) v.push_back(i);
    for (i = 0; i < n; i++) v.push_back(i);
    for (i = 0; i < n; i++) v.push_back(i);
    for (i = 0; i < n; i++) v.push_back(i);
}

void Q2(vector<int> &v, int n)
{
    int i;
    v.clear();
    for (i = 0; i < n; i++) v.push_back(i);
}

int Q3(int n)
{
    if (n == 0) return 1;
    return 1 + Q3(n - 1);
}

int Q4(int n)
{
    if (n == 0) return 1;
    return Q4(n - 1) + Q4(n - 1);
}

void Q5(vector<int> &v, int n)
{
    int i, j;
    v.clear();
    for (i = 0; i < n; i++) {
        for (j = 0; j < i; j++) v.push_back(i);
    }
    for (i = 0; i < n; i++) {
        for (j = 1; j < n; j *= 2) v.push_back(i + j);
    }
}

int main()
{
    clock_t begin = clock();
    vector<int> v;
    
    Q3(200000);
    
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    printf("%f\n", elapsed);
}
