#include "../simulator.hpp"

// =====================================================================
processor_t::processor_t() {
	rob = (rob_entry_t*)malloc(256 * sizeof(rob_entry_t));
};

// =====================================================================
void processor_t::allocate() {

};

// =====================================================================


void processor_t::clock() {
	if (sizeof(rob) == 256) {
		parada = true;
	}

	if (!parada) {
		opcode_package_t new_instruction;
		if (!orcs_engine.trace_reader->trace_fetch(&new_instruction)) {
			orcs_engine.simulator_alive = false;
		}
		else {
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_INT_ALU) {
				// ajustar rob
				rob[0].tipo = INSTRUCTION_OPERATION_INT_ALU;
				rob[0].ciclo_final = ciclos_totais + ciclos_int_alu;

				if (rs_int_alu > 0) {
					rs_int_alu -= 1;
					printf("INT_ALU ");
					ciclos_totais += ciclos_int_alu;
					rs_int_alu += 1;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_INT_MUL) {
				if (rs_int_mul > 0) {
					rs_int_mul -= 1;
					printf("INT_MUL ");
					rs_int_mul += 1;
					ciclos_totais += ciclos_int_mul;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_INT_DIV) {
				if (rs_int_div > 0) {
					rs_int_div -= 1;
					printf("INT_DIV ");
					rs_int_div += 1;
					ciclos_totais += ciclos_int_div;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_FP_ALU) {
				if (rs_fp_alu > 0) {
					rs_fp_alu -= 1;
					printf("FP_ALU ");
					rs_fp_alu += 1;
					ciclos_totais += ciclos_fp_alu;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_FP_MUL) {
				if (rs_fp_mul > 0) {
					rs_fp_mul -= 1;
					printf("FP_MUL ");
					rs_fp_mul += 1;
					ciclos_totais += ciclos_fp_mul;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_FP_DIV) {
				if (rs_fp_div > 0) {
					rs_fp_div -= 1;
					printf("FP_DIV ");
					rs_fp_div += 1;
					ciclos_totais += ciclos_fp_div;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_BRANCH) {
				if (rs_branch > 0) {
					rs_branch -= 1;
					printf("BRANCH ");
					rs_branch += 1;
					ciclos_totais += ciclos_fp_div;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_MEM_LOAD) {
				if (rs_mem_load > 0) {
					rs_mem_load -= 1;
					printf("MEM_LOAD ");
					rs_mem_load += 1;
					ciclos_totais += ciclos_fp_div;
				}
				else {
					parada = true;
				}
			}
			if (new_instruction.opcode_operation == INSTRUCTION_OPERATION_MEM_STORE) {
				if (rs_mem_store > 0) {
					rs_mem_store -= 1;
					printf("MEM_STORE ");
					rs_mem_store += 1;
					ciclos_totais += ciclos_fp_div;
				}
				else {
					parada = true;
				}
			}
		}
	}

	printf("\n====================================");
	printf("\n====> Ciclos Totais: %d\n", ciclos_totais);
	printf("====================================");
};

// =====================================================================
void processor_t::statistics() {

};