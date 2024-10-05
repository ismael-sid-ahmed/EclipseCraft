#include "voxel.h"

#ifndef CHUNK_ARR
Chunk list[(CHUNK_RENDER_DISTANCE*2)*(CHUNK_RENDER_DISTANCE*2)];
int chunks_m = 0;
#endif