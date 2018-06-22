#include <GameKid/cpu.h>
#include <GameKid/runner.h>
#include <GameKid/utils/files.h>
#include <iostream>

int main(const int argc, const char** argv) 
{
    std::string filename(argv[1]);
    runner r(files::read_file(filename));
       
    while (true)
    {
        std::cout << ">>";
        std::vector<std::string> command;

        do
        {
            std::string user_input;
            std::cin >> user_input;
            command.push_back(user_input);
        } while (std::cin.peek() != '\n');

        if (command[0]== "run")
        {
            r.run_until_break();
        }
        else if (command[0] == "break")
        {
            const word address = std::stoi(command[1]);
            r.add_breakpoint(address);
        }
        else if (command[0] == "next")
        {
            r.next();
        }
        else if (command[0] == "list")
        {
            int count = std::stoi(command[1]);
            std::vector<std::string> list = r.list(count);

            for (auto& op : list) 
            {
                std::cout << op << std::endl;
            }
        }
    }
}