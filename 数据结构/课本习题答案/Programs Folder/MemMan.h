// Memory Manager abstract class
class MemManager {
public:
  // Store a record and return the handle
  virtual MemHandle insert(void* space, int length) =0;
  // Release the space associated with a record
  virtual void release(MemHandle h) =0;
  // Get back a copy of a stored record
  virtual int get(void* space, MemHandle h) =0;
};
