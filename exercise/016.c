/* 7-9 旅游规划 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/* 图的邻接表表示法 */
 
#define MaxVertexNum 500    /* 最大顶点数设为500 */
#define INFINITY_2 30001      
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */

// typedef char DataType;        /* 顶点存储的数据类型设为字符型 */
 
/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
    WeightType Weight;  /* 权重 */
    WeightType Money;   /* 收费 */
};
typedef PtrToENode Edge;
 
/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;        /* 邻接点下标 */
    WeightType Weight;  /* 边权重 */
    WeightType Money;   /* 收费 */
    PtrToAdjVNode Next;    /* 指向下一个邻接点的指针 */
};
 
/* 顶点表头结点的定义 */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* 边表头指针 */
} AdjList[MaxVertexNum];    /* AdjList是邻接表类型 */
 
/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;     /* 顶点数 */
    int Ne;     /* 边数   */
    AdjList G;  /* 邻接表 */
};
typedef PtrToGNode LGraph; /* 以邻接表方式存储的图类型 */

Vertex S;
Vertex D;

LGraph BuildGraph();
void Dijkstra( LGraph Graph );

int main(void)
{
    LGraph L = BuildGraph();
    Dijkstra(L);

    return 0;
}


/* 邻接矩阵存储 - 有权图的单源最短路算法 */

#define ERROR -1
 
Vertex FindMinDist( LGraph Graph, int dist[], int mon[], int collected[] )
{ /* 返回未被收录顶点中dist最小者 */
    Vertex MinV, V;
    int MinDist = INFINITY_2;
    int MinMon = INFINITY_2;

 
    for (V=0; V<Graph->Nv; V++) {
        if ( collected[V]==false && (dist[V]<MinDist || (dist[V]==MinDist && mon[V]<MinMon))) {
            MinDist = dist[V]; /* 更新最小距离 */
            MinMon = mon[V];
            MinV = V; /* 更新对应顶点 */
        }
    }
    if (MinDist < INFINITY_2) /* 若找到最小dist */
        return MinV; /* 返回对应的顶点下标 */
    else return ERROR;  /* 若这样的顶点不存在，返回错误标记 */
}
 
void Dijkstra( LGraph Graph )
{
    int collected[MaxVertexNum];
    int dist[MaxVertexNum];
    int mon[MaxVertexNum];
    Vertex V;
    PtrToAdjVNode W = NULL;
 
    /* 初始化 */
    for (V=0; V<Graph->Nv; V++){
        dist[V] = INFINITY_2;
        mon[V] = INFINITY_2;
    }
    for ( W=Graph->G[S].FirstEdge; W; W=W->Next ) {
        dist[W->AdjV] = W->Weight;
        mon[W->AdjV] = W->Money;
        collected[W->AdjV] = false;
    }
    /* 先将起点收入集合 */
    dist[S] = 0;
    mon[S] = 0;
    collected[S] = true;
 
    while (1) {
        /* V = 未被收录顶点中dist最小者 */
        V = FindMinDist( Graph, dist, mon, collected );
        if ( V==ERROR ) /* 若这样的V不存在 */
            break;      /* 算法结束 */
        collected[V] = true;  /* 收录V */
        for( W=Graph->G[V].FirstEdge; W; W=W->Next ) /* 对图中的每个顶点W */
            /* 若W->AdjV未被收录 */
            if ( collected[W->AdjV]==false ) {
                // if ( Graph->G[V][W]<0 ) /* 若有负边 */
                //     return false; /* 不能正确解决，返回错误标记 */
                /* 若收录V使得dist[W]变小 */
                if ( dist[V]+W->Weight < dist[W->AdjV] || 
                    (dist[V]+W->Weight == dist[W->AdjV] && mon[V]+W->Money < mon[W->AdjV])) {
                    dist[W->AdjV] = dist[V]+W->Weight; /* 更新dist[W] */
                    mon[W->AdjV] = mon[V]+W->Money;
                    // printf("i=%d, mon=%d\n", W->AdjV, mon[W->AdjV]);
                }
            }
    } /* while结束*/
    
    printf("%d %d\n", dist[D], mon[D]);
}
 
 
LGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V;
    LGraph Graph;
     
    Graph = (LGraph)malloc( sizeof(struct GNode) ); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接表头指针 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
       for (V=0; V<Graph->Nv; V++)
        Graph->G[V].FirstEdge = NULL;
             
    return Graph; 
}
        
void InsertEdge( LGraph Graph, Edge E )
{
    PtrToAdjVNode NewNode;
     
    /* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Money = E->Money;
    /* 将V2插入V1的表头 */
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode;
         
    /* 若是无向图，还要插入边 <V2, V1> */
    /* 为V1建立新的邻接点 */
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    NewNode->Money = E->Money;
    
    /* 将V1插入V2的表头 */
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode;
}
 
LGraph BuildGraph()
{
    LGraph Graph;
    Edge E;
    int Nv, i;
     
    scanf("%d", &Nv);   /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
     
    scanf("%d %d %d", &(Graph->Ne), &S, &D);   /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */ 
        E = (Edge)malloc( sizeof(struct ENode) ); /* 建立边结点 */ 
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            scanf("%d %d %d %d", &E->V1, &E->V2, &E->Weight, &E->Money); 
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    } 
 
    return Graph;
}