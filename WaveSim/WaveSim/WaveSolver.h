#ifndef WAVESOLVER_H_
#define WAVESOLVER_H_

#include "FieldArray.h"

#include <iostream>
#include <iomanip>

template<typename T>
class WaveSolver {
public:

    WaveSolver(int numCellsX, int numCellsY) :
		mCenterX(numCellsX / 44),
		mCenterY(numCellsY / 4),
        mFieldPrev(numCellsX, numCellsY, 0),
        mField(numCellsX, numCellsY, 0),
        mFieldNext(numCellsX, numCellsY, 0),
        mVelocity(numCellsX, numCellsY, defaultVelocity)
    {
        // Add a single (source) peak in the middle of the current field
        mField(mCenterX, mCenterY) = 1.0;
    }

	WaveSolver(int numCellsX, int numCellsY, int centerX, int centerY) :
		mCenterX(centerX),
		mCenterY(centerY),
        mFieldPrev(numCellsX, numCellsY, 0),
        mField(numCellsX, numCellsY, 0),
        mFieldNext(numCellsX, numCellsY, 0),
        mVelocity(numCellsX, numCellsY, defaultVelocity)
    {
        // Add a single (source) peak in the middle of the current field
        mField(mCenterX, mCenterY) = 1.0;
    }

    FieldArray<T>& getField() { return mField; }
    FieldArray<T> const& getField() const { return mField; }

    FieldArray<T>& getVelocity() { return mVelocity; }
    FieldArray<T> const& getVelocity() const { return mVelocity; }

    void addRectangle(int minX, int minY, int maxX, int maxY, T value = 0.5) {
        assert(minX <= maxX);
        assert(minY <= maxY);

        for (int curX = minX; curX <= maxX; ++curX) {
            for (int curY = minY; curY <= maxY; ++curY) {
                mVelocity(curX, curY) = value;
            }
        }
    }

    void addCircle(int centerX, int centerY, int radius, T value = 0.5) {
        assert(radius >= 0);

        /// This is a very primitive implementation
        const int minX = centerX - radius;
        const int maxX = centerX + radius;
        const int minY = centerY - radius;
        const int maxY = centerY + radius;
		const int radius2 = radius * radius;

        for (int curX = minX; curX <= maxX; ++curX) {
            for (int curY = minY; curY <= maxY; ++curY) {
                const double r2 = (curX - centerX)*(curX - centerX) + (curY - centerY)*(curY - centerY);
                if (r2 <= radius2) {
                    mVelocity(curX, curY) = value;
                }
            }
        }
    }

    void resetMaterials() 
	{
		getVelocity().setToValue(defaultVelocity); 
	}

    void resetField() 
	{
		mFieldPrev.setToValue(0);
		mField.setToValue(0); 
		mFieldNext.setToValue(0);
        mField(mCenterX, mCenterY) = 1.0;
	}

    void doTimestep() {
        const T dx2 = 1;
        const T dy2 = 1;
        const T dt2 =1./2.;

        const int minX = 1;
        const int minY = 1;
        const int maxX = mField.numCellsX() - 1;
        const int maxY = mField.numCellsY() - 1;

        for (int curX = minX; curX < maxX; ++curX) {
            for (int curY = minY; curY < maxY; ++curY) {
                const auto xDerivative = (mField(curX + 1, curY) - 2 * mField(curX, curY) + mField(curX - 1, curY)) / dx2;
                const auto yDerivative = (mField(curX, curY + 1) - 2 * mField(curX, curY) + mField(curX, curY - 1)) / dy2;
                const auto curVelocity2 = mVelocity(curX, curY)*mVelocity(curX, curY);
                mFieldNext(curX, curY) = 2 * mField(curX, curY) - mFieldPrev(curX, curY) + dt2*curVelocity2*(xDerivative + yDerivative);
            }
        }

        /// To avoid re-allocation, we simply rotate the pointer around
        swapData(mFieldPrev, mField);
        swapData(mField, mFieldNext);
    }

private:
	int mCenterX;
	int mCenterY;

    const T defaultVelocity = 1.0;

    FieldArray<T> mFieldPrev;       ///< Field at previous time-step
    FieldArray<T> mField;           ///< Field at current time-step
    FieldArray<T> mFieldNext;       ///< Field at next time-step

    FieldArray<T> mVelocity;
};

#endif // WAVESOLVER_H_
