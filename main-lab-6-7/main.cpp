#include <iostream>
#include "inc/matrix.hpp"

using mt::math::Mat22i;
using mt::math::Vec21i;
using mt::math::Vec31i;
using mt::math::Mat23i;
using mt::math::Mat33i;


int main()
{
	Mat22i A;
	std::cout << "Enter A" << std::endl;
	std::cin >> A;
	std::cout << A;
	std::cout << "Determinant A" << std::endl << A.Det() << std::endl;
	std::cout << "Reverse A" << std::endl << A.Reverse() << std::endl;
	std::cout << "Transposition A" << std::endl << A.Transp() << std::endl;
	//std::cout << A;

	Vec21i B;
	std::cout << "Enter B" << std::endl;
	std::cin >> B;
	//std::cout << B;

	Mat33i D;
	std::cout << "Enter D" << std::endl;
	std::cin >> D;
	std::cout << D;
	std::cout << "Determinant D" << std::endl << D.Det() << std::endl;
	std::cout << "Reverse D" << std::endl << D.Reverse() << std::endl;
	std::cout << "Transposition D" << std::endl << D.Transp() << std::endl;

	

	Vec21i C;

	std::cout << "----------------Test addition-------------------" << std::endl;
	{
		C = A + B;
		std::cout << C << std::endl;
	}
	std::cout << "------------------Test addition done!-------------------" << std::endl;


	std::cout << "----------------Test substraction-------------------" << std::endl;
	{
		C = A - B;
		std::cout << C << std::endl;
	}
	std::cout << "--------------------Test substraction done!-----------------------" << std::endl;


	std::cout << "----------------Test multiplication-------------------" << std::endl;
	{
		C = A * B;
		std::cout << C << std::endl;
	}
	std::cout << "--------------------Test multiplication done!-----------------------" << std::endl;


	std::cout << "----------------Test Determinant-------------------" << std::endl;
	{
		std::cout << C.Det() << std::endl;
	}
	std::cout << "--------------------Test Determinant done!-----------------------" << std::endl;


	std::cout << "----------------Test Reverse-------------------" << std::endl;
	{
		std::cout << C.Reverse() << std::endl;
	}
	std::cout << "--------------------Test Reverse done!-----------------------" << std::endl;


	std::cout << "----------------Test Transposition-------------------" << std::endl;
	{
		std::cout << C.Transp() << std::endl;
	}
	std::cout << "--------------------Test Transpositionn done!-----------------------" << std::endl;


	return 0;
}
