#ifndef _CHIP8_MEMORY_DUMP_INCLUDED_H_
#define _CHIP8_MEMORY_DUMP_INCLUDED_H_

void mem_dump(void);
void mem_dump_partial(unsigned short from_addr, size_t len);

#endif // _CHIP8_MEMORY_DUMP_INCLUDED_H_
