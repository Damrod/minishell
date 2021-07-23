#include <sys/types.h>
#include <asm/unistd.h>

off_t	ft_lseek(int fd, off_t offset, int whence)
{
	ssize_t			ret;

	asm volatile
		(
			"syscall"
			: "=a" (ret)
			: "0" (__NR_lseek), "D"(fd), "S"(offset), "d"(whence)
			: "rcx", "r11"
			);
	return (ret);
}
