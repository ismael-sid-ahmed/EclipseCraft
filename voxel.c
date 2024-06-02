#include "voxel.h"

#include "stdio.h"
#include "stdlib.h"

/*Design:
    Chunks divided into sub chunks, this will contain blocks.

    The chunks shall be stored into a file (format yet to be determined) for each region (16 chunk radius)
    The structure would be a binary tree.

*/

void RegionGen() //32x32 chunks (1024)
{
    WorldNode root;
    root.height = 0;
    
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            ChunkGen(&root, i, j);
        }
    }
    
}

void ChunkGen(WorldNode* root, double X, double Z) //16x16 voxels
{
    WorldNode* chunk = (WorldNode*)malloc(sizeof(WorldNode));
    chunk->Children = (WorldNode*)malloc(98304*sizeof(WorldNode));
    chunk->X = X;
    chunk->Z = Z;
    
    for (int m = 0; m < 24; m++) //Chunk (24 subs)
    {
        
        chunk->Y = m;
        for (int i = 0; i < 16; i++) //Sub-Chunk (4096 vox)
        {
            for (int j = 0; j < 16; j++)
            {
                for (int k = 0; k < 16; k++)
                {
                    WorldNode* voxel = (WorldNode*)malloc(sizeof(WorldNode));
                    voxel->X = i;
                    voxel->Y = j;
                    voxel->Z = k;

                    chunk->Children[i+j+k] = (WorldNode*)malloc(sizeof(WorldNode));
                    chunk->Children[i+j+k] = voxel;
                }
            }
        }
    }
}