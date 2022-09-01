#include "common.hpp"
int delay_ms(u32 t)
{
    volatile u32 delay_cnt = 0, ans = 1;
    // magic number
    while (delay_cnt < t * 3000)
        delay_cnt++, ans |= ans * 1926 + 817;
    return ans;
}
void itostr(int value, char *buf, int base)
{
    if (value == 0)
        *buf++ = '0';
    else if (value < 0)
        *buf++ = '-', value = -value;
    u32 i = 0;
    while (value > 0)
    {
        buf[i++] = (value % base) + '0';
        value /= base;
    }
    buf[i] = '\0';
    for (u32 j = 0; j < i / 2; ++j)
    {
        char tmp = buf[j];
        buf[j] = buf[i - j - 1];
        buf[i - j - 1] = tmp;
    }
}
void strncat(char *dest, const char *src, int n)
{
    while (*dest)
        ++dest;
    while (*src && n-- > 0)
        *dest++ = *src++;
    *dest = '\0';
}
u32 strlen(const char *str)
{
    u32 ans = 0;
    while (*str++)
        ++ans;
    return ans;
}
int strcmp(const char *str1, const char *str2)
{
    while (*str1 && *str2)
        if (*str1++ != *str2++)
            return *(str1 - 1) - *(str2 - 1);
    return *str1 - *str2;
}
void write_reg(u32 reg, u32 value)
{
    *(volatile u32 *)(reg) = value;
}
u32 read_reg(u32 reg)
{
    return *reinterpret_cast<volatile u32 *>(reg);
}