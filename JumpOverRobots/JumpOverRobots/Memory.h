#pragma once

void memTest()
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	std::string totalPhys = std::to_string(statex.ullTotalPhys / 1024);
	std::string availPhys = std::to_string(statex.ullAvailPhys / 1024);
	std::string totalVirt = std::to_string(statex.ullTotalVirtual / 1024);
	std::string availVirt = std::to_string(statex.ullAvailVirtual / 1024);
	std::string memUsage = "There is " + std::to_string(statex.dwMemoryLoad) + " percent of memory in use.\n";
	totalPhys = "There are " + totalPhys + " total KB of physical memory.\n";
	availPhys = "There are " + availPhys + " free  KB of physical memory.\n";
	totalVirt = "There are " + totalVirt + " total KB of virtual memory.\n";
	availVirt = "There are " + availVirt + " free  KB of virtual memory.\n";
	OutputDebugStringA(memUsage.c_str());
	OutputDebugStringA(totalPhys.c_str());
	OutputDebugStringA(availPhys.c_str());
	OutputDebugStringA(totalVirt.c_str());
	OutputDebugStringA(availVirt.c_str());
}
