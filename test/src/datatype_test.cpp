#include <iostream>
#include <immoral/game.hpp>

int main(int argc, char ** argv)
{
	using std::cout;
	using std::endl;
	
	cout << "Immoral Engine: Datatype Test" << endl;
	cout << "sizeof(int8)  = " << sizeof(int8) << endl;
	cout << "sizeof(int16) = " << sizeof(int16) << endl;
	cout << "sizeof(int32) = " << sizeof(int32) << endl;
	cout << "sizeof(int64) = " << sizeof(int64) << endl;
	cout << "sizeof(u8)    = " << sizeof(u8) << endl;
	cout << "sizeof(u16)   = " << sizeof(u16) << endl;
	cout << "sizeof(u32)   = " << sizeof(u32) << endl;
	cout << "sizeof(u64)   = " << sizeof(u64) << endl;
	cout << "sizeof(f32)   = " << sizeof(f32) << endl;
	cout << "sizeof(f64)   = " << sizeof(f64) << endl;
	
	return 0;
}
