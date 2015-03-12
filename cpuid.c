#include "cpuid.h"

#ifdef __x86_64__
#	define PUSHF "pushfq"
#	define POPF  "popfq"
#else
#	define PUSHF "pushfl"
#	define POPF  "popfl"
#endif

static ulong has_eflag(ulong mask)
{
	ulong f0, f1;

	__asm__ (PUSHF "      \n\t"
		 PUSHF "      \n\t"
		 "pop  %0     \n\t"
		 "mov  %0, %1 \n\t"
		 "xor  %2, %1 \n\t"
		 "push %1     \n\t"
		 POPF "       \n\t"
		 PUSHF "      \n\t"
		 "pop  %1     \n\t"
		 POPF "       \n\t"
		 : "=&r"(f0), "=&r" (f1)
		 : "ri" (mask));

	return ((f0^f1) & mask) != 0;
}

static void cpuid(ulong *eax, ulong *ebx, ulong *ecx, ulong *edx)
{
	__asm__ ("movl %0, %%eax \n\t"
		 "movl %1, %%ebx \n\t"
		 "movl %2, %%ecx \n\t"
		 "movl %3, %%edx \n\t"
		 "cpuid          \n\t"
		 "movl %%eax, %0 \n\t"
		 "movl %%ebx, %1 \n\t"
		 "movl %%ecx, %2 \n\t"
		 "movl %%edx, %3 \n\t"
		 : "+m"(*eax), "+m"(*ebx), "+m"(*ecx), "+m"(*edx));
}

/*
static ulong get_max_eax(void)
{
	ulong eax = 0, ebx = 0, ecx = 0, edx = 0;
	cpuid(&eax, &ebx, &ecx, &edx);
	return eax;
}
*/

int has_cpuid(void)
{
	return has_eflag(0x200000);
}

void get_vendor_name(struct vendor_name *vendor)
{
	ulong eax = 0, ebx = 0, ecx = 0, edx = 0;

	cpuid(&eax, &ebx, &ecx, &edx);
	vendor->name[0]  = (ebx & 0x000000ff);
	vendor->name[1]  = (ebx & 0x0000ff00) >> 8;
	vendor->name[2]  = (ebx & 0x00ff0000) >> 16;
	vendor->name[3]  = (ebx & 0xff000000) >> 24;
	vendor->name[4]  = (edx & 0x000000ff);
	vendor->name[5]  = (edx & 0x0000ff00) >> 8;
	vendor->name[6]  = (edx & 0x00ff0000) >> 16;
	vendor->name[7]  = (edx & 0xff000000) >> 24;
	vendor->name[8]  = (ecx & 0x000000ff);
	vendor->name[9]  = (ecx & 0x0000ff00) >> 8;
	vendor->name[10] = (ecx & 0x00ff0000) >> 16;
	vendor->name[11] = (ecx & 0xff000000) >> 24;
	vendor->name[12] = 0;
}

void get_cpu_info(struct cpu_info *info)
{
	ulong eax = 1, ebx = 0, ecx = 0, edx = 0;

	cpuid(&eax, &ebx, &ecx, &edx);
	info->stepping_id = eax & 0x0f;
	info->model_id = eax & 0xf0;
	info->family_id = (eax & 0x0f00) >> 8;
	info->type_id = (eax & 0x3000) >> 12;
	info->extended_model_id = (eax & 0x0f0000) >> 16;
	info->extended_family_id = (eax & 0x0ff00000) >> 20;
	info->brand_id = ebx & 0xff;
	info->cache_line_size = (ebx & 0xff00) >> 5;
	info->max_lcpu_ids = (ebx & 0xff0000) >> 16;
	info->initial_apic_id = (ebx & 0xff000000) >> 24;
	info->feature_flags = ecx | ((ulonglong)edx << 32);
}
