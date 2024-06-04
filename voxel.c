#include "voxel.h"

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "glad.h"
#include "glfw3.h"

#include "cglm.h"

#define CHUNK_RENDER_DISTANCE 4

/*Design:
    Chunks divided into sub chunks, this will contain blocks.

    The chunks shall be stored into a file (format yet to be determined) for each region (16 chunk radius)
    The structure would be a binary tree.

*/

void InitialChunkGenCaller()
{
    FILE* fptr;

    fptr = fopen("world.dat", "r");

    fprintf(fptr, "");
    fclose(fptr);
        for(int i = 0; i < CHUNK_RENDER_DISTANCE; i++)
        {
            for (int j = 0; j < CHUNK_RENDER_DISTANCE; j++)
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
    FILE* fptr;
    fptr = fopen("world.dat", "a");

    fprintf(fptr, "{Chunk:coord(%dX/%dZ)}\n", X, Z);
    fclose(fptr);
}

void ChunkRenderCaller()
{
    FILE* fptr;
    fptr = fopen("World.dat", "r");

    char* buffer = "";

    while (fgets(buffer, 512, fptr) != NULL)
    {
        char** chunkCoordPtr = strstr(buffer, "coord:");
        /*Lösung: Mit die Addresse der koordinaten kann man einfach zu diesem Addresse direkt gehen. Da macht der Programm weiter
        und liest von "(" bis ")". Than speichert die Nummern, die da gefunden sind.*/
    }

    fclose(fptr);
}

void ChunkRender(int X, int Z, unsigned int shaderProgram)
{
    for (int i = 0; i < 16; i++) //Height
    {
        for (int j = 0; j < 16; j++) //X
        {
            for (int k = 0; k < 16; k++) //Z
            {
                mat4 model;
                glm_mat4_identity(model);
                glm_translate(model, (vec3){j+X, -i, k+Z});
                
                int modelLoc = glGetUniformLocation(shaderProgram, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
    }
}