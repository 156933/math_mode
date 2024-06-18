// 包含必要库
#include <stdio.h>
#include <stdbool.h>
// 定义常量
#define TOTAL_GROUPS 33     // 不同组合的数量
#define TOTAL_CANDIDATES 14 // 应聘者的数量

// 计数器
int num = 0;

// 定义整形二维数组，第一表示组，第二表示组内的成员,空缺用-1表示
int groups[TOTAL_GROUPS][3] = {
    {1, 2, 3}, {2, 3, 5}, {6, 7, 8}, {7, 8, 9}, {8, 9, 11}, {8, 10, 11}, {1, 2, -1}, {1, 5, -1}, {2, 3, -1}, {2, 5, -1}, {3, 4, -1}, {3, 5, -1}, {4, 5, -1}, {5, 10, -1}, {6, 7, -1}, {6, 8, -1}, {7, 9, -1}, {8, 9, -1}, {8, 10, -1}, {8, 11, -1}, {9, 10, 11}, {10, 11, -1}, {10, 13, -1}, {11, 12, -1}, {11, 13, -1}, {12, 14, -1}, {13, 14, -1}, {2, -1, -1}, {4, -1, -1}, {12, -1, -1}, {1, 7, -1}, {5, 8, -1}, {6, 9, -1}};

// 检查当前的组是否被覆盖
/*
如果当前comb[] = {0,1,2,3,4},那么S1,S2,S3,S4,S5被包含在检查组内
也就是说{1, 2, 3}, {2, 3, 5}, {6, 7, 8}, {7, 8, 9}, {8, 9, 11}包含S1-S5组
C1,C2,C3,C2,C3,C5,C6,C7,C8,C7,C8,C9,C9,C9,C11

定义一个布尔类型的，存放15个位置的数组covered(从数组的第二个元素1开始到14)初始化为false
遍历comb若出现C(i) 则将covered上对应的位置改为true

最后对covered遍历，若数组从1-14全部为true，则返回true表示当前组合覆盖了所有应聘者，反之返回false
此时cover={false,true,true,true,false,true,true,true,true,true,false,true,false,false,false}
            x     C1   C2   C3         C5   C6   C7   C8  C9          C11
显然这一个组合没有包括全部应聘者 返回false
*/
bool _covers(int comb[], int comb_size)
{
    bool covered[TOTAL_CANDIDATES + 1] = {false};
    for (int i = 0; i < comb_size; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            int candidate = groups[comb[i]][j];
            if (candidate != -1)
            {
                covered[candidate] = true;
            }
        }
    }
    for (int i = 1; i <= TOTAL_CANDIDATES; ++i)
    {
        if (!covered[i])
        {
            return false;
        }
    }
    return true;
}

// 对找到的组合进行打印
void _print(int comb[], int comb_size)
{
    printf("找到一个有效的%d组组合:\n", comb_size);
    num++;
    for (int i = 0; i < comb_size; ++i)
    {
        printf("[");
        for (int j = 0; j < 3; ++j)
        {
            if (groups[comb[i]][j] != -1)
            {
                printf("C%d", groups[comb[i]][j]);
                if (j < 2 && groups[comb[i]][j + 1] != -1)
                {
                    printf(", ");
                }
            }
        }
        printf("]");
        if (i < comb_size - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
}

// 使用递归进行对所有组的遍历
/*
start=0
comb_index=0
comb_size=5
函数开始:
    直接进入for循环,
    第一层：i=0,comb[]={0}，
    第二层: i=1,comb[]={0,1}, 代表选出S1,S2组
    ...
    第五层: i=4,comb[]={0,1,2,3,4}
    此时comb_index = comb_size进入if的判断
    第三十三层: i=32,comb[]={0,1,2,3,33}
    当start达到33时,此时for循环停止
    将会回溯comb[]={0,1,2,4,5}再进行循环判断,直至对全部组合完成遍历
*/
void _find(int start, int comb[], int comb_index, int comb_size)
{
    if (comb_index == comb_size)
    {
        if (_covers(comb, comb_size))
        {
            // 当条件符合，打印对应组合
            _print(comb, comb_size);
        }
        return;
    }
    for (int i = start; i < TOTAL_GROUPS; ++i)
    {
        comb[comb_index] = i;
        _find(i + 1, comb, comb_index + 1, comb_size);
    }
}
int main()
{
    int comb_5[5];
    int comb_6[6];

    printf("问题一：从33个组中选取5个组\n");
    _find(0, comb_5, 0, 5);

    printf("\n问题二：从33个组中选取6个组\n");
    _find(0, comb_6, 0, 6);
    printf("%d", num);

    return 0;
}
