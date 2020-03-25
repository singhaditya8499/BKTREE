#include<iostream>
#include<vector>

using namespace std;

#define THRS 2   //this value stores the lowest threshold we desire in our calculation of edit distance
#define LEN 20   //we have defined the maximum edit distance we can have

struct Node   //stored information about our node
{
    string word;
    int next[LEN];
    Node(string s):word(s)   //parameterized constructor
    {
        word=s;
        for(int i=0;i<LEN;i++)  //initialize all the data items
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
Node nodes[100];  //stores all the nodes
int node_count=0;   

int findEditDistance(string a,string b)   //find edit distance between strings i.e. Levenshtein distance
{
    int n = a.length();
    int m = b.length();
    int arr[n+1][m+1];
    memset(arr,0,sizeof arr);
    for(int i=0;i<=m;i++)
    {
        arr[0][i]=i;
    }
    for(int i=0;i<=n;i++)
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

void add(Node &root,Node &tmp)      //add nodes to the tree
{
    if(root.word=="")
    {
        root=tmp;
        return;
    }
    int editDistance = findEditDistance(root.word,tmp.word);

    if(nodes[root.next[editDistance]].word=="")
    {
        node_count++;
        nodes[node_count]=(tmp);
        root.next[editDistance]=node_count;
    }
    else
    {
        add(nodes[root.next[editDistance]],tmp);
    }
    
}
vector<string> getWords(Node &root,string s)           //find the approximate matching strings. Use trainagular inequality here
{
    vector<string> matched;
    if(root.word=="")
    {
        return matched;
    }
    int distance = findEditDistance(root.word,s);
    if(distance<=THRS)
    {
        matched.push_back(root.word);
    }
    int start = distance - THRS;
    if(start<0)
    {
        start=1;
    }
    while(start<distance+THRS)
    {
        vector<string> tmp = getWords(nodes[root.next[start]],s);
        for(int i=0;i<tmp.size();i++)
        {
            matched.push_back(tmp[i]);
        }
        start++;
    }
    return matched;
}
int main()
{
    string dict[]={"hello","hell","elf","dell","halo","tell","told","old"};   //words in our dictionary
    for(int i=0;i<8;i++)           //add the words to our tree
    {
        Node tmp=Node(dict[i]);
        add(root,tmp);
    }

    string query = "hold";      //query string
    vector<string> matched = getWords(root,query);      //store all the words here
    cout<<"Matched words for the query "<<query<<" are: \n";
    for(int i=0;i<matched.size();i++)
    {
        cout<<matched[i]<<"\n";         //output all the resultant strings of the query
    }
    return 0;
}