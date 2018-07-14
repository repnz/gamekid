#include <gamekid/cpu/cpu.h>
#include <gamekid/runner.h>
#include <gamekid/utils/files.h>
#include <iostream>
#include "gamekid/utils/str.h"
#include "gamekid/cpu/operands_container.h"


void welcome();
std::vector<std::string> get_user_command();

using command = std::function<void(gamekid::runner& runner, const std::vector<std::string>& arguments)>;

// Commands 
void run(gamekid::runner& runner, const std::vector<std::string>& args);
void add_breakpoint(gamekid::runner& runner, const std::vector<std::string>& args);
void regs(gamekid::runner& runner, const std::vector<std::string>& args);
void next(gamekid::runner& runner, const std::vector<std::string>& args);
void list(gamekid::runner& runner, const std::vector<std::string>& args);
void debugger_exit(gamekid::runner& runner, const std::vector<std::string>& args);
void help(gamekid::runner& runner, const std::vector<std::string>& args);
void view(gamekid::runner& runner, const std::vector<std::string>& args);

const std::map<std::string, command> commands =
{
    { "run", run },
    { "break", add_breakpoint },
    { "regs", regs },
    { "next", next },
    { "list", list },
    { "exit", debugger_exit },
    { "help", help },
    { "view", view}
};

bool debugger_running;

int main(const int argc, const char** argv) {
    welcome();

    std::string filename(argv[1]);
    gamekid::rom::cartridge cart(gamekid::utils::files::read_file(filename));
    gamekid::runner r(std::move(cart));
   
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

void welcome() {
    const char* gamekid_art =
        "                            _    _     _ \n"
        "  __ _  __ _ _ __ ___   ___| | _(_) __| |\n"
        " / _` |/ _` | '_ ` _ \\ / _ \\ |/ / |/ _` |\n"
        "| (_| | (_| | | | | | |  __/   <| | (_| |\n"
        " \\__, |\\__,_|_| |_| |_|\\___|_|\\_\\_|\\__,_|\n"
        " |___/                                  \n";

    std::cout << gamekid_art << "\n\n" << std::endl;
    std::cout << ">> Welcome To GameKid Debugger~" << std::endl;
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
    constexpr size_t regs_per_line = 4;
    size_t index = 0;

    for (gamekid::cpu::reg* reg : runner.cpu().regs) {
        std::cout << reg->name() << ": " << std::hex << reg->load_as_word() << " ";
        
        ++index;

        if (index == 4) {
            std::cout << std::endl;
            index = 0;
        }
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
        count = 10;
    }

    std::vector<std::string> list = runner.list(count);

    for (auto& op : list) {
        std::cout << op << std::endl;
    }
}

void debugger_exit(gamekid::runner& runner, const std::vector<std::string>& args) {
    debugger_running = false;
}

void help(gamekid::runner& runner, const std::vector<std::string>& args) {
    for (auto& command_pair : commands) {
        std::cout << command_pair.first << std::endl;
    }
}

void view(gamekid::runner& runner, const std::vector<std::string>& args) {
    const word address_to_view = gamekid::utils::convert::to_number<word>(args[1]);
    constexpr word default_length = 64;
    const word length_to_view = 
        args.size() >= 3 ? gamekid::utils::convert::to_number<word>(args[2]) : default_length;

    size_t index = 0;

    for (byte dump_byte : runner.dump(address_to_view, length_to_view)) {
        if (index % 16 == 0) {
            std::cout << std::endl;
            std::cout << gamekid::utils::convert::to_hex<word>(address_to_view + index) << ": ";
        }

        std::cout << gamekid::utils::convert::to_hex<byte>(dump_byte) << " ";
        ++index;
    }
    
    std::cout << std::endl;
}
