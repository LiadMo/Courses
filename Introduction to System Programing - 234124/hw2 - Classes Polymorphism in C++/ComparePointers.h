#ifndef COMPAREPOINTERS
#define COMPAREPOINTERS

namespace mtm {
    class ComparePointers {
    public:
        template<class T>
        bool operator()(T* t1, T* t2) {
            return *t1 < *t2;
        }
    };
}
#endif //COMPAREPOINTERS
