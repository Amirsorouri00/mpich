MPI_Init() {
	MPIR_Init_thread();
}

// next
//
MPIR_Init_thread() {
	MPII_Init_thread_and_enter_cs();
	//MPII_pre_init_dbg_logging(argc, argv);
	MPIR_T_env_init();
	MPII_init_global();
	MPII_debuger_hold();	// Inline
	OPA_Store_init();		// Setting State
	MPIR_Group_init();
	MPID_init();			// **
	MPI_Coll_init();		// maybe important but i think not|:
	MPI_post_init_global(); // **

	// wait 
	
	MPI_init_async();		// maybe important maybe not
	MPIR_Thread_cs_init();	// Create fine grain mutexes

	if (MPIR_Processes.hasParent) {
		MPID_init_spawn();
	}

	MPID_InitCompleted();
	MPII_init_thread_and_exit_cs();
	OPA_write_barrier();	// make fields of MPIR_Process global visible and set mpich state
	OPA_store_init();
}
