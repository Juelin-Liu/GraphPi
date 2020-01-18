#include <gtest/gtest.h>
#include <../include/graph.h>
#include <../include/dataloader.h>
#include "../include/pattern.h"
#include "../include/schedule.h"
#include "../include/common.h"

#include <iostream>
#include <string>

TEST(livejournal_qg5_test, livejournal_qg5) {
    Graph *g;
    DataLoader D;
    
    std::string type = "LiveJournal";
    std::string path = "/home/zms/livejournal_input";
    DataType my_type;
    if(type == "LiveJournal") my_type = DataType::LiveJournal;
    else {
        printf("invalid DataType!\n");
    }
    
    ASSERT_EQ(D.load_data(g,my_type,path.c_str()),true); 
    
    printf("Load data success!\n");
    
    int dataset_vertex_size = 3997962;
    int dataset_edge_size = 34681189;
    int size = 5;

    Pattern pattern(size);
    pattern.add_edge(0, 1);
    pattern.add_edge(0, 2);
    pattern.add_edge(1, 2);
    pattern.add_edge(1, 3);
    pattern.add_edge(3, 4);
    pattern.add_edge(2, 4);

    bool is_valid;
    Schedule schedule(pattern, is_valid, true, dataset_vertex_size, dataset_edge_size);
    
    ASSERT_EQ(is_valid, true);

    std::vector < std::pair<int, int> > pairs;
    int multi = schedule.aggresive_optimize( schedule.get_adj_mat_ptr(), pairs);
    schedule.add_restrict(pairs);
    
    const int *adj_mat = schedule.get_adj_mat_ptr();
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j)
            printf("%d ",adj_mat[INDEX(i, j, size)]);
            puts("");
    }
    for(int i = 0; i < pairs.size(); ++i)
        printf("(%d,%d) ", pairs[i].first, pairs[i].second);
    puts("");

    int thread_num = 24;
    double t1,t2;
    long long ans;
    
    t1 = get_wall_time();
    ASSERT_NE( ans = g->pattern_matching(schedule, thread_num), 0);
    t2 = get_wall_time();

    printf("%lld %.6lf\n", ans, t2 - t1);

    delete g;
}