#ifndef FIELDARRAY_H_
#define FIELDARRAY_H_

#include <memory> //< unique_ptr
#include <cassert>

template<typename T>
class FieldArray {
public:
    FieldArray(int numCellsX, int numCellsY, T initialValue = 0) :
        mNumCellsX(numCellsX),
        mNumCellsY(numCellsY),
        mFieldData(new T[mNumCellsX*mNumCellsY])
    {
        setToValue(initialValue);
    }

    int numCellsX() const { return mNumCellsX; }
    int numCellsY() const { return mNumCellsY; }

    int size() const { return numCellsX()*numCellsY(); }

    T& operator() (int x, int y) {
        assert(x >= 0); assert(x < mNumCellsX);
        assert(y >= 0); assert(y < mNumCellsY);
        return mFieldData[y*mNumCellsX + x];
    }

    T const& operator() (int x, int y) const {
        assert(x >= 0); assert(x < mNumCellsX);
        assert(y >= 0); assert(y < mNumCellsY);
        return mFieldData[y*mNumCellsX + x];
    }

    void setToValue(T value) {
        for (int i = 0; i < size(); ++i) mFieldData[i] = value;
    }

    T const * getRawPtr() const { return mFieldData.get(); }
    T* getRawPtr() { return mFieldData.get(); }

    void print() const {
        const int maxX = numCellsX();
        const int maxY = numCellsY();

        for (int curY = 0; curY < maxY; ++curY) {
            for (int curX = 0; curX < maxX; ++curX) {
                std::cout << std::setw(5) << std::fixed << std::setprecision(3) << operator()(curX, curY) << " ";
            }
            std::cout << "\n";
        }
        std::cout << std::endl;
    }

    friend void swapData(FieldArray<T>& x, FieldArray<T>& y) {
        assert(x.numCellsX() == y.numCellsX());
        assert(x.numCellsY() == y.numCellsY());
        x.mFieldData.swap(y.mFieldData);
    }


private:
    const int mNumCellsX;
    const int mNumCellsY;
    std::unique_ptr<T[]> mFieldData;
};



#endif // FIELDARRAY_H_
