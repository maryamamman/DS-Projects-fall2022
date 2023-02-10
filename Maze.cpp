#include <cstring>
#include <iostream>
#include <stack>

using namespace std;

#define MAX 12

bool visited[MAX][MAX];

class node {
public:
	int x, y;
	int dir;
	node(int i, int j)
	{
		x = i;
		y = j;
		dir = 0;
	}
};

bool isSafe(int maze[MAX][MAX], int x, int y, int size)
{
	return(x >= 0 && x < size && y >= 0 && y < size && visited[x][y] && !maze[x][y]);
}

bool findPath(int maze[MAX][MAX], stack<node>& answer, int n)
{
	int i = 0, j = 0;
	node temp(i, j);
	answer.push(temp);

	while (!answer.empty()) {
		temp = answer.top();
		int d = temp.dir;
		i = temp.x, j = temp.y;

		temp.dir++;
		answer.pop();
		answer.push(temp);

		if ((i == n-1) && (j == n-1)) {
			return true;
		}

		if (d == 0) {
			if (isSafe(maze, i, j+1, n)) {
				node temp1(i, j + 1);
				visited[i][j + 1] = false;
				answer.push(temp1);
			}
			
		}

		else if (d == 1) {
			if (isSafe(maze, i+1, j, n)) {
				node temp1(i + 1, j);
				visited[i + 1][j] = false;
				answer.push(temp1);
			}
			
		}

		else if (d == 2) {
			if (isSafe(maze, i, j-1, n)) {
				node temp1(i, j - 1);
				visited[i][j - 1] = false;
				answer.push(temp1);
			}
			
		}
		
		else if (d == 3) {
			if (isSafe(maze, i-1, j, n)) {
				node temp1(i - 1, j);
				visited[i - 1][j] = false;
				answer.push(temp1);
			}
			
		}
		else {
			visited[temp.x][temp.y] = true;
			answer.pop();
		}
	}
	return false;
}

void printPath(stack<node> answer, int n)
{
	stack<int> printTemp;
	while (answer.empty() == false) 
	{
		node temp = answer.top();
		printTemp.push((temp.y + 1) + (temp.x * n));
		answer.pop();
	}
	while (!printTemp.empty()) 
	{
		cout << printTemp.top() << " ";
		printTemp.pop();
	}
}

int main()
{
	memset(visited, true, sizeof(visited));
	stack<node> answer;
	
	int size;
	cin >> size;
	int maze[MAX][MAX];

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin >> maze[i][j];
		}
	}

	if (findPath(maze, answer, size)) {
		printPath(answer, size);
	}
	else
		cout << (-1);
		
	return 0;
}
