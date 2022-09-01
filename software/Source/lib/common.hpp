#ifndef COMMON_HPP
#define COMMON_HPP
typedef unsigned int u32;
typedef unsigned char u8;
int delay_ms(u32 t);
void itostr(int value, char *buf, int base);
void strncat(char *dest, const char *src, int n);
u32 strlen(const char *str);
int strcmp(const char *str1, const char *str2);
void write_reg(u32 reg, u32 value);
u32 read_reg(u32 reg);
#endif // COMMON_HPP