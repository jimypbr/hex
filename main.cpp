
#include <iostream>
#include <vector>
#include "cli_hex.hpp"

int main(int argc, char* argv[])
{
	CLI_Hex cli_hex;
	cli_hex.play_game();

	std::vector<int> foo(16);

	for (auto &it : foo)
		it = 6;

	std::cout << foo[5] << std::endl;


	return 0;
}
