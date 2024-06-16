#include <stdio.h>
#include <stdbool.h>

#define TOTAL_GROUPS 33
#define TOTAL_CANDIDATES 14

int num = 0;
// 定义组中包含的应聘者
int groups[TOTAL_GROUPS][3] = {
    {1, 2, 3}, {2, 3, 5}, {6, 7, 8}, {7, 8, 9}, {8, 9, 11}, {8, 10, 11}, {1, 2, -1}, {1, 5, -1}, {2, 3, -1}, {2, 5, -1}, {3, 4, -1}, {3, 5, -1}, {4, 5, -1}, {5, 10, -1}, {6, 7, -1}, {6, 8, -1}, {7, 9, -1}, {8, 9, -1}, {8, 10, -1}, {8, 11, -1}, {9, 10, 11}, {10, 11, -1}, {10, 13, -1}, {11, 12, -1}, {11, 13, -1}, {12, 14, -1}, {13, 14, -1}, {2, -1, -1}, {4, -1, -1}, {12, -1, -1}, {1, 7, -1}, {5, 8, -1}, {6, 9, -1}};

// 检查组合是否覆盖所有应聘者
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
        if (covered[i] == false)
        {
            return false;
        }
    }
    return true;
}

// 使用递归进行对所有组的遍历
void _find(int start, int comb[], int comb_index, int comb_size)
{
    if (comb_index > comb_size)
    {
        return;
    }
    if (comb_index == comb_size)
    {
        if (_covers(comb, comb_size))
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

    return 0;
}
