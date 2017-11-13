//Minimum Spanning tree
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

class edge{                                                                     //a data tyope to store edges
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

int partition (edge arr[], int low, int high){                                  //for quicsort algorithm
    int pivot = arr[high].weight;
    int i = low - 1;
    for (int j = low; j <= high- 1; j++){
        if (arr[j].weight <= pivot){
            i++;
            edge temp = arr[j];                                                 //swap(&arr[i], &arr[j]);
            arr[j]=arr[i];
            arr[i]= temp;
        }
    }
    edge temp = arr[i+1];                                                       //swap(&arr[i + 1], &arr[high]);
    arr[i+1]=arr[high];
    arr[high]= temp;
    return (i + 1);
}
void quickSort(edge arr[], int low, int high){                                  //the controlling quickSort function
    if (low < high){
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}                                                                               //sorts in O(nlogn) time

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

    edge* sort(){                                                                 //before calling quickSort, we must make an array fro ma linked list
        edge* toSort = new edge[nEdges];                                                    //this array will store the edges, and quickSort will sort this array
        edge *current;
        int c1 = 0, c2 = 0;
        while(c2 < nEdges){
            current = startPt[c1++];
            while(current!=NULL){
                toSort[c2++] = *current;                                        //for each vertex, put the corresponding vertices in toSort
                current = current->next;
            }
        }
        //for(int i=0; i<c2; i++)cout<<toSort[i].vertex1<<" "<<toSort[i].vertex2<<" "<<toSort[i].weight<<endl;
        quickSort(toSort,0,c2-1);                                               //this will sort the edges according to their weights
        for(int i=0; i<c2; i++)cout<<toSort[i].vertex1<<" "<<toSort[i].vertex2<<" "<<toSort[i].weight<<endl;
        return toSort;
    }

    void caclMST(){                                                           //calculation of MST using union-find data structure
        edge* sorted = sort();
        int unionFind[nVertices];                                               //THE unionFind data structure shows graph connections
        edge mstEdges[nVertices -1];
        int edgeCounter = 0;
        for(int i = 0; i< nVertices; i++){
            unionFind[i] = i;                                                   //initialiser
        }
        for(int i = 0; i< nVertices; i++){
            int v1 = unionFind[sorted[i].vertex2], v2 = unionFind[sorted[i].vertex1];
            if(v1 != v2){
                mstEdges[edgeCounter++] = sorted[i];                            //add to mstEdges if two vertices are not connected
                for(int j = 0; j< nVertices; j++){
                    if(unionFind[j] == v2)unionFind[j] = v1;                    //update unionFind data structure
                }

            }
        }                                                                       //print the output
        for(int k=0; k< nVertices - 1; k++)cout<<"Edge: "<<mstEdges[k].vertex1<<"-"<<mstEdges[k].vertex2<<": "<<mstEdges[k].weight<<endl;
    }
};

int main(){
    graph A;
    int number = A.buildList();
    A.showList();
    A.caclMST();
    return 0;
}
