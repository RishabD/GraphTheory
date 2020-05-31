/*
Rishab Dalai
adj_matrix program part 1
v1.0 notes
 I had it set up so the code searches for solutions async but overall have the same number of nodes traversed. This means that the first solution found is the shortest path.
I used a vector to create a queue so i can fill it with tasks and have it complete them as they fill up(similar to async code). Once completed, the code clears the queue so that no other operation is done.
(took some inspiration from generators in python)
*/


#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> queue;

struct graph
{
    int nv;
    int adj_matrix[100][100];
};

void reset_graph(graph* data)
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            data->adj_matrix[i][j] = 0;

        }
    }
    data->nv = 100;
}

int print_matrix(graph* data)
{
    for (int i = 0; i < data->nv; i++)
    {
        for (int j = 0; j < data->nv; j++)
        {
            cout << data->adj_matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    return(0);
}

void add_edge(graph* data, int i, int j)
{
    data->adj_matrix[i][j] = 1;
    data->adj_matrix[j][i] = 1;
}

void change_nv(graph* data, int num)
{
    data->nv = num;
}

void remove_adj(graph* data, int i, int j)
{
    data->adj_matrix[i][j] = 0;
    data->adj_matrix[j][i] = 0;
}




int vals_done[100];

bool is_in(int num)
{
    for (int i = 0; i < 100; i++)
    {
        if (num == vals_done[i])
        {
            return(true);
        }

    }
    return(false);
}


void add(int num)
{
    for (int i = 0; i < 100; i++)
    {
        if (vals_done[i] == -1)
        {
            vals_done[i] = num;
            break;
        }
    }
}




vector<int > ans;

void equate_vectors(vector<int> base, vector<int> copy)
{
    for (int i = 0; i < base.size(); i++)
    {
        copy.push_back(base[i]);
    }
}






int short_path(graph* data, int v1, int v2, vector<int> solution)
{
    if (data->adj_matrix[v1][v2] == 1)
    {
        ans = solution;
        ans.push_back(v2);
        queue.clear();
        return(1);

    }
    else
    {
        int exists = 0;
        for (int j = 0; j < data->nv; j++)
        {
            if (j != v1 && !is_in(j) && data->adj_matrix[v1][j]==1)
            {
               add(j);
               vector<int> copy;
               copy = solution;
               copy.push_back(j);
               queue.push_back(short_path(data, j, v2, copy));
            }
        }
        return(exists);

    }
    return(0);
}

int iterate()
{
    while (queue.size() != 0)
    {
        queue[0];
        queue.erase(queue.begin());
    }
    return(0);
}

int main()
{


    graph* data1 = new graph;
    reset_graph(data1);
    add_edge(data1, 2, 3);
    add_edge(data1, 3, 4);
    add_edge(data1, 4, 5);
    add_edge(data1, 2, 6);
    add_edge(data1, 6, 5);
    add_edge(data1, 2, 1);
    data1->nv = 7;
    print_matrix(data1);

    for (int i = 0; i < 100; i++)
    {
        vals_done[i] = -1;
    }
    vals_done[0] = 2;



    queue.push_back(short_path(data1, 2, 5, {2}));
    iterate();



   for (int i = 0; i < ans.size(); i++)
   {
       cout << ans[i] << endl;
   }
   return (0);

}
