#include <../include/graph.h>
#include <../include/dataloader.h>
#include "../include/pattern.h"
#include "../include/schedule.h"
#include "../include/common.h"
#include "../include/motif_generator.h"

#include <assert.h>
#include <iostream>
#include <string>
#include <algorithm>

void print_scheduler(const Pattern &pattern, int v_num, int e_num, int tri_num){
    bool is_pattern_valid;
    int performance_modeling_type = 1;
    int restricts_type = 1;
    int use_in_exclusion_optimize = 0;
    Schedule schedule(pattern, is_pattern_valid, performance_modeling_type, restricts_type, use_in_exclusion_optimize, v_num, e_num, tri_num);
    schedule.print_schedule();
    std::vector< std::vector< std::pair<int,int> > > restricts;
    schedule.restricts_generate(schedule.get_adj_mat_ptr(), restricts);
    int restricts_num = schedule.get_total_restrict_num();
    printf("size of restrict set: %d\n", restricts_num);
    printf("total num: %d\n", restricts.size());
    for(auto &restrict : restricts) {
        for(auto &p : restrict)
            printf("(%d,%d)",p.first,p.second);
        puts("");
    }
};


int main(int argc,char *argv[]) {

    if (argc != 4){
        printf("./scheduler_printer [v_num] [e_num] [tri_num]" );
        return 0;
    }
    int v_num, e_num, tri_num;
    v_num = atoi(argv[1]);
    e_num = atoi(argv[2]);
    tri_num = atoi(argv[3]);

    std::cout << "Q1: " << std::endl;
    Pattern q1(PatternType::Q1);
    print_scheduler(q1, v_num, e_num, tri_num);

    std::cout << "Q2: " << std::endl;
    Pattern q2(PatternType::Q2);
    print_scheduler(q2, v_num, e_num, tri_num);

    std::cout << "Q3: " << std::endl;
    Pattern q3(PatternType::Q3);
    print_scheduler(q3, v_num, e_num, tri_num);

    std::cout << "Q4: " << std::endl;
    Pattern q4(PatternType::Q4);
    print_scheduler(q4, v_num, e_num, tri_num);

    std::cout << "Q5: " << std::endl;
    Pattern q5(PatternType::Q5);
    print_scheduler(q5, v_num, e_num, tri_num);

    std::cout << "Q6: " << std::endl;
    Pattern q6(PatternType::Q6);
    print_scheduler(q6, v_num, e_num, tri_num);

    // printf("5 ");
    // const int* adj_mat = pattern.get_adj_mat_ptr();
    // for(int i = 0; i < 5; ++i)
    //     for(int j = 0; j< 5; ++j)
    //         printf("%d", adj_mat[INDEX(i,j,5)]);
    // puts("");
    // Pattern p(PatternType::Cycle_6_Tri);
    // printf("6 ");
    // const int* adj_mat2 = p.get_adj_mat_ptr();
    // for(int i = 0; i < 6; ++i)
    //     for(int j = 0; j< 6; ++j)
    //         printf("%d", adj_mat2[INDEX(i,j,6)]);
    return 0;
}
