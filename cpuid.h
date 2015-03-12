#ifndef __CPUID_H__
#define __CPUID_H__

typedef unsigned long ulong;
typedef unsigned long long ulonglong;

struct vendor_name {
	char name[13];
};

struct cpu_info {
	unsigned stepping_id;
	unsigned model_id;
	unsigned family_id;
	unsigned type_id;
	unsigned extended_model_id;
	unsigned extended_family_id;
	unsigned brand_id;
	unsigned cache_line_size;
	unsigned max_lcpu_ids;
	unsigned initial_apic_id;
	ulonglong feature_flags;
};


int has_cpuid(void);
void get_vendor_name(struct vendor_name *vendor);
void get_cpu_info(struct cpu_info *info);

#endif /*__CPUID_H__*/
