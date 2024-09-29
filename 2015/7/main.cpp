#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <regex>
#include <cassert>
#include <fstream> 

enum InstructionCommand
{
    INSERT,
    NOT,
    AND,
    OR,
    LSHIFT,
    RSHIFT,
};

bool isDigit(const std::string& str)
{
    return std::isdigit(str[0]);
}

struct Instruction
{
    Instruction() = default;

    Instruction(std::string const &s) noexcept 
    {
        int cnt = std::count(s.begin(), s.end(), ' ');

        switch (cnt)
        {
            case 2: //number to wire
            {    
                // \\w+ ==> [a-zA-Z0-9_]
                const char *re = "(\\w+)\\s->\\s(\\w+)";
                std::smatch m;

                if (!std::regex_search(s, m, std::regex(re))) 
                {
                    std::cerr << "Unable to interpret:" << s << "\n";
                    assert(false);
                }

                input[0] = m.str(1);
                output = m.str(2);
                command = InstructionCommand::INSERT;

                break;
            }
            
            case 3: //NOT command
            {
                const char *re = "(NOT)\\s(\\w+)\\s->\\s(\\w+)";
                std::smatch m;

                if (!std::regex_search(s, m, std::regex(re))) {
                    std::cerr << "Unable to interpret:" << s << "\n";
                    assert(false);
                }

                if(m.str(1) != std::string("NOT"))
                {
                    std::cerr << "Not a NOT command:" << s << "\n";
                    assert(false);
                }

                input[0] = m.str(2);
                output = m.str(3);
                command = InstructionCommand::NOT;

                break;
            }
            
            case 4: //AND|OR|LSHIFT|RSHIFT commands
            {
                const char *re = "(\\w+)\\s(AND|OR|LSHIFT|RSHIFT)\\s(\\w+)\\s->\\s(\\w+)";
                std::smatch m;

                if (!std::regex_search(s, m, std::regex(re))) {
                    std::cerr << "Unable to interpret:" << s << "\n";
                    assert(false);
                }

                if (m.str(2) == std::string("AND")) 
                    command = InstructionCommand::AND;
                else if (m.str(2) == std::string("OR")) 
                    command = InstructionCommand::OR;
                else if (m.str(2) == std::string("LSHIFT")) 
                    command = InstructionCommand::LSHIFT;
                else if (m.str(2) == std::string("RSHIFT")) 
                    command = InstructionCommand::RSHIFT;
                else 
                {
                    std::cerr << "Unable to interpret:" << s << "\n";
                    assert(false);
                }

                input[0] = m.str(1);
                input[1] = m.str(3);
                output = m.str(4);
                
                break;
            }
            
            default: 
                break;
        }
        Instruction::circuit[output] = *(this);
    }

    static unsigned short execute(std::string const &out)
    {
        if(Instruction::circuit.find(out) == Instruction::circuit.end())
            return 0;

        Instruction* execIns = &Instruction::circuit[out];

        if(execIns->isCashed)
        {
            std::cout << "Returning Cashed value for [" << execIns->output << "] value [ " << execIns->cashedOutput << "[" << std::endl;
            return execIns->cashedOutput;
        }

        std::cout << "===================EXECUTING OUTPUT=================" << std::endl;
        std::cout << "Output: " << execIns->output << std::endl;
        std::cout << "Command: " << execIns->command << std::endl;
        std::cout << "Input1: " << execIns->input[0] << std::endl;
        std::cout << "Input2: " << execIns->input[1] << std::endl;

        switch(execIns->command)
        {
            case InstructionCommand::INSERT:
            {
                unsigned short value = isDigit(execIns->input[0]) ? static_cast< unsigned short >(std::stoul(execIns->input[0], nullptr, 10)) : Instruction::execute(execIns->input[0]);

                std::cout << "INSERT WITH VALUE: " << value << std::endl;

                execIns->cashedOutput = value;
                execIns->isCashed = true;

                return value;
            }
            break;
            case InstructionCommand::NOT:
            {
                unsigned short value = isDigit(execIns->input[0]) ? static_cast< unsigned short >(std::stoul(execIns->input[0], nullptr, 10)) : Instruction::execute(execIns->input[0]);

                std::cout << "NOT WITH VALUE: " << value << std::endl;

                unsigned short result = ~value;

                execIns->cashedOutput = result;
                execIns->isCashed = true;

                return result;
            }
            break;
            case InstructionCommand::OR:
            {
                unsigned short value1 = isDigit(execIns->input[0]) ? static_cast< unsigned short >(std::stoul(execIns->input[0], nullptr, 10)) : Instruction::execute(execIns->input[0]);
                unsigned short value2 = isDigit(execIns->input[1]) ? static_cast< unsigned short >(std::stoul(execIns->input[1], nullptr, 10)) : Instruction::execute(execIns->input[1]);

                std::cout << "OR WITH VALUES: " << value1 << " AND " << value2 << std::endl;

                unsigned short result = value1 | value2;

                execIns->cashedOutput = result;
                execIns->isCashed = true;

                return result;
            }
            break;
            case InstructionCommand::AND:
            {
                unsigned short value1 = isDigit(execIns->input[0]) ? static_cast< unsigned short >(std::stoul(execIns->input[0], nullptr, 10)) : Instruction::execute(execIns->input[0]);
                unsigned short value2 = isDigit(execIns->input[1]) ? static_cast< unsigned short >(std::stoul(execIns->input[1], nullptr, 10)) : Instruction::execute(execIns->input[1]);

                std::cout << "AND WITH VALUES: " << value1 << " AND " << value2 << std::endl;

                unsigned short result = value1 & value2;

                execIns->cashedOutput = result;
                execIns->isCashed = true;

                return result;            
            }
            break;
            case InstructionCommand::LSHIFT:
            {
                unsigned short value1 = isDigit(execIns->input[0]) ? static_cast< unsigned short >(std::stoul(execIns->input[0], nullptr, 10)) : Instruction::execute(execIns->input[0]);
                unsigned short value2 = isDigit(execIns->input[1]) ? static_cast< unsigned short >(std::stoul(execIns->input[1], nullptr, 10)) : Instruction::execute(execIns->input[1]);

                std::cout << "LSHIFT WITH VALUES: " << value1 << " AND " << value2 << std::endl;

                unsigned short result = value1 << value2;

                execIns->cashedOutput = result;
                execIns->isCashed = true;

                return result; 
            }
            break;
            case InstructionCommand::RSHIFT:
            {
                unsigned short value1 = isDigit(execIns->input[0]) ? static_cast< unsigned short >(std::stoul(execIns->input[0], nullptr, 10)) : Instruction::execute(execIns->input[0]);
                unsigned short value2 = isDigit(execIns->input[1]) ? static_cast< unsigned short >(std::stoul(execIns->input[1], nullptr, 10)) : Instruction::execute(execIns->input[1]);

                std::cout << "RSHIFT WITH VALUES: " << value1 << " AND " << value2 << std::endl;

                unsigned short result = value1 >> value2;

                execIns->cashedOutput = result;
                execIns->isCashed = true;

                return result; 
            }
            break;
            default:
            {
                return 0;
            }
        }
    }

    std::string input[2] = {"0", "0"};
    std::string output;
    InstructionCommand command;

    unsigned short cashedOutput = 0;
    bool isCashed = false;

    static std::map<std::string, Instruction> circuit;
};

std::map<std::string, Instruction> Instruction::circuit;

int main ()
{   
    for (std::string line; std::getline(std::cin, line);)
    {
        Instruction i(line);
    }

    unsigned short result = Instruction::execute("a");
    std::cout << "Result for output 'a' is [ " << result << "]" << std::endl;

    return 0;
}
