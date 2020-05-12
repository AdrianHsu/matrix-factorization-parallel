#ifndef MPI_BLOCKALLOCATION_H
#define MPI_BLOCKALLOCATION_H

#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_HIGH((id) + 1, p, n) - 1)
#define BLOCK_SIZE(id, p, n) (BLOCK_HIGH(id, p, n) - BLOCK_LOW(id, p, n) + 1)
//#define BLOCK_OWNER(index, p, n) (((p) * ((index) + 1) - 1) / (n))

#endif //MPI_BLOCKALLOCATION_H