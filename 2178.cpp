#include <iostream>
#include <string>
#include <queue>
using namespace std;

bool check[100][100];
int dist[100][100] = { 0 };
char map[100][100];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0 };
int main()
{
	int N, M;
	cin >> N >> M;
	for (int i = 0; i < N; i++) {		
			cin >> map[i];
	}
	queue<pair<int, int>> q;
	check[0][0] = true;
	dist[0][0] = 1;
	q.push(make_pair(0, 0));
	while (!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (check[nx][ny]) continue;
			if (0 <= nx && nx < N && 0 <= ny && ny < M) {
				if (map[nx][ny] == '1') {
					q.push(make_pair(nx, ny));
					check[nx][ny] = true;
					dist[nx][ny] = dist[x][y]+1;
				}
			}
		}
	cout << dist[N-1][M-1];
	return 0;
}
