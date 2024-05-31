//Tree structure

struct Voxel
{
    double blockID;
    double X;
    double Y;
    double Z;
};

typedef struct Voxel Voxel;

struct Chunk
{
    double X;
    double Z;
};

typedef struct Chunk Chunk;

struct Region
{
    double X;
    double Z;
};

typedef struct Region Region;

void ChunkGen();