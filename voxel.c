#include "voxel.h"

#include "stdio.h"
#include "stdlib.h"

#include "glad.h"
#include "glfw3.h"

#include "cglm.h"

/*Design:
    Chunks divided into sub chunks, this will contain blocks.

    The chunks shall be stored into a file (format yet to be determined) for each region (16 chunk radius)
    The structure would be a binary tree.

*/

typedef struct Chunk
{
    double X, Z;
} Chunk;


void ChunkGen(int X, int Z, unsigned int shaderProgram)
{
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
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