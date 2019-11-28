#pragma once

namespace DistanceMatrixDefaultValue {
	int g0Size = 5;
	float g0Value[] = {
		0, 3, 5, 7, 10, 3, 0, 2, 10, 7, 5, 2, 0, 10, 5,
		7, 10, 10, 0, 5, 10, 7, 5, 5, 0
	};
	int g0IndexTable[] = { 2, 3, 6, 9, 13 };

	//G1
	int g1Size = 5;
	float g1Value[] = {
		0, 3, 8, 9, 5, 3, 0, 7, 8, 2, 8, 7, 0, 1, 9,
		9, 8, 1, 0, 10, 5, 2, 9, 10, 0
	};
	int g1IndexTable[] = { 2, 3, 4, 5, 6 };

	//G2
	int g2Size = 3;
	float g2Value[] = {
		0, 1, 5, 1, 0, 4, 5, 4, 0
	};
	int g2IndexTable[] = { 9, 10, 13 };

	// G3
	int g3Size = 4;
	float g3Value[] = {
		0, 2, 5, 9, 2, 0, 3, 8,
		5, 3, 0, 7, 9, 8, 7, 0
	};
	int g3IndexTable[] = { 1, 2, 3, 4 };


	// G4
	int g4Size = 4;
	float g4Value[] = {
		0, 10, 10, 8, 10, 0, 2, 4,
		10, 2, 0, 2, 8, 4, 2, 0
	};
	int g4IndexTable[] = { 5, 6, 7, 8 };


	// G5
	int g5Size = 4;
	float g5Value[] = {
		0, 1, 1, 4, 1, 0, 2, 5, 1, 2, 0, 3, 4, 5, 3, 0
	};
	int g5IndexTable[] = { 9, 10, 11, 12 };


	// G5
	int g6Size = 4;
	float g6Value[] = {
		0, 1, 2, 4, 1, 0, 3, 5, 2, 3, 0, 2, 4, 5, 2, 0
	};
	int g6IndexTable[] = { 13, 14, 15, 16 };
	int gxSize[] = { 5, 5, 3, 4, 4, 4, 4 };

	float *gxValue[] = { g0Value, g1Value, g2Value, g3Value, g4Value, g5Value, g6Value };
	int *gxIndexTable[] = { g0IndexTable, g1IndexTable, g2IndexTable, g3IndexTable, g4IndexTable, g5IndexTable, g6IndexTable };

	int boundaryVertexIndex[] = { 2, 3, 4, 5, 6, 9, 10, 13 };
}

