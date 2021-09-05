#include <iostream>
using namespace std;
#define MAX 100
void adjacency_matrix(int type);
int main()
{
    int type;
    cout << "Adjacency matrix\n\n";
    cout << "1) Undirected graph\n";
    cout << "2) Directed graph\n\n";
    cout << "Enter your choice...\n";
    cin >> type;
    adjacency_matrix(type);
    return 0;
}
void adjacency_matrix(int type)
{
    int num_of_ver,num_of_edge,i,ori,des;
    int matrix[MAX][MAX];
    cout<<"Enter number of vertices\n";
    cin>>num_of_ver;
    num_of_edge=type==2?num_of_ver*(num_of_ver-1):(num_of_ver*(num_of_ver-1))/2;
    for(i=0;i<num_of_edge;i++){
        cout<<"Enter edge"<<i<<"(-1 -1 to quit): \n";
        cin>>ori>>des;
        if(ori==-1&&des==-1)
            break;
        if(ori>(num_of_edge-1)||des>(num_of_edge-1)||ori<0||des<0){
            cout<<"Invalid\n";
            i--;
        }else{
            matrix[ori][des]=1;
            if(type==1)
                matrix[des][ori]=1;
        }

    }
    for(int i=0;i<num_of_ver;i++){
        cout<<"\n";
        for(int j=0;j<num_of_ver;j++)
            cout<<matrix[i][j]<<"\t";
    }
}