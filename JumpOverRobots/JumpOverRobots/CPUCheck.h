#pragma once

void processPrint(int a)
{
	std::string process = "Processor Architecture: ";
	switch (a) {
	case 0: process += "Intel x86\n";
		break;
	case 5: process += "ARM\n";
		break;
	case 6: process += "Intel Itanium-based\n";
		break;
	case 9: process += "AMD x64\n";
		break;
	case 12: process += "ARM64\n";
		break;
	default: process += "Unknown\n";
		break;
	}
	OutputDebugStringA(process.c_str()); 
}

void ArchitectureInfo() {

	SYSTEM_INFO siSysInfo;

	::GetSystemInfo(&siSysInfo);
	processPrint(siSysInfo.wProcessorArchitecture);
}