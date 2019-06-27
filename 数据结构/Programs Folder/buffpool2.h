class BufferPool {
public:
  // Return pointer to the requested block
  virtual void* getblock(int block) = 0;
  // Set the dirty bit for buffer buff
  virtual void dirtyblock(int block) = 0;
  // Tell the size of a buffer
  virtual int blocksize() = 0;
};
