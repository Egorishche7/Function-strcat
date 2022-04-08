#include <iostream>

using namespace std;

char* myStrcat(char* strDestination, const char* strSource);

int main()
{
	setlocale(LC_ALL, "russian");

	char line1[100];
	strcpy_s(line1, "Пример сложения");
	const char* line2 = " строк.";

	cout << myStrcat(line1, line2);

	return 0;
}

char* myStrcat(char* strDestination, const char* strSource)
{
	__asm
	{
		//----------Определяем длину строки strSource----------
		mov ebx, strSource
		lea edi, [ebx]
		cld
		xor al, al
		mov ecx, 0ffffh
		repne scasb
		sub ecx, 0ffffh
		neg ecx
		dec ecx
		mov edx, ecx //помещаем длину строки strSource в edx

		//----------Ищем конец строки strDestination----------
		mov ebx, strDestination
		lea edi, [ebx]
		cld
		xor al, al
		mov ecx, 0ffffh
		repne scasb //edi указывает на следующий символ

		//----------Производим конкатенацию----------
		mov ebx, strSource
		lea esi, [ebx]
		mov ecx, edx
	cycle:
		mov al, [esi]
		mov [edi-1], al
		inc esi
		inc edi
		loop cycle
		xor al, al
		mov [edi-1], al
	}

	return strDestination;
}