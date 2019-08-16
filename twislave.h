#ifndef TWISLAVE_H_
#define TWISLAVE_H_


uint8_t twi_status(uint8_t status);
void twi_mode_addressed(uint8_t addr);
void twi_mode_naddressed();
uint8_t twi_read_ack();
uint8_t twi_read_nack();
void twi_receive(uint8_t addr, uint8_t response[], uint8_t size);


#endif /* TWISLAVE_H_ */