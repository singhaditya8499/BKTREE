#include<iostream>
#include<vector>

using namespace std;

#define THRS 2   //this value stores the lowest threshold we desire in our calculation of edit distance
#define LEN 20   //we have defined the maximum edit distance we can have

struct Node   //stored information about our node
{
    string word;
    int next[LEN];
    Node(string s)   //parameterized constructor
    {
        word=s;
        for(int i=0;i<LEN;i++)
        {
            next[i]=0;
        }
    }
    Node()
    {
        // default constructor
    }
};
Node root;   //root node of our tree
vector<Node> nodes;  //stores all the nodes
int node_count=0;   

void add(Node &root,Node tmp)
{
    
}
int main()
{
    string dict[]={"hello","hell","elf","dell","halo","tell","told","old"};   //words in our dictionary
    for(int i=0;i<8;i++)           //add the words to our tree
    {
        Node tmp=Node(dict[i]);
        add(root,tmp);
    }
}