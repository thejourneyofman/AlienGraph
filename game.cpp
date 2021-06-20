
#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<deque>
#include <algorithm>

// functions
void aiPlay(std::deque<std::vector<int>>&& candidates, std::map<std::vector<int>, bool >&& visited, const int& player); // AI's play
void printQueues(std::map<std::vector<int>, bool>&& visited, const std::vector<std::deque<std::vector<int>>>& Q); // print result
void updateGraph(std::vector<std::deque<std::vector<int>>>&& queues, std::deque<std::vector<int>>&& candidates, const int& player, int&& cnt); //update graph
std::vector<std::string> split(const std::string& str, const std::string& pattern); // split char[]

// main function
int main()
{
	int N = 0;
	int ai = 0;
	int order = 0;
	char ok;
	int player = 0;
	char input[100];
	int x, y;


	printf("=============================Alien Graph=============================\n");
	printf("Press 'Enter' to start the game. Good luck!\n");
	scanf("%c", &ok);
	printf("Enter the number of verticies. N must be greater than 2: ");
	scanf("%d", &N);
	printf("Press '1' for two players, and '2' with computer: ");
	scanf("%d", &ai);
	printf("Press '1' to go first, and '2' to go second: ");
	scanf("%d", &order);

	ai = ai == 1 ? 0 : 1;
	player = order == 1 ? 0 : 1;  // change player's No to array index, player 1 as player[0] and player 2 as player[1]

	std::vector<std::deque<std::vector<int>>> queues;
	std::deque<std::vector<int>> candidates;
	std::map<std::vector<int>, bool > visited;
	std::deque<std::vector<int>> dq = {};
	queues.push_back(dq);
	queues.push_back(dq);

	// initialize the visited edges
	for (int row = 0; row < N; row++) 
	{
		for (int col = 0; col < N; col++)
		{
			if (col > row) {
				std::vector<int> edge = { row, col };
				visited.insert(std::make_pair(edge, false));
			}
		}
	}

	int cnt = 0;
	for (int i = cnt; cnt < N * (N - 1) / 2;) {
		if (player == 0 || !ai) {
			while (1)
			{
				printf("\n[Player %d] Please draw your line (egde with comma. eg. '0,2'): ", player == 0 ? 1 : 2);
				scanf("%s", input);
				std::vector<std::string> svec = split(input, ",");
				if (svec.size() != 2) {
					printf("Not a valid number, try again.\n");
					continue;
				}
				x = std::stoi(svec[0]);
				y = std::stoi(svec[1]);
				if (x >= 0 && y >= 0 && x < N && y < N && x < y) // Conditions for correct inputs
				{
					// new entry
					std::vector<int> entry;
					entry.push_back(x);
					entry.push_back(y);
					std::deque<std::vector<int>>::iterator iter;

					iter = std::find(queues[player].begin(), queues[player].end(), entry);
					if (iter == queues[player].end())
					{
						// if new entry is already colored in the other player's connections
						iter = std::find(queues[1 - player].begin(), queues[1 - player].end(), entry);
						if (iter != queues[1 - player].end()) {
							printf("This edge has been colored.\n");
							continue;
						}
						// correct input is pushed into the candidates' queue
						candidates.push_back(entry);
						cnt++;
						break;
					}
					else // if new entry is already colored in the same player's connections
					{
						printf("This edge has been colored.\n");
					}
				}
				else if (x >= y) {
					printf("y must be greater than x.\n");
				}
				else
				{
					printf("Not a valid number, try again.\n");
				}
			}
		}
		else if (ai) {
			aiPlay(std::move(candidates), std::move(visited), player);
			cnt++;
		}
		updateGraph(std::move(queues), std::move(candidates), player, std::move(cnt)); // update the graph by step
		printQueues(std::move(visited), queues); // print the result by step
		printf("\ntotal = %d", cnt);
		// Change the player
		if (player == 1)
		{
			player = 0;
		}
		else {
			player = 1;
		}
	}
	scanf("%c", &ok);
	return 0;
}

// print result by step
void printQueues(std::map<std::vector<int>, bool>&& visited, const std::vector<std::deque<std::vector<int>>>& Q) {
	for (int i = 0; i < Q.size(); i++) {
		printf("\nPlayer %d ", i == 0 ? 1 : 2);
		for (auto e : Q[i]) {
			printf("(%d,%d)", e[0], e[1]);
			visited[e] = true;
		}
	}
	// print the uncolored edges
	printf("\nUncolored edges: ");
	for (auto v : visited) {
		if (!v.second) {
			printf("\n(%d,%d)", v.first[0], v.first[1]);
		}
	}
}

// update the graph by step (non-recursive way)
void updateGraph(std::vector<std::deque<std::vector<int>>>&& queues,
	std::deque<std::vector<int>>&& candidates, const int& player, int&& cnt) {

	while (!candidates.empty()) {
		std::deque<std::vector<int>>::iterator iter;
		std::vector<int> candidate = candidates.front(); // first element from the front of the queue

		// if it has already been colored in the same player's graph, delete it from the candidates' queue
		iter = std::find(queues[player].begin(), queues[player].end(), candidate);
		if (iter != queues[player].end()) {
			candidates.pop_front();
			continue;
		}

		// match all the edges that can build a triangle in the same player's graph
		for (auto ele : queues[player]) {
			int thirdEdge_x = 0, thirdEdge_y = 0;
			if (candidate[0] == ele[0]) {
				thirdEdge_x = candidate[1] < ele[1] ? candidate[1] : ele[1];
				thirdEdge_y = candidate[1] > ele[1] ? candidate[1] : ele[1];
			}
			else if (candidate[1] == ele[1]) {
				thirdEdge_x = candidate[0] < ele[0] ? candidate[0] : ele[0];
				thirdEdge_y = candidate[0] > ele[0] ? candidate[0] : ele[0];
			}
			else if (candidate[1] == ele[0]) {
				thirdEdge_x = candidate[0];
				thirdEdge_y = ele[1];
			}
			else if (candidate[0] == ele[1]) {
				thirdEdge_x = ele[0];
				thirdEdge_y = candidate[1];
			}
			if (thirdEdge_x == thirdEdge_y) // not found and continue
				continue;

			// Found the edge that can build a triangle with the candidate and define the third edge as a new candidate
			std::vector<int> newcandidate;
			newcandidate.push_back(thirdEdge_x);
			newcandidate.push_back(thirdEdge_y);

			// if the new candidate has already been colored in the same player's graph, pass and continue 
			iter = std::find(queues[player].begin(), queues[player].end(), newcandidate);
			if (iter != queues[player].end()) {
				continue;
			}

			// if the new candidate is not in the candidates' queue, insert it to the queue from back, count + 1
			iter = std::find(candidates.begin(), candidates.end(), newcandidate);
			if (iter == candidates.end()) {
				candidates.push_back(newcandidate);
				cnt++;
			}

			// if the new candidate has already been colored in the other player's graph, remove it from the graph, count - 1
			iter = std::find(queues[1 - player].begin(), queues[1 - player].end(), newcandidate);
			if (iter != queues[1 - player].end()) {
				queues[1 - player].erase(iter);
				cnt--;
			}
		}

		// after the matching process, insert the candidate to the same player's graph and remove it from the candidates' queue
		queues[player].push_back(candidate);
		candidates.pop_front();
	}

}

// ToDo: AI play, strategies are NOT implemented
void aiPlay(std::deque<std::vector<int>>&& candidates, std::map<std::vector<int>, bool >&& visited, const int& player) {

	for (auto e : visited) {
		if (e.second == false) {
			candidates.push_back(e.first);
			break;
		}
	}

}

// string split utility
std::vector<std::string> split(const std::string& str, const std::string& splitter)
{
	//convert std::string to char*
	char* strch = new char[strlen(str.c_str()) + 1];
	strcpy(strch, str.c_str());
	std::vector<std::string> vecStr;
	char* tmpch = strtok(strch, splitter.c_str());
	while (tmpch != NULL)
	{
		vecStr.push_back(std::string(tmpch));
		tmpch = strtok(NULL, splitter.c_str());
	}
	// delete the char*
	delete[] strch;
	return vecStr;
}