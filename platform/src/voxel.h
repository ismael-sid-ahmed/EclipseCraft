/*
    The voxel system will store all world data in a Generic Tree Structure. Whether they are voxels, sub-chuncks or chunks will
    get determined by the height in the tree. 
*/

typedef struct chunk
{
    double X, Z;
}Chunk;

typedef struct chunkArr
{
    size_t size;
    Chunk* array;
}ChunkArray;

void ChunkGenCaller(int X, int Z);
void ChunkGen(int X, int Z);
void ChunkRender(int X, int Z);
void InitialChunkGenCaller();
void ChunkRenderCaller(unsigned int shaderProgram);
void ChunkLoader();