#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>

/**
 * print_percent - Prints a percent sign
 *
 * Return: Always returns 1
 */

int print_percent(void)
{
	write(1, "%", 1);
	return (1);
}

/**
 * print_string - Prints a string to the standard output
 * @args: va_list containing the string argument
 *
 * Return: Number of characters printed
 */

int print_string(va_list args)
{
	char *str = va_arg(args, char*);
	int count = 0;
	int i = 0;

	if (str == NULL)
	{
		str = "(null)";
	}

	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		count++;
		i++;
	}

	return (count);
}

/**
 * print_character - Prints a single character to the standard output
 * @args: va_list containing the character argument
 * 
 * Return: Always returns 1 (Number of characters printed)
 */

int print_character(va_list args)
{
	char c = va_arg(args, int);
	write(1, &c, 1);
	return (1);
}

/**
 * print_integer - prints an integer to standard output
 * @args: va_list containing the integer argument
 * 
 * Return: Number of characters printed (including minus sign if negative)
 */

int print_integer(va_list args)
{
	int num = va_arg(args, int);
	int count = 0;
	int is_negative = 0;
	int digits[12];
	int digit_count = 0;
	int temp_num;
	int i;

	if (num < 0)
	{
		is_negative = 1;
		if (num == -2147483648)
		{
			write(1, "-2147483648", 11);
			return (11);
		}
		else
		{
			num = -num;
		}
	}

	if (num == 0)
	{
		write(1, "0", 1);
		return (1);
	}

	temp_num = num;
	while (temp_num > 0)
	{
		digits[digit_count] = (temp_num % 10) + '0';
		temp_num = temp_num / 10;
		digit_count++;
	}

	if (is_negative) /*Or is_negative == 1*/
	{
		write(1, "-", 1);
		count++;
	}

	for (i = digit_count - 1; i >= 0; i--)
	{
		write(1, &digits[i], 1);
		count++;
	}

	return (count);
}

/**
 * handle_format_specifier - Handles format specifiers for _printf
 * @specifier: The format specifier character (c, s, %, etc.)
 * @args: va_list containing the arguments for the specifier
 * 
 * Return: Number of characters printed
 */

int handle_format_specifier(char specifier, va_list args)
{
	int count = 0;

	if (specifier == 'c')
	{
		count = print_character(args);
	}
	else if (specifier == 's')
	{
		count = print_string(args);
	}
	else if (specifier == '%')
	{
		count = print_percent();
	}
	else if (specifier == 'd')
	{
		count = print_integer(args);
	}
	else if (specifier == 'i')
	{
		count = print_integer(args);
	}
	else
	{
		write(1, "%", 1);
		write(1, &specifier, 1);
		count = 2;
	}

	return (count);
}

/**
 * _printf - Custom implementation of printf function
 * @format: Format string containing text and format specifiers
 * @...: Variable number of arguments corresponding to format specifiers
 * 
 * Return: Number of characters printed
 */

int _printf(const char *format, ...)
{
	int character_count = 0;
	int i = 0;
	int result;
	va_list args;

	if (format == NULL)
	{
		return (-1);
	}

	if (format[0] == '\0')
	{
		return (0);
	}
	
	va_start(args, format);

	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
			{
				break;
			}

			result = handle_format_specifier(format[i], args);
			character_count += result;
		}
		else
		{
			write(1, &format[i], 1);
			character_count++;
		}
		i++;
	}
	va_end(args);
	return (character_count);
}
