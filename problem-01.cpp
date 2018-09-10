/*
给出整数0 ～ n - 1的一个排列，求环的个数

input 
10
1 0 4 2 8 5 7 9 6 3

output
3
*/

#include <cstdio>
#include <vector>

using namespace std;

int f(int n, int *a)
{
    vector<int> res;
    int rnum = 0;
    res.assign(n, -1);
    for (int i = 0; i < n; i++){
        //printf("%d\n",i);
        if (res[i] != -1) continue;
        res[i] = ++rnum;
        //printf("find a new ring %d",i);
        int j = a[i];
        while (res[j] == -1){
            //printf("%d is in the same ring\n", j);
            res[j] = rnum;
            j = a[j];
        }
    }
    return rnum;
}

int main()
{
    int n  = 10;
    int a[] = {1, 0, 4, 2, 8, 5, 7, 9, 6, 3};
    printf("%d\n", f(n,a));
    return 0;
}

/*
0 1 2 3 4 5 6 7 8 9
1 0 4 2 8 5 7 9 6 3

0 - 1
2 - 4 - 8 - 6 - 7 - 9 - 3 - 2
5 - 5

output: 3
*/