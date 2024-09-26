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
    Voxel[98304] Array;
}Chunk;

typedef struct chunkArr
{
    size_t size;
    Chunk* array;
}ChunkArray;

Voxel* VoxelChunkGen(Chunk* chunk);
int isAir();

void ChunkGenCaller(int X, int Z);
void ChunkGen(int X, int Z);
void ChunkRender(int X, int Z);
void InitialChunkGenCaller();
void ChunkRenderCaller(unsigned int shaderProgram);
void ChunkLoader();
