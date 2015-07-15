#ifndef _PDEF_H_
#define _PDEF_H_
#include <vector>
#include <string>

enum pdefQualifType
{
  PDEF_ENUM = 0,  
};

struct pdefEnumEntry
{
  std::string name;
  unsigned int value;
};

struct pdefQualificator
{
  std::string name;
  std::string prefix;
  pdefQualifType type;
  std::vector<pdefEnumEntry> enumEntries;

  typedef std::vector<pdefEnumEntry>::iterator IteratorEntries;
};

struct pdefStreamInfo
{
  int binOffset;
  int binBits;
  int texOffset;
  bool binInstantiator;
  bool texInstantiator;
  bool loader;
  bool saver;
};

struct pdefField
{
  std::string name;
  std::string desc;
  std::string units;
  std::string value;
  int bits;
  int qualificator;
  char groupNdx;
  char startInGroup;
  bool readOnly;
  bool isUnsigned;
  bool isPadding;
  bool isReal;
};

struct pdefPacket
{
  std::string name;
  int size;
  std::vector<pdefField> fields;
  std::string desc;
  int instField;
  bool generate;
  bool publicData;
  bool binCopy;

  typedef std::vector<pdefField>::iterator IteratorFields;
};

struct pdefImpl;
struct pdef
{
  std::vector<pdefQualificator> qualificators;
  std::vector<pdefPacket> packets;
  pdefStreamInfo streamInfo;
  std::string version;
  std::string desc;
  std::string basePacketName;
  std::string ns;
  size_t bitsgroup; // granularity to group bit fields (8 bits by default)
  pdefImpl* impl;
  size_t numBinCopies;

  typedef std::vector<pdefPacket>::iterator IteratorPackets;
  typedef std::vector<pdefQualificator>::iterator IteratorQualificators;
};

enum pdefLogLevel
{
  PDEF_ERROR=0,
  PDEF_WARNING=1,
  PDEF_INFO=2,
};
typedef void (*pdefLogCallback)(pdefLogLevel level, int code, const char* msg);

#endif