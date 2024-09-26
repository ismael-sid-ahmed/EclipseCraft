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
    Chunk* newChunk = (Chunk*)malloc(sizeof(Chunk));

    FILE* fptr;

    VoxelChunkGen(newChunk);

    fptr = fopen("world.dat", "a");

    //Geh durch den Pointers bis die Dateien erreicht werden. Danach könnte das gespeichert werden.
    for(int i = 0; i < 98304; i++)
    {
        fwrite(newChunk->Array[i], sizeof(Voxel), 1, fptr);
    }

    fclose(fptr);

    free(newChunk);
}

Voxel* VoxelChunkGen(Chunk* chunk)
{
    //Remove double pointer, and get all chunks and voxels into a single array of fixed size 98304. I don't need to use malloc
    int gen_voxel_num = 0;

    for (int y = 0; y < 384; y++)
    {
        for (int z = 0; z < 16; z++)
        {
            for (int x = 0; x < 16; x++)
            {
                if (isAir() == 1)
                {
                    chunk->Array[gen_voxel_num]->blockTypeID = 0;
                }
                else
                {
                    chunk->Array[gen_voxel_num]->blockTypeID = 1;
                }
                gen_voxel_num++;
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

    if (xChunk != lastxChunk || zChunk != lastzChunk)
    {
        ChunkLoader(xChunk, zChunk);
    }

    lastxChunk = playerX / 16;
    lastzChunk = playerZ / 16;
}

void ChunkLoader(double X, double Z) //Lad alle benötigte Chunks hoch zum Arbeitsspeicher
{
    FILE* fptr;

    fptr = fopen("world.dat", "r");

    //Chunk
    Chunk** loadedChunks;
    Voxel* voxel;

    voxel = (Voxel*)malloc(sizeof(Voxel));

    loadedChunks = (Chunk*)malloc(sizeof(Chunk));
    
    //Array initializations
    loadedChunks[0] = (Chunk*)malloc(sizeof(Chunk));

    int i = 0;
    double lastChunk = -1;
    while (fread(voxel, sizeof(voxel), 1, fptr) == 1)
    {
        printf("%d\n", i/16);

        if (i/16 != lastChunk) //
        {
            calloc(loadedChunks, (i/16));
            loadedChunks[i/16] = (Chunk*)malloc(sizeof(Chunk));
            loadedChunks[i/16]->Array = (Voxel*)malloc(98304*sizeof(Voxel));
        }

        if (loadedChunks[i/16]->Array[i])

        loadedChunks[i/16]->Array[i] = (Voxel*)malloc(sizeof(Voxel)); //Memory Leak. Even though the memory gets dynamically allocated, it has a limit
        loadedChunks[i/16]->Array[i] = voxel;

        lastChunk = i/16;
        i++;
    }

    fclose(fptr);
}

//Alle Chunks die am ende von eine gesetztes Pointer stehen werden geladen.

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
