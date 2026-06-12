/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2025        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Basic definitions of FatFs */
#include "diskio.h"		/* Declarations FatFs MAI */
#include "bsp_spi.h"
#include "bsp_usart.h"

/* Example: Mapping of physical drive number for each drive */
#define DEV_FLASH	1	


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv) {
	case DEV_FLASH :
		if(sFLASH_ID == spi_flash_read_id()){
			stat &= ~STA_NOINIT;
		}else{
			stat = STA_NOINIT;
		}
		break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;
	uint16_t i = 500;

	switch (pdrv) {
	case DEV_FLASH :
		
		init_spi_flash();
		while(i--);
		spi_flash_wakeup();
		stat = disk_status(DEV_FLASH);
		break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
	case DEV_FLASH:
		sector += 1536;
	
		spi_flash_buffer_read(buff, sector << 12, count << 12);
		res = RES_OK;
		break;
	}

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
	case DEV_FLASH :
		// translate the arguments here
		sector += 1536;
		spi_flash_erise_sector(sector << 12);
		spi_flash_buffer_write((u8 *)buff, sector << 12, count << 12);
		res = RES_OK;
		break;
	}

	return res;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
	case DEV_FLASH:
		switch (cmd) {
			case GET_SECTOR_COUNT:
				*(DWORD * )buff = 2560;
				break;
			case GET_SECTOR_SIZE:
				*(WORD * )buff = 4096;
				break;
			case GET_BLOCK_SIZE:
				*(WORD * )buff = 1;
				break;
		}
		res = RES_OK;
		break;
		
	}

	return res;
}

