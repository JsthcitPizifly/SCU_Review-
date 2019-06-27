class BufferPool {
public:
  // Insert from space sz bytes begining at position pos
  //   of the buffered store
  virtual void insert(void* space, int sz, int pos) = 0;
  // Put into space sz bytes beginning at position pos
  //   of the buffered store
  virtual void getbytes(void* space, int sz, int pos) = 0;
};
