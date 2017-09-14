#include <iostream>
#include <queue>

using namespace std;

int map[50][50];
int room[50][50];
bool check[50][50];
int dx[] = { 0,-1,0,1 };
int dy[] = { -1,0,1,0 };
int N, M, rooms = 0,  maxroom = 0; // room: 방의 갯수, maxroom: 제일 넓은 방의 넓이

void init() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			check[i][j] = false;
		}
	}
}

void bfs()
{
	queue<pair<int, int>> q;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (check[i][j]) continue;
			rooms++;
			q.push(make_pair(i, j));
			int cnt = 0;
			while (!q.empty()) {
				int x = q.front().first;
				int y = q.front().second;
				q.pop();
				for (int k = 0; k < 4; k++) {
					if ((map[x][y] & (1 << k)) != 0) continue;
					int nx = x + dx[k];
					int ny = y + dy[k];
					if (0 <= nx && nx < M && 0 <= ny && ny < N) {
						if (check[nx][ny] == false) {
							check[nx][ny] = true;
							room[nx][ny] = rooms;
							q.push(make_pair(nx, ny));
							cnt++;
						}
					}
				}
			}
			if (maxroom < cnt) maxroom = cnt;
		}
	}	
}
int main()
{
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}
	bfs();
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			cout << room[i][j];
		}
		cout << endl;
	}
	init();
	cout << rooms << endl;
	cout << maxroom << endl;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 2; k < 4; k++) {
				int nx = i + dx[k];
				int ny = j + dy[k];
				if (room[i][j] == room[nx][ny]) continue;
				int save1 = map[i][j];
				int save2 = map[nx][ny];
				if ((map[i][j] & (1 << k)) != 0) {
					map[i][j] &= ~(1 << k);
					map[nx][ny] &= ~(1 << (k + 2) % 4);
					bfs();
					map[i][j] = save1;
					map[nx][ny] = save2;
					init();
				}
			}
		}
	}
	cout << maxroom << endl;
	return 0;
}
