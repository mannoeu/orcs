// ========================================================================
// ========================================================================
class processor_t {
private:
	bool parada = false;

	int ciclos_nop = 1;
	int ciclos_int_alu = 2;
	int ciclos_int_mul = 10;
	int ciclos_int_div = 20;
	int ciclos_fp_alu = 2;
	int ciclos_fp_mul = 15;
	int ciclos_fp_div = 30;
	int ciclos_branch = 2;
	int ciclos_mem_load = 50;
	int ciclos_mem_store = 40;

	int rs_nop = 1;
	int rs_int_alu = 2;
	int rs_int_mul = 1;
	int rs_int_div = 1;
	int rs_fp_alu = 2;
	int rs_fp_mul = 1;
	int rs_fp_div = 1;
	int rs_branch = 2;
	int rs_mem_load = 1;
	int rs_mem_store = 1;

	int ciclos_totais = 0;

public:
	// ===================================================================
	/// Methods
	// ===================================================================
	processor_t();
	void allocate();
	void clock();
	void statistics();

	rob_entry_t* rob;
};

class rob_entry_t {
private:

public:
	instruction_operation_t tipo;
	uint64_t ciclo_final;
};