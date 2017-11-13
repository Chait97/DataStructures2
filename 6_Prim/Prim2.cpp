#include<iostream>
#include<string>
#include<sstream>
#include<climits>

using namespace std;

#define MAX_SIZE 200


//--------------------------------------------------------------Class Definition------------------------------------------------------------------------

class edge{                                                                     //a data type to store edges
public:
    edge *next;                                                                 //for the implementation of an adjacency list
    int vertex1,vertex2,weight;                                                 //3 properties of any edge
    edge(){}                                                                    //default constructor
    edge(int v1,int v2, int w){                                                 //initialiser constructor
        vertex1 = v1;
        vertex2 = v2;
        weight = w;
    }
};

//-------------------------------------------------------------Priority Queue-----------------------------------------------------
class heap{
protected:
    edge *heapArr=NULL;
public:
    int heapSize=0;
    heap(){
        heapSize = 0;
        heapArr = new edge[MAX_SIZE];
    }

    edge extTop(){
        edge output = heapArr[0];
        heapArr[0] = heapArr[heapSize-1];
        heapSize--;
        heapify(0);
        return output;
    }
    void insert(edge x){
        if(heapSize + 1 >= MAX_SIZE){
            cout<<"Heap is full";
            return;
        }
        heapArr[heapSize] = x;
        int index = heapSize;
        while(index != 0){
            int p;
            if(index%2 == 0 )p = index/2 -1;
            else p = index/2;
            if(heapArr[p].weight > heapArr[index].weight){
                edge temp = heapArr[p];
                heapArr[p] = heapArr[index];
                heapArr[index] = temp;
            }
            index = p;
        }
        heapSize++;
    }

private:
    int left(int x){return (2*x + 1);}
    int right(int x){return (2*x +2);}
    void heapify(int x){
        int smallest, l=left(x), r= right(x);
        if(l <heapSize && heapArr[x].weight > heapArr[l].weight) smallest = l;
        else smallest = x;
        if(r <heapSize && heapArr[smallest].weight > heapArr[r].weight) smallest = r;
        if(smallest != x){
            edge temp = heapArr[smallest];
            heapArr[smallest] = heapArr [x];
            heapArr[x] = temp;
            heapify(smallest);
        }
    }
    void buildHeap(){
        for(int i = (heapSize-1)/2; i >= 0; i--)heapify(i);
    }
};

//---------------------------------------------------------------Graph-----------------------------------------------------------------------------

class graph{                                                                    //graph class
protected:
    int nVertices;
    edge **startPt;                                                             //pointer to the first pointer of adjacency list
    int nEdges;                                                                 //number of edges
public:
    graph(){                                                                    //default initialiser
        nVertices = 0;
        startPt = NULL;
        nEdges = 0;
    }
    int buildList(){                                                            //this function takes adjacency list input from the user
        cout<<endl<<"\tInstructions: \n\tFor each node in the graph, enter a space separated list of adjacent vertices and their weights.\n\tFor every vertex in the adjacency list, enter the respective weight with a ':' character.\n\tWhen a list is complete, press 'enter' for the next node\n\n\tNote:\n\tProgram will only consider valid inputs, e.g. if a total of 10 nodes exist, vertices >= 10 will not be considered\n\n\tSyntax\t\tNode [number]: [vertex]:[weight]\n\tExample\t\tNode 5: 1:2 3:8 7:1 8:2 12:3\n"<<endl;                     //input specifications. These are the instructions for the user to input adjacency list
        cout<<"\nEnter the number of nodes in the graph: ";
        cin>>nVertices;
        edge** adList = new edge*[nVertices];                                     //creates an array to store starting addresses for each vertex's likned list
        startPt = adList;                                                       //beginning of the adjacency list stored in the startPt pointer
        for(int i=0;i<nVertices-1;i++){                                         //for each vertex in the graph
            string line;
            cout<<"Enter the adjacency list for node "<<i<<" :";
            if(cin.peek() =='\n')cin.ignore(100,'\n');                          //to check for termination of list according to input format (specified above)
            getline(cin, line,'\n');                                            //extract line from buffer and place in string line
            istringstream streamline(line);                                     //this creates a istringstream object from a string. it is easy to perform operations on this object
            int vertex,weight;
            char temp;                                                          //required to validate user input
            edge **current = adList+i; //**previous = NULL;                     //the edge to-be-filled with data
            adList[i] = NULL;
            while((streamline >> vertex >> temp >> weight) && temp == ':'){     //input validated and stored in respective variables
                if(vertex > i && vertex < nVertices){                              //this is to make sure no edge gets repeated
                    *current = new edge(i,vertex,weight);                       //new edge onject is created
                    nEdges++;                                                   //simultaneously counts the number of edges (which we haven't taken as input, for conveniece)
                    //*previous = *current;
                    current = &((*current)->next);                              //the next element should go into the next field of the current edge. We store is address in current
                }
            }
            *current = NULL;                                                    //the last edge must point to NULL to signal the end of the edge linked list
            //(*previous)->next = NULL
        }
        cout<<"Total of "<<nEdges<<" edges were input."<<endl;
        return nVertices;
    }
    void showList(){                                                            //outputs the adjacency list
        edge* current;
        for(int i=0;i<nVertices-1;i++){
            cout<<"Node: "<<i<<endl;
            for (current = startPt[i]; current != NULL; current=current->next){
                cout<<"\t\tVertices: "<<current->vertex1<<" "<<current->vertex2<<" and its weight is: "<<current->weight<<endl;
            }
        }
        return;
    }

    void caclMST(){                                                           //calculation of MST using prim's algirithm
        int mstEdges[nVertices];
        bool inMST[nVertices];
        heap priorityQueue;
        int key[nVertices];                     // Key values used to pick minimum weight edge in cut

                                                // Initialize all keys as INFINITE
        for (int i = 0; i < nVertices; i++){
            key[i] = INT_MAX;
            inMST[i] = false;
        }
//-------------------------------------------------------PRIM'S ALGORITHM BEGINS--------------------------------------------------------
                                                                                //run once to create a non-empty queue

        inMST[0] = true;                                                        // Include vertex in MST
                                                                                // 'i' is used to get all adjacent vertices of a vertex
        for (edge* i = startPt[0]; i!= NULL; i = i->next){
                                                                                // Get vertex label and weight of current adjacent
                                                                                // of u.
            int v = i->vertex2;
            int weight = i->weight;
                                                                                //  If v is not in MST and weight of (u,v) is smaller
                                                                                // than current key of v
            if (inMST[v] == false && key[v] > weight){
                // Updating key of v
                key[v] = weight;
                priorityQueue.insert(*i);
                mstEdges[v] = 0;
            }
        }
        while (priorityQueue.heapSize > 0){
            int u = priorityQueue.extTop().vertex2;
            inMST[u] = true;                                                    // Include vertex in MST
                                                                                // 'i' is used to get all adjacent vertices of a vertex
            for (edge* i = startPt[u]; i!= NULL; i = i->next){
                                                                                // Get vertex label and weight of current adjacent
                                                                                // of u.
                int v = i->vertex2;
                int weight = i->weight;
                                                                                //  If v is not in MST and weight of (u,v) is smaller
                                                                                // than current key of v
                if (inMST[v] == false && key[v] > weight){
                    // Updating key of v
                    key[v] = weight;
                    priorityQueue.insert(*i);
                    mstEdges[v] = u;
                }
            }
    }
        for(int k = 1; k< nVertices; k++)cout<<"Edge: "<<mstEdges[k]<<"-"<<k<<endl;                     //display the result
    }
};

//------------------------------------------------Driver Program--------------------------------------------------------------------------

int main(){
    graph A;
    int number = A.buildList();
    A.showList();
    A.caclMST();
    return 0;
}
