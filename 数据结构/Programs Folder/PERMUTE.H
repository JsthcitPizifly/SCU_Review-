// Randomly permute the n values of array
template<class Elem> void permute(Elem array[], int n) {
  for (int i=n; i>0; i--)
    swap(array, i-1, Random(i));
}
