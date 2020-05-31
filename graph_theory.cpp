/*
Shortest path v2.0
Code below finds shortest path.
The one I made doesn't need to traverse through all paths. I used semi-aysncronous code to find the path by effectively searching through all paths at the same time.
The first one that finishes is shortest path.
Code can be easily modified to find all paths in increasing order of path length
I didn't use arrays for a lot of the components due to time complexity and also simplicity
*/
#include <iostream>
#include <vector>
#include <map>
std::vector<int> tasks;//Tasks is only used to execute tasks at front and place tasks at end. Arrays would be far slower since items would constantly need to be shifted
std::vector<int> solution;//Solution is only used to add numbers to end of vector. Arrays could be used but would comlicate code
std::map<int, bool> vals_done;//Map is used to check if value has been traversed or not. Time complexity of searching in map vs array is much better.

class graph
{
public:
	int highest_vertex_number;
	int adj_list[100][100]; //Almost all data is constantly being accessed, so array is best due to low latency.

	//Sets adj graph to all 0's
	void reset_graph()
	{
		for (int i = 1; i <= highest_vertex_number;i++)
		{
			for (int j = 1; j <= highest_vertex_number;j++)
			{
				adj_list[i][j] = 0;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	//Prints out adj graph
	void print_graph()
	{
		for (int i = 1; i <= highest_vertex_number;i++)
		{
			for (int j = 1; j <= highest_vertex_number;j++)
			{
				std::cout << adj_list[i][j];
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;
	}
	//1 means adjacent, 0 means not adjacent
	void add_edge(int i, int j)
	{
		adj_list[i][j] = 1;
		adj_list[j][i] = 1;
	}
	void del_edge(int i, int j)
	{
		adj_list[i][j] = 0;
		adj_list[j][i] = 0;
	}


	//Task manager. Continously completes functions in task list until empty
	void iterate()
	{
		while (!tasks.empty())
		{
			tasks[0];
			tasks.erase(tasks.begin());
			vals_done.clear();//Resets code to be used again
		}
	}
	//Function called in main which then sets some prerequesites and triggers _short_path
	void short_path(int v1, int v2)
	{
		std::vector<int> path = { v1 };
		vals_done[2] = 1;
		tasks.push_back(_short_path(v1, v2, path));
		solution.empty();
		iterate();
	}

	//Finds shortest path and stores in vector solution
	int _short_path(int v1, int v2, std::vector<int> path)
	{
		//Saves path in solution if it hs reached end. Clears tasks as well (This part can be modified to save more paths that lead to the end vertex)
		if (adj_list[v1][v2] == 1)
		{
			solution = path;
			solution.push_back(v2);
			tasks.clear();

		}
		//Checks for possible path branches and creates a new instance of _short_path to explore said branches
		else
		{
			for (int i = 1; i <= highest_vertex_number; i++)
			{
				if (adj_list[i][v2] == 1 && !vals_done[i] && i != v1)
				{
					vals_done[i] = 1;
					std::vector<int> new_path = path;
					new_path.push_back(i);
					tasks.push_back(_short_path(i, v2, new_path));
				}
			}
		}
		//Required, but I don't use.
		return(0);
	}
};

//Test code
int main()
{
	graph data1;
	data1.highest_vertex_number = 9;
	data1.reset_graph();
	data1.add_edge(2, 3);
	data1.add_edge(3, 4);
	data1.add_edge(4, 5);
	data1.add_edge(2, 6);
	data1.add_edge(6, 5);
	data1.add_edge(2, 1);
	data1.short_path(2, 5);

	for (int i = 0; i < solution.size(); i++)
		std::cout << solution[i] << ' ';
	return(0);
}
