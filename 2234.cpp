#include <iostream>
#include <queue>

using namespace std;

int map[50][50];
int room[50][50];
int roomsize[50 * 50];

int dx[] = { 0,-1,0,1 };
int dy[] = { -1,0,1,0 };
int N, M, rooms = 0, maxroom = 0; // room: 방의 갯수, maxroom: 제일 넓은 방의 넓이

void bfs(int i, int j)
{
	queue<pair<int, int>> q;
	q.push(make_pair(i, j));		
	int cnt = 0;
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		room[x][y] = rooms;
		q.pop();
		cnt++;
		for (int k = 0; k < 4; k++) {
			if ((map[x][y] & (1 << k)) != 0) continue;
			int nx = x + dx[k];
			int ny = y + dy[k];
			if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
				if (room[nx][ny] == 0) {
					room[nx][ny] = rooms;
					q.push(make_pair(nx, ny));
				}
			}
		}
	}
	roomsize[rooms] = cnt;
	if (maxroom < cnt) maxroom = cnt;
}
int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (room[i][j] > 0) continue;
			rooms++;
			bfs(i,j);
		}
	}
	cout << rooms << endl;
	cout << maxroom << endl;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 2; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (room[i][j] == room[nx][ny]) continue;
				if ((map[i][j] & (1 << k)) != 0) {
					if (maxroom < roomsize[room[i][j]] + roomsize[room[nx][ny]])
						maxroom = roomsize[room[i][j]] + roomsize[room[nx][ny]];
				}
			}
		}
	}
	cout << maxroom << endl;
	return 0;
}
