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
    Chunks divided into sub chunks, this will contain blocks.

    The chunks shall be stored into a file (format yet to be determined) for each region (16 chunk radius)
    The structure would be a binary tree.

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
    Chunk* newChunk = (Chunk*)malloc(sizeof(Chunk));
    newChunk->X = X;
    newChunk->Z = Z;

    FILE* fptr;

    VoxelChunkGen(newChunk);

    fptr = fopen("world.dat", "a");

    //Geh durch den Pointers bis die Dateien erreicht werden. Danach könnte das gespeichert werden.

    for(int i = 0; i < 16; i++)
    {
        Voxel* ptrToArr = newChunk->ArrayX[i];
        fwrite(ptrToArr, sizeof(Voxel), 1, fptr);
    }

    //Y Array
    for(int i = 0; i < 384; i++)
    {
        Voxel* ptrToArr = newChunk->ArrayY[i];
        fwrite(ptrToArr, sizeof(Voxel), 1, fptr);
    }

    //Z Array
    for(int i = 0; i < 16; i++)
    {
        Voxel* ptrToArr = newChunk->ArrayZ[i];
        fwrite(ptrToArr, sizeof(Voxel), 1, fptr);
    }

    fclose(fptr);

    free(newChunk);
}

Voxel* VoxelChunkGen(Chunk* chunk)
{
    chunk->ArrayX = (Voxel*)calloc(16, sizeof(Voxel)); //Gefährilch
    chunk->ArrayY = (Voxel*)calloc(384, sizeof(Voxel)); //Gefährilch
    chunk->ArrayZ = (Voxel*)calloc(16, sizeof(Voxel)); //Gefährilch

    for (int x = 0; x < 16; x++)
    {
        for (int z = 0; z < 16; z++)
        {
            for (int y = 0; y < 384; y++)
            {
                Voxel* voxel = (Voxel*)malloc(sizeof(Voxel));

                if (isAir() == 1)
                {
                    voxel->blockTypeID = 0;
                    voxel->transparent = 1;
                }
                else
                {
                    voxel->blockTypeID = 1;
                    voxel->transparent = 0;
                }

                //chunk->ArrayX[x] = (Voxel*)malloc(sizeof(Voxel));
                chunk->ArrayX[x] = voxel;
                //chunk->ArrayY[y] = (Voxel*)malloc(sizeof(Voxel));
                chunk->ArrayY[y] = voxel;
                //chunk->ArrayZ[z] = (Voxel*)malloc(sizeof(Voxel));
                chunk->ArrayZ[z] = voxel;
            }
        }
    }
}

int isAir()
{
    int seed = time(NULL);
    srand(seed);

    return rand() % 2;
}

bool shouldChunkRender(double playerX, double playerZ) //Guck für den Chunk wo den Spieler steht welchem Chunks gerendert werden mussen.
{
    double xChunk = playerX / 16;
    double zChunk = playerZ / 16;
    double lastxChunk;
    double lastzChunk;

    if (xChunk != lastxChunk)
    {
        ChunkLoader();
    }

    lastxChunk = playerX / 16;
    lastzChunk = playerZ / 16;
}

void ChunkLoader() //Lad alle benötigte Chunks hoch zum Arbeitsspeicher
{
    FILE* fptr;

    fptr = fopen("world.dat", "r");

    //Chunk
    Chunk* chunk;
    Voxel voxel;

    chunk = (Chunk*)malloc(sizeof(Chunk));

    while (fread(&voxel, sizeof(voxel), 1, fptr) == 1)
    {
        printf("block: %d\n", voxel.blockTypeID);
    }

    fclose(fptr);
}

void ChunkRenderCaller(unsigned int shaderProgram)
{
    //Jeder Mal, dass den Spieler zu einem anderem Chunk bewegt wird den ChunkLoader Funktion angeruft.


}

void ChunkRender(int X, int Z, unsigned int shaderProgram)
{
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, (vec3){0, 0, 0});
                
    int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}