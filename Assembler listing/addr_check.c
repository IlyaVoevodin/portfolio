#include "addr_check.h"
#define BIN8(x) BIN___(0##x)
#define BIN___(x)                                    \
	(                                                \
	((x / 01ul) % 010)*(2>>1) +                      \
	((x / 010ul) % 010)*(2<<0) +                     \
	((x / 0100ul) % 010)*(2<<1) +                    \
	((x / 01000ul) % 010)*(2<<2) +                   \
	((x / 010000ul) % 010)*(2<<3) +                  \
	((x / 0100000ul) % 010)*(2<<4) +                 \
	((x / 01000000ul) % 010)*(2<<5) +                \
	((x / 010000000ul) % 010)*(2<<6) +               \
	((x / 0100000000ul) % 010)*(2<<7)                \
	)

#define BIN16(x1,x2) \
    ((BIN___(x1)<<8)+BIN___(x2))

#define BIN32(x1,x2,x3,x4) \
    ((BIN___(x1)<<24)+(BIN___(x2)<<16)+(BIN___(x3)<<8)+BIN___(x4))

int address_checkout(unsigned __int32 virtual_address, page_table* page_node, segment_table* seg_node)
{
	segment_table* seg_tmp = seg_node;
	page_table* page_tmp = page_node;
	
	long seg_check = BIN32(011111111, 011100000, 000000000, 000000000);
	unsigned __int32 real_seg = (virtual_address & seg_check);
	real_seg = (real_seg >> 21);

	if ((0 > real_seg)||(real_seg >= 7))
	{
		printf("\n[Error]: Can't make real adress of [0x%.8X] because segment '%d' dosen't exist!", virtual_address, real_seg);
		return virtual_address;
	}
	else
	{
		while (seg_tmp->next_seg)
		{
			if (seg_tmp->segment_number == real_seg)
				break;
			seg_tmp = seg_tmp->next_seg;
		}
	}

	page_tmp = parse_pages_table(seg_tmp->pages_table_path, seg_tmp);
	if (page_tmp == NULL)
	{
		printf("\n[Error]: Can't make real adress of [0x%.8X] because page dosen't exist at this segment!", virtual_address);
		return virtual_address;
	}

	long page_check = BIN32(000000000, 000011111, 011111000, 000000000);
	unsigned __int32 real_page = (virtual_address & page_check);
	real_page = (real_page >> 11);
	if (real_page >= 16)
	{
		printf("\n[Error]: Can't make real adress of [0x%.8X] because page '%d' dosen't exist!", virtual_address, real_page);
		return virtual_address;
	}
	else
	{
		while (page_tmp->next_page)
		{
			if (page_tmp->page_number == real_page)
				break;
			page_tmp = page_tmp->next_page;
		}
	}
	
	if (page_tmp->bit == 0)
	{
		printf("\n[Error]: Can't make real adress of [0x%.8X] because page '%d' empty!", virtual_address, real_page);
		return virtual_address;
	}
	
	long page_shift = BIN32(000000000, 000000000, 000000111, 011111111);
	unsigned __int32 real_address = (virtual_address & page_shift);
	real_address += page_tmp->frame;
	return real_address;
}
