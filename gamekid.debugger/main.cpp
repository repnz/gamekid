#include <gamekid/cpu/cpu.h>
#include <gamekid/runner.h>
#include <gamekid/utils/files.h>
#include <iostream>
#include "gamekid/utils/str.h"
#include "gamekid/cpu/operands_container.h"
#include "window.h"
#include <thread>
#undef main

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
void del(gamekid::runner& runner, const std::vector<std::string>& args);
void breakpoints(gamekid::runner& runner, const std::vector<std::string>& args);

void sdl_handler();

const std::map<std::string, command> commands =
{
    { "run", run },
    { "break", add_breakpoint },
    { "regs", regs },
    { "next", next },
    { "list", list },
    { "exit", debugger_exit },
    { "help", help },
    { "view", view},
    { "del", del},
    { "breakpoints", breakpoints}
};

bool debugger_running;

int main(const int argc, const char* argv[]) {
    debugger_running = true;
    std::thread sdl_handler_thread(sdl_handler);

    welcome();

    std::string filename(argv[1]);
    gamekid::rom::cartridge cart(gamekid::utils::files::read_file(filename));
    gamekid::runner r(std::move(cart));


    while (debugger_running) {
        std::vector<std::string> command = get_user_command();

        auto key_value_pair = commands.find(command[0]);

        if (key_value_pair == commands.end()) {
            std::cout << "Unknown command '" << command[0] << "'" << std::endl;
        }
        else {
            try {
                key_value_pair->second(r, command);
            } catch (const std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }
    }

    sdl_handler_thread.join();
    return 0;
}

void sdl_handler() {
    gamekid::debugger::window _window;
    _window.put_pixel({ 0, 0 }, gamekid::debugger::colors::A);

    while (debugger_running) {
        _window.poll_events();
        SDL_Delay(500);
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
    std::cout << "set breakpoint at address 0x" << gamekid::utils::convert::to_hex<word>(address) << std::endl;
}

void regs(gamekid::runner& runner, const std::vector<std::string>& args) {
    constexpr size_t regs_per_line = 4;
    const std::vector<gamekid::cpu::reg*>& regs = runner.cpu().regs;

    for (size_t i = 0; i < regs.size(); ++i) {
        std::cout << regs[i]->name() << ": " << std::hex << regs[i]->load_as_word() << " ";

        if ((i + 1) % regs_per_line == 0) {
            std::cout << std::endl;
        }
    }

    std::cout << std::endl;
}

void next(gamekid::runner& runner, const std::vector<std::string>& args) {
    runner.next();
    std::cout << runner.list(runner.cpu().PC.load(), 1)[0] << std::endl;
}

void list(gamekid::runner& runner, const std::vector<std::string>& args) {
    word count;
    word address = runner.cpu().PC.load();

    
    if (args.size() == 2) {
        count = gamekid::utils::convert::to_number<word>(args[1]);
    }
    else if (args.size() == 3) {
        address = gamekid::utils::convert::to_number<word>(args[1], 16);
        count = gamekid::utils::convert::to_number<word>(args[2]);
    }
    else {
        count = 10;
    }

    std::vector<std::string> list = runner.list(address, count);

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
    if (args.size() <= 1) {
        std::cerr << "Missing <address_to_view> argument." << std::endl;
        std::cout << "view <address_to_view> [length_to_view]" << std::endl;
        return;
    }

    const word address_to_view = gamekid::utils::convert::to_number<word>(args[1], 16);

    const word length_to_view =
        args.size() >= 3 ? gamekid::utils::convert::to_number<word>(args[2]) : 64;

    std::vector<byte> mem_view = runner.dump(address_to_view, length_to_view);

    for (word i = 0; i < mem_view.size(); ++i) {
        // if it is a start of a new line
        if (i % 16 == 0) {
            if (i != 0) {
                // print a new line if it is not the first line
                std::cout << std::endl;
            }
            // print the address
            std::cout << gamekid::utils::convert::to_hex<word>(address_to_view + i) << ": ";
        }

        // print the memory byte
        std::cout << gamekid::utils::convert::to_hex<byte>(mem_view[i]) << " ";
    }

    std::cout << std::endl;
}

void del(gamekid::runner& runner, const std::vector<std::string>& args) {
    if (args.size() <= 1) {
        std::cerr << "Missing breakpoint to delete" << std::endl;
        std::cout << "del <address_to_delete>" << std::endl;
        return;
    }

    const word breakpoint_address = gamekid::utils::convert::to_number<word>(args[1], 16);

    try {
        runner.delete_breakpoint(breakpoint_address);
    }
    catch (const std::exception& e) {
        std::cerr << "Cannot delete breakpoint: " << e.what() << std::endl;
        return;
    }

    std::cout << "deleted breakpoint at 0x" <<
        gamekid::utils::convert::to_hex<word>(breakpoint_address) << std::endl;
}

void breakpoints(gamekid::runner& runner, const std::vector<std::string>& args) {
    const std::set<word>& bps = runner.breakpoints();

    if (bps.empty()) {
        std::cout << "No breakpoints set" << std::endl;
        return;
    }

    for (word bp : bps) {
        std::cout << "Breakpoint at address 0x" << gamekid::utils::convert::to_hex<word>(bp) << std::endl;
    }
}
