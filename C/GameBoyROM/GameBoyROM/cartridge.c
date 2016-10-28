#include <stdlib.h>
#include <string.h>
#include "cartridge.h"
#include "file.h"

//Address to read from
#define CARTRIDGE_HEADER_ADDRESS 0x134
#define MAX_ITEMS 8
#define LOW_NIBBLE_MASK 0x0F
#define NIBBLE_LENGTH 4

//Loads a ROM into memory and returns a byte pointer to the data (NULL if the FILE isn't valid)
unsigned char* loadROM(FILE* file) {
  if (file) {
    //Allocate enough memory for the file
    unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char) * fileSize(file));
    //Read data into buffer
    fread(buffer, fileSize(file), sizeof(unsigned char), file);
    //Don't forget to free this memory outside!
    return buffer;
  }
  return NULL;
}

//Parses a gameboy ROM file (pointer to the data) and returns a pointer to the struct with infromation filled in
gameBoyROM* parseROM(unsigned char* rom) {

  //DO NOT FORGET TO FREE THE MEMORY
  if (rom) {

    //Great, I have to change the malloc inside the disassembler
    gameBoyROM* romHeader = (gameBoyROM*)calloc(1,sizeof(gameBoyROM));
	/*
	
	romHeader -> title -> ...
			  -> licenceHigh
			  -> licenseLow
			  -> feature
			  -> cartridgeType
			  -> romSize
			  -> ramSize
			  -> destCode
			  -> licenseeCode
	*/

    //Read the title first
    rom += CARTRIDGE_HEADER_ADDRESS;

    for (int i=0; i < MAX_TITLE_LENGTH; i++) {
      romHeader->title[i] = rom[i];
    }
	rom += MAX_TITLE_LENGTH;

    //Licensee code (high & low)
    romHeader->licenceHigh = *++rom;
    romHeader->licenseLow = *++rom;

    //Feature
    romHeader->feature = *++rom;

    //Cartridge type
    romHeader->cartridgeType = *++rom;

    //ROM size
    romHeader->romSize = *++rom;

    //RAM size
    romHeader->ramSize = *++rom;

    //Destination code
    romHeader->destCode = *++rom;
    
    //Licensee code (old)
    romHeader->licenseeCode = *++rom;

   
    return romHeader;
  }
  return NULL;
}

//Returns an array of strings with the fields of the structure filled out with the correct information
char** displayROM(gameBoyROM* ROM) {
  
  //Array of strings containing the information
  char* romInformation[MAX_ITEMS];

  //Game title
  romInformation[0] = ROM->title;

  //Licensee code
  //Combine the low nibbles of the licensee bytes

  //Confusing names I know but lowHigh here means the low nibble of the high byte 
  unsigned char lowHigh = ROM->licenceHigh & LOW_NIBBLE_MASK;
  unsigned char lowLow = ROM->licenseLow & LOW_NIBBLE_MASK;

  //I don't know what the order is! Is it high first then low ?
  //We'll go with that

  //Combine the nibbles
  //Reference to magic numbers 
  //http://www.zophar.net/fileuploads/2/10597teazh/gbrom.txt
  //I've mixed these cases up by accident whilst reading the file
  switch ((lowHigh << NIBBLE_LENGTH) | lowLow) {
  case 0x00:
    romInformation[1] = "None"; break;
  case 0x13:
    romInformation[1] = "Electronic Arts"; break;
  case 0x20:
    romInformation[1] = "KSS"; break;
  case 0x25:
    romInformation[1] = "San-X"; break;
  case 0x30:
    romInformation[1] = "Viacom"; break;
  case 0x33:
    romInformation[1] = "Ocean/Acclaim"; break;
  case 0x37:
    romInformation[1] = "Taito"; break;
  case 0x41:
    romInformation[1] = "Ubisoft"; break;
  case 0x46:
    romInformation[1] = "Angel"; break;
  case 0x50:
    romInformation[1] = "Absolute"; break;
  case 0x53:
    romInformation[1] = "American Sammy"; break;
  case 0x56:
    romInformation[1] = "LJN"; break;
  case 0x59:
    romInformation[1] = "Milton Bradley"; break;
  case 0x64:
    romInformation[1] = "Lucasarts"; break;
  case 0x70:
    romInformation[1] = "Infogrames"; break;
  case 0x73:
    romInformation[1] = "Sculptured"; break;
  case 0x79:
    romInformation[1] = "Accolade"; break;
  case 0x86:
    romInformation[1] = "Tokuma Shoten"; break;
  case 0x92:
    romInformation[1] = "Video System"; break;
  case 0x96:
    romInformation[1] = "Yonezawa/s'pal"; break;
  case 0x01:
    romInformation[1] = "Nintendo"; break;
  case 0x18:
    romInformation[1] = "Hudsonsoft"; break;
  case 0x22:
    romInformation[1] = "Pow"; break;
  case 0x28:
    romInformation[1] = "Kemco Japan"; break;
  case 0x31:
    romInformation[1] = "Nintendo"; break;
  case 0x34:
    romInformation[1] = "Konami"; break;
  case 0x38:
    romInformation[1] = "Hudson"; break;
  case 0x42:
    romInformation[1] = "Atlus"; break;
  case 0x47:
    romInformation[1] = "Pullet-Proof"; break;
  case 0x51:
    romInformation[1] = "Acclaim "; break;
  case 0x54:
    romInformation[1] = "Konami"; break;
  case 0x57:
    romInformation[1] = "Matchbox "; break;
  case 0x60:
    romInformation[1] = "Titus"; break;
  case 0x67:
    romInformation[1] = "Ocean"; break;
  case 0x71:
    romInformation[1] = "Interplay"; break;
  case 0x75:
    romInformation[1] = "SCI"; break;
  case 0x80:
    romInformation[1] = "Misawa"; break;
  case 0x87:
    romInformation[1] = "Tsukuda Ori"; break;
  case 0x93:
    romInformation[1] = "Ocean/Acclaim"; break;
  case 0x97:
    romInformation[1] = "Kaneko"; break;
  case 0x08:
    romInformation[1] = "Capcom"; break;
  case 0x19:
    romInformation[1] = "B-AI"; break;
  case 0x24:
    romInformation[1] = "PCM Complete"; break;
  case 0x29:
    romInformation[1] = "Seta"; break;
  case 0x32:
    romInformation[1] = "Bandia"; break;
  case 0x35:
    romInformation[1] = "Hector"; break;
  case 0x39:
    romInformation[1] = "Banpresto"; break;
  case 0x44:
    romInformation[1] = "Malibu"; break;
  case 0x49:
    romInformation[1] = "Irem"; break;
  case 0x52:
    romInformation[1] = "Activision"; break;
  case 0x55:
    romInformation[1] = "Hi Tech Entertainment"; break;
  case 0x58:
    romInformation[1] = "Mattel"; break;
  case 0x61:
    romInformation[1] = "Virgin"; break;
  case 0x69:
    romInformation[1] = "Electronic Arts"; break;
  case 0x72:
    romInformation[1] = "Broderbund"; break;
  case 0x78:
    romInformation[1] = "THQ"; break;
  case 0x83:
    romInformation[1] = "Lozc"; break;
  case 0x91:
    romInformation[1] = "Chunsoft"; break;
  case 0x95:
    romInformation[1] = "Varie"; break;
  case 0x99:
    romInformation[1] = "Pack-In-Video"; break;
  default:
    romInformation[1] = "Unknown"; break;
  }

  //Feature
  switch (ROM->feature) {
  case 0x00:
    romInformation[2] = "Gameboy functions";
    break;
  case 0x03:
    romInformation[2] = "Super GameBoy functions";
    break;
  default:
    romInformation[2] = "Unknown";
  }

  //Cartridge type
  switch (ROM->cartridgeType) {
  case 0x00:
    romInformation[3] = "ROM"; break;
  case 0x01:
    romInformation[3] = "MBC1"; break;
  case 0x02:
    romInformation[3] = "MBC1+RAM"; break;
  case 0x03:
    romInformation[3] = "MBC1+RAM+BATTERY"; break;
  case 0x05:
    romInformation[3] = "MBC2"; break;
  case 0x06:
    romInformation[3] = "MBC2+BATTERY"; break;
  case 0x08:
    romInformation[3] = "ROM+RAM "; break;
  case 0x09:
    romInformation[3] = "ROM+RAM+BATTERY"; break;
  case 0x0B:
    romInformation[3] = "MMM01"; break;
  case 0x0C:
    romInformation[3] = "MMM01+RAM"; break;
  case 0x0D:
    romInformation[3] = "MMM01+RAM+BATTERY"; break;
  case 0x0F:
    romInformation[3] = "MBC3+TIMER+BATTERY"; break;
  case 0x10:
    romInformation[3] = "MBC3+TIMER+RAM+BATTERY"; break;
  case 0x11:
    romInformation[3] = "MBC3"; break;
  case 0x12:
    romInformation[3] = "MBC3+RAM"; break;
  case 0x13:
    romInformation[3] = "MBC3+RAM+BATTERY"; break;
  case 0x15:
    romInformation[3] = "MBC4"; break;
  case 0x16:
    romInformation[3] = "MBC4+RAM"; break;
  case 0x17:
    romInformation[3] = "MBC4+RAM+BATTERY"; break;
  case 0x19:
    romInformation[3] = "MBC5"; break;
  case 0x1A:
    romInformation[3] = "MBC5+RAM"; break;
  case 0x1B:
    romInformation[3] = "MBC5+RAM+BATTERY"; break;
  case 0x1C:
    romInformation[3] = "MBC5+RUMBLE"; break;
  case 0x1D:
    romInformation[3] = "MBC5+RUMBLE+RAM"; break;
  case 0x1E:
    romInformation[3] = "MBC5+RUMBLE+RAM+BATTERY"; break;
  case 0xFC:
    romInformation[3] = "POCKET CAMERA"; break;
  case 0xFD:
    romInformation[3] = "Bandai TAMA5"; break;
  case 0xFE:
    romInformation[3] = "HuC3"; break;
  case 0xFF:
    romInformation[3] = "HuC1+RAM+BATTERY"; break;
  default:
    romInformation[3] = "Unknown"; break;
  }

  //ROM size
  switch (ROM->romSize) {
  case 0x00:
    romInformation[4] = "32KB"; break;
  case 0x01:
    romInformation[4] = "64KB"; break;
  case 0x02:
    romInformation[4] = "128KB"; break;
  case 0x03:
    romInformation[4] = "256KB"; break;
  case 0x04:
    romInformation[4] = "512KB"; break;
  case 0x05:
    romInformation[4] = "1MB"; break;
  case 0x06:
    romInformation[4] = "2MB"; break;
  case 0x52:
    romInformation[4] = "1.1MB"; break;
  case 0x53:
    romInformation[4] = "1.2MB"; break;
  case 0x54:
    romInformation[4] = "1.5MB"; break;
  default:
    romInformation[4] = "Unknown"; break;
  }

  //RAM size
  switch (ROM->ramSize) {
  case 0x00:
    romInformation[5] = "None"; break;
  case 0x01:
    romInformation[5] = "2kB"; break;
  case 0x02:
    romInformation[5] = "8kB"; break;
  case 0x03:
    romInformation[5] = "32kB"; break;
  case 0x04:
    romInformation[5] = "128kB"; break;
  default:
    romInformation[5] = "Unknown"; break;
  }

  //Destination code
  switch (ROM->destCode) {
  case 0x00:
    romInformation[6] = "Japanese"; break;
  case 0x01:
    romInformation[6] = "Non-Japanese"; break;
  default:
    romInformation[6] = "Unknown"; break;
  }

  //Licensee code (old)
  switch (ROM->licenseeCode)
  {
  case 0x00:
    romInformation[7] = "None"; break;
  case 0x01:
    romInformation[7] = "Nintendo"; break;
  case 0x08:
    romInformation[7] = "Capcom"; break;
  case 0x09:
    romInformation[7] = "Hot-B"; break;
  case 0x0A:
    romInformation[7] = "Jaleco "; break;
  case 0x0B:
    romInformation[7] = "Coconuts"; break;
  case 0x0C:
    romInformation[7] = "Elite Systems"; break;
  case 0x13:
    romInformation[7] = "Electronic Arts"; break;
  case 0x18:
    romInformation[7] = "Hudsonsoft"; break;
  case 0x19:
    romInformation[7] = "ITC Entertainment"; break;
  case 0x1A:
    romInformation[7] = "Yanoman"; break;
  case 0x1D:
    romInformation[7] = "Clary"; break;
  case 0x1F:
    romInformation[7] = "Virgin"; break;
  case 0x24:
    romInformation[7] = "PCM Complete"; break;
  case 0x25:
    romInformation[7] = "San-X"; break;
  case 0x28:
    romInformation[7] = "Kotobuki Systems"; break;
  case 0x29:
    romInformation[7] = "Seta"; break;
  case 0x30:
    romInformation[7] = "Infogrames"; break;
  case 0x31:
    romInformation[7] = "Nintendo"; break;
  case 0x32:
    romInformation[7] = "Bandai"; break;
  case 0x33:
    romInformation[7] = "Unknown"; break;
  case 0x34:
    romInformation[7] = "Konami "; break;
  case 0x35:
    romInformation[7] = "Hector"; break;
  case 0x38:
    romInformation[7] = "Capcom"; break;
  case 0x39:
    romInformation[7] = "Banpresto"; break;
  case 0x3C:
    romInformation[7] = "Entertainment i"; break;
  case 0x3E:
    romInformation[7] = "Gremlin"; break;
  case 0x41:
    romInformation[7] = "Ubisoft "; break;
  case 0x42:
    romInformation[7] = "Atlus"; break;
  case 0x44:
    romInformation[7] = "Malibu"; break;
  case 0x46:
    romInformation[7] = "Angel"; break;
  case 0x47:
    romInformation[7] = "Spectrum Holoby"; break;
  case 0x49:
    romInformation[7] = "Irem"; break;
  case 0x4A:
    romInformation[7] = "Virgin"; break;
  case 0x4D:
    romInformation[7] = "Malibu"; break;
  case 0x4F:
    romInformation[7] = "U.S. Gold"; break;
  case 0x50:
    romInformation[7] = "Absolute"; break;
  case 0x51:
    romInformation[7] = "Acclaim"; break;
  case 0x52:
    romInformation[7] = "Activision"; break;
  case 0x53:
    romInformation[7] = "American Sammy"; break;
  case 0x54:
    romInformation[7] = "Gametek"; break;
  case 0x55:
    romInformation[7] = "Park Place"; break;
  case 0x56:
    romInformation[7] = "LJN"; break;
  case 0x57:
    romInformation[7] = "Natchbox"; break;
  case 0x59:
    romInformation[7] = "Milton Bradley"; break;
  case 0x5A:
    romInformation[7] = "Mindscape"; break;
  case 0x5B:
    romInformation[7] = "Romstar"; break;
  case 0x5C:
    romInformation[7] = "Naxat Soft"; break;
  case 0x5D:
    romInformation[7] = "Tradewest"; break;
  case 0x60:
    romInformation[7] = "Titus"; break;
  case 0x61:
    romInformation[7] = "Virgin"; break;
  case 0x67:
    romInformation[7] = "Ocean"; break;
  case 0x69:
    romInformation[7] = "Electronic Arts"; break;
  case 0x6E:
    romInformation[7] = "Elite Systems"; break;
  case 0x6F:
    romInformation[7] = "Electro Brain"; break;
  case 0x70:
    romInformation[7] = "Infogrames"; break;
  case 0x71:
    romInformation[7] = "Interplay"; break;
  case 0x72:
    romInformation[7] = "Broderbund"; break;
  case 0x73:
    romInformation[7] = "Sculptered Soft"; break;
  case 0x75:
    romInformation[7] = "The Sales Curve"; break;
  case 0x78:
    romInformation[7] = "THQ"; break;
  case 0x79:
    romInformation[7] = "Accolade"; break;
  case 0x7A:
    romInformation[7] = "Triffix Entertainment"; break;
  case 0x7C:
    romInformation[7] = "Microprose"; break;
  case 0x7F:
    romInformation[7] = "Kemco"; break;
  case 0x80:
    romInformation[7] = "Misawa Entertainment"; break;
  case 0x83:
    romInformation[7] = "Lozc"; break;
  case 0x86:
    romInformation[7] = "Tokuma Shoten"; break;
  case 0x8B:
    romInformation[7] = "Bullet-proof Software"; break;
  case 0x8C:
    romInformation[7] = "Vic Tokai"; break;
  case 0x8E:
    romInformation[7] = "Ape"; break;
  case 0x8F:
    romInformation[7] = "I'max"; break;
  case 0x91:
    romInformation[7] = "Chunsoft"; break;
  case 0x92:
    romInformation[7] = "Video System"; break;
  case 0x93:
    romInformation[7] = "Tsuburava"; break;
  case 0x95:
    romInformation[7] = "Varie"; break;
  case 0x96:
    romInformation[7] = "Yonezawa/s'pal"; break;
  case 0x97:
    romInformation[7] = "Kaneko"; break;
  case 0x99:
    romInformation[7] = "Arc"; break;
  case 0x9A:
    romInformation[7] = "Nihon Bussan"; break;
  case 0x9B:
    romInformation[7] = "Tecmo"; break;
  case 0x9C:
    romInformation[7] = "Imagineer"; break;
  case 0x9D:
    romInformation[7] = "Banpresto"; break;
  case 0x9F:
    romInformation[7] = "Nova"; break;
  case 0xA1:
    romInformation[7] = "Hori Electric"; break;
  case 0xA2:
    romInformation[7] = "Bandai"; break;
  case 0xA4:
    romInformation[7] = "Konami"; break;
  case 0xA6:
    romInformation[7] = "Kawada"; break;
  case 0xA7:
    romInformation[7] = "Takara"; break;
  case 0xA9:
    romInformation[7] = "Technos Japan"; break;
  case 0xAA:
    romInformation[7] = "Broderbund "; break;
  case 0xAC:
    romInformation[7] = "Toei Animation"; break;
  case 0xAD:
    romInformation[7] = "Toho"; break;
  case 0xAF:
    romInformation[7] = "Namco"; break;
  case 0xB0:
    romInformation[7] = "Acclaim"; break;
  case 0xB1:
    romInformation[7] = "Ascii/Nexoft"; break;
  case 0xB2:
    romInformation[7] = "Bandai"; break;
  case 0xB4:
    romInformation[7] = "Enix"; break;
  case 0xB6:
    romInformation[7] = "HAL"; break;
  case 0xB7:
    romInformation[7] = "SNK"; break;
  case 0xB9:
    romInformation[7] = "Pony Canyon"; break;
  case 0xBA:
    romInformation[7] = "Culture Brain"; break;
  case 0xBB:
    romInformation[7] = "Sunsoft"; break;
  case 0xBD:
    romInformation[7] = "Sony Imagesoft"; break;
  case 0xBF:
    romInformation[7] = "Sammy"; break;
  case 0xC0:
    romInformation[7] = "Taito"; break;
  case 0xC2:
    romInformation[7] = "Kemco"; break;
  case 0xC3:
    romInformation[7] = "Squaresoft"; break;
  case 0xC4:
    romInformation[7] = "Tokuma Shoten"; break;
  case 0xC5:
    romInformation[7] = "Data East"; break;
  case 0xC6:
    romInformation[7] = "Tonkin House"; break;
  case 0xC8:
    romInformation[7] = "Koei"; break;
  case 0xC9:
    romInformation[7] = "UFL"; break;
  case 0xCA:
    romInformation[7] = "Ultra"; break;
  case 0xCB:
    romInformation[7] = "VAP"; break;
  case 0xCC:
    romInformation[7] = "USE"; break;
  case 0xCD:
    romInformation[7] = "Meldac"; break;
  case 0xCE:
    romInformation[7] = "Pony Canyon"; break;
  case 0xCF:
    romInformation[7] = "Angel"; break;
  case 0xD0:
    romInformation[7] = "Taito"; break;
  case 0xD1:
    romInformation[7] = "Sofel"; break;
  case 0xD2:
    romInformation[7] = "Quest"; break;
  case 0xD3:
    romInformation[7] = "Sigma Enterprises"; break;
  case 0xD4:
    romInformation[7] = "Ask Kodansha"; break;
  case 0xD6:
    romInformation[7] = "Naxat Soft"; break;
  case 0xD7:
    romInformation[7] = "Copya Systems"; break;
  case 0xD9:
    romInformation[7] = "Banpresto"; break;
  case 0xDA:
    romInformation[7] = "Tomy"; break;
  case 0xDB:
    romInformation[7] = "LJN"; break;
  case 0xDD:
    romInformation[7] = "NCS"; break;
  case 0xDE:
    romInformation[7] = "Human"; break;
  case 0xDF:
    romInformation[7] = "Altron"; break;
  case 0xE0:
    romInformation[7] = "Jaleco "; break;
  case 0xE1:
    romInformation[7] = "Towachiki"; break;
  case 0xE2:
    romInformation[7] = "Uutaka"; break;
  case 0xE3:
    romInformation[7] = "Varie"; break;
  case 0xE5:
    romInformation[7] = "Epoch"; break;
  case 0xE7:
    romInformation[7] = "Athena"; break;
  case 0xE8:
    romInformation[7] = "Asmik"; break;
  case 0xE9:
    romInformation[7] = "Natsume"; break;
  case 0xEA:
    romInformation[7] = "King Records"; break;
  case 0xEB:
    romInformation[7] = "Atlus"; break;
  case 0xEC:
    romInformation[7] = "Epic/Sony Records"; break;
  case 0xEE:
    romInformation[7] = "IGS"; break;
  case 0xF0:
    romInformation[7] = "A Wave"; break;
  case 0xF3:
    romInformation[7] = "Extreme Entertainment"; break;
  case 0xFF:
    romInformation[7] = "LJN"; break;
  default:
    romInformation[7] = "Unknown"; break;
  }
  return romInformation;
}

