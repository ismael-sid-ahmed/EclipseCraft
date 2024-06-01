/*
    The voxel system will store all world data in a Generic Tree Structure. Whether they are voxels, sub-chuncks or chunks will
    get determined by the height in the tree. 
*/

struct Node
{
    double X, Y, Z;
    int height;
    struct Node** Children;
};

typedef struct Node WorldNode;

//Data structure functions


void RegionGen();
void ChunkGen(WorldNode* root, double X, double Z);