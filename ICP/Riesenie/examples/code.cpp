/**
 * @file code.cpp
 * @author Vygenerovane nasim projektom
 * @brief Testovaci priklad vygenerovanej blokovej schemy (preklad: g++ code.cpp ../src/block_schema.o ../src/block.o)
 * @date 2021-05-06
 */

#include "../src/block_schema.h"
#include <iostream>

int main(){
	Block_schema schema;
	schema.add_block(sub);
	schema.add_block(inc);
	schema.add_block(dec);
	schema.add_block(sum);
	schema.set_block_input_by_index(5, "INC block1", 0);
	schema.change_block_name("DEC block1", "C--");
	schema.set_block_input_by_index(5, "C--", 0);
	schema.change_block_name("INC block1", "C++");
	schema.add_junction("C--", 0, "SUB block1", 1);
	schema.add_junction("C++", 0, "SUB block1", 0);
	schema.add_junction("SUB block1", 0, "SUM block1", 1);
	schema.set_block_input_by_index(10, "SUM block1", 0);
	schema.simulate();
}
