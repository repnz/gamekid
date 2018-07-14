#include <gamekid/cpu/cpu.h>
#include <gamekid/runner.h>
#include <gamekid/utils/files.h>
#include <iostream>
#include "gamekid/utils/str.h"

std::vector<std::string> get_command();

int main(const int argc, const char** argv) 
{
    std::string filename(argv[1]);
    gamekid::rom::cartridge cart(gamekid::utils::files::read_file(filename));
    gamekid::runner r(std::move(cart));
    
    while (true){
        std::vector<std::string> command = get_command();

        if (command[0]== "run"){
            r.run_until_break();
        }
        else if (command[0] == "break"){
            const word address = std::stoi(command[1]);
            r.add_breakpoint(address);
        }
        else if (command[0] == "regs") {
            
            for (gamekid::cpu::reg* reg : r.cpu().regs) {
                std::cout << reg->name() << ": " << std::hex << reg->load_as_word() << std::endl;
            }

        }
        else if (command[0] == "next"){
            r.next();
            std::cout << r.list(1)[0] << std::endl;
        }
        else if (command[0] == "list"){
            int count = std::stoi(command[1]);
            std::vector<std::string> list = r.list(count);

            for (auto& op : list) {
                std::cout << op << std::endl;
            }
        } else {
            std::cout << "Unknown command '" << gamekid::utils::str::join(command) << "'" << std::endl;
        }

        std::cout << std::endl;
    }
}

std::vector<std::string> get_command() {
    std::cout << ">> ";
    std::vector<std::string> command;

    do {
        std::string user_input;
        std::cin >> user_input;
        command.push_back(user_input);
    } while (std::cin.peek() != '\n');

    return command;
}