#ifndef MYTYPES_H
#define MYTYPES_H
typedef struct chunk
{
    short voxel[98304];
    int X, Z;
}Chunk;
#endif

#ifndef CHUNK_RENDER_DISTANCE
#define CHUNK_RENDER_DISTANCE 4
#endif

#ifndef MAX_CHUNKS
#define MAX_CHUNKS 32
#endif

#ifndef SPAWN_CHUNK_RADIUS
#define SPAWN_CHUNK_RADIUS 16
#endif

#ifndef INITIAL_CHUNK_ARRAY_SIZE
#define INITIAL_CHUNK_ARRAY_SIZE 2
#endif