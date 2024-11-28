#include <stdio.h>
#include <nds.h>

ITCM_CODE
static inline uint32_t get_ticks(void) {
	return TIMER0_DATA | (TIMER1_DATA << 16);
}

ITCM_CODE
static void press_start_to_continue(void) {
    printf("\nPress button to continue");

    while (1) {
        swiWaitForVBlank();
        scanKeys();

        uint32_t keys_down = keysDown();
        if (keys_down)
            break;
    }

    consoleClear();
}

__attribute__((noinline))
ITCM_CODE
static void memset_bytes(void * s, uint8_t c, size_t n)
{
    uint8_t* p = (uint8_t*) s;
    while ( n-- )
        *p++ = c;
}

__attribute__((noinline))
ITCM_CODE
static void memset_bytes_reversed(void * s, uint8_t c, size_t n)
{
    uint8_t* p = ((uint8_t*) s) + n - 1;
    while ( n-- )
        *p-- = c;
}

__attribute__((aligned(1024)))
uint8_t buffer[65536];

ITCM_CODE
int main(void) {
	defaultExceptionHandler();
	consoleDemoInit();

	TIMER0_DATA = 0;
	TIMER1_DATA = 0;
	TIMER0_CR = TIMER_ENABLE | TIMER_DIV_1;
	TIMER1_CR = TIMER_ENABLE | TIMER_CASCADE;

	uint8_t *buffer_uncached = memUncached(buffer);
	int j = 0;

	printf("-- Cached memory, flush all --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset(buffer, j, i);
			DC_FlushAll();
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Cached memory, flush range --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset(buffer, j, i);
			DC_FlushRange(buffer, i);
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Uncached memory --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset(buffer_uncached, j, i);
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Cached, bytes, flush all --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset_bytes(buffer, j, i);
			DC_FlushAll();
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Cached, bytes, flush range --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset_bytes(buffer, j, i);
			DC_FlushRange(buffer, i);
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Uncached, bytes --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset_bytes(buffer_uncached, j, i);
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Cached, -byte, flush all --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset_bytes_reversed(buffer, j, i);
			DC_FlushAll();
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Cached, -byte, flush range --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset_bytes_reversed(buffer, j, i);
			DC_FlushRange(buffer, i);
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();

	printf("-- Uncached, -byte --\n\n");

	for (int k = 0; k < 2; k++) {
		int i = 16;

		while (i <= 4096) {
			j++;

			DC_FlushAll();
			uint32_t start_ticks = get_ticks();

			memset_bytes_reversed(buffer_uncached, j, i);
			uint32_t end_ticks = get_ticks();

			printf("%d b => %d t\n", i, end_ticks - start_ticks);

			i <<= 1;
		}
	}

	press_start_to_continue();
}
