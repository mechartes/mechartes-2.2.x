CO.storePrevIter();
	
	fvScalarMatrix COEqn
	(
		fvm::div(phi, CO)
	       -fvm::laplacian(DI + (turbulence->nuEff()/Sc_T),CO)
	        ==
		mass_source
	);

//Apply under-relaxation to the equation as defined in system::fvSolution
	COEqn.relax();
	COEqn.solve();
	CO.max(0.0);
	CO.min(1.0);

	AIR = 1.0 - CO;

