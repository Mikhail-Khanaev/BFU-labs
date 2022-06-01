#include <iostream>
#include <BMP.hpp>
using namespace std;
using namespace image;
int main()
{
    // ������������ ������ �9
   try
    {
        BMP test;
        test.Read("in.bmp");
        test.Rotate(45);
        test.Fix();
        test.Save("test.bmp");

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }


    // ������������ ������ �10
    try
    {
        BMP OutBMP;
        OutBMP.Read("in.bmp");
        OutBMP.Filter({ 10, 20, 50 });
        OutBMP.Save("out.bmp");
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;

    return 0;
}