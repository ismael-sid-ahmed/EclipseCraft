/*
    The voxel system will store all world data in a Generic Tree Structure. Whether they are voxels, sub-chuncks or chunks will
    get determined by the height in the tree. 
*/

typedef struct voxel
{
    int blockTypeID;
}Voxel;

//Save all chunks into a single array, no different arrays for each axis
typedef struct chunk
{
    int voxel[98304];
    int X, Z;
}Chunk;


Voxel VoxelChunkGen(Chunk* chunk);
int isAir();

void ChunkGenCaller(int X, int Z);
void ChunkGen(int X, int Z);
void BlockRender(int X, int Z, int Y, unsigned int shaderProgram);
void InitialChunkGenCaller();
void ChunkRenderCaller(unsigned int shaderProgram);
void ChunkLoader(double X, double Z, unsigned int shaderProgram);
