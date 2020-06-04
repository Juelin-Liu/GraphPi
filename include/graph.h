#pragma once
#include "schedule.h"
#include "vertex_set.h"
#include <assert.h>

class Graphmpi;
class Graph {
public:
    int v_cnt; // number of vertex
    unsigned int e_cnt; // number of edge
    long long tri_cnt; // number of triangle
    double max_running_time = 60 * 60 * 24; // second

    int *edge; // edges
    unsigned int *vertex; // v_i's neighbor is in edge[ vertex[i], vertex[i+1]-1]
    
    Graph() {
        v_cnt = 0;
        e_cnt = 0;
        edge = nullptr;
        vertex = nullptr;
    }

    ~Graph() {
        if(edge != nullptr) delete[] edge;
        if(vertex != nullptr) delete[] vertex;
    }

    int intersection_size(int v1,int v2);
    int intersection_size_mpi(int v1,int v2);
    int intersection_size_clique(int v1,int v2);

    long long intersection_times_low;
    long long intersection_times_high;
    long long dep1_cnt;
    long long dep2_cnt;
    long long dep3_cnt;

    //single thread triangle counting
    long long triangle_counting();
    
    //multi thread triangle counting
    long long triangle_counting_mt(int thread_count);

    //multi thread triangle counting with mpi
    long long triangle_counting_mpi(int thread_count);

    //general pattern matching algorithm with multi thread
    long long pattern_matching(const Schedule& schedule, int thread_count, bool clique = false);

    //general pattern matching algorithm with multi thread ans multi process
    long long pattern_matching_mpi(const Schedule& schedule, int thread_count, bool clique = false);
private:
    friend Graphmpi;
    void tc_mt(long long * global_ans);

    void get_edge_index(int v, unsigned int& l, unsigned int& r) const;

    void pattern_matching_func(const Schedule& schedule, VertexSet* vertex_set, VertexSet& subtraction_set, long long& local_ans, int depth, bool clique = false);

    void pattern_matching_aggressive_func(const Schedule& schedule, VertexSet* vertex_set, VertexSet& subtraction_set, VertexSet& tmp_set, long long& local_ans, int depth);

    void pattern_matching_aggressive_func_mpi(const Schedule& schedule, VertexSet* vertex_set, VertexSet& subtraction_set, VertexSet &tmp_set, long long& local_ans, int depth);
};
