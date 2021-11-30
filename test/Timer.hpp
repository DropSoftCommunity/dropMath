#pragma once

#include <chrono>
#include <string>
#include <iostream>

class Timer{
	std::string name;
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	
	public:
		Timer(std::string&& name): name{name}{
			std::cout << "\n----------------------------------------\n" 
					  << "Test: " << name << " started...\n" 
					  << "----------------------------------------\n"; 
			start = std::chrono::high_resolution_clock::now();
		}

		~Timer(){
			auto end = std::chrono::high_resolution_clock::now();

			auto start_mic = std::chrono::time_point_cast<std::chrono::microseconds>(this->start).time_since_epoch();
			auto end_mic = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch();	
			
			auto duration_mic = (end_mic - start_mic).count();
			auto duration_ms = duration_mic * 0.001;
			
			std::cout
			<< "----------------------------------------\n"
			<< "Test: " << name << " ended!\n"
			<< "Duration: " << duration_ms  << "ms (" 
			<< duration_mic << "mic)\n"
			<< "----------------------------------------" << std::endl;
		}
};
