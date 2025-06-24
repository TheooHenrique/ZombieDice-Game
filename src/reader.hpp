/**
 * @file reader.hpp
 * @brief Defines the Reader class for parsing .ini style configuration files.
 * @author Haniel Lucas Machado Rocha
 * @author Theo Henrique da Silva Borges
 * @date June 24th, 2025
 */

#ifndef READER_HPP
#define READER_HPP

#include <map>
#include <string>

/**
 * @class Reader
 * @brief Parses and provides access to data from a .ini style configuration file.
 * 
 * This class reads a file formatted with sections (e.g., [SectionName]) and
 * key-value pairs (e.g., key = value). It stores this data in a nested map
 * and provides a method to retrieve all key-value pairs for a specific section.
 */
class Reader {
public:
    /**
     * @brief Constructs a Reader object and parses the specified file.
     * @param filename The path to the configuration file to be read.
     */
    Reader(const std::string& filename);

    /**
     * @brief Retrieves a map of key-value pairs for a given section.
     * @param section The name of the section to retrieve.
     * @return A constant reference to a map containing the key-value pairs of the section.
     */
    const std::map<std::string, std::string>& getSection(const std::string& section) const;

private:
    //Mapa que relaciona uma key à seu valor. EX: green_amount = 3, max_players = 4
    std::map<std::string, std::string> keys; 
    
    /**
     * @var data
     * @brief Main data storage for the parsed .ini file.
     *
     * It's a map where the key is the section name (e.g., "Game", "Dice")
     * and the value is another map containing the key-value pairs
     * within that section (e.g., {"brains_to_win", "13"}).
     */
    std::map<std::string, std::map<std::string, std::string>> data; 
};

#endif
