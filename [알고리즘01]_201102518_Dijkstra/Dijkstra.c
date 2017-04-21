#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8
#define NOT 100000
char city[][20] =
{
	"Los Angeles", "San Francisco", "Denver", "Chicago",
	"Boston", "New York", "Miami", "New Orleans"
};
int cost[][MAX] =
{ { 0, NOT, NOT, NOT, NOT, NOT, NOT, NOT },
{ 300, 0, NOT, NOT, NOT, NOT, NOT, NOT },
{ 1000, 800, 0, NOT, NOT, NOT, NOT, NOT },
{ NOT, NOT, 1200, 0, NOT, NOT, NOT, NOT },
{ NOT, NOT, NOT, 1500, 0, 250, NOT, NOT },
{ NOT, NOT, NOT, 1000, NOT, 0, 900, 1400 },
{ NOT, NOT, NOT, NOT, NOT, NOT, 0, 1000 },
{ 1700, NOT, NOT, NOT, NOT, NOT, NOT, 0 }
};
// Edge cost
int distance[MAX]; // Vertex�� Cost�� �����ϴ� �迭
int found[MAX]; // �̵��� �� �ִ� Vertex�� �����ϴ� �迭
int path[MAX]; // ��θ� �����ϴ� �迭
int choose(int v); // �� �� �ִ� vertex�� ����
void shortestpath(int start, int end); // start���� end������ shortestpath
void PrintPath(int start, int end); // path�� �����Ͽ� ��θ� ���
void main()
{
	int start, end, i;
	char s[20], e[20];

	printf("Start vertex : ");
	gets(s);
	printf("End vertex : ");
	gets(e);
	for (i = 0; i < MAX; i++)
	{
		if (!strcmp(s, city[i]))
			start = i;
		if (!strcmp(e, city[i]))
			end = i;
	}
	// city�� �Է¹���
	shortestpath(start, end); // shortestpath�� ã��
	printf("\nShortest Path from %s to %s\n: ", city[start], city[end]);
	PrintPath(start, end); // ��� ���
	printf("%s\n", city[end]);
	printf("\nDistance : %d\n", distance[end]);
}
int choose(int v) // �� �� �ִ� vertex�� ����
{
	int i, j, b;
	j = NOT;
	b = -1;
	for (i = 0; i < v; i++)
	{
		if (distance[i] < j && !found[i])
		{
			j = distance[i];
			b = i;
		}
	}
	return b;
}
void shortestpath(int start, int end) // start���� end������ shortestpath
{
	int i, u, w;

	for (i = 0; i < MAX; i++)
	{
		found[i] = 0;
		distance[i] = cost[start][i];
		path[i] = start;
	}
	found[start] = 1;
	distance[start] = 0;

	for (i = 0; i < MAX - 2; i++)
	{
		u = choose(MAX);
		found[u] = 1;
		// �� �� �ִ� index�� check
		for (w = 0; w < MAX; w++)
		{
			if (!found[w])
			{
				if (distance[u] + cost[u][w] < distance[w]) 
				{
					distance[w] = distance[u] + cost[u][w];
					path[w] = u;
					// �ּҰ�θ� ã��
				}
			}
		}
	}
}
void PrintPath(int start, int end) // path�� �����Ͽ� ��θ� ���
{
	if (start == path[end]) // ���� ��ġ�� ��� ���
	{
		printf("%s - ", city[path[end]]);
		return;
	}
	else
	{
		PrintPath(start, path[end]);
		printf("%s - ", city[path[end]]); // �߰���ġ ���
	}
}

