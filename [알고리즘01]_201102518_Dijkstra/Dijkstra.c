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
int distance[MAX]; // Vertex의 Cost를 저장하는 배열
int found[MAX]; // 이동할 수 있는 Vertex를 저장하는 배열
int path[MAX]; // 경로를 저장하는 배열
int choose(int v); // 갈 수 있는 vertex를 리턴
void shortestpath(int start, int end); // start에서 end까지의 shortestpath
void PrintPath(int start, int end); // path를 참조하여 경로를 출력
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
	// city를 입력받음
	shortestpath(start, end); // shortestpath를 찾음
	printf("\nShortest Path from %s to %s\n: ", city[start], city[end]);
	PrintPath(start, end); // 경로 출력
	printf("%s\n", city[end]);
	printf("\nDistance : %d\n", distance[end]);
}
int choose(int v) // 갈 수 있는 vertex를 리턴
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
void shortestpath(int start, int end) // start에서 end까지의 shortestpath
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
		// 갈 수 있는 index를 check
		for (w = 0; w < MAX; w++)
		{
			if (!found[w])
			{
				if (distance[u] + cost[u][w] < distance[w]) 
				{
					distance[w] = distance[u] + cost[u][w];
					path[w] = u;
					// 최소경로를 찾음
				}
			}
		}
	}
}
void PrintPath(int start, int end) // path를 참조하여 경로를 출력
{
	if (start == path[end]) // 시작 위치일 경우 출력
	{
		printf("%s - ", city[path[end]]);
		return;
	}
	else
	{
		PrintPath(start, path[end]);
		printf("%s - ", city[path[end]]); // 중간위치 출력
	}
}

