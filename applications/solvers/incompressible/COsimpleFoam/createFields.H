    Info << "Reading species properties\n" << endl;
    IOdictionary speciesProperties
    (
     	IOobject
	(
	 	"speciesProperties",
		runTime.constant(),
		mesh,
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	)
    );

    dimensionedScalar DI
    (
     	speciesProperties.lookup("DI")
    );

    dimensionedScalar Sc_T
    (
     	speciesProperties.lookup("Sc_T")
    );

    dimensionedScalar mass_source
    (
     	speciesProperties.lookup("mass_source")
    );
    
    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    Info<< "Reading field CO\n" << endl;
    volScalarField CO
    (
     	IOobject
	(
	 	"CO",
		runTime.timeName(),
		mesh,
		IOobject::MUST_READ,
		IOobject::AUTO_WRITE
	),
	mesh
    );

    Info<< "Reading field AIR\n" << endl;
    volScalarField AIR
    (
	IOobject
	(
		 "AIR",
		 runTime.timeName(),
		 mesh,
		 IOobject::MUST_READ,
		 IOobject::AUTO_WRITE
	 ),
	mesh
     );


    #include "createPhi.H"


    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell(p, mesh.solutionDict().subDict("SIMPLE"), pRefCell, pRefValue);

    singlePhaseTransportModel laminarTransport(U, phi);

    autoPtr<incompressible::RASModel> turbulence
    (
        incompressible::RASModel::New(U, phi, laminarTransport)
    );

