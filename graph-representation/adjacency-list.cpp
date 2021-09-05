#include <iostream>
using namespace std;

struct vertex
{
    int info;
    struct edge *firstEdge;
    struct vertex *nextVertex;
} *start = NULL;

struct edge
{
    struct vertex *destVertex;
    struct edge *nextEdge;
};

void insertVertex(int u);
void insertEdge(int u, int v);
void deleteVertex(int u);
vertex *findVertex(int u);
void deleteIncomingEdges(int u);
void display();
void deleteEdge(int u, int v);
int main()
{
    int choice, u, origin, desti;
    cout << "\nAdjacency list\n";
    while (1)
    {
        cout << "\n1. Insert a vertex";
        cout << "\n2. Insert an edge";
        cout << "\n3. Delete a vertex";
        cout << "\n4. Delete an edge";
        cout << "\n5. Display";
        cout << "\n6. Exit";
        cout << "\n\n Enter your choice....\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nEnter a vertex to be inserted";
            cin >> u;
            insertVertex(u);
            break;
        case 2:
            cout << "\nEnter Edge to be inserted";
            cin >> origin>> desti;
            insertEdge(origin, desti);
            break;
        case 3:
            cout << "\nEnter vertex to be deleted";
            cin >> u;
            deleteIncomingEdges(u);
            deleteVertex(u);
            break;
        case 4:
            cout<<"\nEnter origin and destination of edge";
            cin>>origin>>desti;
            deleteEdge(origin,desti);
            break;
        case 5:
            display();
            break;
        case 6:
            exit(0);
            break;

        default:
            break;
        }
    }
    return 0;
}
void insertVertex(int u)
{
    vertex *ptr, *tmp;
    tmp = (vertex *)malloc(sizeof(vertex));
    tmp->info = u;
    tmp->nextVertex = NULL;
    tmp->firstEdge=NULL;
    if(start==NULL){
        start=tmp;
        return;
    }
    ptr = start;
    while (ptr->nextVertex != NULL)
        ptr = ptr->nextVertex;
    ptr->nextVertex = tmp;
}

void insertEdge(int u, int v)
{
    vertex *locu, *locv;
    edge *ptr, *tmp;
    locu = findVertex(u);
    locv = findVertex(v);
    if (locu == NULL)
    {
        cout << "\nStart vertex is not present";
        return;
    }
    if (locv == NULL)
    {
        cout << "\nEnd vertex is present";
        return;
    }
    tmp = (edge *)malloc(sizeof(edge));
    tmp->destVertex = locv;
    tmp->nextEdge = NULL;
    if (locu->firstEdge == NULL)
    {
        locu->firstEdge = tmp;
        return;
    }
    ptr = locu->firstEdge;
    while (ptr->nextEdge != NULL)
        ptr = ptr->nextEdge;
    ptr->nextEdge = tmp;
}

vertex *findVertex(int u)
{
    vertex *ptr, *loc;
    ptr = start;
    while (ptr != NULL)
    {
        if (ptr->info == u)
        {
            loc = ptr;
            return loc;
        }
        else
            ptr = ptr->nextVertex;
    }
    loc = NULL;
    return loc;
}

void deleteVertex(int u)
{
    vertex *tmp, *q;
    edge *p, *tempo;
    if (start == NULL)
    {
        cout << "\nGraph is empty, no vertices for to be deleted";
        return;
    }
    if (start->info == u)
    {
        tmp = start;
        start = start->nextVertex;
    }
    else
    {
        q = start;
        while (q->nextVertex != NULL)
        {
            if (q->nextVertex->info == u)
                break;
            q = q->nextVertex;
        }
        if (q->nextVertex == NULL)
        {
            cout << "\nVertex not found";
            return;
        }
        else
        {
            tmp = q->nextVertex;
            q->nextVertex = tmp->nextVertex;
        }
        p = tmp->firstEdge;
        while (p != NULL)
        {
            tempo = p;
            p = p->nextEdge;
            free(tempo);
        }
        free(tmp);
    }
}
void deleteIncomingEdges(int u)
{
    vertex *ptr;
    edge *q, *temp;
    ptr = start;
    while (ptr != NULL)
    {
        if (ptr->firstEdge == NULL)
        {
            ptr = ptr->nextVertex;
            continue;
        }
        if (ptr->firstEdge->destVertex->info == u)
        {
            temp = ptr->firstEdge;
            ptr->firstEdge = ptr->firstEdge->nextEdge;
            free(temp);
            continue;
        }
        q = ptr->firstEdge;
        while (q ->nextEdge!= NULL)
        {
            if (q->nextEdge->destVertex->info == u)
            {
                temp = q->nextEdge;
                q->nextEdge = q->nextEdge->nextEdge;
                free(temp);
                continue;
            }
            q = q->nextEdge;
        }
        ptr = ptr->nextVertex;
    }
}
void display()
{
    vertex *ptr;
    edge *q;
    ptr = start;
    cout<<"\n\n";
    while (ptr != NULL)
    {
        cout << ptr->info;
        q = ptr->firstEdge;
        while (q != NULL)
        {
            cout << "--" << q->destVertex->info;
            q = q->nextEdge;
        }
        cout << "\n|\n";
        ptr = ptr->nextVertex;
    }
}
void deleteEdge(int u, int v){
    vertex *locu;
    edge *temp,*q;
    locu=findVertex(u);
    if(locu==NULL){
        cout<<"\nStart vertex is not found...";
        return;
    }
    if(locu->firstEdge==NULL){
        cout<<"\n Edge is not present at the provided vertex";
        return;
    }
    if(locu->firstEdge->destVertex->info==v){
        temp=locu->firstEdge;
        locu->firstEdge=temp->nextEdge;
        free(temp);
        return;
    }
    q=locu->firstEdge;
    while(q->nextEdge!=NULL){
        if(q->nextEdge->destVertex->info==v){
            temp=q->nextEdge;
            q->nextEdge=temp->nextEdge;
            free(temp);
            return;
        }
        q=q->nextEdge;
    }
    cout<<"\n This edge is not present in this graph";
}