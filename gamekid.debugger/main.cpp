#include <gamekid/cpu/cpu.h>
#include <gamekid/runner.h>
#include <gamekid/utils/files.h>
#include <iostream>
#include "gamekid/utils/str.h"
#include "gamekid/cpu/operands_container.h"


std::vector<std::string> get_user_command();

using command = std::function<void(gamekid::runner& runner, const std::vector<std::string>& arguments)>;

// Commands 
void run(gamekid::runner& runner, const std::vector<std::string>& args);
void add_breakpoint(gamekid::runner& runner, const std::vector<std::string>& args);
void regs(gamekid::runner& runner, const std::vector<std::string>& args);
void next(gamekid::runner& runner, const std::vector<std::string>& args);
void list(gamekid::runner& runner, const std::vector<std::string>& args);
void debugger_exit(gamekid::runner& runner, const std::vector<std::string>& args);

bool debugger_running;

int main(const int argc, const char** argv)
{
    std::string filename(argv[1]);
    gamekid::rom::cartridge cart(gamekid::utils::files::read_file(filename));
    gamekid::runner r(std::move(cart));
    std::map<std::string, command> commands =
    {
        { "run", run},
        { "break", add_breakpoint},
        { "regs", regs},
        { "next", next},
        { "list", list},
        { "exit", debugger_exit },
    };

    debugger_running = true;

    while (debugger_running) {
        std::vector<std::string> command = get_user_command();

        auto key_value_pair = commands.find(command[0]);

        if (key_value_pair == commands.end()) {
            std::cout << "Unknown command '" << command[0] << "'" << std::endl;
        }
        else {
            key_value_pair->second(r, command);
        }
    }
}

std::vector<std::string> get_user_command() {
    std::cout << ">> ";
    std::vector<std::string> command;

    do {
        std::string user_input;
        std::cin >> user_input;
        command.push_back(user_input);
    } while (std::cin.peek() != '\n');

    return command;
}

void run(gamekid::runner& runner, const std::vector<std::string>& args) {
    runner.run_until_break();
}

void add_breakpoint(gamekid::runner& runner, const std::vector<std::string>& args) {
    if (args.size() <= 1) {
        std::cerr << "breakpoint requires an address" << std::endl;
        return;
    }

    const word address = gamekid::utils::convert::to_number<word>(args[1], 16);
    runner.add_breakpoint(address);
}

void regs(gamekid::runner& runner, const std::vector<std::string>& args) {
    for (gamekid::cpu::reg* reg : runner.cpu().regs) {
        std::cout << reg->name() << ": " << std::hex << reg->load_as_word() << std::endl;
    }
}

void next(gamekid::runner& runner, const std::vector<std::string>& args) {
    runner.next();
    std::cout << runner.list(1)[0] << std::endl;
}

void list(gamekid::runner& runner, const std::vector<std::string>& args) {
    word count;

    if (args.size() == 2) {
        count = gamekid::utils::convert::to_number<word>(args[1]);
    }
    else {
        count = 5;
    }

    std::vector<std::string> list = runner.list(count);

    for (auto& op : list) {
        std::cout << op << std::endl;
    }
}

void debugger_exit(gamekid::runner& runner, const std::vector<std::string>& args) {
    debugger_running = false;
}
