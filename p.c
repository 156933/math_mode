// ������Ҫ��
#include <stdio.h>
#include <stdbool.h>
// ���峣��
#define TOTAL_GROUPS 33     // ӦƸ������
#define TOTAL_CANDIDATES 14 //

// ������
int num = 0;

// �������ζ�ά���飬��һ��ʾ�飬�ڶ���ʾ���ڵĳ�Ա,��ȱ��-1��ʾ
int groups[TOTAL_GROUPS][3] = {
    {1, 2, 3}, {2, 3, 5}, {6, 7, 8}, {7, 8, 9}, {8, 9, 11}, {8, 10, 11}, {1, 2, -1}, {1, 5, -1}, {2, 3, -1}, {2, 5, -1}, {3, 4, -1}, {3, 5, -1}, {4, 5, -1}, {5, 10, -1}, {6, 7, -1}, {6, 8, -1}, {7, 9, -1}, {8, 9, -1}, {8, 10, -1}, {8, 11, -1}, {9, 10, 11}, {10, 11, -1}, {10, 13, -1}, {11, 12, -1}, {11, 13, -1}, {12, 14, -1}, {13, 14, -1}, {2, -1, -1}, {4, -1, -1}, {12, -1, -1}, {1, 7, -1}, {5, 8, -1}, {6, 9, -1}};

// ��鵱ǰ�����Ƿ񱻸���
/*
�����ǰcomb[] = {0,1,2,3,4},��ôS1,S2,S3,S4,S5�������ڼ������
Ҳ����˵{1, 2, 3}, {2, 3, 5}, {6, 7, 8}, {7, 8, 9}, {8, 9, 11}����S1-S5��
����һ���������͵ģ����15��λ�õ�����covered(������ĵڶ���Ԫ��1��ʼ��14)��ʼ��Ϊfalse
����comb������C(i) ��covered�϶�Ӧ��λ�ø�Ϊtrue
����covered������������ȫ��Ϊtrue���򷵻�true��ʾ��ǰ��ϸ���������ӦƸ�ߣ���֮
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

// ���ҵ�����Ͻ��д�ӡ
void _print(int comb[], int comb_size)
{
    printf("�ҵ�һ����Ч��%d�����:\n", comb_size);
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

// ʹ�õݹ���ж�������ı���
/*
start=0
comb_index=0
comb_size=5
������ʼ:
    ֱ�ӽ���forѭ��,
    ��һ�㣺i=0,comb[]={0}��
    �ڶ���: i=1,comb[]={0,1}, ����ѡ��S1,S2��
    ...
    �����: i=4,comb[]={0,1,2,3,4}
    ��ʱcomb_index = comb_size����if���ж�
    ����ʮ����: i=32,comb[]={0,1,2,3,33}
    ��start�ﵽ33ʱ,��ʱforѭ��ֹͣ
    �������comb[]={0,1,2,4,5}�ٽ���ѭ���ж�,ֱ����ȫ�������ɱ���
*/
void _find(int start, int comb[], int comb_index, int comb_size)
{
    if (comb_index == comb_size)
    {
        if (_covers(comb, comb_size))
        {
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

    printf("����һ����33������ѡȡ5����\n");
    _find(0, comb_5, 0, 5);

    printf("\n���������33������ѡȡ6����\n");
    _find(0, comb_6, 0, 6);
    printf("%d", num);

    return 0;
}
