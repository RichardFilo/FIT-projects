/**
 * @file test_block_schema.cpp
 * @author Richard Filo (xfilor00)
 * @brief Test na kontrolu funkcnosti modulu blok_schema
 * @date 2021-05-06
 */

#include "../src/block_schema.h"
#include <iostream>

int main(){
    using namespace std;

    Block_schema schema;
    string sum1 = schema.add_block(sum);
    string sum2 = schema.add_block(sum);
    string sum3 = schema.add_block(sum);
    string sub1 = schema.add_block(sub);
    string sub2 = schema.add_block(sub);
    string inc1 = schema.add_block(inc);

    schema.add_junction(sum1,0,sum2,0);
    schema.add_junction(inc1,0,sum2,1);
    schema.add_junction(sum2,0,sub2,1);

    schema.set_block_input_by_index(3,inc1,0);
    schema.set_block_input_by_index(5,sum1,0);
    schema.set_block_input_by_index(-10,sum1,1);

    schema.remove_junction(sum1,0,sum2,0);
    schema.add_junction(sum1,0,sum2,0);


    if(schema.change_block_name(sum1, "Ajajaj") == 0){
        sum1 = "Ajajaj";
    }
    if(schema.change_block_name(sum2, "Ajajaj") == 0){
        sum2 = "Ajajaj";
    }
    if(schema.change_block_name(sub2, "Ojojoj") == 0){
        sub2 = "Ajajaj";
    }
    schema.simulate();
    cerr << schema.generate_sim_code();
}