#pragma once
#include <cassert>
#include <iostream>

using namespace std;
namespace math
{
	//#define MY_DEBUG

	template<typename T, int N, int M>
	struct MasWrapper
	{
		T mas[N][M];
	};

	template<typename T, int N, int M>
	class Matrix
	{
	public:
		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		Matrix()
		{
#ifdef MY_DEBUG
			cout << "Constructor" << endl;
#endif 
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
			{
				for (int j = 0; j < m_m; j++)
				{
					m_mat[i][j] = 0;
				}
			}
		}

		Matrix(const T mas[N][M])
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas[i][j];
		}


		Matrix(const MasWrapper<T, N, M>& mas)
		{
#ifdef MY_DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mas.mas[i][j];
		}


		template<typename T, int N, int M>
		Matrix(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "Copy constructor" << endl;
#endif 
			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
			{
				for (int j = 0; j < m_m; j++)
				{
					m_mat[i][j] = mat.get(i, j);
				}
			}
		}


		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator = " << endl;
#endif 
			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
			{
				for (int j = 0; j < m_m; j++)
				{
					m_mat[i][j] = mat.get(i, j);
				}
			}
			return *this;
		}

		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator + " << endl;
#endif 
			Matrix<T, N, M> tmp;
			if ((N != mat.getN()) && (M != mat.getM()))
			{
				cout << "Error! " << endl;
			}

			for (int i = 0; i < m_n; i++)
			{
				for (int j = 0; j < m_m; j++)
				{
					tmp.set(i, j, (m_mat[i][j] + mat.get(i, j)));
				}
			}
			return tmp;
		}

		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			cout << "operator - " << endl;
#endif 
			Matrix<T, N, M> tmp;
			if ((N != mat.getN()) && (M != mat.getM()))
			{
				cout << "Error! " << endl;
			}
			for (int i = 0; i < m_n; i++)
			{
				for (int j = 0; j < m_m; j++)
				{
					tmp.set(i, j, (m_mat[i][j] - mat.get(i, j)));
				}
			}
			return tmp;
		}

		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
#ifdef MY_DEBUG
			std::cout << "operator*" << std::endl;
#endif
			Matrix<T, N, M> tmp;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < mat.getM(); j++)
				{
					T sum = 0;
					for (int k = 0; k < m_m; k++)
						sum += m_mat[i][k] * mat.get(k, j);
					tmp.set(i, j, sum);
				}

			return tmp;
		}



		~Matrix()
		{
#ifdef MY_DEBUG
			cout << "Destructor " << endl;
#endif 
		}

		T DET()
		{
#ifdef MY_DEBUG
			std::cout << "Det" << std::endl;
#endif
			if ((m_n != m_m) || ((m_n != 2) && (m_m != 3)))
				cout << "This format is not supported. " << endl;
			if (m_n == 2)
			{
				return m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
			}
			else if (m_n == 3)
			{
				return m_mat[0][0] * m_mat[1][1] * m_mat[2][2]
					+ m_mat[0][1] * m_mat[1][2] * m_mat[2][0]
					+ m_mat[1][0] * m_mat[2][1] * m_mat[0][2]
					- m_mat[0][2] * m_mat[1][1] * m_mat[2][0]
					- m_mat[0][0] * m_mat[1][2] * m_mat[2][1]
					- m_mat[0][1] * m_mat[1][0] * m_mat[2][2];
			}
		}


		Matrix<T, N, M> reverse()
		{
#ifdef MY_DEBUG
			std::cout << "reverse" << std::endl;
#endif
			Matrix<double, N, M> tmp;
			if ((N != M) || ((N != 2) && (N != 3)))
			{
				cout << "This format is not supported. " << endl;
				return tmp;
			}

			double Det = DET();
			if (Det == 0)
			{
				cout << "DET = 0. Inverse Matrix does not exist. " << endl;
				return tmp;
			}
			if ((m_n == m_m && m_n == 2) || (m_n == m_m && m_n == 3))
			{
				if (N == 2)
				{
					tmp.set(0, 0, m_mat[1][1] / Det);
					tmp.set(0, 1, -m_mat[0][1] / Det);
					tmp.set(1, 0, -m_mat[1][0] / Det);
					tmp.set(1, 1, m_mat[1][1] / Det);
					return tmp;
				}
				else if (N == 3)
				{
					tmp.set(0, 0, ((m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / Det));
					tmp.set(1, 0, (-(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / Det));
					tmp.set(2, 0, ((m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / Det));
					tmp.set(0, 1, (-(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / Det));
					tmp.set(1, 1, ((m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / Det));
					tmp.set(2, 1, (-(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / Det));
					tmp.set(0, 2, ((m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / Det));
					tmp.set(1, 2, (-(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / Det));
					tmp.set(2, 2, ((m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / Det));
					return tmp;
				}

			}
		}


		Matrix<T, N, M> Matrix::transposition()
		{
#ifdef MY_DEBUG
			std::cout << "transposition" << std::endl;
#endif
			Matrix<T, M, N> tmp;

			for (int i = 0; i < M; i++)
			{
				for (int j = 0; j < N; j++)
				{
					tmp.set(i, j, m_mat[j][i]);
				}
			}
			return tmp;
		}

		template<typename T, int N, int M>
		friend istream& operator>>(istream& in, Matrix<T, N, M>& mat);

		template<typename T, int N, int M>
		friend ostream& operator<<(ostream& out, const Matrix<T, N, M>& mat);
	private:
		int m_n, m_m;
		T m_mat[N][M];
	};

	template<typename T, int N, int M>
	istream& operator>>(istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
		{
			for (int j = 0; j < mat.m_m; j++)
			{
				in >> mat.m_mat[i][j];
			}
		}
		return in;
	}

	template<typename T, int N, int M>
	ostream& operator<<(ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++)
		{
			for (int j = 0; j < mat.m_m; j++)
			{
				out << mat.m_mat[i][j] << " ";
			}
			out << std::endl;
		}
		return out;
	}

	using Vec2i = Matrix<int, 2, 1>;
	using Vec2d = Matrix<double, 2, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat22d = Matrix<double, 2, 2>;
	using Mat33i = Matrix<int, 3, 3>;
	using Mat33d = Matrix<double, 3, 3>;
}