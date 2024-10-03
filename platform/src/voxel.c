#include "voxel.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "glad.h"
#include "glfw3.h"

#include "cglm.h"
#include <errno.h>

#define CHUNK_RENDER_DISTANCE 4
#define MAX_CHUNKS 32
#define SPAWN_CHUNK_RADIUS 16
#define INITIAL_CHUNK_ARRAY_SIZE 2

/*Design:
    The chunks will get generated with their respective
    voxels inside. Then only the voxels will get serialized
    into a file. When the voxels get loaded once again into
    memory, they will have inside an identifier for their
    position in the chunk and their respective chunk coords.
*/



void InitialChunkGenCaller()
{
    FILE* fptr;
    

    fptr = fopen("world.dat", "w");
    fprintf(fptr, "");
    fclose(fptr);

    for (int i = 0; i < SPAWN_CHUNK_RADIUS; i++)
    {
        for (int j = 0; j < SPAWN_CHUNK_RADIUS; j++)
        {
            ChunkGen(i, j);
        }
    }
}

void ChunkGenCaller(int X, int Z)
{
    
}


void ChunkGen(int X, int Z)
{
    Chunk newChunk;

    FILE* fptr;

    int gen_voxel_num = 0;

    for (int y = 0; y < 384; y++)
    {
        for (int z = 0; z < 16; z++)
        {
            for (int x = 0; x < 16; x++)
            {
                if (isAir() == 1)
                {
                    newChunk.voxel[gen_voxel_num] = 0;
                }
                else
                {
                    newChunk.voxel[gen_voxel_num] = 1;
                }
                gen_voxel_num++;
            }
            //Formula for offset: (Layer: (x+z)*chunk_coords)
        }
    }

    newChunk.X = X;
    newChunk.Z = Z;

    fptr = fopen("world.dat", "a");

    //Geh durch den Pointers bis die Dateien erreicht werden. Danach könnte das gespeichert werden.
    fwrite(&newChunk.X, sizeof(int), 1, fptr);
    fwrite(&newChunk.Z, sizeof(int), 1, fptr);
    fwrite(&newChunk.voxel, sizeof(Voxel), 98304, fptr);

    fclose(fptr);
}

Voxel VoxelChunkGen(Chunk* chunk)
{
    //Remove double pointer, and get all chunks and voxels into a single array of fixed size 98304. I don't need to use malloc
    


}

int isAir()
{
    rand();
    return rand() % 2;
}

bool shouldChunkRender(double playerX, double playerZ) //Guck für den Chunk wo den Spieler steht welchem Chunks gerendert werden mussen.
{
    double xChunk = playerX / 16;
    double zChunk = playerZ / 16;
    double lastxChunk;
    double lastzChunk;

    if (xChunk != lastxChunk || zChunk != lastzChunk)
    {
    }

    lastxChunk = playerX / 16;
    lastzChunk = playerZ / 16;
}

void ChunkLoader(double X, double Z, unsigned int shaderProgram)
{
    FILE* fptr;
    Chunk loadedChunk;

    fptr = fopen("world.dat", "r");

    //Jeder 256 Array-Elemente bestehen einen Ebene

    int i = 0;
    fread(&loadedChunk.voxel, sizeof(Voxel), 98304, fptr);
    
    int voxel_count = 0;
    for (int y = 0; y < 384; y++)
    {
        for (int x = 0; x < 16; x++)
        {
            for (int z = 0; z < 16; z++)
            {
                if (loadedChunk.voxel[voxel_count] == 1)
                {
                    BlockRender(X+x, Z+z, y, shaderProgram);
                }
                voxel_count++;
            }
        }
    }

    fclose(fptr);
}

//Alle Chunks die am ende von eine gesetztes Pointer stehen werden geladen.

void ChunkRenderCaller(unsigned int shaderProgram, int playerX, int playerZ)
{
    
}

void BlockRender(int X, int Z, int Y, unsigned int shaderProgram)
{
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, (vec3){X, Y, Z});
                
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

    glDrawArrays(GL_TRIANGLES, 0, 36);   
}
