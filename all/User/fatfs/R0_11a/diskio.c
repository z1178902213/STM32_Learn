/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */
#include "bsp_spi.h"

/* Definitions of physical drive number for each drive */
#define ATA		0	
#define SPI_FLASH 1


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv) {
	case ATA :
		break;

	case SPI_FLASH:
		if(sFLASH_ID == spi_flash_read_id()){
			stat &= ~STA_NOINIT;
		}else{
			stat = STA_NOINIT;
		}
		break;
		
	default:
		stat = STA_NOINIT;
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
	case ATA :
		break;

	case SPI_FLASH:
		init_spi_flash();
		while(i--);
		spi_flash_wakeup();
		stat = disk_status(SPI_FLASH);
		break;
		
	default:
		stat = STA_NOINIT;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv) {
		case ATA :
			break;

		case SPI_FLASH :
			sector += 1536;
			spi_flash_buffer_read(buff, sector<<12, count<<12);
			res = RES_OK;
			break;
			
		default:
			res = RES_PARERR;
	}
	

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
	case ATA :
		break;
	case SPI_FLASH:
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

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
	case ATA :
		break;
	case SPI_FLASH:
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
#endif
