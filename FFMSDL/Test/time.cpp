#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif  // _WIND32

// ����64λ����
#if defined(_WIN32) && !defined(CYGWIN)
typedef __int64 int64_t;
#else
typedef long long int64_t;
#endif  // _WIN32

// ��ȡϵͳ�ĵ�ǰʱ�䣬��λ΢��(us)
int64_t GetSysTimeMicros()
{
#ifdef _WIN32
// ��1601��1��1��0:0:0:000��1970��1��1��0:0:0:000��ʱ��(��λ100ns)
#define EPOCHFILETIME   (116444736000000000UL)
    FILETIME ft;
    LARGE_INTEGER li;
    int64_t tt = 0;
    GetSystemTimeAsFileTime(&ft);
    li.LowPart = ft.dwLowDateTime;
    li.HighPart = ft.dwHighDateTime;
    // ��1970��1��1��0:0:0:000�����ڵ�΢����(UTCʱ��)
    tt = (li.QuadPart - EPOCHFILETIME) /10;
    return tt;
#else
    timeval tv;
    gettimeofday(&tv, 0);
    return (int64_t)tv.tv_sec * 1000000 + (int64_t)tv.tv_usec;
#endif // _WIN32
    return 0;
}

void main(){
	int64_t tm1 = GetSysTimeMicros();
	printf("tm1 is %ld\n", tm1);
	Sleep(3000);
	int64_t tm2 = GetSysTimeMicros();
	printf("tm2 is %ld\n", tm2);
	printf("tm2 - tm1 = %ld\n", tm2 - tm1);
}