template <class Elem>
class FreqPair { // An element/frequency pair
private:
  Elem it;       // An element of some sort
  int freq;      // Frequency for the element
public:
  FreqPair(const Elem& e, int f) // Constructor
    { it = e; freq = f; }
  ~FreqPair() { }                // Destructor
  int weight() { return freq; }  // Return the weight
  Elem& val() { return it; }     // Return the element
};
