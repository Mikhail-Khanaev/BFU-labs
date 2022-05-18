#pragma once
#include <iostream>

//#define DEBUG


namespace mt::math
{
	//#define DEBUG

	template<typename T, int N, int M>
	class Matrix
	{
	public:

		int getN() const { return m_n; }
		int getM() const { return m_m; }
		T get(int i, int j) const { return m_mat[i][j]; }
		void set(int i, int j, T data) { m_mat[i][j] = data; }

		// Constructor
		Matrix()
		{
#ifdef DEBUG
			std::cout << "Constructor" << std::endl;
#endif
			m_n = N;
			m_m = M;
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = 0;
		}

		// Copy constructor
		Matrix(const Matrix<T, N, M>& matё)
		{
#ifdef DEBUG
			std::cout << "Copy constructor" << std::endl;
#endif

			m_n = mat.getN();
			m_m = mat.getM();

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.get(i, j);
		}
		 
		// Assignment
		template<typename T, int N, int M>
		Matrix<T, N, M>& operator=(const Matrix<T, N, M>& mat)
		{
			if ((m_n == mat.getN()) && (m_m == mat.getM()))
			{
#ifdef DEBUG
				std::cout << "Operator =" << std::endl;
#endif
					m_n = mat.getN();
					m_m = mat.getM();

					for (int i = 0; i < m_n; i++)
						for (int j = 0; j < m_m; j++)
							m_mat[i][j] = mat.get(i, j);
					return *this;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		// Addition operator
		template<typename T, int N, int M>
		Matrix<T, N, M> operator+(const Matrix<T, N, M>& mat)
		{
			if ((m_n == mat.getN()) && (m_m == mat.getM()))
			{
#ifdef DEBUG
				std::cout << "operator+" << std::endl;
#endif
					Matrix<T, N, M> tmp;
					for (int i = 0; i < m_n; i++)
						for (int j = 0; j < m_m; j++)
							tmp.set(i, j, (m_mat[i][j] + mat.get(i, j)));
					return tmp;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		// Subtraction operator
		template<typename T, int N, int M>
		Matrix<T, N, M> operator-(const Matrix<T, N, M>& mat)
		{
			if ((m_n == mat.getN()) && (m_m == mat.getM()))
			{
#ifdef DEBUG
				std::cout << "operator-" << std::endl;
#endif
					Matrix<T, N, M> tmp;
					for (int i = 0; i < m_n; i++)
						for (int j = 0; j < m_m; j++)
							tmp.set(i, j, (m_mat[i][j] - mat.get(i, j)));
					return tmp;
			}
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		// Multiplication operator
		template<typename T, int N, int M>
		Matrix<T, N, M> operator*(const Matrix<T, N, M>& mat)
		{
			if (m_m == mat.getN())
			{
#ifdef DEBUG
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
			else
				std::cout << "Incorrect matrix!" << std::endl;
		}

		// Determinant
		T Det()
		{
			if (m_n != m_m)
			{
				std::cout << "Operation not available!" << std::endl;
			}

			else if (m_n == m_m)
			{
				if (m_n == 2)
				{
					T d = 0;
					d = (m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0]);
					return d;
				}
				else if (m_n == 3)
				{
					T d = 0;
					d = (m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[1][0] * m_mat[2][1] * m_mat[0][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0] - m_mat[0][2] * m_mat[1][1] * m_mat[2][0] - m_mat[1][2] * m_mat[2][1] * m_mat[0][0] - m_mat[0][1] * m_mat[1][0] * m_mat[2][2]);
					return d;
				}
			}
		}

		// Reverse
		Matrix<double, N, M> Reverse()
		{
			T det = Det();

			if (det == 0)
			{
				std::cout << "Inverse matrix not exist!" << std::endl;
			}
			else if (m_n == m_m)
			{
				Matrix<double, N, M> tmp;

				if (m_n == 2)
				{
					tmp.set(0, 0, m_mat[1][1] / det);
					tmp.set(0, 1, -m_mat[0][1] / det);
					tmp.set(1, 0, -m_mat[1][0] / det);
					tmp.set(1, 1, m_mat[1][1] / det);
					return tmp;
				}
				else if (m_n == 3)
				{
					tmp.set(0, 0, ((m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2]) / det));
					tmp.set(1, 0, (-(m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2]) / det));
					tmp.set(2, 0, ((m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1]) / det));
					tmp.set(0, 1, (-(m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2]) / det));
					tmp.set(1, 1, ((m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2]) / det));
					tmp.set(2, 1, (-(m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1]) / det));
					tmp.set(0, 2, ((m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2]) / det));
					tmp.set(1, 2, (-(m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2]) / det));
					tmp.set(2, 2, ((m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1]) / det));
					return tmp;
				}
			}
		}

		// Transposition
		Matrix<T, M, N> Transp()
		{
			Matrix<T, M, N> tmp;
			for (int i = 0; i < M; i++)
				for (int j = 0; j < N; j++)
				{
					tmp.set(i, j, m_mat[j][i]);
				}
			return tmp;
		}

		// Destructor
		~Matrix()
		{
#ifdef DEBUG
			std::cout << "Destructor" << std::endl;
#endif
		}

		
		template<typename T, int N, int M>
		friend std::istream& operator>>(std::istream& os, Matrix<T, N, M>& mat);
		template<typename T, int N, int M>
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat);

		
	private:
		int m_n, m_m;		
		T m_mat[N][M];
	};

	template<typename T, int N, int M>
	std::istream& operator>>(std::istream& in, Matrix<T, N, M>& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;

	}

	template<typename T, int N, int M>
	std::ostream& operator<<(std::ostream& out, const Matrix<T, N, M>& mat)
	{
		out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++) {
			for (int j = 0; j < mat.m_m; j++)
				out << mat.m_mat[i][j] << " ";
			out << std::endl;
		}
		return out;
	}

	using Vec21i = Matrix<int, 2, 1>;
	using Vec31i = Matrix<int, 3, 1>;
	using Mat22i = Matrix<int, 2, 2>;
	using Mat23i = Matrix<int, 2, 3>;
	using Vec12i = Matrix<int, 1, 2>; 
	using Mat33i = Matrix<int, 3, 3>;

}