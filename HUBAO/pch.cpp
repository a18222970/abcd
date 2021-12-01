// pch.cpp: 与预编译标头对应的源文件

#include "pch.h"
ACCSCC cmd;

//创建一个互斥对象
//hMutex = CreateMutex(NULL, FALSE, NULL);
// 当使用预编译的头时，需要使用此源文件，编译才能成功。
//HANDLE hMutex;//互斥量