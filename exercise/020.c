/* 7-18 Hashing - Hard Version */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* 图的邻接矩阵表示法 */
 
#define MaxVertexNum 1000    /* 最大顶点数设为100 */
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */
        
/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

int input[MaxVertexNum];
int input_n = 0;


MGraph BuildGraph();
void TopSort( MGraph Graph );

int main(void)
{
    MGraph G = BuildGraph();
    TopSort(G);

    return 0;
}


int Hash(int key, int size)
{
    return key % size;
} 
 
MGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;
     
    Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        for (W=0; W<Graph->Nv; W++)  
            Graph->G[V][W] = 0;
             
    return Graph; 
}
 
MGraph BuildGraph()
{
    MGraph Graph;
    int Nv, i, j;
     
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 

    for(i=0; i<Nv; ++i){
        scanf("%d", &input[input_n]);
        if(input[input_n]>=0){  // 不为-1
            j = Hash(input[input_n], Nv);
            while(j!=i){
                Graph->G[j][i] = 1;
                j = (j+1) % Nv;
            }
        }else{  // 未输入的结点
            Graph->G[0][i] = -1;
        }
        input_n++;
    }
 
    return Graph;
}


// 队列数组实现
#ifndef ERROR
#define ERROR -1
#endif
typedef int Position;
typedef int ElementType;
struct QNode {
    ElementType *Data;     /* 存储元素的数组 */
    Position Front, Rear;  /* 队列的头、尾指针 */
    int MaxSize;           /* 队列最大容量 */
};
typedef struct QNode *Queue;
 
Queue CreateQueue( int MaxSize )
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
 
bool IsFull( Queue Q )
{
    return ((Q->Rear+1)%Q->MaxSize == Q->Front);
}
 
bool AddQ( Queue Q, ElementType X )
{
    if ( IsFull(Q) ) {
        printf("队列满");
        return false;
    }
    else {
        Q->Rear = (Q->Rear+1)%Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}
 
bool IsEmpty( Queue Q )
{
    return (Q->Front == Q->Rear);
}
 
ElementType DeleteQ( Queue Q )
{
    if ( IsEmpty(Q) ) { 
        printf("队列空");
        return ERROR;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}

/* 堆 */
typedef struct
{
    int Element;
    int Index;
}OneNode;
typedef OneNode ElementType_2;
typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode {
    ElementType_2 *Data; /* 存储元素的数组 */
    int size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
typedef Heap MinHeap; /* 最小堆 */
 
#define MAXDATA 10000  /* 该值应根据具体情况定义为大于堆中所有可能元素的值 */

int compare2keys(OneNode a, OneNode b)
{ /* 比较两种键值：按key1非升序排列；如果key1相等，则按key2非降序排列 */
    return b.Element - a.Element;
}
 
MinHeap CreateHeap( int MaxSize )
{ /* 创建容量为MaxSize的空的最大堆 */
 
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->Data = (ElementType_2 *)malloc((MaxSize+1)*sizeof(ElementType_2));
    H->size = 0;
    H->Capacity = MaxSize;
    H->Data[0].Element = -1; /* 定义"哨兵"为大于堆中所有可能元素的值*/
 
    return H;
}
 
bool IsFull_2( MinHeap H )
{
    return (H->size == H->Capacity);
}
 
bool Insert( MinHeap H, ElementType_2 X )
{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
    int i;
  
    if ( IsFull_2(H) ) { 
        printf("最大堆已满");
        return false;
    }
    i = ++H->size; /* i指向插入后堆中的最后一个元素的位置 */
    for ( ; compare2keys(H->Data[i/2], X)<0; i/=2 )
        H->Data[i] = H->Data[i/2]; /* 上滤X */
    H->Data[i] = X; /* 将X插入 */
    return true;
}
 
// #define ERROR -1 /* 错误标识应根据具体情况定义为堆中不可能出现的元素值 */
 
bool IsEmpty_2( MinHeap H )
{
    return (H->size == 0);
}
 
ElementType_2 DeleteMin( MinHeap H )
{ /* 从最大堆H中取出键值为最大的元素，并删除一个结点 */
    int Parent, Child;
    ElementType_2 MaxItem, X;
 
    // if ( IsEmpty_2(H) ) {
    //     printf("最大堆已为空");
    //     return ERROR;
    // }
 
    MaxItem = H->Data[1]; /* 取出根结点存放的最大值 */
    /* 用最大堆中最后一个元素从根结点开始向上过滤下层结点 */
    X = H->Data[H->size--]; /* 注意当前堆的规模要减小 */
    for( Parent=1; Parent*2<=H->size; Parent=Child ) {
        Child = Parent * 2;
        if( (Child!=H->size) && compare2keys(H->Data[Child], H->Data[Child+1])<0 )
            Child++;  /* Child指向左右子结点的较大者 */
        if( compare2keys(X, H->Data[Child])>=0  ) break; /* 找到了合适位置 */
        else  /* 下滤X */
            H->Data[Parent] = H->Data[Child];
    }
    H->Data[Parent] = X;
 
    return MaxItem;
} 

/* 拓扑排序算法 */


struct List
{
    OneNode *Arr;
    int size;
}TmpList;




void TopSort( MGraph Graph )
{ /* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
    int* Indegree, *output;
    int output_n = 0;;
    Vertex V, W;
    ElementType_2 tmp_node;
    Queue Q = CreateQueue( Graph->Nv + 1 );
    MinHeap H = CreateHeap( Graph->Nv );

    Indegree = (int *)malloc(sizeof(int)*Graph->Nv);    // 每个结点的当前入度
    output = (int *)malloc(sizeof(int)*Graph->Nv);    // 每个结点的当前入度
    TmpList.Arr = (OneNode *)malloc(sizeof(OneNode)*Graph->Nv); // 待排序的结点
    TmpList.size = 0;
  
    /* 初始化Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        Indegree[V] = 0;
         
    /* 遍历图，得到Indegree[] */
    for (W=0; W<Graph->Nv; W++)
        for (V=0; V<Graph->Nv; V++){
            if(Graph->G[V][W]==-1){ // 未输入的结点
                Indegree[W] = -1;
                break;
            }
            if(Graph->G[V][W]==1)
                Indegree[W]++;
        }
             
    /* 将所有入度为0的顶点入列 */
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 ){
            tmp_node.Element = input[V];
            tmp_node.Index = V;
            Insert(H, tmp_node);
        }

    tmp_node = DeleteMin(H);
    AddQ(Q, tmp_node.Index);
             
    /* 下面进入拓扑排序 */ 
    while( !IsEmpty(Q) ){
        V = DeleteQ(Q); /* 弹出一个入度为0的顶点 */
        output[output_n++] = V; /* 将之存为结果序列的下一个元素 */
        /* 对V的每个邻接点W->AdjV */
        for ( W=0; W<Graph->Nv; W++ )
            if ( Graph->G[V][W] == 1 ){
                Indegree[W]--;
                if(Indegree[W]==0){
                    tmp_node.Element = input[W];
                    tmp_node.Index = W;
                    Insert(H, tmp_node);    
                }
            }
        if( IsEmpty_2(H) ){
            break;
        }else{
            tmp_node = DeleteMin(H);
            AddQ(Q, tmp_node.Index); 
        }
    } /* while结束*/
    for(V=0; V<output_n-1; V++)
        printf("%d ", input[output[V]]);
    printf("%d\n", input[output[V]]);
}