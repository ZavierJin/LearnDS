/* 7-11 Saving James Bond - Hard Version */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NODES   100
#define SIDE_LEN    100
#define CENTER_DIA  15
#define Null        -1

typedef double PointType;
typedef struct
{
    PointType x;
    PointType y;
}Point;

struct Node
{
    Point Position;
    int dist;
    int pre_id;
    PointType first_dist;
}Corc[MAX_NODES];

bool can_jump(Point start, Point end, PointType D);
bool can_escape(Point now, PointType D);
// bool DFS(Point now, PointType D);
int BFS(PointType D);
PointType cal_dist(Point start, Point end);
void show_res(int last_pre_id);

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

Queue CreateQueue( int MaxSize );
bool AddQ( Queue Q, ElementType X );
ElementType DeleteQ( Queue Q );
bool IsEmpty( Queue Q );

int N;
Queue Q = NULL;

int main(void)
{
    PointType D, x, y;
    int i;
    Point center;
    int last_pre_id = Null;

    scanf("%d%lf", &N, &D);
    for(i=0; i<N; ++i){
        scanf("%lf%lf", &x, &y);
        Corc[i].Position.x = x;
        Corc[i].Position.y = y;
        Corc[i].dist = Null;
        Corc[i].pre_id = Null;
        Corc[i].first_dist = Null;
    }

    Q = CreateQueue(N+1);
    center.x = center.y = 0;
    if(can_escape(center, D+CENTER_DIA/2)){
        last_pre_id = -2;
    }else{
        for(i=0; i<N; ++i){
            if(Corc[i].dist==Null && can_jump(center, Corc[i].Position, D+CENTER_DIA/2)){
                Corc[i].dist = 1;
                Corc[i].first_dist = cal_dist(center, Corc[i].Position);
                AddQ(Q, i);
                // printf("i=%d\n", i);
                // printf("add=%d\n", i);
            }
        }
        last_pre_id = BFS(D);
    }
    // printf("2last=%d\n", last_pre_id);
    show_res(last_pre_id);
}

void show_res(int last_pre_id)
{
    int* output;
    int distance = 0;
    int i, j;
    PointType x, y;
    if(last_pre_id==Null){
        printf("0\n");
    }else if(last_pre_id==-2){
        printf("1\n");
    }else{
        distance = Corc[last_pre_id].dist + 1;
        output = (int *)malloc(sizeof(int)*(distance));
        i = last_pre_id;
        j = distance - 1;
        while(i!=Null){
            output[j--] = i;
            i = Corc[i].pre_id;
            // printf("next_i=%d\n", i);
        }
        printf("%d\n", distance);
        for(j=1; j<distance; ++j){
            x = Corc[output[j]].Position.x;
            y = Corc[output[j]].Position.y;
            printf("%.f %.f\n", x, y);
        }
    }
    return;
}

int BFS(PointType D)
{
    int last_pre_id = Null;
    int last_dist = Null;
    PointType min_first_dist = Null;
    bool change = false;
    int now_id;
    int i;
    while(!IsEmpty(Q)){
        now_id = DeleteQ(Q);
        // printf("now_id=%d\n", now_id);
        if(can_escape(Corc[now_id].Position, D)){
            change = (last_dist==Null) || (last_dist>=Corc[now_id].dist+1 
                && min_first_dist>Corc[now_id].first_dist);
            if(change) {
                last_pre_id = now_id;
                last_dist = Corc[now_id].dist + 1;
                min_first_dist = Corc[now_id].first_dist;
            }
        }else{
            for(i=0; i<N; ++i){
                if(can_jump(Corc[now_id].Position, Corc[i].Position, D)){
                    change = (Corc[i].dist==Null) || (Corc[i].dist>=Corc[now_id].dist+1 
                        && Corc[i].first_dist>Corc[now_id].first_dist);
                    if(change){
                        Corc[i].dist = Corc[now_id].dist + 1;
                        Corc[i].pre_id = now_id;
                        Corc[i].first_dist = Corc[now_id].first_dist;
                        // printf("i=%d, dist=%d, pre_id=%d\n", i, Corc[i].dist, Corc[i].pre_id);
                        AddQ(Q, i);
                    }
                }
            }
        }
    }
    // printf("last=%d\n", last_pre_id);
    return last_pre_id;
}

// bool DFS(Point now, PointType D)
// {
//     int i;
//     bool is_succ = false;
//     if(can_escape(now, D)){
//         is_succ = true;
//     }else{
//         for(i=0; i<N; ++i){
//             if(!Corc[i].is_visit && can_jump(now, Corc[i].Position, D)){
//                 Corc[i].is_visit = 1;
//                 is_succ = DFS(Corc[i].Position, D);
//                 if(is_succ) break;
//             }
//         }
//     }
//     return is_succ;
// }

bool can_escape(Point now, PointType D)
{
    PointType nx, ny;
    nx = now.x;
    ny = now.y;
    return abs(nx-SIDE_LEN/2)<=D || abs(ny-SIDE_LEN/2)<=D;
}

bool can_jump(Point start, Point end, PointType D)
{
    return cal_dist(start, end)<= D;
}

PointType cal_dist(Point start, Point end)
{
    PointType tx, ty;
    tx = end.x - start.x;
    ty = end.y - start.y;
    return sqrt(tx*tx+ty*ty);
}


 
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
        printf("full");
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
        printf("empty");
        return ERROR;
    }
    else  {
        Q->Front =(Q->Front+1)%Q->MaxSize;
        return  Q->Data[Q->Front];
    }
}