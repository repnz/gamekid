#include <GameKid/cpu/opcode_encoder.h>
#include <sstream>
#include <GameKid/cpu/instruction.h>

std::vector<std::string> split(const std::string &s, char delim);

opcode_encoder::opcode_encoder(instruction_set& set) : _set(set)
{
}

std::vector<byte> opcode_encoder::encode(const std::string& instruction)
{
	std::vector<std::string> splitted = split(instruction, ' ');
	std::unique_ptr<::instruction>* ins = _set.get_instruction(splitted[0]);

	if (ins == nullptr)
	{
		return {};
	}

	return (*ins)->parse(splitted);
}

template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}