#include<bits/stdc++.h>
#define mxn 10000
#define inf 0x3f3f3f3f

using namespace std;

vector< int > graph[mxn],edgeWeight[mxn];
int start_node, goal_node, parent_node[mxn], heuristics[mxn];

int getParentNode(int node)
{
    return parent_node[node];
}

void path(int current_node)
{
    if(current_node == start_node)
    {
        printf("%d",current_node);
        return;
    }
    path(getParentNode(current_node));
    printf("->%d",current_node);
}

bool A_star(int current_node, int CostToReachThisNode)
{
    if(current_node == goal_node)
    {
        printf("Total cost : %d\n",CostToReachThisNode);
        return true;
    }


    int child, best_child = -1, number_of_child = graph[current_node].size(), minimum = inf, totalCost, CostToReachChild, costofbest;

    for(int i=0; i<number_of_child ; i++)
    {
        child = graph[current_node][i];
        CostToReachChild = edgeWeight[current_node][i];

        totalCost = CostToReachThisNode + CostToReachChild;
        if((totalCost+heuristics[child])<minimum)
        {
            best_child = child;
            minimum = totalCost+heuristics[child];
            costofbest = CostToReachChild;
        }
    }
    if(best_child == -1)return false;

    parent_node[best_child] = current_node;
    return A_star(best_child , CostToReachThisNode + costofbest);
}

int main()
{
    freopen("A_Star_Search_Input.txt","r", stdin);

    int number_of_nodes, number_of_edges, edge_start, edge_end, n, h, weight;
    printf("Enter the number of Nodes : ");
    scanf("%d",&number_of_nodes);
    printf("Enter the number of Edges : ");
    scanf("%d",&number_of_edges);
    printf("Enter the Edges with weights: \n");

    for(int i=1; i<=number_of_edges; i++)
    {
        scanf("%d %d %d",&edge_start,&edge_end,&weight);
        graph[edge_start].push_back(edge_end);
        edgeWeight[edge_start].push_back(weight);
        graph[edge_end].push_back(edge_start);
        edgeWeight[edge_end].push_back(weight);
    }

    printf("\nEnter start node : ");
    scanf("%d",&start_node);
    printf("Enter goal node : ");
    scanf("%d",&goal_node);
    printf("Enter the node then the heuristics of the node for all nodes : \n");
    for(int i=1; i<=number_of_nodes; i++)
    {
        scanf("%d %d",&n,&h);
        heuristics[n] = h;
    }

    printf("\nUsing A* Search");
    if(A_star(start_node,0))
    {
        printf("\npath from start to goal node : ");
        path(goal_node);
        printf("\n");
    }
    else
    {
        printf("\nThere is no path from start to goal node.\n");
    }
    return 0;
}



