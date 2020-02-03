/* 7-10 Saving James Bond - Easy Version */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NODES   100
#define SIDE_LEN    100
#define CENTER_DIA  15

typedef double PointType;
typedef struct
{
    PointType x;
    PointType y;
}Point;

struct Node
{
    Point Position;
    int is_visit;
}Corc[MAX_NODES];

bool can_jump(Point start, Point end, PointType D);
bool can_escape(Point now, PointType D);
bool DFS(Point now, PointType D);

int N;

int main(void)
{
    PointType D, x, y;
    int i;
    Point center;
    bool is_succ = false;

    scanf("%d%lf", &N, &D);
    for(i=0; i<N; ++i){
        scanf("%lf%lf", &x, &y);
        Corc[i].Position.x = x;
        Corc[i].Position.y = y;
        Corc[i].is_visit = 0;
    }

    center.x = center.y = 0;
    if(can_escape(center, D+CENTER_DIA/2)){
        is_succ = true;
    }else{
        for(i=0; i<N; ++i){
            if(!Corc[i].is_visit && can_jump(center, Corc[i].Position, D+CENTER_DIA/2)){
                Corc[i].is_visit = 1;
                is_succ = DFS(Corc[i].Position, D);
                if(is_succ) break;
            }

        }
    }
    printf("%s\n", is_succ?"Yes":"No");
}

bool DFS(Point now, PointType D)
{
    int i;
    bool is_succ = false;
    if(can_escape(now, D)){
        is_succ = true;
    }else{
        for(i=0; i<N; ++i){
            if(!Corc[i].is_visit && can_jump(now, Corc[i].Position, D)){
                Corc[i].is_visit = 1;
                is_succ = DFS(Corc[i].Position, D);
                if(is_succ) break;
            }
        }
    }
    return is_succ;
}

bool can_escape(Point now, PointType D)
{
    PointType nx, ny;
    nx = now.x;
    ny = now.y;
    return abs(nx-SIDE_LEN/2)<=D || abs(ny-SIDE_LEN/2)<=D;
}

bool can_jump(Point start, Point end, PointType D)
{
    PointType tx, ty;
    tx = end.x - start.x;
    ty = end.y - start.y;
    return (tx*tx+ty*ty) <= D*D;
}