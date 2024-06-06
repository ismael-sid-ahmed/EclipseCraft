/*
    The voxel system will store all world data in a Generic Tree Structure. Whether they are voxels, sub-chuncks or chunks will
    get determined by the height in the tree. 
*/

typedef struct voxel
{
    int blockTypeID;
    int transparent;
}Voxel;

typedef struct chunk
{
    double X, Z;
    Voxel** ArrayX;
    Voxel** ArrayY;
    Voxel** ArrayZ;
}Chunk;

typedef struct chunkArr
{
    size_t size;
    Chunk* array;
}ChunkArray;

Voxel* VoxelChunkGen(Chunk* chunk);
int isAir(Voxel* voxel);

void ChunkGenCaller(int X, int Z);
void ChunkGen(int X, int Z);
void ChunkRender(int X, int Z);
void InitialChunkGenCaller();
void ChunkRenderCaller(unsigned int shaderProgram);
void ChunkLoader();