/* 7-12 How Long Does It Take */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* 图的邻接矩阵表示法 */
 
#define MaxVertexNum 100    /* 最大顶点数设为100 */
// #define Null 65535        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */
 
/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;
        
/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

int NodesMinTime[MaxVertexNum]; /* 抵达每个结点所需最短时间 */

#define Null -1 /* 不通的路径 */

void TopSort( MGraph Graph );
MGraph BuildGraph();


int main(void)
{
    MGraph G = BuildGraph();
    TopSort(G);

    return 0;
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
            Graph->G[V][W] = Null;
             
    return Graph; 
}
        
void InsertEdge( MGraph Graph, Edge E )
{
     /* 插入边 <V1, V2> */
     Graph->G[E->V1][E->V2] = E->Weight;    
     /* 若是无向图，还要插入边<V2, V1> */
     // Graph->G[E->V2][E->V1] = E->Weight;
}
 
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv, i;
     
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
     
    scanf("%d", &(Graph->Ne));   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */ 
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
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
/* 邻接表存储 - 拓扑排序算法 */
 
void TopSort( MGraph Graph )
{ /* 对Graph进行拓扑排序 */
    int Indegree[MaxVertexNum], cnt;
    Vertex i, j, k;
    Queue Q = CreateQueue( Graph->Nv + 1 );
    WeightType node_max_time = 0;
  
    /* 初始化Indegree[] */
    for (i=0; i<Graph->Nv; i++)
        Indegree[i] = 0;
         
    /* 遍历图，得到Indegree[] */
    for(i=0; i<Graph->Nv; ++i)
        for(j=0; j<Graph->Nv; ++j)
            if(Graph->G[i][j] != Null)
                Indegree[j]++;  /* 对有向边<i, j>累计终点的入度 */
             
    /* 将所有入度为0的顶点入列 */
    for (i=0; i<Graph->Nv; i++)
        if ( Indegree[i]==0 ){
            AddQ(Q, i);
            NodesMinTime[i] = 0;
        }
             
    /* 下面进入拓扑排序 */ 
    cnt = 0; 
    while( !IsEmpty(Q) ){
        i = DeleteQ(Q); /* 弹出一个入度为0的顶点 */
        cnt++;
        /* 对i的每个邻接点j */
        for (j=0; j<Graph->Nv; ++j){
            if(Graph->G[i][j] == Null) continue;
            if ( --Indegree[j] == 0 ){/* 若删除i使得j入度为0 */
                AddQ(Q, j); /* 则该顶点入列 */
                node_max_time = 0;
                for(k=0; k<Graph->Nv; ++k){
                    if(Graph->G[k][j] == Null) continue;
                    if(node_max_time < NodesMinTime[k]+Graph->G[k][j])
                        node_max_time = NodesMinTime[k]+Graph->G[k][j];
                }
                NodesMinTime[j] = node_max_time;
            } 
        }
    } /* while结束*/
     
    if ( cnt != Graph->Nv )
        printf("Impossible\n"); /* 说明图中有回路, 返回不成功标志 */ 
    else{
        node_max_time = 0;
        for(k=0; k<Graph->Nv; ++k)
            if(node_max_time < NodesMinTime[k])
                node_max_time = NodesMinTime[k];
        printf("%d\n", node_max_time);
    }
}