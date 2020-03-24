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
        word="";
        for(int i=0;i<LEN;i++)
        {
            next[i]=0;
        }
    }
};
Node root;   //root node of our tree
vector<Node> nodes;  //stores all the nodes
int node_count=0;   

int findEditDistance(string a,string b)
{
    int n = a.length();
    int m = b.length();
    int arr[n+1][m+1];
    memset(arr,0,sizeof arr);
    for(int i=0;i<=m;i++)
    {
        arr[0][i]=i;
    }
    for(int i=0;j<=n;i++)
    {
        arr[i][0]=i;
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            if(a[i-1]!=b[j-1])
            {
                arr[i][j]=1+min(arr[i-1][j],min(arr[i-1][j-1],arr[i][j-1]));
            }
            else
            {
                arr[i][j]=arr[i-1][j-1];
            }
        }
    }
    return arr[n][m];
}

void add(Node &root,Node tmp)
{
    if(root.word=="")
    {
        root=tmp;
        return;
    }
    int editDistance = findEditDistance(root.word,tmp.word);
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