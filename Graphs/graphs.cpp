//Graphs
//In acoordance with pepcoding content
#include <bits/stdc++.h>

using namespace std;


class edge 
{
public:
  	int sourc;
  	int desti;
  	int wt;

  	edge(int source, int desti, int wt) 
  	{
    	this->sourc = source;
    	this->desti = desti;
    	this->wt = wt;
  	}
};


	
vector <string> paths;

bool vis[100002];

void print_all_paths(vector <edge> graph[], int source, int desti, string path)
{
	if(source == desti)
	{
		paths.push_back(path);
		return;
	}

	vis[source] = true;
	for(auto child : graph[source])
	{
		if(vis[child.desti] == false)
		{
			print_all_paths(graph, child.desti, desti, path + to_string(child.desti));
		}
	}
	vis[source] = false;
}



int min_path = INT_MAX; 
int max_path = INT_MIN;
int ceil_path = INT_MAX;
int floor_path = INT_MIN;

string ceil_p, floor_p, min_p, max_p, k_path;
priority_queue <pair <int, string>, vector <pair <int, string> > , greater <pair <int, string>> > pq;

void multisolver(vector <edge> graph[], int source, int desti, string path, int path_sum, int criteria, int k)
{
	if(source == desti)
	{
		if(path_sum < min_path)
		{
			min_path = path_sum;
			min_p = path + "@" + to_string(min_path);
		}

		if(path_sum > max_path)
		{
			max_path = path_sum;
			max_p = path + "@" + to_string(max_path);
		}

		if(path_sum > criteria && path_sum < ceil_path)
		{
			ceil_path = path_sum;
			ceil_p = path + "@" + to_string(ceil_path);
		}

		if(path_sum < criteria && path_sum > floor_path)
		{
			floor_path = path_sum;
			floor_p = path + "@" + to_string(path_sum);
		}

		if(pq.size() < k)
		{
			pq.push({path_sum, path});
		}

		else
		{
			if(pq.top().first < path_sum)
			{
				pq.pop();
				pq.push({path_sum, path});
			}
			k_path = pq.top().second + "@" + to_string(pq.top().first);
		}
	}

	vis[source] = true;
	for(auto child : graph[source])
	{
		if(vis[child.desti] == false)
		{
			multisolver(graph, child.desti, desti, path + to_string(child.desti), path_sum + child.wt, criteria, k);
		}
	}
	vis[source] = false;

}



set <int> visi;
void hamiltonian_path(vector <edge> graph[], int n, int source, string path)
{
	if(visi.size() == n - 1)
	{
		int x = path[0] - '0';
		int y = path.back() - '0';

		for(auto child : graph[x])
		{
			if(child.desti == y)
			{
				cout << path << "*\n";
				return;
			}
		}

		cout << path << ".\n";
		return;
	}


	visi.insert(source);

	for(auto child : graph[source])
	{
		if(visi.count(child.desti) == 0)
		hamiltonian_path(graph, n, child.desti, path + to_string(child.desti));
	}

	visi.erase(source);

}

queue <pair <int, string> > q;
void bfs(vector <edge> graph[], int source, string path)
{
	q.push({source, path});

	while(q.size() > 0)
	{
		pair <int, string> node = q.front();
		q.pop();

		if(vis[node.first])
			continue;

		vis[node.first] = true;

		cout << node.first << "@" << node.second << endl;

		for(auto child : graph[node.first])
		{
			if(vis[child.desti] == false)
				q.push({child.desti, node.second + to_string(child.desti)});
		}
	}
}

bool is_cyclic(vector <edge> graph[], int source)
{
	queue <int> q;
	q.push(source);

	while(q.size())
	{
		int front = q.front();
		q.pop();

		//if any is visited already then it means there are two paths to this node
		//which upon extending will meet at some point and form a cycle
		if(vis[front])
			return true;

		vis[front] = true;

		for(auto child : graph[front])
		{
			if(vis[child.desti] == false)
			{
				q.push(child.desti);
			}
		}
	}

	return false;
}


int level[100002];
bool is_bipartite(vector <edge> graph[], int source, int lev)
{
	queue <pair <int, int> > q;
	q.push({source, lev});

	while(q.size())
	{
		pair <int, int> front = q.front();
		q.pop();

		//if the level of a node isn't -1, then it means it is being visited second time
		//in this case the level of this node should be same from all paths
		if(level[front.first] != -1)
		{
			if(level[front.first] != front.second)
				return false;
		}
		else
			level[front.first] = front.second;

		for(auto child : graph[front.first])
		{
			if(level[child.desti] == -1)
				q.push({child.desti, front.second + 1});
		}
	}

	return true;
}


int spread_infection(vector <edge> graph[], int source, int t)
{
	queue <pair <int, int> > q;
	q.push({source, 1});

	int infected = 0;

	while(q.size())
	{
		pair <int, int> front = q.front();
		q.pop();

		if(front.second > t)
			break;

		if(level[front.first] != -1)
			continue;

		else
			level[front.first] = front.second;

		for(auto child : graph[front.first])
		{
			if(level[child.desti] == -1)
				q.push({child.desti, front.second + 1});
		}

		infected++;
	}

	return infected;
}


//iterative DFS 
//exactly same code as that of BFS except that stack is used in iterative DFS instead of queue
void iterative_dfs(vector <edge> graph[], int source, string path)
{
	stack <pair <int, string> > s;
	s.push({source, path});

	while(s.size())
	{
		pair <int, string> top = s.top();
		s.pop();

		if(vis[top.first])
			continue;

		vis[top.first] = true;

		cout << top.first << "@" << top.second << endl;

		for(auto child : graph[top.first])
		{
			if(vis[child.desti] == false)
				s.push({child.desti, top.second + to_string(child.desti)});
		}
	}
}


//Topological sort : It is a permutation P of nodes of a graph such that for every edge uv, u appears before v in P
//Nodes are added in the stack in their post order
stack <int> st;
void topological_sort(vector <edge> graph[], int source)
{
	vis[source] = true;

	for(auto child : graph[source])
	{
		if(vis[child.desti] == false)
			topological_sort(graph, child.desti);
	}

	st.push(source);
}


//Dijkstra Algorithm
struct Tuple
{
	int wt;
	int v;
	string path;

	Tuple(int wt, int v, string path)
	{
		this->wt = wt;
		this->v = v;
		this->path = path;
	}
};

struct compo
{
	bool operator()(Tuple const &t1, Tuple const t2)
	{
		if(t1.wt == t2.wt)
		{
			if(t1.path.size() == t2.path.size())
				return t1.path > t2.path;

			else
				return t1.path.size() > t2.path.size();
		}

		return t1.wt > t2.wt;
	}
};


void Dijkstra(vector <edge> graph[], int source)
{
	priority_queue <Tuple, vector <Tuple>, compo> pq;
	pq.push(Tuple(0, source, to_string(source)));

	while(pq.size())
	{
		Tuple top = pq.top();
		pq.pop();

		if(vis[top.v])
			continue;

		vis[top.v] = true;

		cout << top.v << " via " << top.path << " @ " << top.wt << endl;

		for(auto child : graph[top.v])
		{
			if(vis[child.desti] == false)
				pq.push(Tuple(top.wt + child.wt, child.desti, top.path + to_string(child.desti)));
		}
	}	 
}


//Prims Algorithm
void Prims(vector <edge> graph[], int source)
{
	priority_queue <Tuple, vector <Tuple>, compo> pq;
	pq.push(Tuple(0, source, to_string(source)));

	while(pq.size())
	{
		Tuple top = pq.top();
		pq.pop();

		if(vis[top.v])
			continue;

		vis[top.v] = true;

		if(top.wt != 0)
		cout << "[" << top.v << "-" << top.path << "@" << top.wt << "]" << endl;

		for(auto child : graph[top.v])
		{
			if(vis[child.desti] == false)
				pq.push(Tuple(child.wt, child.desti, to_string(top.v)));
		}
	}	 
}


int32_t main()
{

	int vertices;
  	cin >> vertices;

  	vector <edge> graph[vertices];

  	int edges;
  	cin >> edges;

  	for (int i = 0; i < edges; i++) 
  	{
    	int v1, v2, wt;
    	cin >> v1 >> v2 >> wt;

    	graph[v1].push_back(edge(v1, v2, wt));
    	graph[v2].push_back(edge(v2, v1, wt));
  	}
  
}
