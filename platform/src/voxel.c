#include "voxel.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "glad.h"
#include "glfw3.h"

#include "cglm.h"

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

    VoxelChunkGen(newChunk);

    FILE* fptr;

    fptr = fopen("world.dat", "a");
    fwrite(newChunk, sizeof(Chunk), 1, fptr);

    fclose(fptr);

    free(newChunk);
}

Voxel* VoxelChunkGen(Chunk* chunk)
{
    chunk->ArrayX = (Voxel*)malloc(sizeof(Voxel)*16); //Gefährilch
    chunk->ArrayY = (Voxel*)malloc(sizeof(Voxel)*384); //Gefährilch
    chunk->ArrayZ = (Voxel*)malloc(sizeof(Voxel)*16); //Gefährilch

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            for (int z = 0; z < 384; z++)
            {
                Voxel* voxel = (Voxel*)malloc(sizeof(Voxel));

                if (isAir == 1)
                {
                    voxel->blockTypeID = 0;
                    voxel->transparent = 1;
                }
                else
                {
                    voxel->blockTypeID = 1;
                    voxel->transparent = 0;
                }

                chunk->ArrayX[x] = (Voxel*)malloc(sizeof(Voxel));
                chunk->ArrayX[x] = voxel;
                chunk->ArrayY[y] = (Voxel*)malloc(sizeof(Voxel));
                chunk->ArrayY[y] = voxel;
                chunk->ArrayZ[z] = (Voxel*)malloc(sizeof(Voxel));
                chunk->ArrayZ[z] = voxel;
            }
        }
    }
}

int isAir(Voxel* voxel)
{
    int seed = 135681364961324;
    srand(seed);

    return rand() & 1;
}

void ChunkLoader() //Load needed chunks once into memory
{
    FILE* fptr;

    fptr = fopen("world.dat", "r");

    Chunk* chunk = (Chunk*)malloc(sizeof(Chunk));
    ChunkArray* chunkArr = (ChunkArray*)malloc(sizeof(ChunkArray));
    size_t cnt_chunks =  0;

    chunkArr->size = INITIAL_CHUNK_ARRAY_SIZE;
    chunkArr->array = (Chunk*)malloc(sizeof(Chunk)*INITIAL_CHUNK_ARRAY_SIZE);

    int i = 0;

    while(cnt_chunks=fread(chunk, sizeof(Chunk), 1, fptr))
    {
        if (i >= chunkArr->size)
        {
            //Allocate memory
            chunkArr->size++;
            chunkArr->array = (Chunk*)realloc(chunkArr->array, chunkArr->size * sizeof(Chunk));
        }
        chunkArr->array[i].X = chunk->X;
        chunkArr->array[i].Z = chunk->Z;
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        printf("%dX %dZ\n", chunkArr->array[j].X, chunkArr->array[j].X);
    }

    fclose(fptr);
}

void ChunkRenderCaller(unsigned int shaderProgram)
{
    
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