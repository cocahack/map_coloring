#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#define N 6
#define D 3
using namespace std;

typedef enum {red = 1, green, blue} color;
int d[3]{ red, green, blue };
vector<int*> assignment;

int graph_arc[N][N]
{
	0, 1, 0, 0, 0, 1
  , 1, 0, 1, 0, 0, 1
  , 0, 1, 0, 1, 0, 1
  , 0, 0, 1, 0, 1, 1
  , 0, 0, 0, 1, 0, 1
  , 1, 1, 1, 1, 1, 0
};

string get_color_text(int c)
{
	static string color_str[3]{ "RED", "GREEN", "BLUE" };
	if (c == red) return color_str[0];
	if (c == green) return color_str[1];
	if (c == blue) return color_str[2];
	return "ERROR";
}

bool check_all_assigned(const vector<int>& draw)
{
	for (int i = 0; i < N; ++i)
		if (draw[i] == 0) return false;
	return true;
}

void save_result(const vector<int>& draw)
{
	int* assign = new int[N];
	for (int i = 0; i < N; ++i)
		assign[i] = draw[i];
	assignment.push_back(assign);
}

bool check_neighbor(const vector<int>& draw, int node)
{
	for (int i = 0; i < N; ++i) 
		if (graph_arc[node][i] == 1) 
			if (draw[i] == draw[node]) return false;
	return true;
}

void recursive_backtracking(vector<int> draw, int node)
{
	if (check_all_assigned(draw)) {
		save_result(draw);
		return;
	}
	for (int i = 0; i < D; ++i) {
		draw[node] = d[i];
		if (!check_neighbor(draw, node)) continue;
		recursive_backtracking(draw, node+1);
	}
}

void backtracking_search()
{
	vector<int> draw{ 0,0,0,0,0,0 };
	recursive_backtracking(draw, 0);
}

void print_result(int i)
{
	for (int j = 0; j < N; ++j)
		cout << get_color_text(assignment[i][j]) << " ";
	cout << "\n";
}
int main()
{
	backtracking_search();
	int len = assignment.size(), i;

	if (len == 0) cout << "Solution does not exist." << endl;
	else {
		for (i = 0; i < len; ++i) {
			print_result(i);
		}
		do {
			--i;
			delete[] assignment[i];
		} while (i > 0);
	}
	return 0;
}