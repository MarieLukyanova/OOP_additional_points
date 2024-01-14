#include <iostream>
#include <stdexcept>
 
 
class Matrix {
private:
	int height;
	int width;
	double** MatrixTable;
public:
	Matrix(int heightIn, int widthIn) {
		height = heightIn;
		width = widthIn;
		MatrixTable = new double* [heightIn];
		for (int i = 0; i < heightIn; i++)
		{
			MatrixTable[i] = new double[width];
		}
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				MatrixTable[i][j] = 0;
			}
		}
	}
 
	Matrix(const Matrix& other) : height(other.height), width(other.width) {
 
		MatrixTable = new double* [height];
		for (int i = 0; i < height; ++i) {
			MatrixTable[i] = new double[width];
 
 
			for (int j = 0; j < height; ++j) {
				MatrixTable[i][j] = other.MatrixTable[i][j];
			}
		}
	}
 
 
 
 
	int getHeight() const {
		return this->height;
	}
	int getWitdht() const {
		return this->width;
	}
 
	void setHeight(int newHeight) {
		this->height = newHeight;
	}
 
	void setWidth(int newWidth) {
		this->width = newWidth;
	}
 
 
	Matrix& operator=(const Matrix& other) {
		if (this != &other) {
			for (int i = 0; i < height; i++) {
				delete[]MatrixTable[i];
			}
			delete[]MatrixTable;
		}
		height = other.height;
		width = other.width;
		MatrixTable = new double* [height];
		for (int i = 0; i < height; ++i) {
			MatrixTable[i] = new double[width];
			for (int j = 0; j < width; ++j) {
				MatrixTable[i][j] = other.MatrixTable[i][j];
			}
		}
		return *this;
	}
 
	int rank() const {
		Matrix temp(*this); 
		int rank = 0;
 
		for (int i = 0; i < std::min(height, width); ++i) {
 
			int maxRowIndex = i;
			for (int j = i + 1; j < height; ++j) {
				if (std::abs(temp.MatrixTable[j][i]) > std::abs(temp.MatrixTable[maxRowIndex][i])) {
					maxRowIndex = j;
				}
			}
 
 
			if (temp.MatrixTable[maxRowIndex][i] != 0) {
				++rank;
 
				std::swap(temp.MatrixTable[i], temp.MatrixTable[maxRowIndex]);
 
				for (int j = i + 1; j < height; ++j) {
					double factor = temp.MatrixTable[j][i] / temp.MatrixTable[i][i];
					for (int k = i; k < width; ++k) {
						temp.MatrixTable[j][k] -= factor * temp.MatrixTable[i][k];
					}
				}
			}
		}
 
		return rank;
	}
 
	Matrix operator+(const Matrix& other) const {
		if (height != other.height || width != other.width)
			throw std::invalid_argument("Wrong matrix size");
		Matrix resultMatrix(this->height, this->width);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				resultMatrix.MatrixTable[i][j] = this->MatrixTable[i][j] + other.MatrixTable[i][j];
			}
		}
		return resultMatrix;
	}
 
	Matrix operator-(const Matrix& other) const {
		if (height != other.height || width != other.width)
			throw std::invalid_argument("Wrong matrix size");
		Matrix resultMatrix(this->height, this->width);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				resultMatrix.MatrixTable[i][j] = this->MatrixTable[i][j] - other.MatrixTable[i][j];
			}
		}
		return resultMatrix;
	}
 
	Matrix operator*(const Matrix& other) const {
		if (height != other.width)
			throw std::invalid_argument("Wrong matrix size");
		Matrix resultMatrix(this->height, other.width);
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < other.width; j++) {
				for (int k = 0; k < width; k++) {
					resultMatrix.MatrixTable[i][j] += this->MatrixTable[i][k] * other.MatrixTable[k][j];
				}
			}
		}
		return resultMatrix;
	}
 
 
 
	void PrintMatrix() {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (j != width - 1) std::cout << this->MatrixTable[i][j] << " ";
				else std::cout << this->MatrixTable[i][j];
			}
			std::cout << "\n";
		}
	}
 
	double& at(int i, int j) {
		if (i < 0 || i >= height || j < 0 || j >= width) {
			throw std::invalid_argument("Wrong index");
		}
		return this->MatrixTable[i][j];
	}
 
	~Matrix()
	{
		for (int i = 0; i < height; i++) {
			delete[] MatrixTable[i];
		}
		delete[] MatrixTable;
	}
};
 
 
int main() {
	Matrix test = Matrix(3, 4);
 
	test.at(0, 0) = 2;
	test.at(0, 1) = 0;
	test.at(0, 2) = 4;
	test.at(0, 3) = 0;
	test.at(1, 0) = 3;
	test.at(1, 1) = 0;
	test.at(1, 2) = 6;
	test.at(1, 3) = 0;
	test.at(2, 0) = 1;
	test.at(2, 1) = 0;
	test.at(2, 2) = -3;
	test.at(2, 3) = 0;
 
	std::cout << test.rank() << "\n";
 
 
}
