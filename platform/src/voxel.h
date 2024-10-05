/*
    The voxel system will store all world data in a Generic Tree Structure. Whether they are voxels, sub-chuncks or chunks will
    get determined by the height in the tree. 
*/

//Save all chunks into a single array, no different arrays for each axis

int isAir();

int chunksInMemoryRecall();
void ChunkGenCaller(int X, int Z);
void ChunkGen(int X, int Z);
void BlockRender(int X, int Z, int Y, unsigned int shaderProgram, unsigned __int8 Voxel);
void RegionGen();
void ChunkRenderCaller(unsigned int shaderProgram);
void ChunkLoader(int X, int Z, unsigned int shaderProgram);
void ChunkRender();
