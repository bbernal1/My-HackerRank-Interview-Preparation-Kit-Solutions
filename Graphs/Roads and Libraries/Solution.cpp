//URL for problem:
//https://www.hackerrank.com/challenges/torque-and-development/problem?h_l=interview&playlist_slugs%5B%5D=interview-preparation-kit&playlist_slugs%5B%5D=graphs

#include <bits/stdc++.h>

using namespace std;
vector<string> split_string(string);


//////////////////My Solution//////////////
long cityCount = 0; //global var used to track how many nodes(cities) in a connected graph

void DFS(int c_lib, int c_road, vector<vector<int>>& graph, int src, vector<bool>& vis) {
	vis[src] = true;
	for (int i = 0; i < graph[src].size(); ++i) {
		if (!vis[graph[src][i]]) {
			++cityCount; //Increment the city count when new city is discovered
			DFS(c_lib, c_road, graph, graph[src][i], vis);
		}
	}
}
long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>>& graph) {
	vector<bool> vis(n + 1);
	long total = 0; //Sum of the costs for each connected graph
	for (int i = 1; i < n + 1; ++i) { //try all nodes as a source
		if (!vis[i]) {
			if (!graph[i].empty()) {
				DFS(c_lib, c_road, graph, i, vis);
				long cost1 = c_lib + c_road * cityCount; //cost for 1 library and required roads
				long cost2 = c_lib * (cityCount + 1); //cost for all libraries without any roads
				if (cost1 < cost2) total += cost1; //choose cheaper option
				else total += cost2;
				cityCount = 0; //Reset the city count as a connected graph has been explored
			}
			else total += c_lib; //city exists but is not connected to any other cities
		}
	}
	return total;
}
///////////////////////////////////////////

int main()
{
	ofstream fout(getenv("OUTPUT_PATH"));
	int q;
	cin >> q;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int q_itr = 0; q_itr < q; q_itr++) {
		string nmC_libC_road_temp;
		getline(cin, nmC_libC_road_temp);

		vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

		int n = stoi(nmC_libC_road[0]);

		int m = stoi(nmC_libC_road[1]);

		int c_lib = stoi(nmC_libC_road[2]);

		int c_road = stoi(nmC_libC_road[3]);

		vector<vector<int>> cities(n + 1);
		for (int i = 0; i < m; i++) {
			int vertex;
			int edge;
			cin >> vertex;
			cin >> edge;
			cities[vertex].push_back(edge);
			cities[edge].push_back(vertex);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		long result = roadsAndLibraries(n, c_lib, c_road, cities);
		fout << result << "\n";
	}
	fout.close();
	return 0;
}

vector<string> split_string(string input_string) {
	string::iterator new_end = unique(input_string.begin(), input_string.end(), [](const char &x, const char &y) {
		return x == y and x == ' ';
	});

	input_string.erase(new_end, input_string.end());

	while (input_string[input_string.length() - 1] == ' ') {
		input_string.pop_back();
	}

	vector<string> splits;
	char delimiter = ' ';

	size_t i = 0;
	size_t pos = input_string.find(delimiter);

	while (pos != string::npos) {
		splits.push_back(input_string.substr(i, pos - i));

		i = pos + 1;
		pos = input_string.find(delimiter, i);
	}

	splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

	return splits;
}