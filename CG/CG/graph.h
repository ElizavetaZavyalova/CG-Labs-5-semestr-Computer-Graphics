#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    float t=1;//A<t<B
    float a=1;//a>0
    float A=-9; //A<B
    float B=-8;//B<-1
public:
    void x(float t);
    void y(float t);
    Graph();
};

#endif // GRAPH_H
