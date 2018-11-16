#pragma once

unsigned long long Qfree = 0;

bool storage()
{
	ULARGE_INTEGER freeBytes;
	GetDiskFreeSpaceEx(TEXT("c:\\"), &freeBytes, 0, 0);
	Qfree = freeBytes.QuadPart;
	std::cout << "Bytes available: " << Qfree << "\nMB available: " << Qfree / 1024 / 1024 << " MB" << std::endl;
	if (Qfree / 1024 / 1024 >= 300)
		return true;
	return false;
}