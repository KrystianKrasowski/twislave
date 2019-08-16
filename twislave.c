#include <avr/io.h>
#include <util/twi.h>

uint8_t twi_status(uint8_t status)
{
	uint8_t current = TW_STATUS;
	return current == status;
}

void twi_mode_addressed(uint8_t addr)
{
	TWAR = addr;
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
}

void twi_mode_naddressed()
{
	TWCR = (1 << TWINT) | (TWEN);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t twi_read_ack()
{
	TWCR = (1 << TWINT) | (1 << TWEA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

uint8_t twi_read_nack()
{
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return TWDR;
}

void twi_receive(uint8_t addr, uint8_t response[], uint8_t size)
{
	twi_mode_addressed(addr);
	
	for (uint8_t i = 0; i < size; i++)
	{
		if (twi_status(TW_SR_SLA_ACK) || twi_status(TW_SR_DATA_ACK))
		{
			if (size - 1 == i)
			{
				response[i] = twi_read_nack();
			}
			else
			{
				response[i] = twi_read_ack();
			}
		}
		else
		{
			twi_mode_naddressed();
		}
	}
}