#pragma once
/*
	some net layer mock
*/
#include <iostream>
#include <vector>
#include <chrono>

auto startTime = std::chrono::high_resolution_clock::now();
int milliseconds() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count();
}

int sockscounter = 100;

int socket() {
	std::cout << "created socket " << sockscounter << std::endl;
	return sockscounter++;
}

void connect(int sock, const char* address) {
	std::cout << "connect " << sock << " socket to " << address << std::endl;
}

bool checkSocketConnected(int sock) {
	bool result = milliseconds() > sock * 10;
	if(result)
		std::cout << "socket " << sock << " connected" << std::endl;
	return result;
}

int send(int sock, const char* buffer, size_t size) {
	bool connected = checkSocketConnected(sock);
	std::cout << "socket " << sock << " send " << size << " bytes " << buffer;
	if(!connected)
		std::cout << " failed (not connected yet)";
	std::cout << std::endl;
	std::cout << "these symbols:" << std::endl;
	for(size_t i = 0; i < size; ++i) {
		if(i > 0 && i % 16 == 0)
			std::cout << std::endl;
		std::cout << (buffer[i] > 31 && buffer[i] < 127 ? buffer[i] : '.');
	}
	std::cout << std::endl;
	return connected ? size : -1;
}

int recv(int sock, char* buffer, int size) {
	std::cout << "socket " << sock << " recv";
	if(!checkSocketConnected(sock)) {
		std::cout << " falied (not connected yet)";
		return -1;
	}
	std::cout << " got " << size << " bytes" << std::endl;
	for(size_t i = 0; i < size - 1; ++i)
		buffer[i] = "hello :-) "[i % 10];
	buffer[size - 1] = 0;
	return size;
}


void close(int sock) {
	std::cout << "closed socket " << sock << std::endl;
}