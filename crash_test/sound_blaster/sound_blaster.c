#include <sound_blaster.h>
#include <stdint.h>
#include <stdbool.h>
#include <io/cursor.h>

bool detect_dsp() {

	outb(DSP_RESET_PORT, 0x1);
	io_wait();
	outb(DSP_RESET_PORT, 0x1);

	if (inb(DSP_READ_PORT) == 0xAA)
		return true;
	else
		return false;
}

void turn_on_speaker() {
	outb(DSP_WRITE_PORT, TURN_SPEAKER_ON);
}

void turn_off_speaker() {
	outb(DSP_WRITE_PORT, TURN_SPEAKER_OFF);
}

uint8_t set_volume(uint8_t left, uint8_t right) {

	uint8_t volume = (left << 8) + (right << 8);
	outb(DSP_MIXER_PORT, MASTER_VOLUME);
	outb(MASTER_VOLUME, volume);

	return volume;
}

void set_irq(uint8_t irq_number) {

	outb(DSP_MIXER_PORT, 0x80);
	outb(DSP_MIXER_DATA_PORT, irq_number);
}
