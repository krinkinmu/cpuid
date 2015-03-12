#include <stdio.h>
#include "cpuid.h"

int main()
{
	struct vendor_name vendor;
	struct cpu_info info;

	if (!has_cpuid()) {
		printf("This CPU doesn't support CPUID instruction\n");
		return 0;
	}

	get_vendor_name(&vendor);
	printf("Vendor Name is %s\n", vendor.name);

	get_cpu_info(&info);
	printf("CPU INFO:\n");
	printf("\tstepping id: %x\n", info.stepping_id);
	printf("\tmodel: %x\n", info.model_id);
	printf("\tfamily: %x\n", info.family_id);
	printf("\ttype: %x\n", info.type_id);
	printf("\textended model id: %x\n", info.extended_model_id);
	printf("\textended family id: %x\n", info.extended_family_id);
	printf("\tbrand index: %x\n", info.brand_id);
	printf("\tcache line size: %x\n", info.cache_line_size);
	printf("\tmax number of addressable IDs for logical CPUs: %x\n",
						info.max_lcpu_ids);
	printf("\tinitial APIC ID: %x\n", info.initial_apic_id);
	printf("\tfeatures falgs: %llx\n", info.feature_flags);

	return 0;
}
